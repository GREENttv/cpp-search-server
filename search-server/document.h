//Вставьте сюда своё решение из урока «Очередь запросов» темы «Стек, очередь, дек».‎
#pragma once
#include <ostream>


enum class DocumentStatus {
    ACTUAL,
    IRRELEVANT,
    BANNED,
    REMOVED,
};


struct Document {
    Document() = default;
    Document(int id, double relevance, int rating);

    int id = 0;
    double relevance = 0.0;
    int rating = 0;
};


std::ostream& operator<<(std::ostream& out, const Document& document);
