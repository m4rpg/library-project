//
// Created by Maria on 02.03.2026.
//
#include "Book.h"
#include <string>
#include <format>


Book(std::string id, std::string title, std::string author, int year) : id(std::move(id)), title(std::move(title)),
    author(std::move(author)), year(year) {}

const std::string& Book::getId() const {
    return id;
}

const std::string& Book::getTitle() const {
    return title;
}

const std::string& Book::getAuthor() const {
    return author;
}

int Book::getYear() const {
    return year;
}

std::string Book::to_String() const {
    return std::format("{}: {} by {} ({})", id, title, author, year);
}
