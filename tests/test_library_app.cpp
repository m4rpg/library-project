#include <gtest/gtest.h>
#include "LibraryApp.h"
#include "Librarian.h"

TEST(LibraryAppTest, AddBookWorks) {
    auto catalog = std::make_shared<BookCatalog>();
    auto registry = std::make_shared<ReaderRegistry>();
    auto librarian = std::make_unique<Librarian>("l1", "Alexander", "EMP001");

    LibraryApp app(catalog, registry, std::move(librarian));

    auto result = app.addBook(
        "b1",
        "Преступление и наказание",
        "Федор Достоевский",
        1866
    );

    EXPECT_TRUE(std::holds_alternative<LibraryApp::Success>(result));
}

TEST(LibraryAppTest, AddReaderWorks) {
    auto catalog = std::make_shared<BookCatalog>();
    auto registry = std::make_shared<ReaderRegistry>();
    auto librarian = std::make_unique<Librarian>("l1", "Alexander", "EMP001");

    LibraryApp app(catalog, registry, std::move(librarian));

    auto result = app.addReader(
        "r1",
        "Maria",
        "maria@mail.com"
    );

    EXPECT_TRUE(std::holds_alternative<LibraryApp::Success>(result));
}

TEST(LibraryAppTest, IssueBookWorks) {
    auto catalog = std::make_shared<BookCatalog>();
    auto registry = std::make_shared<ReaderRegistry>();
    auto librarian = std::make_unique<Librarian>("l1", "Alexander", "EMP001");

    LibraryApp app(catalog, registry, std::move(librarian));

    app.addBook(
        "b1",
        "Анна Каренина",
        "Лев Толстой",
        1877
    );

    app.addReader(
        "r1",
        "George",
        "george@mail.com"
    );

    auto result = app.issueBook("b1", "r1");

    EXPECT_TRUE(std::holds_alternative<LibraryApp::Success>(result));
}