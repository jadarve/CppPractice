function(add_catchTest NAME SRCS)
    
    add_executable (${NAME} ${SRCS})
    target_link_libraries (${NAME} visitor Catch stdc++ ${ARGV2})
    add_test (NAME ${NAME}  COMMAND ${NAME})

endfunction()


include_directories (
    include
)

add_library(visitor
	src/ComputeGraph.cpp
	src/Visitor.cpp
)

target_link_libraries(visitor
	json
)

add_catchTest (test_JsonReader             test/test_JsonReader.cpp)
add_catchTest (test_JsonWriter             test/test_JsonWriter.cpp)
