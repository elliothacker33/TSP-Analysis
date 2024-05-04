cmake_minimum_required(VERSION 3.27)
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
        src/model/Vertex.h)
