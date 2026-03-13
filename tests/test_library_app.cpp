#include <gtest/gtest.h>
#include "LibraryApp.h"
#include "Librarian.h"
#include "LoanService.h"

TEST(LibraryAppTest, AddBookReturnsSuccess) {
    auto catalog = std::make_shared<BookCatalog>();
    auto registry = std::make_shared<ReaderRegistry>();
    auto librarian = std::make_unique<Librarian>("l1", "Alexander", "EMP001");
    auto loanService = std::make_shared<LoanService>(*catalog, *registry);

    LibraryApp app(catalog, registry, std::move(librarian), loanService);

    auto result = app.addBook(
        "b1",
        "Преступление и наказание",
        "Федор Достоевский",
        1866
    );

    EXPECT_TRUE(std::holds_alternative<LibraryApp::Success>(result));
}

TEST(LibraryAppTest, AddDuplicateBookReturnsAlreadyExists) {
    auto catalog = std::make_shared<BookCatalog>();
    auto registry = std::make_shared<ReaderRegistry>();
    auto librarian = std::make_unique<Librarian>("l1", "Alexander", "EMP001");
    auto loanService = std::make_shared<LoanService>(*catalog, *registry);

    LibraryApp app(catalog, registry, std::move(librarian), loanService);

    app.addBook("b1", "Анна Каренина", "Лев Толстой", 1877);
    auto result = app.addBook("b1", "Анна Каренина", "Лев Толстой", 1877);

    EXPECT_TRUE(std::holds_alternative<LibraryApp::AlreadyExists>(result));
}

TEST(LibraryAppTest, AddReaderReturnsSuccess) {
    auto catalog = std::make_shared<BookCatalog>();
    auto registry = std::make_shared<ReaderRegistry>();
    auto librarian = std::make_unique<Librarian>("l1", "Alexander", "EMP001");
    auto loanService = std::make_shared<LoanService>(*catalog, *registry);

    LibraryApp app(catalog, registry, std::move(librarian), loanService);

    auto result = app.addReader("r1", "Maria", "maria@mail.com");

    EXPECT_TRUE(std::holds_alternative<LibraryApp::Success>(result));
}

TEST(LibraryAppTest, AddDuplicateReaderReturnsAlreadyExists) {
    auto catalog = std::make_shared<BookCatalog>();
    auto registry = std::make_shared<ReaderRegistry>();
    auto librarian = std::make_unique<Librarian>("l1", "Alexander", "EMP001");
    auto loanService = std::make_shared<LoanService>(*catalog, *registry);

    LibraryApp app(catalog, registry, std::move(librarian), loanService);

    app.addReader("r1", "Maria", "maria@mail.com");
    auto result = app.addReader("r1", "Maria", "maria@mail.com");

    EXPECT_TRUE(std::holds_alternative<LibraryApp::AlreadyExists>(result));
}

TEST(LibraryAppTest, IssueBookFailsIfBookMissing) {
    auto catalog = std::make_shared<BookCatalog>();
    auto registry = std::make_shared<ReaderRegistry>();
    auto librarian = std::make_unique<Librarian>("l1", "Alexander", "EMP001");
    auto loanService = std::make_shared<LoanService>(*catalog, *registry);

    LibraryApp app(catalog, registry, std::move(librarian), loanService);
    app.addReader("r1", "Maria", "maria@mail.com");

    auto result = app.issueBook("missing", "r1");

    EXPECT_TRUE(std::holds_alternative<LibraryApp::NotFound>(result));
}

TEST(LibraryAppTest, IssueBookFailsIfReaderMissing) {
    auto catalog = std::make_shared<BookCatalog>();
    auto registry = std::make_shared<ReaderRegistry>();
    auto librarian = std::make_unique<Librarian>("l1", "Alexander", "EMP001");
    auto loanService = std::make_shared<LoanService>(*catalog, *registry);

    LibraryApp app(catalog, registry, std::move(librarian), loanService);
    app.addBook("b1", "Война и мир", "Лев Толстой", 1869);

    auto result = app.issueBook("b1", "missing");

    EXPECT_TRUE(std::holds_alternative<LibraryApp::NotFound>(result));
}

TEST(LibraryAppTest, IssueBookReturnsSuccessForValidData) {
    auto catalog = std::make_shared<BookCatalog>();
    auto registry = std::make_shared<ReaderRegistry>();
    auto librarian = std::make_unique<Librarian>("l1", "Alexander", "EMP001");
    auto loanService = std::make_shared<LoanService>(*catalog, *registry);

    LibraryApp app(catalog, registry, std::move(librarian), loanService);
    app.addBook("b1", "Мертвые души", "Николай Гоголь", 1842);
    app.addReader("r1", "George", "george@mail.com");

    auto result = app.issueBook("b1", "r1");

    EXPECT_TRUE(std::holds_alternative<LibraryApp::Success>(result));
}

TEST(LibraryAppTest, IssueBookFailsWhenBookAlreadyIssued) {
    auto catalog = std::make_shared<BookCatalog>();
    auto registry = std::make_shared<ReaderRegistry>();
    auto librarian = std::make_unique<Librarian>("l1", "Alexander", "EMP001");
    auto loanService = std::make_shared<LoanService>(*catalog, *registry);

    LibraryApp app(catalog, registry, std::move(librarian), loanService);
    app.addBook("b1", "Мастер и Маргарита", "Михаил Булгаков", 1967);
    app.addReader("r1", "Maria", "maria@mail.com");

    app.issueBook("b1", "r1");
    auto result = app.issueBook("b1", "r1");

    EXPECT_TRUE(std::holds_alternative<LibraryApp::AlreadyExists>(result));
}

TEST(LibraryAppTest, ReturnBookFailsIfBookWasNotIssued) {
    auto catalog = std::make_shared<BookCatalog>();
    auto registry = std::make_shared<ReaderRegistry>();
    auto librarian = std::make_unique<Librarian>("l1", "Alexander", "EMP001");
    auto loanService = std::make_shared<LoanService>(*catalog, *registry);

    LibraryApp app(catalog, registry, std::move(librarian), loanService);
    app.addBook("b1", "Анна Каренина", "Лев Толстой", 1877);

    auto result = app.returnBook("b1");

    EXPECT_TRUE(std::holds_alternative<LibraryApp::NotFound>(result));
}

TEST(LibraryAppTest, ReturnBookReturnsSuccessForIssuedBook) {
    auto catalog = std::make_shared<BookCatalog>();
    auto registry = std::make_shared<ReaderRegistry>();
    auto librarian = std::make_unique<Librarian>("l1", "Alexander", "EMP001");
    auto loanService = std::make_shared<LoanService>(*catalog, *registry);

    LibraryApp app(catalog, registry, std::move(librarian), loanService);
    app.addBook("b1", "Преступление и наказание", "Федор Достоевский", 1866);
    app.addReader("r1", "George", "george@mail.com");
    app.issueBook("b1", "r1");

    auto result = app.returnBook("b1");

    EXPECT_TRUE(std::holds_alternative<LibraryApp::Success>(result));
}