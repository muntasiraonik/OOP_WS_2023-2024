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

const int annual_average_cpp = 200;
const int annual_average_psm = 9.0;
const int annual_average_ped = 200;
const int annual_avverage_cpp_with_ewh = 550;
const int column_width = 35;
float price_of_one_kilowatt = 0;

enum Use
{
    once,
    daily,
    mo_fr,
    sa_su,
    weekly
};

void input_use(string string, Use &frequency)
{
    cout << "daily (d)" << endl;
    cout << "mon_fri (m)" << endl;
    cout << "once (o)" << endl;
    cout << "sa_su (s)" << endl;
    cout << "weekly (w)" << endl;

    char choice;
    cin >> choice;

    switch (choice)
    {
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
    case 'w':
        frequency = Use::weekly;
        break;
    default:
        cout << "Invalid choice. Using 'once' by default." << endl;
        frequency = Use::once;
    }
}

struct consumer
{
    string description;
    float watt;
    float watt_standby;
    float hours;
    Use use;
    consumer *next;
};

struct household
{
    string city;
    int people;
    int sqr;
    bool hot_water_electric;
    consumer *consumers;
};

void add_consumer_to_household(household *household1, consumer *consumer1)
{
    if (household1 == nullptr || consumer1 == nullptr)
    {
        cerr << "Invalid household or consumer pointer." << endl;
        return;
    }

    consumer1->next = household1->consumers;
    household1->consumers = consumer1;
}

float annual_hours_of_use(consumer *consumer1)
{
    switch (consumer1->use)
    {
    case Use::once:
        return consumer1->hours;
    case Use::daily:
        return consumer1->hours * 365.0;
    case Use::mo_fr:
        return consumer1->hours * 260.0;
    case Use::sa_su:
        return consumer1->hours * 104.0;
    case Use::weekly:
        return consumer1->hours * 52.0;
    default:
        return 0.0;
    }
}

float annual_hours_of_standby(consumer *consumer1)
{
    return 8760.0 - annual_hours_of_use(consumer1);
}

float annual_kWh(consumer *consumer1)
{
    float annual_use_hours = annual_hours_of_use(consumer1);
    float annual_standby_hours = annual_hours_of_standby(consumer1);
    float consumption = (annual_use_hours * consumer1->watt + annual_standby_hours * consumer1->watt_standby) / 1000.0;
    return consumption;
}

consumer *move_up(consumer *firstConsumer, int k)
{
    if (firstConsumer == nullptr || k <= 1)
    {
        return firstConsumer;
    }

    if (k == 2)
    {
        consumer *currentConsumer = firstConsumer->next;
        firstConsumer->next = currentConsumer->next;
        currentConsumer->next = firstConsumer;
        return currentConsumer;
    }

    consumer *prevConsumer = firstConsumer;
    consumer *currentConsumer = firstConsumer->next;
    int position = 2;

    while (currentConsumer != nullptr)
    {
        if (position == k)
        {
            prevConsumer->next = currentConsumer->next;
            currentConsumer->next = prevConsumer->next;
            prevConsumer->next = currentConsumer;
            return firstConsumer;
        }

        prevConsumer = currentConsumer;
        currentConsumer = currentConsumer->next;
        position++;
    }

    return firstConsumer;
}

void print_consumer(consumer *consumer1, int number)
{
    cout << setw(column_width) << number << ": " << right << consumer1->description << endl;
    cout << setw(column_width) << "power consumption "
         << ": " << right << consumer1->watt << " W" << endl;

    cout << setw(column_width) << "power consumption standby "
         << ": " << right << consumer1->watt_standby << " W" << endl;

    cout << setw(column_width) << "annual hours of use "
         << ": " << right << annual_hours_of_use(consumer1) << " h" << endl;

    cout << setw(column_width) << "annual hours of standby "
         << ": " << right << annual_hours_of_standby(consumer1) << " h" << endl;

    cout << setw(column_width) << "annual consumption "
         << ": " << right << annual_kWh(consumer1) << " kWh" << endl;

    cout << setw(column_width) << "annual costs "
         << ": " << right << annual_kWh(consumer1) * price_of_one_kilowatt << " EUR" << endl;
}

void print_household(household *household1, float price_of_one_kilowatt)
{
    if (household1 == nullptr)
    {
        cerr << "Invalid household pointer." << endl;
        return;
    }

    cout << "HOUSEHOLD POWER CONSUMPTION" << endl;
    cout << "-------------------------------------------------- --------------------" << endl;
    cout << setw(column_width) << "city"
         << ": " << right << household1->city << " " << endl;

    ;

    cout << setw(column_width) << "price for one kWh"
         << ": " << fixed << setprecision(2) << right << price_of_one_kilowatt * 100 << " ct/kWh" << endl;

    cout << setw(column_width) << "square meters"
         << ": " << right << household1->sqr << " sqm" << endl;

    cout << setw(column_width) << "persons"
         << ": " << right << household1->people << endl;

    cout << setw(column_width) << "water heated using electricity"
         << ": " << right;
    cout << (household1->hot_water_electric ? "yes" : "no") << endl;

    cout << setw(column_width) << "list of consumers" << right << endl;
    cout << "-------------------------------------------------- --------------------" << endl;

    consumer *currentConsumer = household1->consumers;
    int consumerNumber = 1;

    while (currentConsumer != nullptr)
    {
        
        print_consumer(currentConsumer, consumerNumber);
        currentConsumer = currentConsumer->next;
        consumerNumber++;
    }

    float sqr_consumption = household1->sqr * annual_average_psm;
    cout << "-------------------------------------------------- --------------------" << endl;
    cout << setw(column_width) << "power consumption square meters"
         << ": " << fixed << setprecision(2) << right << sqr_consumption << " kWh" << endl;

    float person_consumption = household1->people * annual_avverage_cpp_with_ewh;
    cout << setw(column_width) << "power consumption all persons"
         << ": " << fixed << setprecision(2) << right << person_consumption << " kWh" << endl;

    float total_consumption = sqr_consumption + person_consumption;

    currentConsumer = household1->consumers;
    while (currentConsumer != nullptr)
    {
        total_consumption += annual_kWh(currentConsumer);
        currentConsumer = currentConsumer->next;
    }

    cout << setw(column_width) << "total annual power consumption"
         << ": " << fixed << setprecision(2) << right << total_consumption << " kWh" << endl;

    cout << setw(column_width) << "total annual power costs"
         << ": " << fixed << setprecision(2) << right << total_consumption * price_of_one_kilowatt << " EUR" << endl;
}

int main()
{

    household *household1 = new household;
    household1->consumers = nullptr;
    cout << "CALCULATION OF AVERAGE POWER COSTS FOR A HOUSEHOLD" << endl;

    cout << "in which city is the household located? ";

    cin >> household1->city;

    cout << "what is the price for one kWh in EUR? ";
    cin >> price_of_one_kilowatt;

    cout << "how many square metres does the household have? ";
    cin >> household1->sqr;

    cout << "how many people live in this household? ";

    cin >> household1->people;

    cout << "is hot water heated using electricity? (y(es) or n(o)) ";

    char hot_water_choice;
    cin >> hot_water_choice;

    household1->hot_water_electric = (hot_water_choice == 'y');

    while (true)
    {

        cout << "q quit" << endl;
        cout << "i input power consumer" << endl;
        cout << "u move up power consumer" << endl;
        cout << "p print household" << endl;

        char option;
        cin >> option;

        switch (option)
        {

        case 'q':
            return 0;
        case 'i':
        {
            consumer *consumer1 = new consumer;
            consumer1->next = nullptr;

            cout << "what is the description of the power consumer? ";
            cin.ignore();
            getline(cin, consumer1->description);

            cout << "how many watts will it have? ";
            cin >> consumer1->watt;

            cout << "how many watts standby will it have? ";
            cin >> consumer1->watt_standby;

            input_use("how often will it be used?", consumer1->use);

            cout << "how many hours it will be operating then? ";
            cin >> consumer1->hours;

            add_consumer_to_household(household1, consumer1);
        }
        break;

        case 'p':
            print_household(household1, price_of_one_kilowatt);
            break;

        case 'u':
        {
            int k;
            cout << "which one? ";
            cin >> k;
            household1->consumers = move_up(household1->consumers, k);
            break;
        }

        default:
            cout << "sorry wrong choice" << endl;
        }
    }

    return 0;
}
