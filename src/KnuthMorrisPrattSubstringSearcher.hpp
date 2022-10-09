#pragma once
#include "SubstringSearcher.hpp"

class KnuthMorrisPrattSubstringSearcher : public SubstringSearcher {
private:
    std::function<void()> funcAfterCompare;
    const char separatorChar = '%';
    std::string substring;

    std::vector<int> prefixFunction(const std::string& string) const {
        auto result = std::vector<int>(string.length(), 0);

        for (size_t i = 1; i < string.length(); i++) {
            int j = result[i - 1];

            while (j > 0) {                   
                funcAfterCompare();
                if (string[i] != string[j])
                    j = result[j - 1];                          
                else 
                    break;
            }

            if (string[i] == string[j]) {
                result[i] = j + 1;
            }
            else {
                result[i] = j;
            }
            funcAfterCompare();
        }
        return result;
    }

public:
    KnuthMorrisPrattSubstringSearcher(std::function<void()> funcAfterCompare = []() {}) :
        funcAfterCompare(funcAfterCompare)
    {    }

    std::vector<SubstringSearcherResult> search(const std::string& substring, const std::string& text) const override {
        auto result = std::vector<SubstringSearcherResult>();
        auto pi = prefixFunction(substring + separatorChar + text);
        for (size_t i = 0; i < text.length(); i++) {
            if (pi[substring.length() + 1 + i] == substring.length())
                result.push_back(SubstringSearcherResult(text, substring, i - substring.length() + 1));
        }
        return result;
    }
};