#include <iostream>
#include <ctime>
using namespace std;

class Date {
private:
    int day;
    int month;
    int year;

public:
    Date(int d, int m, int y)
        : day{ d }, month{ m }, year{ y } {
    }

    int getDay() const { return day; }
    int getMonth() const { return month; }
    int getYear() const { return year; }

    long timeInSeconds() const {
        struct tm timeinfo = { 0 };
        timeinfo.tm_mday = day;
        timeinfo.tm_mon = month - 1; 
        timeinfo.tm_year = year - 1900;  
        timeinfo.tm_isdst = -1;
        return mktime(&timeinfo);
    }

    friend long operator-(const Date& lhs, const Date& rhs) {
        return (lhs.timeInSeconds() - rhs.timeInSeconds()) / (24 * 3600);
    }

    void operator+=(int days) {
        struct tm timeinfo = { 0 };
        timeinfo.tm_mday = day;
        timeinfo.tm_mon = month - 1;
        timeinfo.tm_year = year - 1900;
        timeinfo.tm_isdst = -1;

        time_t current_time = mktime(&timeinfo);
        current_time += days * 24 * 3600;  
        struct tm* new_date = localtime(&current_time);

        day = new_date->tm_mday;
        month = new_date->tm_mon + 1;
        year = new_date->tm_year + 1900;
    }

    friend std::ostream& operator<<(std::ostream& os, const Date& d) {
        return os << '(' << d.day << '.' << d.month << '.' << d.year << ')';
    }
};

int main() {
    Date date1(10, 10, 2010);
    Date date2(20, 12, 2019);

    // Разница между датами
    long difference = date2 - date1;
    cout << "Разница между датами: " << difference << " дней.\n";

    date1 += 100;
    cout << "Дата после увеличения на 100 дней: " << date1 << '\n';

    return 0;
}