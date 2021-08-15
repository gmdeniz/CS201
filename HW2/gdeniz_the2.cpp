#include <iostream>
#include <iomanip>
#include <string>
#include "strutils.h"

using namespace std;

bool check_input(string color, double height, double width, double length ) {
	if (height > 0 && width > 0 && length > 0) {
		return true;
	}
	return false;
}

void checkCubeandDisplay(string color, double height, double width, double length) {
	if (length = width && length == height) {
		cout << color << " cuboid is a cube." << endl << endl;
	}
	else {
		cout << color << " cuboid is not a cube." << endl << endl;
	}
}

void display(string color, double area, double volume) {
	cout << "Results for the " << color << " cuboid:" << endl << "Area: " << area << endl << "Volume: " << volume << endl;	
}

void calculate(string color, double width, double height, double length, double &area, double &volume) {
	volume = height * width * length;
	area = 2 * (height * width + width * length + height * length);

	display(color, area, volume);
	checkCubeandDisplay(color, height, width, length);
}

string compare(string colorA, string colorB, string metric, double areaA, double volumeA, double areaB, double volumeB) {
	if (metric == "Volume") {
		if (volumeA == volumeB) {
			return "Two cuboids have the same volume.";
		}
		else if (volumeA > volumeB) {
			return colorA + " has the largest volume.";
		}
		else {
			return colorB + " has the largest volume.";
		}
	}
	else if (metric == "Area") {
		if (areaA == areaB) {
			return "Two cuboids have the same area.";
		}
		else if (areaA > areaB) {
			return colorA + " has the largest area.";
		}
		else {
			return colorB + " has the largest area.";
		}
	}
}

int main() {
	cout.setf(ios::fixed);
	cout.precision(2);

	string color1, color2;
	double width1, height1, length1, width2, height2, length2, area, volume;
	double area1, volume1, area2, volume2;

	cout << "Hello! This program compares two cuboids..." << endl;

	cout << "Please enter colors for the two cuboids: ";
	cin >> color1 >> color2;

	if (LowerString(color1) == LowerString(color2)) {
		cout << "Color names cannot be the same, good bye..." << endl;
		return 0;
	}

	cout << "Please enter length, width and height of the " << color1 << " cuboid: ";
	cin >> length1 >> width1 >> height1;

	if (check_input(color1, height1, width1, length1) == false) {
		cout << "Invalid entry for " << color1 << " cuboid. Dimensions should be positive real numbers!"<< endl;
		return 0;
	}

	cout << "Please enter length, width and height of the " << color2 << " cuboid: ";
	cin >> length2 >> width2 >> height2;

	if (check_input(color2, height2, width2, length2) == false) {
		cout << "Invalid entry for " << color2 << " cuboid. Dimensions should be positive real numbers!" << endl;
		return 0;
	}
	
	calculate(color1, width1, height1, length1, area, volume);
	area1 = area;
	volume1 = volume;
	
	calculate(color2, width2, height2, length2, area, volume);
	area2 = area;
	volume2 = volume;

	cout << "Comparison of the two cuboids:" << endl;
	cout << compare(color1, color2, "Volume", area1, volume1, area2, volume2) << endl;
	cout << compare(color1, color2, "Area", area1, volume1, area2, volume2) << endl;

	return 0;
}