#pragma once
#include <string_view>

#include "SubstringSearcher.hpp"

class NaiveSubstringSearcher : public SubstringSearcher {
private:
	std::function<void()> funcAfterCompare;

	bool isEquals(const std::string_view& string1, const std::string_view& string2) const {
		if (string1.size() != string2.size()) return false;
		for (size_t i = 0; i < string1.size(); i++){
			funcAfterCompare();
			if (string1[i] != string2[i]) return false;
		}
		return true;
	}

public:
	NaiveSubstringSearcher(std::function<void()> funcAfterCompare = []() {}) :
		funcAfterCompare(funcAfterCompare)
	{	}

	std::vector<SubstringSearcherResult> search(const std::string& substring, const std::string& text) const override {
		auto result = std::vector<SubstringSearcherResult>();
		for (int i = 0; i < text.length() - substring.length() + 1; i++) {
			auto slicedString = std::string_view(text.data() + i, substring.length());
			if (isEquals(slicedString, substring)) {
				result.push_back(SubstringSearcherResult(text, substring, i));
			}
		}
		return result;
	}
};