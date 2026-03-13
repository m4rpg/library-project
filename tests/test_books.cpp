#include <gtest/gtest.h>
#include "Book.h"
#include "BookCatalog.h"

TEST(BookTest, CreatesBookCorrectly) {
    Book book("b1", "Преступление и наказание", "Федор Достоевский", 1866);

    EXPECT_EQ(book.id(), "b1");
    EXPECT_EQ(book.title(), "Преступление и наказание");
    EXPECT_EQ(book.author(), "Федор Достоевский");
    EXPECT_EQ(book.year(), 1866);
}

TEST(BookTest, ToStringContainsMainFields) {
    Book book("b2", "Анна Каренина", "Лев Толстой", 1877);

    std::string text = book.toString();

    EXPECT_NE(text.find("Анна Каренина"), std::string::npos);
    EXPECT_NE(text.find("Лев Толстой"), std::string::npos);
    EXPECT_NE(text.find("1877"), std::string::npos);
}

TEST(BookCatalogTest, AddBookIncreasesSize) {
    BookCatalog catalog;

    catalog.addBook(Book("b1", "Преступление и наказание", "Федор Достоевский", 1866));

    EXPECT_EQ(catalog.size(), 1);
    EXPECT_TRUE(catalog.exists("b1"));
}

TEST(BookCatalogTest, AddSeveralBooksStoresAllOfThem) {
    BookCatalog catalog;

    catalog.addBook(Book("b1", "Преступление и наказание", "Федор Достоевский", 1866));
    catalog.addBook(Book("b2", "Анна Каренина", "Лев Толстой", 1877));
    catalog.addBook(Book("b3", "Мертвые души", "Николай Гоголь", 1842));

    EXPECT_EQ(catalog.size(), 3);
    EXPECT_TRUE(catalog.exists("b1"));
    EXPECT_TRUE(catalog.exists("b2"));
    EXPECT_TRUE(catalog.exists("b3"));
}

TEST(BookCatalogTest, FindByIdReturnsCorrectBook) {
    BookCatalog catalog;
    catalog.addBook(Book("b1", "Война и мир", "Лев Толстой", 1869));

    auto result = catalog.findById("b1");

    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->title(), "Война и мир");
    EXPECT_EQ(result->author(), "Лев Толстой");
}

TEST(BookCatalogTest, FindByIdReturnsEmptyForMissingBook) {
    BookCatalog catalog;

    auto result = catalog.findById("missing");

    EXPECT_FALSE(result.has_value());
}

TEST(BookCatalogTest, ExistsReturnsFalseForMissingBook) {
    BookCatalog catalog;

    EXPECT_FALSE(catalog.exists("missing"));
}

TEST(BookCatalogTest, RemoveBookDeletesExistingBook) {
    BookCatalog catalog;
    catalog.addBook(Book("b1", "Мастер и Маргарита", "Михаил Булгаков", 1967));

    EXPECT_TRUE(catalog.removeBook("b1"));
    EXPECT_FALSE(catalog.exists("b1"));
    EXPECT_EQ(catalog.size(), 0);
}

TEST(BookCatalogTest, RemoveBookReturnsFalseForMissingBook) {
    BookCatalog catalog;

    EXPECT_FALSE(catalog.removeBook("missing"));
}

TEST(BookCatalogTest, DuplicateBookThrowsException) {
    BookCatalog catalog;
    catalog.addBook(Book("b1", "Преступление и наказание", "Федор Достоевский", 1866));

    EXPECT_THROW(
        catalog.addBook(Book("b1", "Анна Каренина", "Лев Толстой", 1877)),
        DuplicateBookException
    );
}

TEST(BookCatalogTest, EmptyIdThrowsException) {
    BookCatalog catalog;

    EXPECT_THROW(
        catalog.addBook(Book("", "Преступление и наказание", "Федор Достоевский", 1866)),
        InvalidBookDataException
    );
}

TEST(BookCatalogTest, EmptyTitleThrowsException) {
    BookCatalog catalog;

    EXPECT_THROW(
        catalog.addBook(Book("b1", "", "Федор Достоевский", 1866)),
        InvalidBookDataException
    );
}

TEST(BookCatalogTest, EmptyAuthorThrowsException) {
    BookCatalog catalog;

    EXPECT_THROW(
        catalog.addBook(Book("b1", "Преступление и наказание", "", 1866)),
        InvalidBookDataException
    );
}

TEST(BookCatalogTest, InvalidYearThrowsException) {
    BookCatalog catalog;

    EXPECT_THROW(
        catalog.addBook(Book("b1", "Очень старая книга", "Неизвестный автор", 1200)),
        InvalidBookDataException
    );
}