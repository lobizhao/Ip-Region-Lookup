cmake_minimum_required(VERSION 3.28)
project(Ip_Region_Lookup)

set(CMAKE_CXX_STANDARD 23)

add_executable(Ip_Region_Lookup main.cpp
        src/IpLocator.cpp
        src/JsonReader.cpp
        src/JsonReader.h
        src/IpLocator.h)
