#include "LoanService.h"

LoanService::LoanService(BookCatalog& catalog, ReaderRegistry& readers)
    : catalog_(catalog), readers_(readers) {
}

bool LoanService::loanBook(const std::string& bookId, const std::string& readerId) {
    if (!catalog_.exists(bookId)) {
        return false;
    }

    if (!readers_.exists(readerId)) {
        return false;
    }

    if (isBookLoaned(bookId)) {
        return false;
    }

    LoanRecord record;
    record.bookId = bookId;
    record.readerId = readerId;
    record.returned = false;

    loans_.push_back(record);
    return true;
}

bool LoanService::returnBook(const std::string& bookId) {
    for (auto& loan : loans_) {
        if (loan.bookId == bookId && !loan.returned) {
            loan.returned = true;
            return true;
        }
    }

    return false;
}

bool LoanService::isBookLoaned(const std::string& bookId) const {
    for (const auto& loan : loans_) {
        if (loan.bookId == bookId && !loan.returned) {
            return true;
        }
    }

    return false;
}

std::vector<LoanService::LoanRecord> LoanService::listLoans() const {
    return loans_;
}