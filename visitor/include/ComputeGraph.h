#ifndef COMPUTE_GRAPH_H_
#define COMPUTE_GRAPH_H_

#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>


// forward declarations
class Visitor;


class Memory {

public:
    void accept(Visitor* visitor) {
        // nothing to do, no more objects in the hierarchy
    }

    // Getters and Setters

    void setPageSize(const uint32_t size) noexcept            { pageSize = size;}
    uint32_t getPageSize() const noexcept                     { return pageSize;}

    const std::vector<std::string>& getFlags() const noexcept { return flags;}
    void pushFlag(const std::string& flag)                    { flags.push_back(flag);}

private:
    uint32_t pageSize;
    std::vector<std::string> flags;

    // Vulkan stuff

}; // class Memory


class Buffer {

public:
    Buffer(const size& size, std::shared_ptr<Memory> memory) :
        size {size},
        memory {memory} {

    }


    void accept(Visitor* visitor) {
        // nothing to do, no more objects in the hierarchy
    }

    uint32_t getSize() const noexcept                  { return size;}
    std::shared_ptr<Memory> getMemory() const noexcept { return memory;}

private:
    uint32_t size;
    std::shared_ptr<Memory> memory;

    // Vulkan stuff

}; // class Buffer


class ComputeGraph {

public:

    void accept(Visitor* visitor) {

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


    void addMemory(const std::string& name, std::shared_ptr<Memory> memory)                      { memories[name] = memory;}
    // const std::unordered_map<std::string, std::shared_ptr<Memory>>& getMemories() const noexcept { return memories;}
    std::string getMemoryName(std::shared_ptr<Memory> memory) {

        for (const auto& v : memories) {
            if (v.second == memory) { return v.first; }
        }
        return std::string {}; // should throw exception
    }

    void addBuffer(const std::string& name, std::shared_ptr<Buffer> buffer)                      { buffers[name] = buffer;}
    // const std::unordered_map<std::string, std::shared_ptr<Buffer>>& getBuffers() const noexcept  { return buffers;}

    void setName(const std::string& name)          { this->name = name;}
    const std::string& getName() const noexcept    { return name;}

    void setVersion(const std::string& version)    { this->version = version;}
    const std::string& getVersion() const noexcept { return version;}

private:
    std::string name;
    std::string version;

    std::unordered_map<std::string, std::shared_ptr<Memory>> memories;
    std::unordered_map<std::string, std::shared_ptr<Buffer>> buffers;

    // Vulkan stuff
};

#endif // COMPUTE_GRAPH_H_