#ifndef DATE_H
#define DATE_H

#pragma once

#include <iostream>

using namespace std;

class Date
{
    friend istream& operator>>(istream&, Date&);
    friend ostream& operator<<(ostream&, const Date&);
    friend ofstream& operator<<(ofstream&, const Date&);

public:
    Date(int = 1, int = 1, int = 1900);
    
    void setDate(const int, const int, const int);
    void setMonth(const int);
    void setDay(const int);
    void setYear(const int);

    string getDate(void) const;
    inline int getMonth(void) const;
    inline int getDay(void) const;
    inline int getYear(void) const;

    void nextDay(void);

    Date& operator+=(const unsigned int);
    Date& operator++();
    Date operator++(int);

    bool operator==(const Date&) const;
    bool operator>(const Date&) const;
    bool operator<=(const Date&) const;

private:
    int month;
    int day;
    int year;
    const static int daysInMonths[13];
    const static string monthsInstring[13];

    bool isDayValid(int) const;
    bool isLeapYear(void) const;
    bool isEndOfMonth(void) const;
    bool isEndOfYear(void) const;
};

#endif