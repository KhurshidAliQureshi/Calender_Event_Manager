#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <cmath>
#include <fstream>

using namespace std;

string ToString(int val)
{
	stringstream stream;
	stream << val;
	return stream.str();
}

struct enteredDate {
	int day;
	int month;
	int year;
	int weekday;

	enteredDate() {
		day = 1;
		month = 1;
		year = 1754;
		weekday = dow(day, month, year);
	};

	string getDate() {
		return (ToString(day) + "." + ToString(month) + "." + ToString(year));
	};

	bool setDate(int dy, int mth, int yr) {
		if (isLeapYear(yr) == true && mth == 2 && dy > 29) {
			cout << "Invalid Date Entered." << endl;
			return false;
		}
		else if (isLeapYear(yr) == false && mth == 2 && dy > 28) {
			cout << "Invalid Date Entered." << endl;
			return false;
		}
		else if (dy > 31 && (mth == 1 || mth == 3 || mth == 5 || mth == 7 || mth == 8 || mth == 10 || mth == 12)) {
			cout << "Invalid Date Entered." << endl;
			return false;
		}
		else if (dy > 30 && !(mth == 1 || mth == 3 || mth == 5 || mth == 7 || mth == 8 || mth == 10 || mth == 12)) {
			cout << "Invalid Date Entered." << endl;
			return false;
		}
		else if (dy < 1) {
			cout << "Invalid Date Entered." << endl;
			return false;
		}

		if (mth > 12 || mth < 1) {
			cout << "Invalid Date Entered." << endl;
			return false;
		}


		if (yr < 1754 || yr > 9999) {
			cout << "Invalid Date Entered." << endl;
			return false;
		}

		day = dy;
		month = mth;
		year = yr;
		weekday = dow(day, month, year);
		return true;
	};

	void incrementDate() {
		if (isLeapYear(year) == true && month == 2 && day == 28) {
			day++;
		}
		else if (isLeapYear(year) == true && month == 2 && day == 29) {
			day = 1;
			incrementMonth();
		}
		else if (isLeapYear(year) == false && month == 2 && day == 28) {
			day = 1;
			incrementMonth();
		}
		else if (day == 30 && (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)) {
			day++;
		}
		else if (day == 30 && !(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)) {
			day = 1;
			incrementMonth();
		}
		else if (day == 31) {
			day = 1;
			incrementMonth();
		}
		else {
			day++;
		}
		weekday = dow(day, month, year);
	};

	void incrementMonth() {
		if (month == 12) {
			month = 1;
			year++;
		}
		else {
			month++;
		}
	};


	bool isLeapYear(int year)
	{
		if (year % 4 != 0)
			return false;
		if (year % 100 != 0)
			return true;
		if (year % 400 == 0)
			return true;
		else
			return false;
	}

	int dow(int d, int m, int y) {

		int temp = ((d += m < 3 ? y-- : y - 2, 23 * m / 9 + d + 4 + y / 4 - y / 100 + y / 400) % 7);

		if (temp == 0) return 7;
		else return temp;

	};

	string getDay(int wkday) {
		string temp;
		switch (wkday)
		{
		case 1:
			temp = "[Mon]";
			break;
		case 2:
			temp = "[Tue]";
			break;
		case 3:
			temp = "[Wed]";
			break;
		case 4:
			temp = "[Thu]";
			break;
		case 5:
			temp = "[Fri]";
			break;
		case 6:
			temp = "[Sat]";
			break;
		case 7:
			temp = "[Sun]";
			break;
		default:
			break;
		}
		return temp;
	};

	int getLastDay() {
		if (isLeapYear(year) == true && month == 2) {
			return 29;
		}
		else if (isLeapYear(year) == false && month == 2) {
			return 28;
		}
		else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
			return 31;
		}
		else {
			return 30;
		}
	};

};

class EventSpec {
public:
	int day;
	int month;
	int year;
	int weekDay;
	string event;

};

string repalceChars(string str_in, string to_replace, string replacement)
{
	for (int i = 0; i < (signed)str_in.length(); i++)
	{
		if (str_in.substr(i, 1) == to_replace) {
			str_in.replace(i, 1, replacement);
		};
	}

	return str_in;
}

int SDTI(string SD) {
	int temp = -9;

	if (SD == "Mon") temp = 1;
	else if (SD == "Tue") temp = 2;
	else if (SD == "Wed") temp = 3;
	else if (SD == "Thu") temp = 4;
	else if (SD == "Fri") temp = 5;
	else if (SD == "Sat") temp = 6;
	else if (SD == "Sun") temp = 7;
	else if (SD == "0") temp = 0;

	return temp;

};

int StringToNumber (const string &Text )
{
	istringstream ss(Text);
	int result;
	return ss >> result ? result : 0;
}

int main()
{
	
	bool isFileValid = false;
	string fileName = "Events.dat";
	
	ifstream fileReader(".\\Events.dat");
	
	while(!isFileValid){
		if(fileReader.is_open()){
			isFileValid = true;
			continue;
		};
		cout << "invalid file, Please place file in project directory and enter name" << endl;
		cin >> fileName;
		fileName = ".\\" + fileName;
		fileReader.close();
		fileReader.clear();
		fileReader.open(fileName.c_str());
	};

	string line;



	int pos1, pos2, pos3, pos4;

	int d, m, y;
	string dayOfWeek, eventInput;

	int counter = 0;
	int index = 0;


	if (fileReader.is_open()) {
		while (getline(fileReader, line))
		{
			if (line.substr(0, 1) == "#" || line == "") {
				continue;
			}
			counter++;
		}
	};
	fileReader.clear();
	fileReader.seekg(0);

	EventSpec * z = new EventSpec[counter + 1];



	if (fileReader.is_open()) {
		while (getline(fileReader, line)) {
			if (line.substr(0, 1) == "#" || line == "") {
				continue;
			}

			line = repalceChars(line, "*", "0");
			line = repalceChars(line, "$", "-1");

			pos1 = line.find(".");
			pos2 = line.find(".", pos1 + 1);
			pos3 = line.find(":", pos2 + 1);
			pos4 = line.find(":", pos3 + 1);

			d = StringToNumber(line.substr(0, pos1));
			m = StringToNumber(line.substr(pos1 + 1, (pos2 - pos1)));
			y = StringToNumber(line.substr(pos2 + 1, pos3 - pos2 - 1));
			dayOfWeek = line.substr(pos3 + 1, pos4 - pos3 - 1);
			eventInput = line.substr(pos4 + 1);

			//cout << d << m << y << dayOfWeek << eventInput << endl;
			z[index++] = { d, m, y, SDTI(dayOfWeek), eventInput };
		};
		fileReader.close();
		z[index] = { 0, 0, 0, 0, "end_of_array" };
	}
	else {
		cout << "Can't open the file." << endl;
	}

	enteredDate x;


	bool flag = true;
	int day, month, year;

	while (flag) {
		cout << "Enter a valid Day" << endl;
		cin >> day;
		cout << endl;
		cout << "Enter a valid month" << endl;
		cin >> month;
		cout << endl;
		cout << "Enter a valid Year" << endl;
		cin >> year;
		cout << endl;


		if (x.setDate(day, month, year) == true) {
			for (int i = 0; i < 7; i++) {
				int j = 0;
				string currentEvents = "";

				while (z[j].event != "end_of_array") {


					if (x.year == z[j].year || z[j].year == 0) { //same year or any year
						if (x.month == z[j].month || z[j].month == 0) {//same month or any month
							if (x.day == z[j].day || z[j].day == 0) {//same day or any day
								if (x.weekday == z[j].weekDay || z[j].weekDay == 0) {//same weekday
									if (currentEvents == "") {
										currentEvents = z[j].event;
									}
									else {
										currentEvents = currentEvents + ", " + z[j].event;
									}
								}
							}


							if (z[j].day == -1) {
								if (x.day == x.getLastDay()) {
									if (x.weekday == z[j].weekDay || z[j].weekDay == 0) {
										if (currentEvents == "") {
											currentEvents = z[j].event;
										}
										else {
											currentEvents = currentEvents + ", " + z[j].event;
										}
									}
								}
							}
						}
					}
					j++;
				}

				cout << x.getDate() + " " + x.getDay(x.weekday) + " " + currentEvents << endl;
				x.incrementDate();
			};
			flag = false;
		}
		else {
			cout << "Invalid Date Entered." << endl;
		}

	};

	delete[] z;

	std::system("PAUSE");

	return 0;

}



