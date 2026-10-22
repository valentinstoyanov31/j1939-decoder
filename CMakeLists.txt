cmake_minimum_required(VERSION 3.20)

project(
    J1939Decoder
    VERSION 1.0
    DESCRIPTION "A simple C++ project with interdependent subdirectories"  
    LANGUAGES CXX
)

# Set C++ standard (e.g., C++20)  
set(CMAKE_CXX_STANDARD 20)  
set(CMAKE_CXX_STANDARD_REQUIRED ON)  
set(CMAKE_CXX_EXTENSIONS OFF)  # Disable compiler-specific extensions

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

if (MSVC)
# warning level 4
    add_compile_options(/W4)
else()
# additional warnings
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

add_subdirectory(src)

enable_testing()
add_subdirectory(tests)

