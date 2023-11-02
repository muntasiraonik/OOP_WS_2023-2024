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
const int annual_avverage_cpp_with_ewh = 550;

struct household
{
    string city;
    int person;
    int sqr;
    int larger_electrical_device;
    bool water_is_heated_electrically;
};

int calculate_annual_pcon(household &data)
{
    int power_consumption;
    if (data.water_is_heated_electrically)
    {
        power_consumption = (data.person * annual_avverage_cpp_with_ewh) + (data.sqr * annual_average_psm) + (data.larger_electrical_device * annual_average_ped);
    }
    else
    {

        power_consumption = (data.person * annual_average_cpp) + (data.sqr * annual_average_psm) + (data.larger_electrical_device * annual_average_ped);
    }

    return power_consumption;
}

int calculate_annual_pcost(household &data, float price_of_kilowatt)
{
    
    double power_cost = calculate_annual_pcon(data) * price_of_kilowatt;

    cout << power_cost << endl;
    return power_cost;
}

void input_city(string &city_name)
{
    cout << "in which city is the household located? ";
    cin >> city_name;
}

void input_integer(string prompt, int &value)
{

    cout << prompt;
    cin >> value;
}

void input_electric_water_heating(bool &water_is_heated_electrically)
{
    cout << "is hot water heated using electricity? (y(es) or n(o)) ";
    char hot_water_choice;
    cin >> hot_water_choice;

    if (hot_water_choice == 'y')
    {
        water_is_heated_electrically = true;
    }
    else if (hot_water_choice == 'n')
    {
        water_is_heated_electrically = false;
    }
}

int print_household(household &data, float price_of_kilowatt)
{
    string yes_no;

    if (data.water_is_heated_electrically)
    {
        yes_no = "yes";
    }
    else
    {
        yes_no = "no";
    }

    cout << "AVERAGE POWER COSTS" << endl;
    cout << "===================" << endl;
    cout << "household in: " << data.city << endl;
    cout << "square metres: " << data.sqr << endl;
    cout << "persons: " << data.person << endl;
    cout << "electrical devices: " << data.larger_electrical_device << endl;
    cout << "water heated using electricity: " << yes_no << endl;
    cout << "price for one kWh: " << price_of_kilowatt << " EUR" << endl;
    cout << "annual power consumption: " << calculate_annual_pcon(data) << " kWh" << endl;
    cout << "annual power costs: " << calculate_annual_pcost(data, price_of_kilowatt) << " EUR" << endl
         << endl;
    return 0;
}

int main()
{

    float price_of_one_kilowatt;
    cout << "CALCULATION OF AVERAGE POWER COSTS FOR A HOUSEHOLD" << endl;

    household household1;
    input_city(household1.city);

    input_integer("how many square metres does the household have? ", household1.sqr);
    input_integer("how many (major) electrical devices does the household have? ", household1.larger_electrical_device);

    input_electric_water_heating(household1.water_is_heated_electrically);

    for (int n = 1; n <= 5; n++)
    {
        household1.person = n;

        for (int j = 1; j <= 3; j++)
        {
            if (j == 1)
            {
                price_of_one_kilowatt = 0.3;
            }
            else if (j == 2)
            {
                price_of_one_kilowatt = 0.35;
            }
            else if (j == 3)
            {
                price_of_one_kilowatt = 0.4;
            }

            print_household(household1,price_of_one_kilowatt);
           
        }
    }

    return 0;
}