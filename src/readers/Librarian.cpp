#include "Librarian.h"
#include <utility>
Librarian::Librarian(std::string id, std::string name, std::string employeeCode)
    : Person(std::move(id), std::move(name)),
      employeeCode_(std::move(employeeCode)) {}
const std::string& Librarian::employeeCode() const {
    return employeeCode_;
}
std::string Librarian::role() const {
    return "Librarian";
}
std::string Librarian::toString() const {
    return "Role: " + role() +
           ", ID: " + id_ +
           ", Name: " + name_ +
           ", Employee code: " + employeeCode_;
}