#pragma once
#include <string>

class Book {
private:
    std::string id_;
    std::string title_;
    std::string author_;
    int year_;

public:
    static constexpr int kMinYear = 1450;
    static constexpr int kMaxYear = 2100;

    Book(std::string id, std::string title, std::string author, int year);

    const std::string& id() const;
    const std::string& title() const;
    const std::string& author() const;
    int year() const;

    std::string toString() const;
};