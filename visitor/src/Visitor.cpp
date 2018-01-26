#include "Visitor.h"
#include "ComputeGraph.h"




JsonReader::JsonReader(const std::string& filePath) {

    std::ifstream inputFile {filePath};
    inputFile >> jsonObject;
}

void JsonReader::visitComputeGraph(ComputeGraph* graph) {

    // save state
    this->graph = graph;

    std::cout << "JsonReader::visitComputeGraph()" << std::endl;

    const auto name = jsonObject["name"].get<std::string>();
    const auto version = jsonObject["version"].get<std::string>();

    graph->setName(name);
    graph->setVersion(version);


    // create memories
    for (const auto& m : jsonObject["memories"]) {

        const auto mName = m["name"].get<std::string>();

        auto memory = std::make_shared<Memory>();
        memory->setPageSize(m["page_size"].get<uint32_t>());

        // memory flags
        for (const auto& flag : m["flags"]) {
            memory->pushFlag(flag.get<std::string>());
        }

        graph->addMemory(mName, memory);
    }
}

void JsonReader::visitMemory(const std::string& name, std::shared_ptr<Memory> memory) {

    std::cout << "JsonReader::visitMemory(): " << name << std::endl;

    // for each buffer json description
    for (const auto& b : jsonObject["buffers"]) {

        const auto bufferName = b["name"].get<std::string>();
        const auto memName = b["memory"].get<std::string>();

        if (memName == name) {

            const auto bSize = b["size"].get<uint32_t>();
            auto buffer = std::make_shared<Buffer>(bSize, memory);
            graph->addBuffer(bufferName, buffer);
        }
    }
}

void JsonReader::visitBuffer(const std::string& name, std::shared_ptr<Buffer> buffer) {

    std::cout << "JsonReader::Buffer(): " << name << std::endl;

    // nothing to do
}



///////////////////////////////////////////////////////////
// JsonWriter
///////////////////////////////////////////////////////////

void JsonWriter::visitComputeGraph(ComputeGraph* graph) {

    std::cout << "JsonWriter::visitComputeGraph(): " << graph->getName() << std::endl;

    // saves state
    this->graph = graph;

    jsonObject["name"] = graph->getName();
    jsonObject["version"] = graph->getVersion();

    // placeholders for arrays
    jsonObject["memories"] = nullptr;
    jsonObject["buffers"] = nullptr;
}

void JsonWriter::visitMemory(const std::string& name, std::shared_ptr<Memory> memory) {

	std::cout << "JsonWriter::visitMemory(): " << name << std::endl;

    auto memJson = json {};

    memJson["name"]      = name;
    memJson["page_size"] = memory->getPageSize();
    memJson["flags"]     = std::vector<std::string> (memory->getFlags()); // copy constructor

    jsonObject["memories"].push_back(memJson);
}

void JsonWriter::visitBuffer(const std::string& name, std::shared_ptr<Buffer> buffer) {
    
    std::cout << "JsonWriter::visitBuffer(): " << name << std::endl;

    auto bufferJson = json {};

    bufferJson["name"]   = name;
    bufferJson["memory"] = graph->getMemoryName(buffer->getMemory());
    bufferJson["size"]   = buffer->getSize();

    jsonObject["buffers"].push_back(bufferJson);
}


void JsonWriter::write(const std::string& filePath) {

	std::ofstream writer {filePath};
	writer << std::setw(4) << jsonObject;
}