#pragma once
#include <string>
class Person {
protected:
    std::string id_;
    std::string name_;
public:
    static constexpr std::size_t kMaxIdLength = 20;
    static constexpr std::size_t kMaxNameLength = 100;

    Person(std::string id, std::string name);
    virtual ~Person() = default;
    const std::string& id() const;
    const std::string& name() const;
    virtual std::string role() const = 0;
    virtual std::string toString() const;
};