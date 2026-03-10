#pragma once

#include <string>
class Person {
protected:
    std::string id_;
    std::string name_;
public:
    Person(const std::string& id, const std::string& name);
    virtual ~Person() = default;
    const std::string& getId() const;
    const std::string& getName() const;
    virtual std::string getRole() const = 0;
    virtual std::string toString() const = 0;
};