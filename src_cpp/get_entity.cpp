#include "../include_cpp/my.h"

std::string BookManager::get_books(void)
{
    sqlite3 *db = BookManager::init_db();
    std::vector<Book> bookList;
    if (!db) {
        std::cerr << "Failed to initialize db !" << std::endl;
        return "[]";
    }
    std::string fetchQuery = "SELECT * FROM BOOKS;";
    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, fetchQuery.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "SQL prepare error: " << sqlite3_errmsg(db) << std::endl;
        BookManager::closedb(db);
        return "[]";
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Book book;
        book.identifier     = sqlite3_column_int(stmt, 0);
        book.title          = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        book.author         = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        book.genre          = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        book.YearPublished  = sqlite3_column_int(stmt, 4);
        bookList.push_back(book);
    }

    sqlite3_finalize(stmt);
    BookManager::closedb(db);

    return BookManager::bookToJson(bookList);
}