#ifndef LIBRARY_PROJECT_BOOK_H
#define LIBRARY_PROJECT_BOOK_H

#include <string>

class Book {
private:
    std::string id;
    std::string title;
    std::string author;
    int year;

public:
    Book(std::string id, std::string title, std::string author, int year);
    
    const std::string& getId() const;
    const std::string& getTitle() const;
    const std::string& getAuthor() const;
    int getYear() const;
    std::string to_string() const;
};

#endif //LIBRARY_PROJECT_BOOK_H
