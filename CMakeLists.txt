cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(SFML-Sockets)

find_package(SFML COMPONENTS system window graphics network REQUIRED)

add_executable(client src/client.cpp)
add_executable(server src/server.cpp)

set(SFML_LIBRARIES 
  sfml-graphics
  sfml-window
  sfml-system
  sfml-network
)

if (SFML_FOUND)
    target_link_libraries(client ${SFML_LIBRARIES})
    target_link_libraries(server ${SFML_LIBRARIES})
    if (WIN32)
        file(GLOB BINARY_DEP_DLLS "${SFML_DIR}/../../../bin/*.dll")
        file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})    
    endif()
endif()