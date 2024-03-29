#include "process_queries.h" 
#include <algorithm> 
#include <execution>

std::vector<Document> ProcessQueriesJoined(const SearchServer& search_server, const std::vector<std::string>& queries) { std::vector<std::vector<Document>> documents_lists = ProcessQueries(search_server, queries); size_t total_docs = 0; for (const auto& doc_list : documents_lists) { total_docs += doc_list.size(); }

std::vector<Document> documents;
documents.reserve(total_docs);
for (const auto& doc_list : documents_lists) {
    for (const auto& doc : doc_list) {
        documents.push_back(doc);
    }
}

return documents;
}

std::vector<std::vector<Document>> ProcessQueries(const SearchServer& search_server, const std::vector<std::string>& queries) {
   
std::vector<std::vector<Document>> result(queries.size()); std::transform(std::execution::par, queries.begin(), queries.end(), result.begin(), [&](const std::string& query) { return search_server.FindTopDocuments(query); }); return result; 
}