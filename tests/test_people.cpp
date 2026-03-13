#include <gtest/gtest.h>
#include "Librarian.h"
#include "Reader.h"

TEST(PersonHierarchyTest, ReaderRoleIsCorrect) {
    Reader reader("r1", "Maria", "maria@mail.com");

    EXPECT_EQ(reader.role(), "Reader");
}

TEST(PersonHierarchyTest, LibrarianRoleIsCorrect) {
    Librarian librarian("l1", "Alexander", "EMP001");

    EXPECT_EQ(librarian.role(), "Librarian");
}

TEST(PersonHierarchyTest, LibrarianStoresEmployeeCode) {
    Librarian librarian("l2", "George", "EMP777");

    EXPECT_EQ(librarian.employeeCode(), "EMP777");
}

TEST(PersonHierarchyTest, ReaderCanBeUsedPolymorphically) {
    Reader reader("r1", "Maria", "maria@mail.com");
    Person* person = &reader;

    EXPECT_EQ(person->role(), "Reader");
}

TEST(PersonHierarchyTest, LibrarianCanBeUsedPolymorphically) {
    Librarian librarian("l1", "Alexander", "EMP001");
    Person* person = &librarian;

    EXPECT_EQ(person->role(), "Librarian");
}