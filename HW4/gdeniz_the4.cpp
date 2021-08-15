#include <iostream>
#include <string>
#include <fstream>
#include "strutils.h"
#include <sstream>

using namespace std;

string readFileName(string mode) {
	
	ifstream input;
	string filename;
	bool awaitCorrectFormat = true;

	cout << "Please enter a filename for the "<< mode << ": ";
	cin >> filename;

	while (awaitCorrectFormat) {
		input.open(filename.c_str());
		if (input.fail()) {
			cout << "Cannot open the " << mode << " file." << endl;
			cout << "Please enter a filename for the " << mode << ": ";
			cin >> filename;
		}
		else {
			awaitCorrectFormat = false;
			input.close();
			return filename;
		}
	}
}

string poolStr(string poolName) {

	ifstream poolInput;
	string poolStr;

	poolInput.open(poolName.c_str());

	while (!poolInput.eof()) {
		string word;
		poolInput >> word;
		poolStr += word + ' ';
	}
	poolStr.substr(0, poolStr.length() - 1);
	poolInput.close();
	return LowerString(poolStr);
}

bool spellCheck(string word, string pool) {
	if (pool.find(word) != string::npos) {
		return true;
	}
	return false;
}

string checkWord(string word, string pool){

	istringstream poolCheck(pool);
	string checkword, correctedline;
	double halfCount = word.length() / 2.0;
	bool foundMatch = false;
	int maxSimilar = 0, count = 0;

	while (poolCheck >> checkword) {
		int similarities = 0;
		if (checkword.length() == word.length()) {
			for (int i = 0; i < word.length(); i++) {
				if (checkword[i] == word[i]) {
					similarities += 1;
				}
			}
			if (similarities >= halfCount) {
				if (similarities > maxSimilar) {
					maxSimilar = similarities;
					count = 0;
					foundMatch = true;
					correctedline = "";
					correctedline += checkword + ",";
					count++;
				}
				else if (similarities == maxSimilar) {
					foundMatch = true;
					correctedline += checkword + ",";
					count++;
				}
			}
		}
	}
	if (foundMatch && count == 1) {
		return correctedline.substr(0, correctedline.length() - 1);
	}
	else if (foundMatch) {
		return "(" + correctedline.substr(0, correctedline.length() - 1) + ")";
	}
	else {
		return "{" + word + "}";
	}
}

int main() {

	string poolName = readFileName("word pool");
	string mainName = readFileName("main text");
	string lineM;
	ifstream mainInput;

	mainInput.open(mainName.c_str());
	cout << "You may find the results below:" << endl << endl;
	while (getline(mainInput, lineM)) {
		istringstream lineInput(lineM);
		string word, newline = "";
		while (lineInput >> word) {
			if (spellCheck(LowerString(word), poolStr(poolName))) {
				newline += LowerString(word) + ' ';
			}
			else {
				newline += checkWord(LowerString(word), poolStr(poolName)) + ' ';
			}
		}
		cout << newline.substr(0, newline.length() - 1) << endl;
	}
	mainInput.close();
	return 0;
}