#include <gtest/gtest.h>
#include "Reader.h"
#include "ReaderRegistry.h"

TEST(ReaderTest, CreatesReaderCorrectly) {
    Reader reader("r1", "Maria", "maria@mail.com");

    EXPECT_EQ(reader.id(), "r1");
    EXPECT_EQ(reader.name(), "Maria");
    EXPECT_EQ(reader.email(), "maria@mail.com");
    EXPECT_EQ(reader.role(), "Reader");
}

TEST(ReaderTest, ToStringContainsReaderInfo) {
    Reader reader("r2", "Alexander", "alexander@mail.com");

    std::string text = reader.toString();

    EXPECT_NE(text.find("Alexander"), std::string::npos);
    EXPECT_NE(text.find("alexander@mail.com"), std::string::npos);
}

TEST(ReaderRegistryTest, AddReaderIncreasesSize) {
    ReaderRegistry registry;

    registry.addReader(Reader("r1", "Maria", "maria@mail.com"));

    EXPECT_EQ(registry.size(), 1);
    EXPECT_TRUE(registry.exists("r1"));
}

TEST(ReaderRegistryTest, AddSeveralReadersStoresAllOfThem) {
    ReaderRegistry registry;

    registry.addReader(Reader("r1", "Maria", "maria@mail.com"));
    registry.addReader(Reader("r2", "Alexander", "alexander@mail.com"));
    registry.addReader(Reader("r3", "George", "george@mail.com"));

    EXPECT_EQ(registry.size(), 3);
    EXPECT_TRUE(registry.exists("r1"));
    EXPECT_TRUE(registry.exists("r2"));
    EXPECT_TRUE(registry.exists("r3"));
}

TEST(ReaderRegistryTest, FindByIdReturnsCorrectReader) {
    ReaderRegistry registry;
    registry.addReader(Reader("r3", "George", "george@mail.com"));

    auto result = registry.findById("r3");

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->name(), "George");
    EXPECT_EQ(result->email(), "george@mail.com");
}

TEST(ReaderRegistryTest, FindByIdReturnsEmptyForMissingReader) {
    ReaderRegistry registry;

    auto result = registry.findById("missing");

    EXPECT_FALSE(result.has_value());
}

TEST(ReaderRegistryTest, ExistsReturnsFalseForMissingReader) {
    ReaderRegistry registry;

    EXPECT_FALSE(registry.exists("missing"));
}

TEST(ReaderRegistryTest, RemoveReaderDeletesExistingReader) {
    ReaderRegistry registry;
    registry.addReader(Reader("r1", "Maria", "maria@mail.com"));

    EXPECT_TRUE(registry.removeReader("r1"));
    EXPECT_FALSE(registry.exists("r1"));
    EXPECT_EQ(registry.size(), 0);
}

TEST(ReaderRegistryTest, RemoveReaderReturnsFalseForMissingReader) {
    ReaderRegistry registry;

    EXPECT_FALSE(registry.removeReader("missing"));
}

TEST(ReaderRegistryTest, DuplicateReaderThrowsException) {
    ReaderRegistry registry;
    registry.addReader(Reader("r1", "Maria", "maria@mail.com"));

    EXPECT_THROW(
        registry.addReader(Reader("r1", "Alexander", "alexander@mail.com")),
        DuplicateReaderException
    );
}

TEST(ReaderRegistryTest, EmptyIdThrowsException) {
    ReaderRegistry registry;

    EXPECT_THROW(
        registry.addReader(Reader("", "Maria", "maria@mail.com")),
        InvalidReaderDataException
    );
}

TEST(ReaderRegistryTest, EmptyNameThrowsException) {
    ReaderRegistry registry;

    EXPECT_THROW(
        registry.addReader(Reader("r1", "", "maria@mail.com")),
        InvalidReaderDataException
    );
}

TEST(ReaderRegistryTest, EmptyEmailThrowsException) {
    ReaderRegistry registry;

    EXPECT_THROW(
        registry.addReader(Reader("r1", "Maria", "")),
        InvalidReaderDataException
    );
}