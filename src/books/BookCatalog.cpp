#include "BookCatalog.h"

void BookCatalog::validateBook(const Book& book) const {
    if (book.id().empty()) {
        throw InvalidBookDataException("Book id cannot be empty");
    }

    if (book.title().empty()) {
        throw InvalidBookDataException("Book title cannot be empty");
    }

    if (book.author().empty()) {
        throw InvalidBookDataException("Book author cannot be empty");
    }

    if (book.year() < Book::kMinYear || book.year() > Book::kMaxYear) {
        throw InvalidBookDataException("Book year is out of allowed range");
    }
}

void BookCatalog::addBook(const Book& book) {
    validateBook(book);

    if (exists(book.id())) {
        throw DuplicateBookException(book.id());
    }

    books_.push_back(book);
}

bool BookCatalog::removeBook(const std::string& id) {
    for (auto it = books_.begin(); it != books_.end(); ++it) {
        if (it->id() == id) {
            books_.erase(it);
            return true;
        }
    }

    return false;
}

std::optional<Book> BookCatalog::findById(const std::string& id) const {
    for (const auto& book : books_) {
        if (book.id() == id) {
            return book;
        }
    }

    return std::nullopt;
}

std::vector<Book> BookCatalog::listAll() const {
    return books_;
}

bool BookCatalog::exists(const std::string& id) const {
    for (const auto& book : books_) {
        if (book.id() == id) {
            return true;
        }
    }

    return false;
}

std::size_t BookCatalog::size() const {
    return books_.size();
}