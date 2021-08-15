#include <iostream>
#include <string>
#include "favoriteseries.h"
#include "strutils.h"
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

vector <series> readFromSeriesFileToList(string s) {
	vector <series> serieslist;
	ifstream inputS;
	string line;
	inputS.open(s.c_str());
	while (getline(inputS, line)) {
		series seriesToAdd;
		istringstream lineInput(line);
		string splitLine;
		int smode = 1;

		while (getline(lineInput >> ws, splitLine, ';')) {

			istringstream splitlineInput(splitLine);

			if (smode == 1) {
				string seriesNameToAdd;
				splitlineInput >> seriesToAdd.seriesCode;
				getline((splitlineInput) >> ws, seriesNameToAdd);
				seriesToAdd.seriesName = UpperString(seriesNameToAdd);
				smode = 2;
			}

			else if (smode == 2) {
				vector <string> actors;
				string actor;
				while (getline(splitlineInput >> ws, actor, ',')) {
					StripWhite(actor);
					actors.push_back(UpperString(actor));
				}
				seriesToAdd.actorNames = actors;
			}
		}
		serieslist.push_back(seriesToAdd);
	}
	inputS.close();
	return serieslist;
}

vector<series> formSeriesList(string s, string e) {
	vector<series> serieslist = readFromSeriesFileToList(s);
	ifstream inputE;
	string line;

	inputE.open(e.c_str());
	while (getline(inputE, line)) {
		string rdate, timeslot, episodeName;
		int code;
		episode tmp;
		istringstream lineInput(line);
		int month, day, year;
		string dmp;
		lineInput >> code;
		lineInput >> rdate;
		lineInput >> timeslot;
		timeslot = UpperString(timeslot);
		getline(lineInput >> ws, episodeName);
		episodeName = UpperString(episodeName);
		istringstream dateInput(rdate);
		getline(dateInput, dmp, '/');
		month = stoi(dmp);
		getline(dateInput, dmp, '/');
		day = stoi(dmp);
		getline(dateInput, dmp, '/');
		year = stoi(dmp);

		for (int j = 0; j < serieslist.size(); j++) {
			if (code == serieslist[j].seriesCode) {
				StripWhite(episodeName);
				tmp.date = Date(month, day, year);
				tmp.slot = timeslot;
				tmp.seriesCode = code;
				tmp.episodeName = episodeName;
				serieslist[j].episodes.push_back(tmp);
			}
		}
	}
	return serieslist;
}

vector<episode> episodeListByDate(vector<series> s) {
	vector<episode> sortedEpisodes;
	for (int i = 0; i < s.size(); i++) {
		for (int j = 0; j < s[i].episodes.size(); j++) {
			sortedEpisodes.push_back(s[i].episodes[j]);
		}
	}
	int a, b, minIndex, numElts = sortedEpisodes.size();
	episode temp;

	for (a = 0; a < numElts - 1; a++) {
		minIndex = a;
		for (b = a + 1; b < numElts; b++)
			if (sortedEpisodes[b].date < sortedEpisodes[minIndex].date) {
				minIndex = b;
			}
		temp = sortedEpisodes[a];
		sortedEpisodes[a] = sortedEpisodes[minIndex];
		sortedEpisodes[minIndex] = temp;
	}

	for (int jj = 0; jj < sortedEpisodes.size() - 1; jj++) {
		for (int kk = jj + 1; kk < sortedEpisodes.size(); kk++) {
			if (sortedEpisodes[jj].date == sortedEpisodes[kk].date && sortedEpisodes[kk].slot == "MORNING") {
				swap(sortedEpisodes[kk], sortedEpisodes[jj]);
			}
			else if (sortedEpisodes[jj].date == sortedEpisodes[kk].date && sortedEpisodes[kk].slot == "AFTERNOON" && sortedEpisodes[jj].slot != "MORNING") {
				swap(sortedEpisodes[kk], sortedEpisodes[jj]);
			}
			else if (sortedEpisodes[jj].date == sortedEpisodes[kk].date && sortedEpisodes[kk].slot == "EVENING" && sortedEpisodes[jj].slot != "MORNING" && sortedEpisodes[jj].slot != "AFTERNOON") {
				swap(sortedEpisodes[kk], sortedEpisodes[jj]);
			}
		}
	}

	for (int jj = 0; jj < sortedEpisodes.size() - 1; jj++) {
		for (int kk = jj + 1; kk < sortedEpisodes.size(); kk++) {
			if (sortedEpisodes[jj].date == sortedEpisodes[kk].date && sortedEpisodes[kk].slot == sortedEpisodes[jj].slot && sortedEpisodes[kk].seriesCode < sortedEpisodes[jj].seriesCode) {
				swap(sortedEpisodes[kk], sortedEpisodes[jj]);
			}
		}
	}
	return sortedEpisodes;
}

int main() {
	string uSurname, uName, episodesfile = "episodes.txt", seriesfile = "series.txt";
	bool on = true;
	int programMode;
	vector<series> serieslist = formSeriesList(seriesfile, episodesfile);

	cout << "Welcome to my favorite TV series schedule program!" << endl;
	cout << "Please, enter your name and surname: ";
	cin >> uName;
	uName = UpperString(uName);
	getline(cin >> ws, uSurname);
	uSurname = UpperString(uSurname);
	FavoriteSeries favseries(uName, uSurname);

	while (on) {

		cout << "---" << endl << "MENU" << endl;
		cout << "1. Print all TV series" << endl;
		cout << "2. Add TV series" << endl;
		cout << "3. Drop TV series" << endl;
		cout << "4. Print your favorite series with schedule" << endl;
		cout << "5. Print all your favorite actors" << endl;
		cout << "6. Exit" << endl;
		cout << "---" << endl << "Please enter your choice: ";
		cin >> programMode;

		if (programMode == 1) {
			vector<episode> episodelist = episodeListByDate(serieslist);
			string episodeseries;
			cout << "CODE,SERIES,EPISODE,DATE,SLOT" << endl;
			for (int i = 0; i < episodelist.size(); i++) {
				for (int j = 0; j < serieslist.size(); j++) {
					if (episodelist[i].seriesCode == serieslist[j].seriesCode) {
						episodeseries = serieslist[j].seriesName;
					}
				}
				cout << episodelist[i].seriesCode << "," << episodeseries << "," << episodelist[i].episodeName << "," << episodelist[i].date << "," << episodelist[i].slot << endl;
			}
		}
		else if (programMode == 2) {
			series sToAdd;
			int addCode;
			cout << "Enter code for the TV series you want to add: ";
			cin >> addCode;

			if (favseries.ifExists(addCode)) {
				cout << favseries.getFullName() << ", you can't add this TV series because you already added it!" << endl;
			}
			else {
				bool found = false;
				for (int e = 0; e < serieslist.size(); e++) {
					if (addCode == serieslist[e].seriesCode) {
						sToAdd = serieslist[e];
						found = true;
					}
				}
				if (found) {
					if (favseries.isConflict(sToAdd)) {
						cout << favseries.getFullName() << ", you can't add this TV series because of a date and slot conflict!" << endl;
					}
					else {
						favseries.addSeries(sToAdd);
						cout << favseries.getFullName() << ", " << sToAdd.seriesName << " added to your schedule." << endl;
					}
				}
				else {
					cout << favseries.getFullName() << ", there is no such TV series in the database!" << endl;
				}
			}
		}
		else if (programMode == 3) {
			if (favseries.isListEmpty()) {
				cout << favseries.getFullName() << ", you did not add any TV series yet!" << endl;
			}
			else {
				series sToRemove;
				int removeCode;
				cout << "Enter code for the TV series you want to drop: ";
				cin >> removeCode;

				for (int ee = 0; ee < serieslist.size(); ee++) {
					if (removeCode == serieslist[ee].seriesCode) {
						sToRemove = serieslist[ee];
					}
				}
				if (favseries.ifExists(removeCode)) {
					favseries.dropSeriesSorted(removeCode);
					cout << favseries.getFullName() << ", " << sToRemove.seriesName << " has been dropped from your favorite list!" << endl;
				}
				else {
					cout << favseries.getFullName() << ", there is no such TV series in your favorite list!" << endl;
				}
			}
		}
		else if (programMode == 4) {
			if (favseries.isListEmpty()) {
				cout << favseries.getFullName() << ", you did not add any TV series yet!" << endl;
			}
			else {
				cout << favseries.getFullName() << ", here is your favorite TV series:" << endl;
				favseries.displayFavoriteList();
			}
		}
		else if (programMode == 5) {
			if (favseries.isListEmpty()) {
				cout << favseries.getFullName() << ", you did not add any TV series yet!" << endl;
			}
			else {
				favseries.displayFavoriteActors();
			}
		}
		else if (programMode == 6) {
			cout << "Goodbye, " << favseries.getFullName() << "!" << endl;
			on = false;
		}
		else {
			cout << "Invalid option!" << endl;
		}
	}
	return 0;
}