#ifndef VISITOR_H_
#define VISITOR_H_

#include "json/json.hpp"

#include <iostream>
#include <fstream>

using json = nlohmann::json;


// forward declarations
class Memory;
class Buffer;
class ComputeGraph;


class Visitor {

public:
    virtual void visitComputeGraph(ComputeGraph* graph) = 0;
    virtual void visitMemory(const std::string& name, std::shared_ptr<Memory> memory) = 0;
    virtual void visitBuffer(const std::string& name, std::shared_ptr<Buffer> buffer) = 0;

}; // class Visitor


class JsonReader : public Visitor {

public:
    JsonReader(const std::string& filePath);

    virtual void visitComputeGraph(ComputeGraph* graph);
    virtual void visitMemory(const std::string& name, std::shared_ptr<Memory> memory);
    virtual void visitBuffer(const std::string& name, std::shared_ptr<Buffer> buffer);


private:
    // visitor state
    json jsonObject;
    ComputeGraph* graph {nullptr};

}; // class JsonReader



class JsonWriter : public Visitor {

public:
    virtual void visitComputeGraph(ComputeGraph* graph);
    virtual void visitMemory(const std::string& name, std::shared_ptr<Memory> memory);
    virtual void visitBuffer(const std::string& name, std::shared_ptr<Buffer> buffer);


    void write(const std::string& filePath);

private:
    // visitor state
    json jsonObject;
    ComputeGraph* graph {nullptr};

}; // class JsonReader

#endif // VISITOR_H_