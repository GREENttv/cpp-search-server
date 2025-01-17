//Вставьте сюда своё решение из урока «Очередь запросов» темы «Стек, очередь, дек».‎
#include "request_queue.h"

RequestQueue::RequestQueue(const SearchServer& search_server)
    : search_server_(search_server)
    , current_time_(0)
    , no_results_count_(0)
{
}

std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query,
                                                   DocumentStatus status)
{
    return AddFindRequest(raw_query, 
        [status](int, DocumentStatus document_status, int) {
            return document_status == status;
        }
    );
}

std::vector<Document> RequestQueue::AddFindRequest(const std::string& raw_query) {
    return AddFindRequest(raw_query, DocumentStatus::ACTUAL);
}

int RequestQueue::GetNoResultRequests() const {
    return no_results_count_;
}

void RequestQueue::RemoveOldRequests() {
    while (!requests_.empty() && requests_.front().time <= current_time_ - min_in_day_) {
        if (requests_.front().is_empty) {
            --no_results_count_;
        }
        requests_.pop_front();
    }
}
