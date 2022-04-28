cmake_minimum_required(VERSION 3.20)
project(Fireworks)

set(CMAKE_CXX_STANDARD 14)

add_executable(Fireworks WIN32 main.cpp firework.cpp firework.hpp fireworkApp.cpp fireworkApp.hpp
        launcher.hpp launcher.cpp physics.cpp physics.hpp designer.hpp designer.cpp)

set(RESOURCE_FILES
        assets/fonts/anita_square.ttf
        assets/audio/sample_launch.wav
        assets/audio/sample_explosion.wav)

include_directories(Fireworks "C:/Program Files/SFML-2.5.1/include")

set(SFML_ROOT "C:/Program Files/SFML-2.5.1")
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Fireworks ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

# Copy dlls to build
if(WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
    file(GLOB MINGW_DEP_DLLS "C:/Program Files/mingw64/bin/*.dll")
    file(COPY ${MINGW_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()
