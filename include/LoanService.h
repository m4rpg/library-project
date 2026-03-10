#pragma once
#include <string>
#include <vector>
#include "BookCatalog.h"
#include "ReaderRegistry.h"
class LoanService {
public:
    struct LoanRecord {
        std::string bookId;
        std::string readerId;
        bool returned = false;
    };
private:
    BookCatalog& catalog_;
    ReaderRegistry& readers_;
    std::vector<LoanRecord> loans_;
public:
    LoanService(BookCatalog& catalog, ReaderRegistry& readers);
    bool loanBook(const std::string& bookId, const std::string& readerId);
    bool returnBook(const std::string& bookId);
    bool isBookLoaned(const std::string& bookId) const;
    std::vector<LoanRecord> listLoans() const;
};