#include "ReaderRegistry.h"

void ReaderRegistry::validateReader(const Reader& reader) const {
    if (reader.id().empty()) {
        throw InvalidReaderDataException("Reader id cannot be empty");
    }

    if (reader.name().empty()) {
        throw InvalidReaderDataException("Reader name cannot be empty");
    }

    if (reader.email().empty()) {
        throw InvalidReaderDataException("Reader email cannot be empty");
    }

    if (reader.id().size() > Person::kMaxIdLength) {
        throw InvalidReaderDataException("Reader id is too long");
    }

    if (reader.name().size() > Person::kMaxNameLength) {
        throw InvalidReaderDataException("Reader name is too long");
    }

    if (reader.email().size() > Reader::kMaxEmailLength) {
        throw InvalidReaderDataException("Reader email is too long");
    }
}

void ReaderRegistry::addReader(const Reader& reader) {
    validateReader(reader);

    if (exists(reader.id())) {
        throw DuplicateReaderException(reader.id());
    }

    readers_.push_back(reader);
}

bool ReaderRegistry::removeReader(const std::string& id) {
    for (auto it = readers_.begin(); it != readers_.end(); ++it) {
        if (it->id() == id) {
            readers_.erase(it);
            return true;
        }
    }

    return false;
}

std::optional<Reader> ReaderRegistry::findById(const std::string& id) const {
    for (const auto& reader : readers_) {
        if (reader.id() == id) {
            return reader;
        }
    }

    return std::nullopt;
}

std::vector<Reader> ReaderRegistry::listAll() const {
    return readers_;
}

bool ReaderRegistry::exists(const std::string& id) const {
    for (const auto& reader : readers_) {
        if (reader.id() == id) {
            return true;
        }
    }

    return false;
}

std::size_t ReaderRegistry::size() const {
    return readers_.size();
}