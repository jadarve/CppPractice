#include "ComputeGraph.h"

#include "Visitor.h"


///////////////////////////////////////////////////////////
// Memory
///////////////////////////////////////////////////////////

void Memory::accept(Visitor* visitor) {
    // nothing to do, no more objects in the hierarchy
}

// Getters and Setters

void Memory::setPageSize(const uint32_t size) noexcept            { pageSize = size;}
uint32_t Memory::getPageSize() const noexcept                     { return pageSize;}

const std::vector<std::string>& Memory::getFlags() const noexcept { return flags;}
void Memory::pushFlag(const std::string& flag)                    { flags.push_back(flag);}



///////////////////////////////////////////////////////////
// Buffer
///////////////////////////////////////////////////////////

Buffer::Buffer(const uint32_t size, std::shared_ptr<Memory> memory) :
    size {size},
    memory {memory} {

}


void Buffer::accept(Visitor* visitor) {
    // nothing to do, no more objects in the hierarchy
}

uint32_t Buffer::getSize() const noexcept                  { return size;}
std::shared_ptr<Memory> Buffer::getMemory() const noexcept { return memory;}


///////////////////////////////////////////////////////////
// ComputeGraph
///////////////////////////////////////////////////////////

void ComputeGraph::accept(Visitor* visitor) {

    visitor->visitComputeGraph(this);

    // visit memories
    for (const auto& v : memories) {
        visitor->visitMemory(v.first, v.second);
    }

    // visit buffers
    for (const auto& v : buffers) {
        visitor->visitBuffer(v.first, v.second);
    }
}


void ComputeGraph::addMemory(const std::string& name, std::shared_ptr<Memory> memory)                      { memories[name] = memory;}
std::string ComputeGraph::getMemoryName(std::shared_ptr<Memory> memory) {

    for (const auto& v : memories) {
        if (v.second == memory) { return v.first; }
    }
    return std::string {}; // should throw exception
}

void ComputeGraph::addBuffer(const std::string& name, std::shared_ptr<Buffer> buffer)                      { buffers[name] = buffer;}

void ComputeGraph::setName(const std::string& name)          { this->name = name;}
const std::string& ComputeGraph::getName() const noexcept    { return name;}

void ComputeGraph::setVersion(const std::string& version)    { this->version = version;}
const std::string& ComputeGraph::getVersion() const noexcept { return version;}
