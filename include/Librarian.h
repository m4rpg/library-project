#pragma once
#include "Person.h"
#include <string>
class Librarian : public Person {
private:
    std::string employeeCode_;
public:
    static constexpr std::size_t kMaxEmployeeCodeLength = 20;
    Librarian(std::string id, std::string name, std::string employeeCode);
    const std::string& employeeCode() const;
    std::string role() const override;
    std::string toString() const override;
};