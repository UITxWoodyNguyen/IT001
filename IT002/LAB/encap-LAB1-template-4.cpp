#include <iostream>
using namespace std;

class Date {
    private:
        int day;
        int month;
        int year;

    public: 
        Date (int _day, int _month, int _year) {
            this->day = _day;
            this->month = _month;
            this->year = _year;
        }

        void setDate (int _day, int _month, int _year) {
            this->day = _day;
            this->month = _month;
            this->year = _year;
        }

        void setDay (int _day) { this->day = _day; }
        void setMonth (int _month) { this->month = _month; }
        void setYear (int _year) { this->year = _year; }

        int getDay() { return day; }
        int getMonth() { return month; }
        int getYear() { return year; }
        void display() { 
            string date;
            date = date + (day < 10 ? "0" : "") + to_string(day) + "/";
            date = date + (month < 10 ? "0" : "") + to_string(month) + "/";
            date = date + to_string(year);
            cout << date << endl;
        }
};

int main () {
    Date d(1, 1, 1997);
	d.display();
	d.setDate(12, 12, 2004);
	d.display();
	d.setMonth(3);
	d.display();	
	return 0;
}