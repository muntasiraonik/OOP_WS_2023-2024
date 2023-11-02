/**************************************************** **********************
Matr. no.: 3164924
Last name/Surname: Helal
First name/Given name: Muntasir Ebna
University email: muntasir.helal@stud.uni-duisburg-essen.de
Study program/Course of studies: Computer Engineering ISE, Vert. Software Engineering
************************************************** *********************/

#include <iostream>
using namespace std;

// Global integer variable
const int annual_average_cpp = 200;
const int annual_average_psm = 9;
const int annual_average_ped = 200;


struct household
{
    string city;
    int person;
    int sqr;
    int larger_electrical_device;
};

int calculate_annual_pcon(household &data)
{
    int power_consumption = (data.person * annual_average_cpp) + (data.sqr * annual_average_psm) + (data.larger_electrical_device * annual_average_ped);
    return power_consumption;
}

int calculate_annual_pcost(household &data, float price_of_kilowatt)
{
    int power_consumption = (data.person * annual_average_cpp) + (data.sqr * annual_average_psm) + (data.larger_electrical_device * annual_average_ped);
    int power_cost = power_consumption * price_of_kilowatt;
    return power_cost;
}

int print_household(household &data, float price_of_kilowatt)
{
    cout << "AVERAGE POWER COSTS" << endl;
    cout << "===================" << endl;
    cout << "household in: " << data.city << endl;
    cout << "square metres: " << data.sqr << endl;
    cout << "persons: " << data.person << endl;
    cout << "(major) electrical devices: " << data.larger_electrical_device << endl;
    cout << "price for one kWh: " << price_of_kilowatt << " EUR" << endl;
    cout << "annual power consumption: " << calculate_annual_pcon(data) << " kWh" << endl;
    cout << "annual power costs: " << calculate_annual_pcost(data, price_of_kilowatt) << " EUR" << endl  << endl;
    return 0;
}

int main()
{

    float price_of_one_kilowatt;
    cout << "CALCULATION OF AVERAGE POWER COSTS FOR A HOUSEHOLD" << endl;

    cout << "in which city is the household located? ";

    household household1;

    cin >> household1.city;

    cout << "how many square metres does the household have? ";
    cin >> household1.sqr;

    cout << "how many (major) electrical devices does the household have? ";
    cin >> household1.larger_electrical_device;

    cout << "how many EUR does one kWh in Duisburg cost? ";
    cin >> price_of_one_kilowatt;

    for (int n = 1; n <= 5; n++)
    {
        household1.person = n;
        print_household(household1, price_of_one_kilowatt);
    }

    return 0;
}