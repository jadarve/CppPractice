#ifndef COMPUTE_GRAPH_H_
#define COMPUTE_GRAPH_H_

#include "Visitor.h"

#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>


class Memory {

public:
    void accept(Visitor* visitor);

    // Getters and Setters

    void setPageSize(const uint32_t size) noexcept;
    uint32_t getPageSize() const noexcept;

    const std::vector<std::string>& getFlags() const noexcept;
    void pushFlag(const std::string& flag);

private:
    uint32_t pageSize;
    std::vector<std::string> flags;

    // Vulkan stuff

};


class Buffer {

public:
    Buffer(const uint32_t size, std::shared_ptr<Memory> memory);

    void accept(Visitor* visitor);

    uint32_t getSize() const noexcept;
    std::shared_ptr<Memory> getMemory() const noexcept;

private:
    uint32_t size;
    std::shared_ptr<Memory> memory;

    // Vulkan stuff

};


class ComputeGraph {

public:

    void accept(Visitor* visitor);


    void addMemory(const std::string& name, std::shared_ptr<Memory> memory);
    std::string getMemoryName(std::shared_ptr<Memory> memory);

    void addBuffer(const std::string& name, std::shared_ptr<Buffer> buffer);

    void setName(const std::string& name);
    const std::string& getName() const noexcept;

    void setVersion(const std::string& version);
    const std::string& getVersion() const noexcept;

private:
    std::string name;
    std::string version;

    std::unordered_map<std::string, std::shared_ptr<Memory>> memories;
    std::unordered_map<std::string, std::shared_ptr<Buffer>> buffers;

    // Vulkan stuff
};

#endif // COMPUTE_GRAPH_H_