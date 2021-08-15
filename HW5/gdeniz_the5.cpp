#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "strutils.h"
#include <sstream>

using namespace std;

struct series {
	int rank;
	string name, actor;
	double points;
};

int countLines(string filename) {
	ifstream inputC;
	int noOfLines = 0;
	string lineC;
	inputC.open(filename.c_str());
	while (getline(inputC, lineC)) {
		noOfLines++;
	}
	inputC.close();
	return noOfLines;
}

void SelectSort(vector<series>& a) {

	int j, k, minIndex, numElts = a.size();
	series temp;

	for (k = 0; k < numElts - 1; k++) {
		minIndex = k;          
		for (j = k + 1; j < numElts; j++) {
			if (a[j].points > a[minIndex].points) {
				minIndex = j;
			}
		}
		temp = a[k];         
		a[k] = a[minIndex];
		a[minIndex] = temp;
	}
	int chck;
	for (int jj = 0; jj < a.size()-1 ; jj++) {
		chck = jj;
		for (int kk = jj + 1; kk < a.size(); kk++) {
			if (a[jj].points == a[kk].points && a[kk].name < a[jj].name) {
				swap(a[kk], a[jj]);
			}
		}
	}
}

vector<series> formList(string asfile, string rfile) {
	vector<series> seriesData(countLines(asfile));
	ifstream inputF;
	string line;
	int mode = 1, eIndex = 0;
	inputF.open(asfile.c_str());
	while (getline(inputF, line)) {

		istringstream lineInput(line);
		string element;
		int mode = 1;

		while (getline(lineInput >> ws, element, ';')) {
			if (mode == 1) {
				seriesData[eIndex].actor = element;
				mode = 2;
			}
			else if (mode == 2) {
				seriesData[eIndex].name = element;
				mode = 1;
				eIndex++;
			}
		}
	}
	inputF.close();

	string name;
	for (int i = 0; i < seriesData.size(); i++) {

		double pointSum = 0.0, point;
		inputF.open(rfile.c_str());
		int reviewCount = 0;

		while (getline(inputF, line)) {
			istringstream lineInput(line);
			string element;
			int mode = 1;
			while (getline(lineInput >> ws, element, '\t')) {
				if (mode == 1) {
					point = stod(element);
					mode = 2;
				}

				else if (mode == 2) {
					name = element;
					mode = 1;
				}
			}
			if (UpperString(seriesData[i].name) == UpperString(name)) {
				reviewCount++;
				pointSum += point;
			}
		}
		seriesData[i].points = pointSum / reviewCount;
		inputF.close();
	}
	SelectSort(seriesData);

	for (int j = 0; j < seriesData.size(); j++) {
		seriesData[j].rank = j + 1;
	}
	return seriesData;
}

string fileNameReader(string readMode) {

	ifstream input;
	string fileName;
	bool awaitValidName = true;

	cout << "Please enter a filename for " << readMode << " file: ";
	cin >> fileName;

	while (awaitValidName) {
		input.open(fileName.c_str());
		if (input.fail()) {
			cout << "Can not find the specified file." << endl;
			cout << "Please enter a filename for " << readMode << " file: ";
			cin >> fileName;
		}
		else {
			awaitValidName = false;
			input.close();
			return fileName;
		}
	}
}

int main() {
	cout << "Welcome to Netflix TV Series Ratings Calculator!" << endl;

	string seriesActorFile = fileNameReader("Series-Actor");
	string ratingFile = fileNameReader("Rating");
	int programMode = 0;
	bool controller = true;
	vector<series> favlist;
	vector<series> slst = formList(seriesActorFile, ratingFile);

	while (controller) {

		cout << "---" << endl << "MENU" << endl;
		cout << "1. Print the series" << endl;
		cout << "2. Search the series according to the rating" << endl;
		cout << "3. Add the series to the favorite list" << endl;
		cout << "4. Print the favorite list" << endl;
		cout << "5. Exit" << endl;
		cout << "---" << endl << "Enter your choice: ";
		cin >> programMode;
		cout << "---" << endl;
		
		if (cin.fail()) {
			string dmp3;
			cin.clear();
			cin >> dmp3;
		}
		else if (programMode == 1) {
			cout << "RANK,NAME,ACTOR,POINTS" << endl;
			for (int k = 0; k < slst.size(); k++) {
				cout << slst[k].rank << ',' << UpperString(slst[k].name) << ',' << UpperString(slst[k].actor) << ',' << slst[k].points << endl;
			}
		}
		else if (programMode == 2) {
			double minRating;
			cout << "Please enter the minimum rating: ";
			cin >> minRating;
			if (cin.fail()) {
				string dmp2;
				cin.clear();
				cin >> dmp2;
				cout << "This is not a valid rating!" << endl;
			}
			else if (minRating > 10 || minRating < 0) {
				cout << "This is not a valid rating!" << endl;
			}
			else {
				cout << "RANK,NAME,ACTOR,POINTS" << endl;
				for (int k = 0; k < slst.size(); k++) {
					if (slst[k].points >= minRating) {
						cout << slst[k].rank << ',' << UpperString(slst[k].name) << ',' << UpperString(slst[k].actor) << ',' << slst[k].points << endl;
					}
				}
			}
		}
		else if (programMode == 3) {
			string addSeries, dmp;
			bool match = false, infavlist = false;
			cout << "Please enter the name of series: ";
			getline(cin, dmp);
			cin.clear();
			getline(cin,addSeries);

			for (int kk = 0; kk < favlist.size(); kk++) {
				if (UpperString(favlist[kk].name) == UpperString(addSeries)) {
					infavlist = true;
				}
			}
			if (infavlist) {
				cout << "Your favorite list already have " << UpperString(addSeries) << endl;
			}
			else {
				for (int kk = 0; kk < slst.size(); kk++) {
					if (UpperString(slst[kk].name) == UpperString(addSeries)) {
						match = true;
						favlist.push_back(slst[kk]);
					}
				}
				if (match) {
					SelectSort(favlist);
				}
				else {
					cout << "There is no such TV series!" << endl;
				}
			}
		}
		else if (programMode == 4) {
			if (favlist.empty()) {
				cout << "Your favorite list is currently empty!" << endl;
			}
			else {
				cout << "RANK,NAME,ACTOR,POINTS" << endl;
				for (int k = 0; k < favlist.size(); k++) {
					cout << k+1 << ',' << UpperString(favlist[k].name) << ',' << UpperString(favlist[k].actor) << ',' << favlist[k].points << endl;
				}
			}
		}
		else if (programMode == 5) {
			controller = false;
		}
		else {
			cout << "This is not a valid option!" << endl;
		}
	}
	return 0;
}