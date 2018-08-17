#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct date
{
    int day;
    int month;
    int year;
} Date;

void next_date(Date *date);
bool is_leap_year(int year);
int days_in_month(int month, int year);

void test(void);
void test_is_leap_year(void);
void test_days_in_month(void);

int main(void)
{
    test_is_leap_year();
    test_days_in_month();
    test();
    printf("\nAll tests passed!\n");
    return 0;
}

void next_date(Date *date)
{
    int day = date->day;
    int month = date->month;
    int year = date->year;

    int days_in_curr_month = days_in_month(month, year);
    day++;
    if (day > days_in_curr_month) {
        month++;
        day = 1;
        if (month > 12) {
            year++;
            month = 1;
        }
    }

    date->day = day;
    date->month = month;
    date->year = year;
}

void test(void)
{
    Date *date = (Date *)malloc(sizeof(Date));

    date->day = 31;
    date->month = 12;
    date->year = 2016;
    next_date(date);
    assert(date->day == 1 && date->month == 1 && date->year == 2017);

    date->day = 31;
    date->month = 12;
    date->year = 2017;
    next_date(date);
    assert(date->day == 1 && date->month == 1 && date->year == 2018);

    date->day = 28;
    date->month = 2;
    date->year = 2016;
    next_date(date);
    assert(date->day == 29 && date->month == 2 && date->year == 2016);

    date->day = 28;
    date->month = 2;
    date->year = 2017;
    next_date(date);
    assert(date->day == 1 && date->month == 3 && date->year == 2017);

    date->day = 31;
    date->month = 1;
    date->year = 2017;
    next_date(date);
    assert(date->day == 1 && date->month == 2 && date->year == 2017);


    date->day = 30;
    date->month = 6;
    date->year = 2015;
    next_date(date);
    assert(date->day == 1 && date->month == 7 && date->year == 2015);

    date->day = 30;
    date->month = 7;
    date->year = 1975;
    next_date(date);
    assert(date->day == 31 && date->month == 7 && date->year == 1975);

    date->day = 31;
    date->month = 7;
    date->year = 1975;
    next_date(date);
    assert(date->day == 1 && date->month == 8 && date->year == 1975);

    date->day = 31;
    date->month = 8;
    date->year = 1975;
    next_date(date);
    assert(date->day == 1 && date->month == 9 && date->year == 1975);

    date->day = 30;
    date->month = 8;
    date->year = 1975;
    next_date(date);
    assert(date->day == 31 && date->month == 8 && date->year == 1975);

    free(date);

    printf("Next date tests passed!\n");
}

void test_is_leap_year(void)
{
    assert(is_leap_year(0) == true);
    assert(is_leap_year(3) == false);
    assert(is_leap_year(4) == true);
    assert(is_leap_year(1600) == true);
    assert(is_leap_year(1700) == false);
    assert(is_leap_year(1800) == false);
    assert(is_leap_year(1900) == false);
    assert(is_leap_year(1975) == false);
    assert(is_leap_year(1976) == true);
    assert(is_leap_year(2000) == true);
    assert(is_leap_year(2004) == true);
    assert(is_leap_year(2015) == false);
    assert(is_leap_year(2016) == true);
    assert(is_leap_year(2017) == false);

    printf("Leap year tests passed!\n");
}

void test_days_in_month(void)
{
    assert(days_in_month(1, 2015) == 31);
    assert(days_in_month(2, 2015) == 28);
    assert(days_in_month(3, 2015) == 31);
    assert(days_in_month(4, 2015) == 30);
    assert(days_in_month(5, 2015) == 31);
    assert(days_in_month(6, 2015) == 30);
    assert(days_in_month(7, 2015) == 31);
    assert(days_in_month(8, 2015) == 31);
    assert(days_in_month(9, 2015) == 30);
    assert(days_in_month(10, 2015) == 31);
    assert(days_in_month(11, 2015) == 30);
    assert(days_in_month(12, 2015) == 31);

    assert(days_in_month(1, 2016) == 31);
    assert(days_in_month(2, 2016) == 29);
    assert(days_in_month(3, 2016) == 31);
    assert(days_in_month(4, 2016) == 30);
    assert(days_in_month(5, 2016) == 31);
    assert(days_in_month(6, 2016) == 30);
    assert(days_in_month(7, 2016) == 31);
    assert(days_in_month(8, 2016) == 31);
    assert(days_in_month(9, 2016) == 30);
    assert(days_in_month(10, 2016) == 31);
    assert(days_in_month(11, 2016) == 30);
    assert(days_in_month(12, 2016) == 31);

    printf("Days in a month tests passed!\n");
}

bool is_leap_year(int year)
{
    if (year % 400 == 0)
        return true;

    if (year % 100 == 0)
        return false;

    if (year % 4 == 0)
        return true;

    return false;
}

int days_in_month(int month, int year)
{
    switch (month) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return 31;

        case 4:
        case 6:
        case 9:
        case 11:
            return 30;

        case 2:
            if (is_leap_year(year))
                return 29;
            else
                return 28;

        default:
            return 30;
    }
}

