#pragma once
#include <string>
#include "Person.h"
class Librarian : public Person {
public:
    Librarian(const std::string& id, const std::string& name);
    std::string getRole() const override;
    std::string toString() const override;
};