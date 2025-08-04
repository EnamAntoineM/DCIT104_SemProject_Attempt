#include "../include_cpp/my.h"

bool BookManager::create_entity(const std::string &book)
{
    sqlite3 *db = BookManager::init_db();
    if (!db) return false;
    Book toCreate = BookManager::jsonToBook(book);
    std::string createQuery = "INSERT INTO BOOKS "
    "(title, author, genre, YearPublished) "
    "VALUES (?, ?, ?, ?);";
    sqlite3_stmt *stmt;
    bool result;

    if (sqlite3_prepare_v2(db, createQuery.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "SQL prepare error: " << sqlite3_errmsg(db) << std::endl;
        BookManager::closedb(db);
        return false;
    }

    sqlite3_bind_text(stmt, 1, toCreate.title.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, toCreate.author.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, toCreate.genre.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 4, toCreate.YearPublished);

    if (!(result = (sqlite3_step(stmt) == SQLITE_DONE))) {
        std::cerr << "SQL step error: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
    BookManager::closedb(db);
    return result;
}