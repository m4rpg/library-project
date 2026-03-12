#pragma once
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>
#include "Book.h"

class BookCatalogException : public std::runtime_error {
public:
    explicit BookCatalogException(const std::string& message)
        : std::runtime_error(message) {}
};

class DuplicateBookException : public BookCatalogException {
public:
    explicit DuplicateBookException(const std::string& id)
        : BookCatalogException("Book with id '" + id + "' already exists") {}
};

class InvalidBookDataException : public BookCatalogException {
public:
    explicit InvalidBookDataException(const std::string& message)
        : BookCatalogException(message) {}
};

class BookCatalog {
private:
    std::vector<Book> books_;

    void validateBook(const Book& book) const;

public:
    void addBook(const Book& book);
    bool removeBook(const std::string& id);
    std::optional<Book> findById(const std::string& id) const;
    std::vector<Book> listAll() const;
    bool exists(const std::string& id) const;
    std::size_t size() const;
};