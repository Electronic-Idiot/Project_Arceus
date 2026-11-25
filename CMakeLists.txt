cmake_minimum_required(VERSION 3.25)
project(vecstore VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(VECSTORE_ENABLE_SANITIZERS "Enable AddressSanitizer and UndefinedBehaviorSanitizer" OFF)
option(VECSTORE_BUILD_TESTS "Build unit tests" ON)

# Project-only strict warnings (never leaks into third-party FetchContent targets)
add_library(vecstore_warnings INTERFACE)
target_compile_options(vecstore_warnings INTERFACE
  -Wall
  -Wextra
  -Wpedantic
  -Wconversion
  -Wsign-conversion
  -Werror
)

# Sanitizer configuration (propagates to all binaries linking vecstore)
add_library(vecstore_sanitizers INTERFACE)
if(VECSTORE_ENABLE_SANITIZERS)
  target_compile_options(vecstore_sanitizers INTERFACE
    -g
    -O1
    -fno-omit-frame-pointer
    -fsanitize=address,undefined
  )
  target_link_options(vecstore_sanitizers INTERFACE
    -fsanitize=address,undefined
  )
endif()

# Core library target
add_library(vecstore STATIC
  src/version.cpp
)
target_include_directories(vecstore PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(vecstore
  PRIVATE vecstore_warnings
  PUBLIC vecstore_sanitizers
)

# Unit tests via GoogleTest v1.18.0
if(VECSTORE_BUILD_TESTS)
  enable_testing()
  include(FetchContent)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.18.0
    GIT_SHALLOW TRUE
  )
  set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)

  include(GoogleTest)

  add_executable(vecstore_tests
    tests/smoke_test.cpp
  )
  target_link_libraries(vecstore_tests PRIVATE
    vecstore
    vecstore_warnings
    GTest::gtest_main
  )
  gtest_discover_tests(vecstore_tests)
endif()
cmake_minimum_required(VERSION 3.25)
project(Project_Arceus VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(ARCEUS_ENABLE_SANITIZERS "Enable AddressSanitizer and UndefinedBehaviorSanitizer" OFF)
option(ARCEUS_BUILD_TESTS "Build unit tests" ON)

# Project-only strict warnings (never leaks into FetchContent dependencies)
add_library(arceus_warnings INTERFACE)
target_compile_options(arceus_warnings INTERFACE
  -Wall
  -Wextra
  -Wpedantic
  -Wconversion
  -Wsign-conversion
  -Werror
)

# Sanitizer configuration (propagates to all binaries linking arceus)
add_library(arceus_sanitizers INTERFACE)
if(ARCEUS_ENABLE_SANITIZERS)
  target_compile_options(arceus_sanitizers INTERFACE
    -g
    -O1
    -fno-omit-frame-pointer
    -fsanitize=address,undefined
  )
  target_link_options(arceus_sanitizers INTERFACE
    -fsanitize=address,undefined
  )
endif()

# Core library target
add_library(arceus STATIC
  src/version.cpp
)
target_include_directories(arceus PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(arceus
  PRIVATE arceus_warnings
  PUBLIC arceus_sanitizers
)

# Unit tests via GoogleTest v1.18.0
if(ARCEUS_BUILD_TESTS)
  enable_testing()
  include(FetchContent)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.18.0
    GIT_SHALLOW TRUE
  )
  set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)

  include(GoogleTest)

  add_executable(arceus_tests
    tests/smoke_test.cpp
  )
  target_link_libraries(arceus_tests PRIVATE
    arceus
    arceus_warnings
    GTest::gtest_main
  )
  gtest_discover_tests(arceus_tests)
endif()
