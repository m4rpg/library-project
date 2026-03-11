#ifndef LIBRARY_PROJECT_BOOKCATALOG_H
#define LIBRARY_PROJECT_BOOKCATALOG_H

#include "Book.h"
#include <vector>
#include <string>
#include <optional>

class BookCatalog {
private:
    std::vector<Book> books;
    
public:
    void addBook(Book book);
    std::optional<Book> searchById(const std::string& id) const;
    bool removeById(const std::string& id);
    const std::vector<Book>& listAll() const;
    bool is_existed(const std::string& id) const;
    size_t size() const;
    void clear();
    
};

#endif //LIBRARY_PROJECT_BOOKCATALOG_H
