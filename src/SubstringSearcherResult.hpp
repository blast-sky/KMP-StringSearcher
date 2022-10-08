#pragma once
#include <string>


struct SubstringSearcherResult {
	
	const std::string& text;
	const std::string& substring;
	
	int startOffset;

	SubstringSearcherResult(const std::string& text, const std::string& substring, int startOffset) :
		text(text),
		substring(substring),
		startOffset(startOffset)
	{	}

	operator std::string() const {
		return std::to_string(startOffset);
	}
};