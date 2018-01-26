#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"

#include "ComputeGraph.h"
#include "Visitor.h"

#include <memory>
#include <iostream>


TEST_CASE("WriteEmptyGraph", "JsonWriterTest") {

	// auto reader = JsonReader {"/Users/juan.adarve/git/CppPractice/visitor/data/graph.json"};

	auto graph = ComputeGraph {};
	graph.setName("This is my graph");
	graph.setVersion("1.2.3");

	// MEMORIES
	auto mem0 = std::make_shared<Memory>();
	mem0->setPageSize(4096u);
	mem0->pushFlag("DEVICE_LOCAL");
	graph.addMemory("device", mem0);

	auto mem1 = std::make_shared<Memory>();
	mem1->setPageSize(1024u);
	mem1->pushFlag("HOST_VISIBLE");
	mem1->pushFlag("HOST_COHERENT");
	graph.addMemory("host", mem1);


	// BUFFERS
	graph.addBuffer("buffer_0", std::make_shared<Buffer>(512, mem0));
	graph.addBuffer("buffer_1", std::make_shared<Buffer>(256, mem0));
	graph.addBuffer("buffer_2", std::make_shared<Buffer>(1024, mem1));

	auto writer = JsonWriter {};
	graph.accept(&writer);

	writer.write("out.json");

	std::cout << "end" << std::endl;
}

