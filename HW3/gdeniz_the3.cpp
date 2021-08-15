#include <iostream>
#include <string>
#include "strutils.h"

using namespace std;

string getInput() {
	string srcStr,strToAdd;
	bool controller = true;

	cin >> srcStr;

	while (controller) {
		cin >> strToAdd;
		if (LowerString(strToAdd) == "end") {
			return srcStr;
		}
		else {
			srcStr = srcStr + " " + strToAdd;
		}
	}
}

bool isSourceValid(string source) {
	for (int i = 0; i < source.length(); i++) {
		if (!( (source.at(i) == 32) || (source.at(i) >= '0' && source.at(i) <= '9') || (source.at(i) >= 'A' && source.at(i) <= 'Z') || (source.at(i) >= 'a' && source.at(i) <= 'z'))) {
			return false;
		}
	}
	return true;
}

string searchType(string search) {
	if (LowerString(search) == "quit") {
		return "quit";
	}
	if (search.substr(search.length() - 2, 2) == "**") {
		return "**";
	}
	if (search.substr(search.length() - 1, 1) == "*") {
		return "*"; 
	}
	if (search.substr(search.length() - 1, 1) == "+") {
		return "+";
	}
	if (search.substr(search.length() - 1, 1) == ".") {
		return ".";
	}
	else {
		return "none";
	}
}

string strippedSearchStr(string searchStr, string searchType) {
	if (searchType == "*" || searchType == "+" || searchType == ".") {
		return searchStr.substr(0, searchStr.length() - 1);
	}
	else if (searchType == "**") {
		return searchStr.substr(0, searchStr.length() - 2);
	}
}

void printResult(string searchStr, string sourceStr, string searchMode) {
	string searchStr2 = strippedSearchStr(searchStr, searchMode);
	string checkStr;
	int startIndex, currentWordStart, currentWordEnd;
	
	for (int index = 0; index <= sourceStr.length() - searchStr2.length(); index++) {
		checkStr = sourceStr.substr(index, searchStr2.length());

		if (checkStr == searchStr2) {
			startIndex = index;

			currentWordStart = sourceStr.rfind(' ', startIndex)+1 ;
			currentWordEnd = sourceStr.find(' ', startIndex)-1 ;

			if (searchMode == "**") {
				cout << "index: " << startIndex -1 << " ";
				cout << "word: " << sourceStr.substr(currentWordStart, (currentWordEnd - currentWordStart + 1)) << endl;
			}
			else if (searchMode == "*") {
				if (sourceStr.at(startIndex - 1) != ' ' && sourceStr.at(startIndex + searchStr2.length()) != ' ' && sourceStr.substr(currentWordStart, searchStr2.length()) != searchStr2 && sourceStr.substr(currentWordEnd-searchStr2.length()+1, searchStr2.length()) != searchStr2) {
					cout << "index: " << startIndex -1 << " ";
					cout << "word: " << sourceStr.substr(currentWordStart, (currentWordEnd - currentWordStart + 1)) << endl;
				}
			}
			else if (searchMode == ".") {
				if (sourceStr.at(startIndex + searchStr2.length()) == ' ') {
					cout << "index: " << startIndex -1 << " ";
					cout << "word: " << sourceStr.substr(currentWordStart, (currentWordEnd - currentWordStart + 1)) << endl;
				}
			}
			else if (searchMode == "+") {
				if (sourceStr.at(startIndex - 1) == ' ') {
					cout << "index: " << startIndex -1 << " ";
					cout << "word: " << sourceStr.substr(currentWordStart, (currentWordEnd - currentWordStart + 1)) << endl;
				}
			}
		}
	}	
}

int main() {
	string sourceStr, searchStr;
	bool isInvalidInput = true;
	bool searchOn = true;

	while (isInvalidInput) {

		isInvalidInput = true;
		cout << "Enter source string: ";
		sourceStr = getInput();

		if ((isSourceValid(sourceStr) == true)) {
			isInvalidInput = false;
		}
	}

	while (searchOn){

		cout << "Enter search string: ";
		cin >> searchStr;

		if (searchType(searchStr) == "quit") {
			searchOn = false;
		}
		else if (searchType(searchStr) == "none") {
		}
		else {
			printResult(searchStr, ' ' + sourceStr + ' ', searchType(searchStr));
		}
	}
	return 0;
}