cmake_minimum_required(VERSION 3.16)
project(Compiler)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_PREFIX_PATH "/usr/local/llvm/lib/cmake/llvm" ${CMAKE_PREFIX_PATH})
# Find and configure LLVM
find_package(LLVM REQUIRED CONFIG)
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# Add your source files here
add_executable(Compiler src/CodeGen.cpp src/node.cpp src/main.cpp src/parser.cpp src/lex.yy.cc src/CodeGen.h src/node.h src/parser.hpp)

set(LLVM_LINK_COMPONENTS
    Core
    Support
    ExecutionEngine
    # engine
    Interpreter
    MC
    nativecodegen
    asmparser
    x86asmparser
    asmprinter
    aarch64asmparser
    mcjit
    # orcjit
    )
llvm_map_components_to_libnames(llvm_libs ${LLVM_LINK_COMPONENTS})
target_link_libraries(Compiler ${llvm_libs})

# Link against additional required libraries
if (APPLE)
    target_link_libraries(Compiler
        # Add any additional libraries specific to Apple here
    )
else()
    target_link_libraries(Compiler
        # Add any additional libraries specific to other platforms here
    )
endif()
