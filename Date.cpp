#include "Date.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <iomanip>
#include <sstream>

const int Date::daysInMonths[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

const string Date::monthsInstring[13] = {"", "January", "February", "March", "April", "May",
                                             "June", "July", "August", "September", "October", 
                                             "November", "December"};

Date::Date(int month, int day, int year) { setDate(month, day, year); }

void Date::setDate(const int month, const int day, const int year)
{
    setMonth(month);
    setYear(year);
    setDay(day);
}

void Date::setMonth(const int month)
{
    if(month >= 1 && month <= 12)
        this->month = month;
    else
        throw out_of_range("Month is out of range!");
}

void Date::setDay(const int day)
{
    if(isDayValid(day))
        this->day = day;
    else
        throw out_of_range("Day is out of range!");
}

void Date::setYear(const int year)
{
    if(year > 0)
        this->year = year;
    else 
        out_of_range("Year is out of range!");
}

string Date::getDate(void) const
{
    ostringstream output;
    output << this->getYear() << '/'
           << this->getMonth() << "/"
           << this->getDay();
    return output.str();
}

inline int Date::getMonth(void) const { return this->month; }

inline int Date::getDay(void) const { return this->day; }

inline int Date::getYear(void) const { return this->year; }

void Date::nextDay(void)
{    
    if(isEndOfYear())
    {
        ++this->year;
        this->day = 1;
        this->month = 1;
        return;
    }
    if(isEndOfMonth() && !isEndOfYear())
    {
        this->day = 1;
        ++this->month;
        return;
    }
    if(!isEndOfMonth() && !isEndOfYear())
    {
        ++this->day;    
        return;
    }
}

bool Date::isDayValid(int day) const
{
    if(day <= Date::daysInMonths[this->month])
        return true;
    if(day == 29 && this->month == 2 && isLeapYear())
        return true;
    return false;
}

bool Date::isLeapYear(void) const
{
    if((this->year % 400 == 0) || 
       (this->year % 100 != 0  &&  this->year % 4 == 0))
        return true;
    return false;
}

bool Date::isEndOfMonth(void) const
{
    if(this->day == 29 && this->month == 2 && isLeapYear())
        return true;
    if(this->day == Date::daysInMonths[this->month])
        return true;
    return false;
}

bool Date::isEndOfYear(void) const
{
    if(isEndOfMonth() && this->month == 12)
        return true;
    return false;
}

Date& Date::operator+=(const unsigned int daysToAdd)
{
    for(int i = 0; i < daysToAdd; ++i)
        nextDay();
    return *this;
}

Date& Date::operator++(void)
{
    nextDay();
    return *this;
}

Date Date::operator++(int)
{
    Date temp = *this;
    nextDay();
    return temp;
}

bool Date::operator>(const Date& right) const
{
    if(this->getYear() > right.getYear())
        return true;
    if(this->getYear() < right.getYear())
        return false;
    if(this->getYear() == right.getYear())
    {
        if(this->getMonth() > right.getMonth())
            return true;
        if(this->getMonth() < right.getMonth())
            return false;
        if(this->getMonth() == right.getMonth())
        {
            if(this->getDay() > right.getDay())
                return true;
            else
                return false;
        }
    }
}

bool Date::operator<=(const Date& right) const { return !(*this > right); }

bool Date::operator==(const Date& right) const
{
    return this->getYear() == right.getYear()   &&
           this->getMonth() == right.getMonth() &&
           this->getDay() == right.getDay();
}

istream& operator>>(istream& input, Date& date)
{
    string month;
    string year;
    string day;

    input >> setw(4) >> year;
    input.ignore();
    input >> setw(2) >> month;
    input.ignore();
    input >> setw(2) >> day;

    date.setMonth(stoi(month));
    date.setYear(stoi(year));
    date.setDay(stoi(day));

    return input;
}

ostream& operator<<(ostream& output, const Date& date)
{
    output << date.getDate();
    return output;
}

ofstream& operator<<(ofstream& output, const Date& date)
{
    output << date.getDate();
    return output;
}