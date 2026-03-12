#include <gtest/gtest.h>
#include "Reader.h"
#include "ReaderRegistry.h"

TEST(ReaderTest, CreatesReaderCorrectly) {
    Reader reader("r1", "Maria", "maria@mail.com");

    EXPECT_EQ(reader.name(), "Maria");
    EXPECT_EQ(reader.email(), "maria@mail.com");
    EXPECT_EQ(reader.role(), "Reader");
}

TEST(ReaderTest, ToStringContainsReaderInfo) {
    Reader reader("r1", "Alexander", "alexander@mail.com");

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

TEST(ReaderRegistryTest, AddSeveralReaders) {
    ReaderRegistry registry;

    registry.addReader(Reader("r1", "Maria", "maria@mail.com"));
    registry.addReader(Reader("r2", "Alexander", "alexander@mail.com"));
    registry.addReader(Reader("r3", "George", "george@mail.com"));

    EXPECT_EQ(registry.size(), 3);
}

TEST(ReaderRegistryTest, FindReaderById) {
    ReaderRegistry registry;

    registry.addReader(Reader("r1", "George", "george@mail.com"));

    auto result = registry.findById("r1");

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->name(), "George");
}

TEST(ReaderRegistryTest, RemoveReaderWorks) {
    ReaderRegistry registry;

    registry.addReader(Reader("r1", "Maria", "maria@mail.com"));

    EXPECT_TRUE(registry.removeReader("r1"));
    EXPECT_FALSE(registry.exists("r1"));
}

TEST(ReaderRegistryTest, DuplicateReaderThrowsException) {
    ReaderRegistry registry;

    registry.addReader(Reader("r1", "Maria", "maria@mail.com"));

    EXPECT_THROW(
        registry.addReader(Reader("r1", "Alexander", "alex@mail.com")),
        DuplicateReaderException
    );
}

TEST(ReaderRegistryTest, InvalidReaderDataThrowsException) {
    ReaderRegistry registry;

    EXPECT_THROW(
        registry.addReader(Reader("", "George", "george@mail.com")),
        InvalidReaderDataException
    );
}