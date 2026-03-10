#include "Person.h"
Person::Person(const std::string& id, const std::string& name)
    : id_(id), name_(name) {
}
const std::string& Person::getId() const {
    return id_;
}
const std::string& Person::getName() const {
    return name_;
}