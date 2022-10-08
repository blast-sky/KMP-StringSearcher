#pragma once
#include <string>
#include <vector>
#include <functional>

#include "SubstringSearcherResult.hpp"

class SubstringSearcher {
public:
	virtual std::vector<SubstringSearcherResult> search(const std::string& substring, const std::string& text) const = 0;
};