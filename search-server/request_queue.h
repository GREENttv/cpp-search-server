//Вставьте сюда своё решение из урока «Очередь запросов» темы «Стек, очередь, дек».
#pragma once

#include <deque>
#include <string>
#include <vector>
#include "search_server.h"
#include "document.h"

class RequestQueue {
public:
    explicit RequestQueue(const SearchServer& search_server);

    template <typename DocumentPredicate>
    std::vector<Document> AddFindRequest(const std::string& raw_query,
                                         DocumentPredicate document_predicate);

    std::vector<Document> AddFindRequest(const std::string& raw_query,
                                         DocumentStatus status);

    std::vector<Document> AddFindRequest(const std::string& raw_query);

    int GetNoResultRequests() const;

private:
    struct QueryResult {
        int time;
        bool is_empty;
    };

    std::deque<QueryResult> requests_;
    const SearchServer& search_server_;
    int current_time_;
    int no_results_count_;
    static const int min_in_day_ = 1440;

    void RemoveOldRequests();
};


template <typename DocumentPredicate>
std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query,
                                                   DocumentPredicate document_predicate)
{
    std::vector<Document> result = search_server_.FindTopDocuments(raw_query, document_predicate);
    ++current_time_;
    RemoveOldRequests();
    bool empty = result.empty();
    requests_.push_back({current_time_, empty});
    if (empty) {
        ++no_results_count_;
    }
    return result;
}
