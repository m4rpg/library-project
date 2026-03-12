#include "Reader.h"
#include <utility>g
Reader::Reader(std::string id, std::string name, std::string email)
    : Person(std::move(id), std::move(name)),
      email_(std::move(email)) {}
const std::string& Reader::email() const {
    return email_;
}
std::string Reader::role() const {
    return "Reader";
}
std::string Reader::toString() const {
    return "Role: " + role() +
           ", ID: " + id_ +
           ", Name: " + name_ +
           ", Email: " + email_;
}