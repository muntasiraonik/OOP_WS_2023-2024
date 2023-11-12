/**************************************************** **********************
Matr. no.: 3164924
Last name/Surname: Helal
First name/Given name: Muntasir Ebna
University email: muntasir.helal@stud.uni-duisburg-essen.de
Study program/Course of studies: Computer Engineering ISE, Vert. Software Engineering
************************************************** *********************/

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int number_of_days_in_a_year = 10;
const int number_of_qh_intervals_in_a_day = 12;

enum Use
{
    monday,
    tuesday,
    wednesday,
    thursday,
    friday,
    saturday,
    sunday,
    once,
    daily,
    mo_fr,
    sa_su

};

struct year
{
    int year_val;
    Use first_day_of_week;
    string unit_of_values_stored;
    float data[number_of_days_in_a_year][number_of_qh_intervals_in_a_day];
};

year &zeros(year &year)
{
    for (int day = 0; day < number_of_days_in_a_year; ++day)
    {
        for (int quarter_hour = 0; quarter_hour < number_of_qh_intervals_in_a_day; ++quarter_hour)
        {
            year.data[day][quarter_hour] = 0.0;
        }
    }
    return year;
}

inline int time(int h, int m)
{
    return h * 60 + m;
}

ostream &operator<<(ostream &os, Use &use)
{
    const char *use_strings[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday", "once", "daily", "mon_fri", "sat_sun"};
    os << use_strings[static_cast<int>(use)];
    return os;
}

Use operator++(Use &use)
{
    Use temp = use;
    use = static_cast<Use>((static_cast<int>(use) + 1) % 7);
    return temp;
}

Use next_day_of_week(Use day)
{
    return static_cast<Use>((static_cast<int>(day) + 1) % 7);
}

ostream &operator<<(ostream &os, year &year)
{

    os << "year: " << year.year_val << endl;

    Use current_day = year.first_day_of_week;

    for (int day = 0; day < number_of_days_in_a_year; ++day)
    {
        os << "day " << day << ": " << current_day << endl;

        for (int hour = 0; hour < 3; ++hour)
        {
            os << setw(2) << setfill(' ') << hour << ":00";
            for (int minute = 0; minute < 60; minute += 15)
            {
                os << fixed << setprecision(2) << setw(10) << year.data[day][4 * hour + minute / 15];
            }
            os << endl;
        }
        current_day = next_day_of_week(current_day);
    }

    return os;
}

year operator+(year &f, year &s)
{
    if (f.year_val == s.year_val &&
        f.first_day_of_week == s.first_day_of_week &&
        f.unit_of_values_stored == s.unit_of_values_stored)
    {
        year result = f;

        for (int i = 0; i < number_of_days_in_a_year; ++i)
        {
            for (int j = 0; j < number_of_qh_intervals_in_a_day; ++j)
            {
                result.data[i][j] += s.data[i][j];
            }
        }

        return result;
    }
    else
    {
        cerr << "Error: in Operator+" << endl;
        exit(EXIT_FAILURE);
    }
}

void add_consumption(year &y, int day, int from_hour, int from_minute, int to_hour, int to_minute, float watt)
{
    int from_minute_of_day = time(from_hour, from_minute);
    int to_minute_of_day = time(to_hour, to_minute);

    for (int minute = from_minute_of_day; minute < to_minute_of_day; ++minute)
    {
        int interval = minute / 15;
        y.data[day][interval] += watt / 60.0;
    }
}

void add_consumption(year &y, Use frequency, int from_hour, int from_minute, int to_hour, int to_minute, float watt)
{
    switch (frequency)
    {
    case monday:
    case tuesday:
    case wednesday:
    case thursday:
    case friday:
    case saturday:
    case sunday:
        for (int day = frequency; day < number_of_days_in_a_year; day += 7)
        {
            add_consumption(y, day, from_hour, from_minute, to_hour, to_minute, watt);
        }
        break;
    case once:
        add_consumption(y, 0, from_hour, from_minute, to_hour, to_minute, watt);
        break;
    case daily:
        for (int day = 0; day < number_of_days_in_a_year; ++day)
        {
            add_consumption(y, day, from_hour, from_minute, to_hour, to_minute, watt);
        }
        break;
    case mo_fr:
        for (int day = 0; day < number_of_days_in_a_year; ++day)
        {
            int days[7] = {0, 1, 2, 3, 4, 5, 6};
            int dayOfWeek = days[day % 7];
            if (dayOfWeek >= 0 && dayOfWeek <= 4)
            {

                add_consumption(y, day, from_hour, from_minute, to_hour, to_minute, watt);
            }
        }
        break;
    case sa_su:
        for (int day = 0; day < number_of_days_in_a_year; ++day)
        {
            int days[7] = {0, 1, 2, 3, 4, 5, 6};
            int dayOfWeek = days[day % 7];
            if (dayOfWeek == 5 || dayOfWeek == 6)
            {
                add_consumption(y, day, from_hour, from_minute, to_hour, to_minute, watt);
            }
        }
        break;
    default:
        cerr << "Invalid frequency of use." << endl;
        exit(EXIT_FAILURE);
    }
}

float sum(const year &y)
{
    float total = 0.0;

    for (int i = 0; i < number_of_days_in_a_year; ++i)
    {
        for (int j = 0; j < number_of_qh_intervals_in_a_day; ++j)
        {
            total += y.data[i][j];
        }
    }

    return total;
}

void input_use(string string, Use &frequency)
{
    cout << "Monday (0)" << endl;
    cout << "Tuesday (1)" << endl;
    cout << "Wednesday (2)" << endl;
    cout << "Thursday (3)" << endl;
    cout << "Friday (4)" << endl;
    cout << "Saturday (5)" << endl;
    cout << "Sunday (6)" << endl;
    cout << "daily (d)" << endl;
    cout << "mon_fri (m)" << endl;
    cout << "once (o)" << endl;
    cout << "sa_su (s)" << endl;
    cout << "weekly (w)" << endl;

    char choice;
    cin >> choice;

    if (choice == 'o')
    {
        cout << "on which day? ";
        cin >> choice;
    }

    switch (choice)
    {
    case '0':
        frequency = Use::monday;
        break;
    case '1':
        frequency = Use::tuesday;
        break;
    case '2':
        frequency = Use::wednesday;
        break;
    case '3':
        frequency = Use::thursday;
        break;
    case '4':
        frequency = Use::friday;
        break;
    case '5':
        frequency = Use::saturday;
        break;
    case '6':
        frequency = Use::sunday;
        break;
    case 'd':
        frequency = Use::daily;
        break;
    case 'm':
        frequency = Use::mo_fr;
        break;
    case 'o':
        frequency = Use::once;
        break;
    case 's':
        frequency = Use::sa_su;
        break;
    default:
        cout << "sorry wrong choice. Using 'once' by default." << endl;
        frequency = Use::once;
    }
}

int main()
{

    year actual = {2024, Use::monday, "Watt", {}};
    year total = {2024, Use::monday, "Watt", {}};

    zeros(actual);
    zeros(total);

    float price_of_one_kilowatt = 0.30;

    cout << "YEARLY CONSUMPTION QUARTER HOUR" << endl;
    char option;
    while (true)
    {

        cout << "q quit" << endl;
        cout << "a add actual to total (using operator +)" << endl;
        cout << "c annual consumption and cost (price for one kWh: 30.00 ct/kWh; calling function sum)" << endl;
        cout << "o output actual (using operator <<)" << endl;
        cout << "t output total (using operator <<)" << endl;
        cout << "u add consumption according to frequency of use (call functions add_consumption)" << endl;
        cout << "z set actual to zeros (call function zeros)" << endl;

        cin >> option;

        switch (option)
        {
        case 'a':
            total = total + actual;
            break;
        case 'c':

            cout << "sum actual = " << fixed << setprecision(2) << sum(actual)
                 << " Watt (costs: " << (sum(actual) / 1000) * price_of_one_kilowatt << " EUR)" << endl;
            cout << "sum total = " << fixed << setprecision(2) << sum(total)
                 << " Watt (costs: " << (sum(total) / 1000) * price_of_one_kilowatt << " EUR)" << endl;
            break;
        case 'o':
            cout << actual;
            break;
        case 't':
            cout << total;
            break;
        case 'u':
        {
            Use frequency;
            input_use("Enter the frequency of use: ", frequency);

            int from_hour, from_minute, to_hour, to_minute;
            float watt;

            cout << "from hour:minute? ";
            char colon;
            cin >> from_hour >> colon >> from_minute;
            cout << "to hour:minute? ";
            cin >> to_hour >> colon >> to_minute;

            cout << "how many watt it will have? ";
            cin >> watt;

            add_consumption(actual, frequency, from_hour, from_minute, to_hour, to_minute, watt);
        }
        break;
        case 'z':
            zeros(actual);
            break;
        case 'q':
            break;
        default:
            cout << "sorry wrong choice" << endl;
        }
    }
    while (option != 'q');

    return 0;
}