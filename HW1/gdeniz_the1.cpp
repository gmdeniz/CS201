#include <iostream>
#include <string>
//Mirac Deniz Gozen - 27806
using namespace std;

int main() {

	string studentName, courseCode, firstTime, currentGrade, switchGrade, previousGrade, selectedGrade;

	cout << "Welcome to the Fall 2020-2021 Semester grading system. What is your name? ";
	cin >> studentName;

	cout << "Hello " << studentName << "! Please enter the name of the course to be processed: ";
	cin >> courseCode;

	cout << "Hello " << studentName << "! If you take the " << courseCode << " for the first time, enter YES otherwise NO: ";
	cin >> firstTime;

	if (firstTime == "YES" || firstTime == "NO") {
		if (firstTime == "YES") {
			cout << "What is your grade from (A,B,C,D,F)? ";
			cin >> currentGrade;			
			if (currentGrade == "A" || currentGrade == "B" || currentGrade == "C" || currentGrade == "D" || currentGrade == "F") {
				if (currentGrade == "A" || currentGrade == "B" || currentGrade == "C" || currentGrade == "D") {
					cout << "Do you want to switch your grade from " << currentGrade << " to S (YES or NO)? ";
					cin >> switchGrade;
					if (switchGrade == "YES" || switchGrade == "NO") {
						if (switchGrade == "YES") {
							cout << studentName << ", your final grade for " << courseCode << " is S. Goodbye..." << endl;
							return 0;
						}
						else if (switchGrade == "NO") {
							cout << studentName << ", your final grade for " << courseCode << " is " << currentGrade << ". Goodbye..." << endl;
							return 0;
						}
					}
					else {						
						cout << "Invalid grade selection. Goodbye..." << endl;
						return 0;
					}
				}
				else if (currentGrade == "F") {
					cout << "Do you want to switch your grade from F to U (YES or NO)? ";
					cin >> switchGrade;
					if (switchGrade == "YES" || switchGrade == "NO") {
						if (switchGrade == "YES") {
							cout << studentName << ", your final grade for " << courseCode << " is U. Goodbye..." << endl;
							return 0;
						}
						else if (switchGrade == "NO") {
							cout << studentName << ", your final grade for " << courseCode << " is F. Goodbye..." << endl;
						}
					}
					else {
						cout << "Invalid grade selection. Goodbye..." << endl;
						return 0;
					}
				}
			}
			else {				
				cout << "Invalid grade selection. Goodbye..." << endl;
				return 0;
			}
		}
		else if (firstTime == "NO") {
			cout << "Please enter your previous grade from (A,B,C,D,F,S,U): " ;
			cin >> previousGrade;
			if (previousGrade == "A" || previousGrade == "B" || previousGrade == "C" || previousGrade == "D" || previousGrade == "F" || previousGrade == "S" || previousGrade == "U") {
				cout << "Please enter your current grade from (A,B,C,D,F): ";
				cin >> currentGrade;
				if (currentGrade == "A" || currentGrade == "B" || currentGrade == "C" || currentGrade == "D" || currentGrade == "F" ) {
					cout << "Please enter the grade you want to choose from (A,B,C,D,F,S,U): ";
					cin >> selectedGrade;
					if (currentGrade == "A" || currentGrade == "B" || currentGrade == "C" || currentGrade == "D") {
						if (selectedGrade == currentGrade || selectedGrade == "S") {
							cout << studentName << ", your final grade for " << courseCode << " is " << selectedGrade << ". Goodbye..." << endl;
							return 0;
						}
						else if (previousGrade == "U") {
							cout << "Invalid grade selection. If you received U before, you may choose S or current letter grade." << endl;				
							return 0;
						}
						else if ( selectedGrade == "A" || selectedGrade == "B" || selectedGrade == "C" || selectedGrade == "D" || selectedGrade == "F" || selectedGrade == "S" || selectedGrade == "U"){
							cout << "Invalid grade selection. You cannot choose a higher or lower grade than you deserve." << endl;
							return 0;
						}
						else {
							cout << "Invalid grade selection.Goodbye..." << endl;	
							return 0;
						}
					}
					else if (currentGrade == "F") {
						if (selectedGrade != "A" && selectedGrade != "B" && selectedGrade != "C" && selectedGrade != "D" && selectedGrade != "F" && selectedGrade != "S" && selectedGrade != "U" ) {
							cout << "Invalid grade selection.Goodbye..." << endl;
							return 0;
						}
						if (previousGrade == "A" || previousGrade == "B" || previousGrade == "C" || previousGrade == "D") {
							if (selectedGrade == "F" || selectedGrade == "U") {
								cout << studentName << ", your final grade for " << courseCode << " is " << selectedGrade << ". Goodbye..." << endl;
								return 0;
							}
							else if (selectedGrade == "A" || selectedGrade == "B" || selectedGrade == "C" || selectedGrade == "D") {
								cout << "Invalid grade selection. You cannot choose a higher or lower grade than you deserve." << endl;
								return 0;
							}
						}
						else if (previousGrade == "F")  {
							if (selectedGrade == "F" ) {
								cout << studentName << ", your final grade for " << courseCode << " is F. Goodbye..." << endl;
								return 0;
							}
							else {
								cout << "Invalid grade selection. If you received " << previousGrade << " before, and fail this semester, you get F." << endl;
								return 0;
							}
						}
						else if (previousGrade == "S") {
							if (selectedGrade == "F") {
								cout << studentName << ", your final grade for " << courseCode << " is F. Goodbye..." << endl;
								return 0;
							}
							else {
								cout << "Invalid grade selection. If you received " << previousGrade << " before and fail this semester, you get F." << endl;
								return 0;
							}
						}
						else if (previousGrade == "U") {
							if (selectedGrade == "F" || selectedGrade == "U") {
								cout << studentName << ", your final grade for " << courseCode << " is "<< selectedGrade << ". Goodbye..." << endl;
								return 0;
							}
							else {
								cout << "Invalid grade selection. If you received " << previousGrade << " before and fail this semester, you get F." << endl;
								return 0;
							}
						}
					}
				}
				else {
					cout << "Invalid grade selection. Goodbye..." << endl;
					return 0;
				}
			}
			else {
				cout << "Invalid grade selection. Goodbye..." << endl;
				return 0;
			}
		}
	}
	else {
		return 0;
	}
}