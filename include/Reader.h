#pragma once
#include "Person.h"
#include <string>
class Reader : public Person {
private:
    std::string email_;
public:
    static constexpr std::size_t kMaxEmailLength = 100;
    Reader(std::string id, std::string name, std::string email);
    const std::string& email() const;
    std::string role() const override;
    std::string toString() const override;
};