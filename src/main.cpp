#include <iostream>
#include <fstream>
#include <chrono>

#include "NaiveSubstringSearcher.hpp"
#include "KnuthMorrisPrattSubstringSearcher.hpp"

#include "ConsoleView.hpp"

std::string loadText(const std::string& path) {
	auto result = std::string();
	
	auto file = std::ifstream(path);
	auto buffer = std::string();

	while (std::getline(file, buffer)) {
		result += buffer;
	}

	return result;
}

void appendStringToFile(const std::string& filePath, const std::string& string) {
	auto file = std::ofstream(filePath, std::ios_base::app);
	file << string;
}

std::string generateString(size_t size) {
	auto result = std::string(size, 'a');
	for (size_t i = 0; i < size; i++) {
		int randomCharOrder = std::rand() % 4;
		char randomChar = 'a' + randomCharOrder;
		result[i] = randomChar;
	}
	return result;
}

void testSerchers(const std::string& substring, const std::string& filePostfix, std::function<std::string(int)> stringGenerator) {
	size_t compareCounter = 0;
	auto counter = [&]() { compareCounter++; };

	auto searchers = std::vector<SubstringSearcher*>();
	auto naive = NaiveSubstringSearcher(counter); searchers.push_back(&naive);
	auto knuth = KnuthMorrisPrattSubstringSearcher(counter); searchers.push_back(&knuth);

	auto timeMeasurements = std::vector<std::string>{ std::string(), std::string() };
	auto compareCountMeasurements = std::vector<std::string>{ std::string(), std::string() };
	for (size_t i = 3; i <= 7; i++) {
		auto text = stringGenerator(i);

		for (size_t i = 0; i < searchers.size(); i++) {
			compareCounter = 0;
			auto start = std::chrono::system_clock::now();
			auto results = searchers[i]->search(substring, text);
			auto end = std::chrono::system_clock::now();

			std::chrono::duration<double> diff = end - start;
			timeMeasurements[i] += std::to_string(diff.count()) + ';';
			compareCountMeasurements[i] += std::to_string(compareCounter) + ';';
		}
	}

	auto filePath = "time_measurements" + filePostfix + ".csv";
	auto file = std::ofstream(filePath, std::ios_base::app);
	file << timeMeasurements[0] << '\n' << timeMeasurements[1] << '\n';

	auto compareFilePath = "compare_count_measurements" + filePostfix + ".csv";
	auto ccfile = std::ofstream(compareFilePath, std::ios_base::app);
	ccfile << compareCountMeasurements[0] << '\n' << compareCountMeasurements[1] << '\n';
}

void testSerchersFair() {
	auto substring = "ababababa";
	testSerchers(substring, "", [](int i) { return generateString(std::pow(10, i)); });
}

void testSerchersUnfair() {
	auto substring = "aaaaaaaab";
	testSerchers(substring, "_unfair", [](int i) { return std::string(std::pow(10, i), 'a'); });
}

int main() {
	//testSerchersFair();
	//testSerchersUnfair();

	auto view = ConsoleView();
	view.interact();
	return 0;
}