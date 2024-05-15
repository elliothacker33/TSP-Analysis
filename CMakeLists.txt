cmake_minimum_required(VERSION 3.26.4)
project(TSP_Analysis)

set(CMAKE_CXX_STANDARD 17)

add_executable(TSP_Analysis main.cpp
        src/controller/Manager.cpp
        src/controller/Manager.h
        src/model/Graph.cpp
        src/model/Graph.h
        src/model/Edge.cpp
        src/model/Edge.h
        src/model/Vertex.cpp
        src/model/Vertex.h
        src/model/Coordinates.cpp
        src/model/Coordinates.h
        src/Exceptions/CustomError.cpp
        src/Exceptions/CustomError.h
        src/controller/Parser.cpp
        src/controller/Parser.h
        src/controller/HashTable.cpp
        src/controller/HashTable.h
        src/controller/Coder.cpp
        src/controller/Coder.h
        src/controller/Visualizer.cpp
        src/controller/Visualizer.h
        src/view/Menu.h
        src/view/Menu.cpp
        src/controller/Coder.cpp
)
