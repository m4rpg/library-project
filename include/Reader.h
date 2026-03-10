#pragma once
#include <string>
#include "Person.h"
class Reader : public Person {
public:
    Reader(const std::string& id, const std::string& name);
    std::string getRole() const override;
    std::string toString() const override;
};