#include <gtest/gtest.h>
#include "Librarian.h"
#include "Reader.h"

TEST(PersonTest, ReaderRoleIsCorrect) {
    Reader reader("r1", "Maria", "maria@mail.com");

    EXPECT_EQ(reader.role(), "Reader");
}

TEST(PersonTest, LibrarianRoleIsCorrect) {
    Librarian librarian("l1", "Alexander", "EMP001");

    EXPECT_EQ(librarian.role(), "Librarian");
}

TEST(PersonTest, LibrarianStoresEmployeeCode) {
    Librarian librarian("l1", "George", "EMP777");

    EXPECT_EQ(librarian.employeeCode(), "EMP777");
}

TEST(PersonTest, PolymorphismWorksForPeople) {
    Reader reader("r1", "Maria", "maria@mail.com");
    Librarian librarian("l1", "Alexander", "EMP001");

    Person* p1 = &reader;
    Person* p2 = &librarian;

    EXPECT_EQ(p1->role(), "Reader");
    EXPECT_EQ(p2->role(), "Librarian");
}