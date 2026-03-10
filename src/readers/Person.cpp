#include "Person.h"
#include <utility>
Person::Person(std::string id, std::string name)
    : id_(std::move(id)), name_(std::move(name)) {}
const std::string& Person::id() const {
    return id_;
}
const std::string& Person::name() const {
    return name_;
}
std::string Person::toString() const {
    return "ID: " + id_ + ", Name: " + name_;
}