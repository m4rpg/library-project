#include "Book.h"
#include <utility>

Book::Book(std::string id, std::string title, std::string author, int year)
    : id_(std::move(id)),
      title_(std::move(title)),
      author_(std::move(author)),
      year_(year) {}

const std::string& Book::id() const {
    return id_;
}

const std::string& Book::title() const {
    return title_;
}

const std::string& Book::author() const {
    return author_;
}

int Book::year() const {
    return year_;
}

std::string Book::toString() const {
    return "ID: " + id_ +
           ", Title: " + title_ +
           ", Author: " + author_ +
           ", Year: " + std::to_string(year_);
}