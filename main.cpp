/*
** MY_PROJECT, 2025
** main.cpp
** )
** Author: Enam KODJOH-KPAKPASSOU
** Email: eakodjoh-kpakpassou@st.ug.edu.gh
** File description:
*/

#include <saucer/smartview.hpp>
#include "include_cpp/my.h"
#include "embedded/all.hpp"

int main()
{
    auto app = saucer::application::init({      // Instantiate application
        .id = "104SemProject",                    // Choose a suitable ID for your program
    });

    saucer::smartview smartview{{
        .application = app,
    }};

    smartview.set_title("DCIT104 SEMESTER PROJECT");

    // Expose a synchronous native function "add_ten" using the default serializer
    smartview.expose("create_book", BookManager::create_entity);
    smartview.expose("update_book", BookManager::update_book);
    smartview.expose("delete_book", BookManager::delete_book);
    smartview.expose("fetchItems", BookManager::get_books);

    smartview.embed(saucer::embedded::all());
    smartview.serve("index.html");
    smartview.show();

    app->run();

    return 0;
}
