#include "Reader.h"
Reader::Reader(const std::string& id, const std::string& name)
    : Person(id, name) {
}
std::string Reader::getRole() const {
    return "Reader";
}
std::string Reader::toString() const {
    return "Reader: " + id_ + " | " + name_;
}