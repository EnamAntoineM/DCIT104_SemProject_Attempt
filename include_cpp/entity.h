#ifndef ENTITY
    #define ENTITY
    #include "my.h"

    class BookManager {
    public:
        BookManager(); // Constructor

        //Book example
        static bool create_entity(const std::string &book);
        static bool update_book(const std::string &book);
        static bool delete_book(const std::string &book);
        static std::string get_books(void);

    private:
        static Book jsonToBook(const std::string &bookStr);
        static std::string bookToJson(std::vector<Book> &dbContent);
        static sqlite3 *init_db();
        static bool closedb(sqlite3 *db);
    };
#endif