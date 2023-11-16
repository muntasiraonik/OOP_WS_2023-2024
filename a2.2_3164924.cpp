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
int number_household;

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
    int household_number;
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

    while (currentConsumer != nullptr && position < k)
    {
        prevConsumer = currentConsumer;
        currentConsumer = currentConsumer->next;
        position++;
    }

    if (currentConsumer == nullptr)
    {

        return firstConsumer;
    }

    prevConsumer->next = currentConsumer->next;
    currentConsumer->next = prevConsumer;
    firstConsumer->next = currentConsumer;

    return firstConsumer;
}

void print_consumer(consumer *consumer1, int number)
{
    cout << setw(column_width) << number << ": " << right << consumer1->description << " (at address: " << (void *)&consumer1 << ")" << endl;
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

void print_household(household *household1, float price_of_one_kilowatt, int household_number)
{
    if (household1 == nullptr)
    {
        cerr << "Invalid household pointer." << endl;
        return;
    }

    cout << "H O U S E H O L D   N O  " << household_number << "  P O W E R   C O N S U M P T I O N" << endl;
    cout << "-------------------------------------------------- --------------------" << endl;
    cout << setw(column_width) << "city"
         << ": " << right << household1->city
         << " (at address: " << (void *)&household1->city << ")" << endl;

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
         << ": " << fixed << setprecision(1) << right << sqr_consumption << " kWh" << endl;

    float person_consumption;
    if (household1->hot_water_electric)
    {
        person_consumption = household1->people * annual_avverage_cpp_with_ewh;
    }
    else
    {
        person_consumption = household1->people * annual_average_cpp;
    }

    cout << setw(column_width) << "power consumption all persons"
         << ": " << fixed << setprecision(1) << right << person_consumption << " kWh" << endl;

    float total_consumption = sqr_consumption + person_consumption;

    currentConsumer = household1->consumers;
    while (currentConsumer != nullptr)
    {
        total_consumption += annual_kWh(currentConsumer);
        currentConsumer = currentConsumer->next;
    }

    cout << setw(column_width) << "total annual power consumption"
         << ": " << fixed << setprecision(1) << right << total_consumption << " kWh" << endl;

    cout << setw(column_width) << "total annual power costs"
         << ": " << fixed << setprecision(1) << right << total_consumption * price_of_one_kilowatt << " EUR" << endl;
}

void input_household(household *household)
{

    cout << "how many square metres does the household have? ";
    cin >> household->sqr;

    cout << "how many people live in this household? ";

    cin >> household->people;

    cout << "is hot water heated using electricity? (y(es) or n(o)) ";

    char hot_water_choice;
    cin >> hot_water_choice;

    household->hot_water_electric = (hot_water_choice == 'y');
    household->consumers = nullptr;
}

household *copy_consumers(const household *source, household *destination)
{

    consumer *newConsumerList = nullptr;

    consumer *sourceConsumer = source->consumers;
    while (sourceConsumer != nullptr)
    {
        consumer *newConsumer = new consumer;
        newConsumer->description = sourceConsumer->description;
        newConsumer->watt = sourceConsumer->watt;
        newConsumer->watt_standby = sourceConsumer->watt_standby;
        newConsumer->hours = sourceConsumer->hours;
        newConsumer->use = sourceConsumer->use;
        newConsumer->next = newConsumerList;
        newConsumerList = newConsumer;

        sourceConsumer = sourceConsumer->next;
    }


    consumer *destinationConsumer = destination->consumers;
    while (destinationConsumer != nullptr)
    {
        consumer *newConsumer = new consumer;
        newConsumer->description = destinationConsumer->description;
        newConsumer->watt = destinationConsumer->watt;
        newConsumer->watt_standby = destinationConsumer->watt_standby;
        newConsumer->hours = destinationConsumer->hours;
        newConsumer->use = destinationConsumer->use;
        newConsumer->next = newConsumerList;
        newConsumerList = newConsumer;

        destinationConsumer = destinationConsumer->next;
    }

   

    consumer *prev = nullptr;
    consumer *current = newConsumerList;
    consumer *next = nullptr;

   

    while (current != nullptr)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    destination->consumers = prev;

    return destination;
}

int main()
{
    cout << "CALCULATION OF AVERAGE POWER COSTS FOR A HOUSE" << endl;

    cout << "how many households does the house have? ";
    cin >> number_household;

    household *households[number_household];
    string city;
    cout << "in which city is the household located? ";
    cin >> city;

    cout << "what is the price for one kWh in EUR? ";
    cin >> price_of_one_kilowatt;

    for (int i = 0; i < number_household; ++i)
    {
        households[i] = new household;
        households[i]->consumers = nullptr;
        households[i]->city = city;
    }

    while (true)
    {
        cout << "q quit" << endl;
        cout << "i input power consumer" << endl;
        cout << "u move up power consumer" << endl;
        cout << "p print household" << endl;
        cout << "a print all households" << endl;
        cout << "n new household" << endl;
        cout << "c copy all consumers (added to already existing ones)" << endl;

        char option;
        cin >> option;

        switch (option)
        {
        case 'q':
            return 0;

        case 'i':
        {
            int household_index;
            cout << "number of household? ";
            cin >> household_index;

            if (household_index >= 0 && household_index < number_household)
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

                add_consumer_to_household(households[household_index], consumer1);
            }
        }
        break;

        case 'p':
        {
            int household_index;
            cout << "number of household? ";
            cin >> household_index;

            if (household_index >= 0 && household_index < number_household)
            {
                print_household(households[household_index], price_of_one_kilowatt, households[household_index]->household_number);
            }
        }
        break;

        case 'u':
        {
            int household_index;
            cout << "number of household? ";
            cin >> household_index;

            if (household_index >= 0 && household_index < number_household)
            {
                int k;
                cout << "which one? ";
                cin >> k;
                households[household_index]->consumers = move_up(households[household_index]->consumers, k);
            }
        }
        break;

        case 'n':
        {
            int household_index;
            cout << "number of household? ";
            cin >> household_index;

            if (household_index >= 0 && household_index < number_household)
            {
                if (households[household_index] == nullptr)
                {
                    households[household_index] = new household;
                    households[household_index]->consumers = nullptr;
                }
            }

            if (households[household_index]->household_number)
            {
                cout << "Already Exists" << endl;
                break;
            }
            
            households[household_index]->household_number = household_index;
            input_household(households[household_index]);
        }
        break;

        case 'a':
            for (int i = 0; i < number_household; ++i)
            {
                if (households[i]->household_number)
                {
                    print_household(households[i], price_of_one_kilowatt, households[i]->household_number);
                }
            }
            break;

        case 'c':
        {
            int source_household, destination_household;
            cout << "number of household from which to copy consumers? ";
            cin >> source_household;
            cout << "number of household to copy to? ";
            cin >> destination_household;

            copy_consumers(households[source_household], households[destination_household]);
            break;
        }

        default:
            cout << "sorry wrong choice" << endl;
        }
    }

    return 0;
}
