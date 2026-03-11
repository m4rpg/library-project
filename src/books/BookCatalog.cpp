#include "BookCatalog.h"
#include <algorithm>

void BookCatalog::addBook(Book book) {
    books.push_back(std::move(book));
}

std::optional<Book> BookCatalog::searchById(const std::string& id) const {
    for (const auto& book : books) {
        if (book.getId == id) {
            return book;
        }
    }
    return std::nullopt;
}

bool BookCatalog::removeById(const std::string& id) const {
    auto it = std::remove_if(books.begin(), books.end(), [&id](const Book& b) { return b.getId() == id; });
    
    if (it != books.end()) {
        books.erase(it, books.end());
        return true;
    }
    return false;
}

const std::vector<Book>& BookCatalog::listAll() const {
    return books;
}

bool BookCatalog::is_existed(const std::string& id) const {
    return searchById(id).has_value();
}

size_t BookCatalog::size() const {
    return books.size();
}

void BookCatalog::clear() {
    books.clear();
}
