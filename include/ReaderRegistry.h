#pragma once
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>
#include "Reader.h"

class ReaderRegistryException : public std::runtime_error {
public:
    explicit ReaderRegistryException(const std::string& message)
        : std::runtime_error(message) {}
};

class DuplicateReaderException : public ReaderRegistryException {
public:
    explicit DuplicateReaderException(const std::string& id)
        : ReaderRegistryException("Reader with id '" + id + "' already exists") {}
};

class InvalidReaderDataException : public ReaderRegistryException {
public:
    explicit InvalidReaderDataException(const std::string& message)
        : ReaderRegistryException(message) {}
};

class ReaderNotFoundException : public ReaderRegistryException {
public:
    explicit ReaderNotFoundException(const std::string& id)
        : ReaderRegistryException("Reader with id '" + id + "' not found") {}
};

class ReaderRegistry {
private:
    std::vector<Reader> readers_;

    void validateReader(const Reader& reader) const;

public:
    void addReader(const Reader& reader);

    bool removeReader(const std::string& id);

    std::optional<Reader> findById(const std::string& id) const;

    std::vector<Reader> listAll() const;

    bool exists(const std::string& id) const;

    std::size_t size() const;
};