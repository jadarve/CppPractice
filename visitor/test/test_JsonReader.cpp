#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"

#include "ComputeGraph.h"
#include "Visitor.h"

#include <iostream>


TEST_CASE("ReadFile", "JsonReaderTest") {

	auto reader = JsonReader {"/Users/juan.adarve/git/CppPractice/visitor/data/graph.json"};

	auto graph = ComputeGraph {};
	graph.accept(&reader);


	std::cout << "Graph name    : " << graph.getName() << std::endl;
	std::cout << "Graph version : " << graph.getVersion() << std::endl;

}

