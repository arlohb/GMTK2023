cmake_minimum_required(VERSION 3.25.3)

############################
#         COMPILER         #
############################

if (UNIX)
	set(CMAKE_BUILD_TYPE "Debug")
endif(UNIX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

############################
#       DEPENDENCIES       #
############################

# Import this cmake module
include(FetchContent)

# TODO make sure this only affects dependencies
add_compile_options(-Wno-everything)

# Fetch raylib
message("Fetching raylib")
set(CUSTOMIZE_BUILD ON CACHE BOOL "" FORCE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
set(SUPPORT_FILEFORMAT_WAV ON CACHE BOOL "" FORCE)
# This is REALLY not a good way to do this,
# but the jam deadline is in 2 hours lol
if (UNIX)
    include_directories(/nix/store/61r6ay93bxjx6d2ff2j3vwb00xpw0iyg-libpulseaudio-16.1/lib/libpulse.so)
    link_directories(/nix/store/61r6ay93bxjx6d2ff2j3vwb00xpw0iyg-libpulseaudio-16.1/lib/libpulse.so)
endif(UNIX)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib
    GIT_TAG 4.5.0
)
FetchContent_MakeAvailable(raylib)

# Fetch raylib-cpp
message("Fetching raylib-cpp")
FetchContent_Declare(
    raylib_cpp
    GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp
    GIT_TAG v4.5.1
)
FetchContent_MakeAvailable(raylib_cpp)

# Fetch fmt
message("Fetching fmt")
FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt
    GIT_TAG 10.0.0
)
FetchContent_MakeAvailable(fmt)

############################
#         PROJECT          #
############################

# Set project compiler options
add_compile_options(-Wall -Wextra -Wpedantic)

# Setup the project
project(GMTK2023)
file(GLOB SOURCES src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

# Link required libraries
target_link_libraries(${PROJECT_NAME} raylib raylib_cpp fmt)

# Copy assets to the build dir
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

# Symlink compile_commands to root dir
if (UNIX)
	file(CREATE_LINK
		"${CMAKE_BINARY_DIR}/compile_commands.json"
		"${CMAKE_SOURCE_DIR}/compile_commands.json"
		SYMBOLIC
	)
endif(UNIX)

