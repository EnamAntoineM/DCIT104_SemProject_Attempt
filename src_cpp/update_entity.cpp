#include "../include_cpp/my.h"


bool BookManager::update_book(const std::string &book)
{
    sqlite3 *db = BookManager::init_db();
    if (!db) return false;
    Book toUpdate = BookManager::jsonToBook(book);
    std::string updateQuery = "UPDATE BOOKS SET title = ?, author = ?, genre = ?, yearPublished = ? WHERE identifier = ?;";
    sqlite3_stmt *stmt;
    bool result;

    if (sqlite3_prepare_v2(db, updateQuery.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "SQL prepare error: " << sqlite3_errmsg(db) << std::endl;
        BookManager::closedb(db);
        return false;
    }

    if (toUpdate.identifier <= 0) {
        std::cerr << "Identifier cannot be <= 0 !" << std::endl;
        BookManager::closedb(db);
        return false;
    }
    sqlite3_bind_text(stmt, 1, toUpdate.title.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, toUpdate.author.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, toUpdate.genre.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, toUpdate.YearPublished);
    sqlite3_bind_int(stmt, 5, toUpdate.identifier);

    if (!(result = (sqlite3_step(stmt) == SQLITE_DONE))) {
        std::cerr << "SQL step error: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
    BookManager::closedb(db);

    return result;
}