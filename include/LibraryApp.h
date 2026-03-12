#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <variant>
#include "BookCatalog.h"
#include "Librarian.h"
#include "ReaderRegistry.h"

class LibraryApp {
public:
    struct Success {
        std::string message;
    };

    struct NotFound {
        std::string message;
    };

    struct ValidationError {
        std::string message;
    };

    struct AlreadyExists {
        std::string message;
    };

    using ActionResult = std::variant<Success, NotFound, ValidationError,
    AlreadyExists>;

private:
    std::shared_ptr<BookCatalog> catalog_;
    std::shared_ptr<ReaderRegistry> registry_;
    std::unique_ptr<Person> librarian_;
    std::unordered_map<std::string, std::string> activeLoans_;

    static constexpr int kExitCommand = 0;
    static constexpr int kAddBookCommand = 1;
    static constexpr int kAddReaderCommand = 2;
    static constexpr int kFindBookCommand = 3;
    static constexpr int kFindReaderCommand = 4;
    static constexpr int kListBooksCommand = 5;
    static constexpr int kListReadersCommand = 6;
    static constexpr int kIssueBookCommand = 7;
    static constexpr int kReturnBookCommand = 8;
    static constexpr int kRemoveBookCommand = 9;

    void showMenu() const;
    void handleResult(const ActionResult& result) const;

    ActionResult addBook(const std::string& id, const std::string& title, const std::string& author, int year);
    ActionResult addReader(const std::string& id, const std::string& name, const std::string& email);
    ActionResult issueBook(const std::string& bookId, const std::string& readerId);
    ActionResult returnBook(const std::string& bookId);

    void addBookUI();
    void addReaderUI();
    void findBookUI() const;
    void findReaderUI() const;
    void listBooksUI() const;
    void listReadersUI() const;
    void issueBookUI();
    void returnBookUI();
    void removeBookUI();

public:
    LibraryApp();
    LibraryApp(std::shared_ptr<BookCatalog> catalog, std::shared_ptr<ReaderRegistry> registry, std::unique_ptr<Person> librarian);
    void run();

};