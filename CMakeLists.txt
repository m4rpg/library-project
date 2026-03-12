cmake_minimum_required(VERSION 3.16)

project(library_project)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_library(library_core
        src/books/Book.cpp
        src/books/BookCatalog.cpp
        src/readers/Person.cpp
        src/readers/Librarian.cpp
        src/readers/Reader.cpp
        src/readers/ReaderRegistry.cpp
        src/ui/LibraryApp.cpp
)

add_executable(library_app
        src/ui/main.cpp
)

target_link_libraries(library_app PRIVATE library_core)

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(library_tests
        tests/test_books.cpp
        tests/test_readers.cpp
        tests/test_people.cpp
        tests/test_library_app.cpp
)

target_link_libraries(library_tests
        PRIVATE
        library_core
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(library_tests)