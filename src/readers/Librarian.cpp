#include "Librarian.h"
Librarian::Librarian(const std::string& id, const std::string& name)
    : Person(id, name) {
}
std::string Librarian::getRole() const {
    return "Librarian";
}
std::string Librarian::toString() const {
    return "Librarian: " + id_ + " | " + name_;
}