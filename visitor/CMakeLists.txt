function(add_catchTest NAME SRCS)
    
    add_executable (${NAME} ${SRCS})
    target_link_libraries (${NAME} Catch stdc++ ${ARGV2})
    add_test (NAME ${NAME}  COMMAND ${NAME})

endfunction()

# add_library(visitor
#     src/
# )

include_directories (
    include
    src
)

add_catchTest (test_JsonReader             test/test_JsonReader.cpp)
