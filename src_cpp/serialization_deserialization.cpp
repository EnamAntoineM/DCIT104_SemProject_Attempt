#include "../include_cpp/my.h"
#include <nlohmann/json.hpp>
using nlohmann::json;

Book BookManager::jsonToBook(const std::string &bookStr) {
    json j = json::parse(bookStr);
    Book book;
    book.identifier = j.at("identifier").get<uint32_t>();
    book.title = j.at("title").get<std::string>();
    book.author = j.at("author").get<std::string>();
    book.genre = j.at("genre").get<std::string>();
    book.YearPublished = j.at("YearPublished").get<int>();
    return book;
}

std::string BookManager::bookToJson(std::vector<Book> &dbContent) {
    json JSbookArray = json::array();
    for (const auto& singleBook : dbContent) {
        JSbookArray.push_back({
            {"identifier", singleBook.identifier},
            {"title", singleBook.title},
            {"author", singleBook.author},
            {"genre", singleBook.genre},
            {"YearPublished", singleBook.YearPublished}
        });
    }
    return JSbookArray.dump();
}