#pragma once
#include <iostream>
#include <string>
#include <functional>
#include <chrono>
#include <iomanip>

#include "NaiveSubstringSearcher.hpp"
#include "KnuthMorrisPrattSubstringSearcher.hpp"

class ConsoleView {
private:
	
	double measureTime(std::function<void(void)> block) {
		auto start = std::chrono::system_clock::now();
		block();
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> diff = end - start;
		return diff.count();
	}

	void clearConsole() {
		system("cls");
	}

	void pauseConsole() {
		system("pause");
	}

	std::string generateString(size_t size, size_t alphabetSize) {
		auto result = std::string(size, 'a');
		for (size_t i = 0; i < size; i++) {
			int randomCharOrder = std::rand() % alphabetSize;
			char randomChar = 'a' + randomCharOrder;
			result[i] = randomChar;
		}
		return result;
	}

	std::string getInteractString(size_t alphabetSize) {
		std::string result;

		bool isOkAnswer = false;
		while (!isOkAnswer) {
			std::cout << "1) Enter the word" << '\n';
			std::cout << "2) Generate word from alphabet size k" << '\n';
			std::cout << "3) Generate (B1 B2 .. Bs)^k word" << "\n\n";

			std::cout << "Answer: ";
			std::string answer;
			std::cin >> answer;

			isOkAnswer = true;
			clearConsole();

			if (answer == "1") {
				std::cout << "Enter the word: ";
				std::cin >> result;
			}
			else if (answer == "2") {
				std::cout << "Enter size of the word: ";
				int k;
				std::cin >> k;
				result = generateString(k, alphabetSize);
			}
			else if (answer == "3") {
				std::cout << "Enter k: ";
				int k;
				std::cin >> k;

				std::cout << "\nEnter (B1 B2 .. Bs) string: ";
				std::string string;
				std::cin >> string;

				for (int i = 0; i < k; i++) {
					result += string;
				}
			}
			else {
				std::cout << "Not available answer\n";
				pauseConsole();
				isOkAnswer = false;
			}
		}
		return result;
	}


public:
	
	void interact() {
		int alphabetSize;
		std::cout << "Enter alphabet size: ";
		std::cin >> alphabetSize;
		clearConsole();

		std::cout << "Substring parameters\n\n";
		std::string substring = getInteractString(alphabetSize);
		clearConsole();

		std::cout << "Text parameters\n\n";
		std::string text = getInteractString(alphabetSize);
		clearConsole();

		std::cout << std::fixed << std::setprecision(6);

		SubstringSearcher* sercher = new NaiveSubstringSearcher();
		std::cout << "Naive time: " << measureTime([&]() {
			sercher->search(substring, text);
		}) << '\n';
		delete sercher;

		sercher = new KnuthMorrisPrattSubstringSearcher();
		std::cout << "KMP time: " << measureTime([&]() {
			sercher->search(substring, text);
		}) << '\n';
		delete sercher;

		pauseConsole();
	}
};