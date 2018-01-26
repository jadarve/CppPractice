#ifndef VISITOR_H_
#define VISITOR_H_

#include "ComputeGraph.h"

#include "json/json.hpp"

#include <iostream>
#include <fstream>

using json = nlohmann::json;


class Visitor {

public:
    virtual void visitComputeGraph(ComputeGraph* graph) = 0;
    virtual void visitMemory(const std::string& name, std::shared_ptr<Memory> memory) = 0;
    virtual void visitBuffer(const std::string& name, std::shared_ptr<Buffer> buffer) = 0;

}; // class Visitor


class JsonReader : public Visitor {

public:
    JsonReader(const std::string& filePath) {

        std::ifstream inputFile {"/home/jadarve/git/lluvia/local/moni.json"};
        inputFile >> jsonObject;
    }

    virtual void visitComputeGraph(ComputeGraph* graph) {

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

    virtual void visitMemory(const std::string& name, std::shared_ptr<Memory> memory) {

        std::cout << "JsonReader::visitMemory(): " << name << std::endl;

        // for each buffer json description
        for (const auto& b : jsonObject["buffers"]) {

            const auto bufferName = b["name"].get<std::string>();
            const auto memName = b["memory"].get<std::string>();

            if (memName == name) {

                const auto bSize = b["size"].get<uint32_t>();
                auto buffer = std::make_shared<Buffer>(bSize, memory);
                graph->addBuffer(bufferName, memory);
            }
        }
    }

    virtual void visitBuffer(const std::string& name, std::shared_ptr<Buffer> buffer) {

        std::cout << "JsonReader::Buffer(): " << name << std::endl;

        // nothing to do
    }


private:
    // visitor state
    json jsonObject;

    ComputeGraph* graph {nullptr};

}; // class JsonReader



class JsonWriter : public Visitor {

public:
    virtual void visitComputeGraph(ComputeGraph* graph) {

        std::cout << "JsonWriter::visitComputeGraph(): " << graph->getName() << std::endl;

        // saves state
        this->graph = graph;

        jsonObject["name"] = graph->getName();
        jsonObject["version"] = graph->getVersion();
    }

    virtual void visitMemory(const std::string& name, std::shared_ptr<Memory> memory) {

        auto memJson = json {};

        memJson["name"]      = name;
        memJson["page_size"] = memory->getPageSize();
        memJson["flags"]     = std::vector<std::string> (memory->getFlags()); // copy constructor

        jsonObject["memories"].push_back(memJson);
    }

    virtual void visitBuffer(const std::string& name, std::shared_ptr<Buffer> buffer) {
        
        auto bufferJson = json {};

        bufferJson["name"]   = name;
        bufferJson["memory"] = graph->getMemoryName(buffer->getMemory());
        bufferJson["size"]   = buffer->getSize();

        jsonObject["buffers"].push_back(bufferJson);
    }


private:
    // visitor state
    json jsonObject;
    ComputeGraph* graph {nullptr};

}; // class JsonReader

#endif // VISITOR_H_