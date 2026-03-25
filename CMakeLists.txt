cmake_minimum_required(VERSION 3.11)
project(VideoGame VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

include_directories(include)
include_directories(gui)
include_directories(audio)
include_directories(graphics)
include_directories(external/raylib-tileson)
include_directories(external/tileson)
include_directories(level)
file(GLOB_RECURSE SOURCES "src/*.cpp" "gui/*.cpp" "audio/*.cpp" "graphics/*.cpp")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_MakeAvailable(raylib)
  endif()
endif()


add_executable(VideoGame ${SOURCES})

target_link_libraries(VideoGame raylib)