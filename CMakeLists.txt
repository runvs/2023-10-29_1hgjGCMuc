cmake_minimum_required(VERSION 3.26)
set(PROJECTNAME "1hgjGCMuc")
project(${PROJECTNAME})

## Helper Functions
#####################################################
include(config/cmake/helpers.cmake)
include(config/cmake/cache_variables.cmake)

set(SFML_STATIC_LIBRARIES TRUE)
set(BUILD_SHARED_LIBS OFF)

## Other variables and compiler setup I
#####################################################

if (JT_ENABLE_AUDIO_TESTS)
    add_definitions(-DJT_ENABLE_AUDIO_TESTS)
endif ()

if (JT_ENABLE_CLANG_TIDY)
    set(CMAKE_CXX_CLANG_TIDY "clang-tidy")
endif ()

if (JT_ENABLE_WEB)
    add_compile_definitions(MUSIC_OGG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_SDL=2")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='[\"bmp\",\"png\"]'")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_VORBIS=1 -s USE_OGG=1")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_SDL_TTF=2")

    add_link_options("SHELL:-s TOTAL_MEMORY=256MB"
            "SHELL:-s ALLOW_MEMORY_GROWTH=1"
            "SHELL:--use-preload-plugins"
            "SHELL:--preload-file assets")
elseif (MSVC)
elseif (NOT CMAKE_CXX_COMPILER_ID MATCHES "^(Apple)?Clang$")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lstdc++fs")
endif ()

## set include for mac homebrew
#####################################################
if (APPLE)
    mac_sdl_setup()
endif ()

set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD 17)

## get externals
#####################################################


add_subdirectory(ext)

if (USE_SFML)
    setup_sfml()
else ()
    setup_sdl()
endif ()

add_subdirectory(impl)

## copy .clang-format to build directory
#####################################################
configure_file(${CMAKE_SOURCE_DIR}/.clang-format ${CMAKE_BINARY_DIR}/ COPYONLY)
