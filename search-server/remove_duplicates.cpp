#include "remove_duplicates.h"

using namespace std;

void RemoveDuplicates(SearchServer& search_server) {

    set<int> duplicates;

    set<set<string>> docs;

    for (auto it = search_server.begin(); it != search_server.end(); ++it) {
        const auto& doc = search_server.GetWordFrequencies(*it);

        set<string> doc_words;

        for (const auto& [word, freq] : doc) {
            doc_words.insert(word);
        }

        if (docs.count(doc_words)) {
            duplicates.insert(*it);
        }

        else {
            docs.insert(doc_words);
        }
    }

    for (auto id : duplicates) {
        cout << "Found duplicate document id "s << id << endl;
        search_server.RemoveDocument(id);
    }
}
