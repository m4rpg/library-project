cmake_minimum_required(VERSION 3.16)
project(library_project)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories(include)
add_library(library_core
        src/books/Book.cpp
        src/books/BookCatalog.cpp
        src/readers/Reader.cpp
        src/readers/ReaderRegistry.cpp
        src/loans/LoanService.cpp
        src/readers/Person.cpp
        src/readers/Librarian.cpp
)
add_executable(library_app
        src/ui/LibraryApp.cpp
        src/ui/main.cpp
)
target_link_libraries(library_app PRIVATE library_core)