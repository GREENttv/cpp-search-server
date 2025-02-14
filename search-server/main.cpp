//Вставьте сюда своё решение из урока «Очередь запросов» темы «Стек, очередь, дек».
#include <iostream>
#include "document.h"
#include "search_server.h"
#include "paginator.h"
#include "request_queue.h"
#include "read_input_functions.h"
#include "string_processing.h"   

using namespace std;

int main() {
    {
       
        SearchServer search_server("и в на"s);
        search_server.AddDocument(1, "пушистый кот пушистый хвост"s,
                                  DocumentStatus::ACTUAL, {7, 2, 7});
        search_server.AddDocument(2, "пушистый пёс и модный ошейник"s,
                                  DocumentStatus::ACTUAL, {1, 2, 3});
        search_server.AddDocument(3, "большой кот модный ошейник "s,
                                  DocumentStatus::ACTUAL, {1, 2, 8});
        search_server.AddDocument(4, "большой пёс скворец евгений"s,
                                  DocumentStatus::ACTUAL, {1, 3, 2});
        search_server.AddDocument(5, "большой пёс скворец василий"s,
                                  DocumentStatus::ACTUAL, {1, 1, 1});

        const auto search_results = search_server.FindTopDocuments("пушистый пёс"s);
        int page_size = 2;
        const auto pages = Paginate(search_results, page_size);

        for (auto page = pages.begin(); page != pages.end(); ++page) {
            cout << *page << endl;
            cout << "Разрыв страницы"s << endl;
        }
    }

    cout << "\n----- Jetzt Beispiel aus der Aufgabe -----\n\n"s;

    {
       
        SearchServer search_server("and in at"s);
        RequestQueue request_queue(search_server);

        search_server.AddDocument(1, "curly cat curly tail"s, 
                                  DocumentStatus::ACTUAL, {7, 2, 7});
        search_server.AddDocument(2, "curly dog and fancy collar"s, 
                                  DocumentStatus::ACTUAL, {1, 2, 3});
        search_server.AddDocument(3, "big cat fancy collar "s, 
                                  DocumentStatus::ACTUAL, {1, 2, 8});
        search_server.AddDocument(4, "big dog sparrow Eugene"s, 
                                  DocumentStatus::ACTUAL, {1, 3, 2});
        search_server.AddDocument(5, "big dog sparrow Vasiliy"s, 
                                  DocumentStatus::ACTUAL, {1, 1, 1});

    
        for (int i = 0; i < 1439; ++i) {
            request_queue.AddFindRequest("empty request"s);
        }

     
        request_queue.AddFindRequest("curly dog"s);
        request_queue.AddFindRequest("big collar"s);
        request_queue.AddFindRequest("sparrow"s);

        cout << "Total empty requests: "s
             << request_queue.GetNoResultRequests() << endl;
    }

    return 0;
}
