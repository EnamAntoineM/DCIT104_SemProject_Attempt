#include "../include_cpp/my.h"

static const char *bookTbSqlQuery = "CREATE TABLE IF NOT EXISTS BOOKS ("
                 "identifier INTEGER PRIMARY KEY AUTOINCREMENT, "
                 "title TEXT NOT NULL, "
                 "author TEXT NOT NULL, "
                 "genre TEXT NOT NULL, "
                 "yearPublished INTEGER NOT NULL);";

sqlite3 *BookManager::init_db(void)
{
    namespace fs = std::filesystem;
    fs::path pathPt1;
    fs::path pathPt2;
    fs::path DbFullpath;
    sqlite3 *db = nullptr;
    char *errmsg;
    char *appdata;
    char *home;
    std::string errormsg;

    std::cout << "I've been called" << std::endl;
    #ifdef _WIN32
        appdata = std::getenv("APPDATA");
        pathPt1 = appdata ? fs::path(appdata) : fs::temp_directory_path();
    #else
        home = std::getenv("HOME");
        pathPt1 = home ? fs::path(home) / ".local" / "share" : fs::temp_directory_path();
    #endif

    pathPt2 = pathPt1 / "sm104";
    fs::create_directories(pathPt2);
    DbFullpath = pathPt2 / "bookdb.sqlite";

    if (sqlite3_open(DbFullpath.string().c_str(), &db) != SQLITE_OK) {
        errormsg = "Failed to open database: ";
        errormsg += sqlite3_errmsg(db);
        std::cerr << errormsg << std::endl;
        BookManager::closedb(db);
        throw std::runtime_error("Failed to open database");
    }
    
    if (sqlite3_exec(db, bookTbSqlQuery, 0, 0, &errmsg) != SQLITE_OK) {
        errormsg = "Failed to create table: ";
        errormsg += errmsg;
        std::cerr << errormsg << std::endl;
        sqlite3_free(errmsg);
        BookManager::closedb(db);
        throw std::runtime_error("Failed to create table!");
    }
    return db;
}

bool BookManager::closedb(sqlite3 *db)
{
    if (db != nullptr) {
        return sqlite3_close(db) == SQLITE_OK;
    }
    return false;
}