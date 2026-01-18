#include <iostream>
using namespace std;

class Time {
    private:
        int hour;
        int minute;
        int second;

    public:
        Time (int _hour, int _minute, int _second) {
            this->hour = _hour;
            this->minute = _minute;
            this->second = _second;
        }

        void setTime (int _hour, int _minute, int _second) {
            this->hour = _hour;
            this->minute = _minute;
            this->second = _second;
        }

        void setHour (int _hour) { this->hour = _hour; }
        void setMinute (int _minute) { this->minute = _minute; }
        void setSecond (int _second) { this->second = _second; }

        int getHour() { return hour; }
        int getMinute() { return minute; }
        int getSecond() { return second; }

        void nextSecond() {
            second++;
            if (second == 60) {
                second = 0;
                minute++;
                if (minute == 60) {
                    minute = 0;
                    hour++;
                    if (hour == 24) {
                        hour = 0;
                    }
                }
            }
        }

        void previousSecond() {
            second--;
            if (second == -1) {
                second = 59;
                minute--;
                if (minute == -1) {
                    minute = 59;
                    hour--;
                    if (hour == -1) {
                        hour = 23;
                    }
                }
            }
        }

        void display() { 
            string time;
            time = time + (hour < 10 ? "0" : "") + to_string(hour) + ":";
            time = time + (minute < 10 ? "0" : "") + to_string(minute) + ":";
            time = time + (second < 10 ? "0" : "") + to_string(second);
            cout << time << endl;
        }
};

int main () {
    Time t(12, 1, 1);
	t.display();
	t.setTime(23, 59, 59);
	t.display();
	t.nextSecond();
	t.display();
	t.nextSecond();
	t.display();
	t.setTime(7, 0, 0);
	t.display();
	t.previousSecond();
	t.display();
	return 0;
}