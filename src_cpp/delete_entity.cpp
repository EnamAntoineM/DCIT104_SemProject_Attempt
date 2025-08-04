#include "../include_cpp/my.h"

bool BookManager::delete_book(const std::string &book)
{
    sqlite3 *db = BookManager::init_db();
    if (!db) return false;
    Book toDelete = BookManager::jsonToBook(book);
    std::string deleteQuery = "DELETE FROM BOOKS WHERE identifier = ?";
    sqlite3_stmt *stmt;
    bool result;

    if (sqlite3_prepare_v2(db, deleteQuery.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "SQL prepare error: " << sqlite3_errmsg(db) << std::endl;
        BookManager::closedb(db);
        return false;
    }

    if (toDelete.identifier <= 0) {
        std::cerr << "Invalid identifier for deletion." << std::endl;
        BookManager::closedb(db);
        return false;
    }

    sqlite3_bind_int(stmt, 1, toDelete.identifier);

    if (!(result = (sqlite3_step(stmt) == SQLITE_DONE))) {
        std::cerr << "SQL step error: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
    BookManager::closedb(db);

    return result;
}