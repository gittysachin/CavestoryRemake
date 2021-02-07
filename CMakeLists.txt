cmake_minimum_required(VERSION 3.13)
project(cavestory)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra -Weffc++ -ansi")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(cavestory ${SDL2_INCLUDE_DIRS})
include_directories(cavestory ${SDL2_IMAGE_INCLUDE_DIRS}})
include_directories(src)

# Include dependencies installed via Conan
#if (EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
#    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
#    conan_basic_setup()
#else ()
#    message(WARNING "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
#endif ()

add_executable(cavestory
        src/Graphics.cpp
        src/Graphics.h
        src/main.cpp
        src/Game.cpp
        src/Game.h
        src/util/Flags.h
        src/sprite/AnimatedSprite.cpp
        src/sprite/AnimatedSprite.h
        src/Player.cpp
        src/Player.h
        src/util/Globals.h
        src/Level.cpp
        src/Level.h
        lib/nlohmann/json.hpp
        src/tile/Tileset.cpp
        src/tile/Tileset.h
        src/tile/Tile.cpp
        src/tile/Tile.h
        src/exceptions/InvalidLevelException.cpp
        src/exceptions/InvalidLevelException.h
        src/BoundingBox.cpp
        src/BoundingBox.h
        src/sprite/Sprite.cpp
        src/sprite/Sprite.h
        src/Slope.cpp
        src/Slope.h
        src/tile/AnimatedTile.cpp
        src/tile/AnimatedTile.h
        src/tile/TileAnimation.cpp
        src/tile/TileAnimation.h)

target_link_libraries(cavestory
        ${SDL2_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES})
