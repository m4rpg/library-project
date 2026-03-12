#include "LibraryApp.h"

#include <iostream>
#include <limits>
#include <stdexcept>
#include <utility>
#include <variant>

LibraryApp::LibraryApp()
    : catalog_(std::make_shared<BookCatalog>()),
      registry_(std::make_shared<ReaderRegistry>()),
      librarian_(std::make_unique<Librarian>("lib1", "Main Librarian", "EMP001")) {}

LibraryApp::LibraryApp(std::shared_ptr<BookCatalog> catalog,
                       std::shared_ptr<ReaderRegistry> registry,
                       std::unique_ptr<Person> librarian)
    : catalog_(std::move(catalog)),
      registry_(std::move(registry)),
      librarian_(std::move(librarian)) {
    if (!catalog_ || !registry_ || !librarian_) {
        throw std::invalid_argument("LibraryApp dependencies cannot be null");
    }
}

void LibraryApp::showMenu() const {
    std::cout << "\n===== Library Menu =====\n";
    std::cout << "1. Add book\n";
    std::cout << "2. Add reader\n";
    std::cout << "3. Find book by id\n";
    std::cout << "4. Find reader by id\n";
    std::cout << "5. List all books\n";
    std::cout << "6. List all readers\n";
    std::cout << "7. Issue book\n";
    std::cout << "8. Return book\n";
    std::cout << "9. Remove book\n";
    std::cout << "0. Exit\n";
    std::cout << "Choose action: ";
}

void LibraryApp::handleResult(const ActionResult& result) const {
    std::visit([](const auto& value) {
        std::cout << value.message << '\n';
    }, result);
}

LibraryApp::ActionResult LibraryApp::addBook(const std::string& id,
                                             const std::string& title,
                                             const std::string& author,
                                             int year) {
    try {
        if (catalog_->is_existed(id)) {
            return AlreadyExists{"Book with this id already exists"};
        }

        catalog_->addBook(Book{id, title, author, year});
        return Success{"Book added successfully"};
    } catch (const std::exception& e) {
        return ValidationError{e.what()};
    }
}

LibraryApp::ActionResult LibraryApp::addReader(const std::string& id,
                                               const std::string& name,
                                               const std::string& email) {
    try {
        if (registry_->exists(id)) {
            return AlreadyExists{"Reader with this id already exists"};
        }

        registry_->addReader(Reader{id, name, email});
        return Success{"Reader added successfully"};
    } catch (const std::exception& e) {
        return ValidationError{e.what()};
    }
}

LibraryApp::ActionResult LibraryApp::issueBook(const std::string& bookId,
                                               const std::string& readerId) {
    if (!catalog_->is_existed(bookId)) {
        return NotFound{"Book not found"};
    }

    if (!registry_->exists(readerId)) {
        return NotFound{"Reader not found"};
    }

    if (activeLoans_.contains(bookId)) {
        return AlreadyExists{"This book is already issued"};
    }

    activeLoans_[bookId] = readerId;
    return Success{"Book issued successfully"};
}

LibraryApp::ActionResult LibraryApp::returnBook(const std::string& bookId) {
    auto it = activeLoans_.find(bookId);

    if (it == activeLoans_.end()) {
        return NotFound{"This book is not currently issued"};
    }

    activeLoans_.erase(it);
    return Success{"Book returned successfully"};
}

void LibraryApp::addBookUI() {
    std::string id;
    std::string title;
    std::string author;
    int year = 0;

    std::cout << "Enter book id: ";
    std::getline(std::cin, id);

    std::cout << "Enter title: ";
    std::getline(std::cin, title);

    std::cout << "Enter author: ";
    std::getline(std::cin, author);

    std::cout << "Enter year: ";
    std::cin >> year;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    handleResult(addBook(id, title, author, year));
}

void LibraryApp::addReaderUI() {
    std::string id;
    std::string name;
    std::string email;

    std::cout << "Enter reader id: ";
    std::getline(std::cin, id);

    std::cout << "Enter name: ";
    std::getline(std::cin, name);

    std::cout << "Enter email: ";
    std::getline(std::cin, email);

    handleResult(addReader(id, name, email));
}

void LibraryApp::findBookUI() const {
    std::string id;
    std::cout << "Enter book id: ";
    std::getline(std::cin, id);

    auto result = catalog_->searchById(id);
    if (result.has_value()) {
        std::cout << result->to_string() << '\n';
    } else {
        std::cout << "Book not found\n";
    }
}

void LibraryApp::findReaderUI() const {
    std::string id;
    std::cout << "Enter reader id: ";
    std::getline(std::cin, id);

    auto result = registry_->findById(id);
    if (result.has_value()) {
        std::cout << result->toString() << '\n';
    } else {
        std::cout << "Reader not found\n";
    }
}

void LibraryApp::listBooksUI() const {
    const auto books = catalog_->listAll();

    if (books.empty()) {
        std::cout << "No books in catalog\n";
        return;
    }

    for (const auto& book : books) {
        std::cout << book.to_string() << '\n';
    }
}

void LibraryApp::listReadersUI() const {
    const auto readers = registry_->listAll();

    if (readers.empty()) {
        std::cout << "No readers in registry\n";
        return;
    }

    for (const auto& reader : readers) {
        std::cout << reader.toString() << '\n';
    }
}

void LibraryApp::issueBookUI() {
    std::string bookId;
    std::string readerId;

    std::cout << "Enter book id: ";
    std::getline(std::cin, bookId);

    std::cout << "Enter reader id: ";
    std::getline(std::cin, readerId);

    handleResult(issueBook(bookId, readerId));
}

void LibraryApp::returnBookUI() {
    std::string bookId;

    std::cout << "Enter book id: ";
    std::getline(std::cin, bookId);

    handleResult(returnBook(bookId));
}

void LibraryApp::removeBookUI() {
    std::string id;

    std::cout << "Enter book id: ";
    std::getline(std::cin, id);

    if (activeLoans_.contains(id)) {
        std::cout << "Cannot remove a book that is currently issued\n";
        return;
    }

    if (catalog_->removeById(id)) {
        std::cout << "Book removed successfully\n";
    } else {
        std::cout << "Book not found\n";
    }
}

void LibraryApp::run() {
    std::cout << "Welcome to the library system\n";
    std::cout << "Current user: " << librarian_->toString() << "\n";

    int command = -1;

    while (command != kExitCommand) {
        showMenu();

        if (!(std::cin >> command)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input\n";
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (command) {
            case kAddBookCommand:
                addBookUI();
                break;
            case kAddReaderCommand:
                addReaderUI();
                break;
            case kFindBookCommand:
                findBookUI();
                break;
            case kFindReaderCommand:
                findReaderUI();
                break;
            case kListBooksCommand:
                listBooksUI();
                break;
            case kListReadersCommand:
                listReadersUI();
                break;
            case kIssueBookCommand:
                issueBookUI();
                break;
            case kReturnBookCommand:
                returnBookUI();
                break;
            case kRemoveBookCommand:
                removeBookUI();
                break;
            case kExitCommand:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Unknown command\n";
                break;
        }
    }
}