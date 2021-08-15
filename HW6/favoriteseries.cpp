#include "favoriteseries.h"

FavoriteSeries::FavoriteSeries(string uName, string uSurname)
{
	userName = uName;
	userSurname = uSurname;
}

string FavoriteSeries::getFullName() const
{
	return userName + " " + userSurname;
}

void FavoriteSeries::addSeries(const series& s)
{
	favSeries.push_back(s);
}

bool FavoriteSeries::ifExists(int seriesCode)
{
	for (int f = 0; f < favSeries.size(); f++) {
		if (seriesCode == favSeries[f].seriesCode) {
			return true;
		}
	}
	return false;
}

bool FavoriteSeries::isListEmpty() const
{
	if (favSeries.size() == 0) {
		return true;
	}
	return false;
}

void FavoriteSeries::dropSeriesSorted(int c)
{
	for (int aa = 0; aa < favSeries.size(); aa++) {
		if (favSeries[aa].seriesCode == c) {
			favSeries.erase(favSeries.begin()+aa);
		}
	}
}

void FavoriteSeries::displayFavoriteList() const
{
	string s = "series.txt", e = "episodes.txt";
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
	ifstream inputE;
	string line2;

	inputE.open(e.c_str());
	while (getline(inputE, line2)) {
		string rdate, timeslot, episodeName;
		int code;
		episode tmp;
		istringstream lineInput(line2);
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
	vector <series> ss = favSeries;
	vector <episode> sortedEpisodes;
	for (int i = 0; i < ss.size(); i++) {
		for (int j = 0; j < ss[i].episodes.size(); j++) {
			sortedEpisodes.push_back(ss[i].episodes[j]);
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
	vector<episode> favepisodes = sortedEpisodes;
	string episodeseries;
	cout << "CODE,SERIES,EPISODE,DATE,SLOT" << endl;
	for (int i = 0; i < favepisodes.size(); i++) {
		for (int j = 0; j < serieslist.size(); j++) {
			if (favepisodes[i].seriesCode == serieslist[j].seriesCode) {
				episodeseries = serieslist[j].seriesName;
			}
		}
		cout << favepisodes[i].seriesCode << "," << episodeseries << "," << favepisodes[i].episodeName << "," << favepisodes[i].date << "," << favepisodes[i].slot << endl;
	}
}

void FavoriteSeries::displayFavoriteActors() const
{
	vector<actor> actorData;

	for (int gg = 0; gg < favSeries.size(); gg++) {
		for (int hh = 0; hh < favSeries[gg].actorNames.size(); hh++) {
			actor tempactor;
			bool found = false;
			for (int rr = 0; rr < actorData.size(); rr++) {
				if (favSeries[gg].actorNames[hh] == actorData[rr].name) {
					found = true;
					actorData[rr].screenCount++;
				}
			}
			if (!found) {
				tempactor.name = favSeries[gg].actorNames[hh];
				tempactor.screenCount = 1;
				actorData.push_back(tempactor);
			}
		}
	}

	int j, k, minIndex, numElts = actorData.size();
	actor temp;

	for (k = 0; k < numElts - 1; k++) {
		minIndex = k;
		for (j = k + 1; j < numElts; j++)
			if (actorData[j].screenCount > actorData[minIndex].screenCount) {
				minIndex = j;
			}
		temp = actorData[k];
		actorData[k] = actorData[minIndex];
		actorData[minIndex] = temp;
	}
	for (int jj = 0; jj < actorData.size() - 1; jj++) {
		for (int kk = jj + 1; kk < actorData.size(); kk++) {
			if (actorData[jj].screenCount == actorData[kk].screenCount && actorData[kk].name < actorData[jj].name) {
				swap(actorData[kk], actorData[jj]);
			}
		}
	}

	cout << userName << " " << userSurname << ", here is your favorite actors:" << endl;
	for (int ss = 0; ss < actorData.size(); ss++) {
		cout << actorData[ss].name << ": " << actorData[ss].screenCount << endl;
	}
}

bool FavoriteSeries::isConflict(const series& inSeries) const
{
	for (int m = 0; m < inSeries.episodes.size(); m++) {
		for (int g = 0; g < favSeries.size(); g++) {
			for (int h = 0; h < favSeries[g].episodes.size(); h++) {
				if (inSeries.episodes[m].date == favSeries[g].episodes[h].date && inSeries.episodes[m].slot == favSeries[g].episodes[h].slot)
					return true;
			}
		}
	}
	return false;
}

vector<episode> FavoriteSeries::sortEpisodes()
{
	vector <series> s = favSeries;
	vector <episode> sortedEpisodes;
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