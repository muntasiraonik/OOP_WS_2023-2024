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
#include <fstream>
#include <sstream>

using namespace std;

const int annual_average_cpp = 200;
const int annual_average_psm = 9.0;
const int annual_average_ped = 200;
const int annual_avverage_cpp_with_ewh = 550;
const int column_width = 35;
int number_household;

enum Use
{
    once,
    daily,
    mo_fr,
    sa_su,
    weekly
};

string useToString(Use use)
{
    switch (use)
    {
    case once:
        return "once";
    case daily:
        return "daily";
    case mo_fr:
        return "Monday to Friday";
    case sa_su:
        return "Saturday and Sunday";
    case weekly:
        return "weekly";
    default:
        return "unknown";
    }
}

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
    float power_price;
    string power_suplier;
};

void add_consumer_to_household(household *household1, consumer *consumer1)
{
    if (household1 == nullptr || consumer1 == nullptr)
    {
        cerr << "Invalid household or consumer pointer." << endl;
        return;
    }

    consumer1->next = nullptr;

    if (household1->consumers == nullptr)
    {
        household1->consumers = consumer1;
    }
    else
    {

        consumer *lastConsumer = household1->consumers;
        while (lastConsumer->next != nullptr)
        {
            lastConsumer = lastConsumer->next;
        }

        lastConsumer->next = consumer1;
    }
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

void print_consumer(consumer *consumer1, int number, float powerPrice)
{
    cout << setw(column_width) << number << ": " << right << consumer1->description << " (at address: " << &consumer1 << ")" << endl;
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
         << ": " << right << annual_kWh(consumer1) * powerPrice << " EUR" << endl;
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
         << " (at address: " << &household1->city << ")" << endl;

    cout << setw(column_width) << "price for one kWh"
         << ": " << fixed << setprecision(2) << right << household1->power_price * 100 << " ct/kWh" << endl;

    cout << setw(column_width) << "power supplier"
         << ": " << fixed << setprecision(2) << right << household1->power_suplier << "" << endl;

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

        print_consumer(currentConsumer, consumerNumber, household1->power_price);
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
        // cout << "worked" << endl;
        total_consumption += annual_kWh(currentConsumer);
        // cout << total_consumption << endl;
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

    cout << "what is the price for one kWh in EUR? ";
    cin >> household->power_price;

    cout << "who is the power supplier? ";
    cin >> household->power_suplier;
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

    /* cout << newConsumerList->description << endl; */

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

    /* cout << newConsumerList->description << endl; */

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

void write_to_file(const string &filename, char separator, household *households[], string &city)
{
    ofstream outFile(filename);

    if (!outFile.is_open())
    {
        cerr << "Error opening file for writing: " << filename << endl;
        return;
    }

    cout << "output file \"" << filename << "\" opened..." << endl;

    outFile << "A4" << separator << number_household << separator << households[0]->city << "\n";

    for (int i = 0; i < number_household; ++i)
    {
        if (households[i]->household_number)
        {
            outFile << "household" << separator << i << separator << households[i]->city << separator
                    << (households[i]->hot_water_electric ? "true" : "false") << separator
                    << households[i]->people << separator << households[i]->sqr << separator << households[i]->power_price << separator << households[i]->power_suplier << "\n";

            consumer *currentConsumer = households[i]->consumers;
            while (currentConsumer != nullptr)
            {
                outFile << "consumer" << separator << currentConsumer->description << separator
                        << currentConsumer->hours << separator
                        << useToString(currentConsumer->use) << separator
                        << currentConsumer->watt << separator
                        << currentConsumer->watt_standby << "\n";
                currentConsumer = currentConsumer->next;
            }
        }
    }

    outFile.close();

    cout << "out file \"" << filename << "\" closed" << endl;
}

void read_from_file(const string &filename, char separator, household *households[])
{
    ifstream inFile(filename);

    if (!inFile.is_open())
    {
        cerr << "Error opening file for reading: " << filename << endl;
        return;
    }

    cout << "input file \"" << filename << "\" opened..." << endl;

    int current_index_to_insert;

    string line;
    char characterAfterA4;
    while (getline(inFile, line))
    {
        // cout << "Read line: " << line << endl;
        if (line.find("A4") != string::npos)
        {
            characterAfterA4 = line[2];
            // cout << characterAfterA4 << endl;
            istringstream iss(line);
            string task_name;
            string max_households_str;
            string city;
            
           

            getline(iss, task_name, separator);
            getline(iss, max_households_str, separator);
            getline(iss, city, separator);
             
            int max_households = stod(max_households_str);
            if (max_households > number_household)
            {
                cerr << "file contains up to " << max_households << " households, but here only " << number_household << " are supported" << endl;
                inFile.close();
                return;
            }

            // number_household = max_households;

            for (int i = 0; i < number_household; ++i)
            {
                households[i]->consumers = nullptr;
                households[i]->city = city;
            }
        }

        if (line.find("household") != string::npos)
        {

            // cout << "i'm on household" << endl;


            // household|2|Bergisch Gladbach|true|5|200|0.3|Yello Strom

            istringstream iss(line);
            string type;
            string householdNumberStr;
            string city;
            string hotWaterElectricStr;
            string numberOfPeopleStr;
            string squareMetersStr;
            string powerPriceStr;
            string powerSupplier;

            getline(iss, type, separator);
            getline(iss, householdNumberStr, separator);
            getline(iss, city, separator);
            getline(iss, hotWaterElectricStr, separator);
            getline(iss, numberOfPeopleStr, separator);
            getline(iss, squareMetersStr, separator);
            getline(iss, powerPriceStr, separator);
            getline(iss, powerSupplier, separator);

          

            int householdNumber = stod(householdNumberStr);
            bool hotWaterElectric = (hotWaterElectricStr == "true");
            int numberOfPeople = stod(numberOfPeopleStr);
            int squareMeters = stod(squareMetersStr);
            float powerPrice = stod(powerPriceStr);

            current_index_to_insert = householdNumber;

            if (householdNumber >= 0 && householdNumber < number_household)
            {
                if (households[householdNumber] == nullptr)
                {
                    households[householdNumber] = new household;
                    households[householdNumber]->consumers = nullptr;
                }
            }

            if (households[householdNumber]->household_number)
            {
                cout << "Already Exists" << endl;
                break;
            }

            households[householdNumber]->household_number = householdNumber;
            households[householdNumber]->sqr = squareMeters;
            households[householdNumber]->city = city;
            households[householdNumber]->people = numberOfPeople;
            households[householdNumber]->hot_water_electric = hotWaterElectric;
            households[householdNumber]->power_price = powerPrice;
            households[householdNumber]->power_suplier = powerSupplier;

            for (int i = 0; i < number_household; ++i)
            {

                households[i]->city = city;
            }
        }

        if (line.find("consumer") != string::npos)
        {


            //  cout << "i'm on consumer" << endl;

            istringstream iss(line);
            string type;
            string description;
            string hours_str;
            string use;
            string watt_str;
            string watt_standby_str;

            getline(iss, type, separator);
            getline(iss, description, separator);
            getline(iss, hours_str, separator);
            getline(iss, use, separator);
            getline(iss, watt_str, separator);
            getline(iss, watt_standby_str, separator);

            // cout << hours_str << endl;

            double hours = stod(hours_str);
            double watt = stod(watt_str);
            double watt_standby = stod(watt_standby_str);
            // cout << hours << endl;
            consumer *consumer1 = new consumer;
            consumer1->next = nullptr;
            consumer1->description = description;

            consumer1->watt = watt;

            consumer1->watt_standby = watt_standby;

            if (use == "daily")
            {
                consumer1->use = Use::daily;
            }
            else if (use == "weekly")
            {
                consumer1->use = Use::weekly;
            }
            else if (use == "Monday to Friday")
            {
                consumer1->use = Use::mo_fr;
            }
            else if (use == "Saturday and Sunday")
            {
                consumer1->use = Use::sa_su;
            }
            else if (use == "Once")
            {
                consumer1->use = Use::once;
            }

            consumer1->hours = hours;

            // cout << hours << endl;

            add_consumer_to_household(households[current_index_to_insert], consumer1);
        }
    }

    inFile.close();

    cout << "Input file \"" << filename << "\" closed" << endl;
}

int main()
{
    cout << "CALCULATION OF AVERAGE POWER COSTS FOR A HOUSE" << endl;

    cout << "how many households does the house have? ";
    cin >> number_household;

    household *households[number_household];
    string city;
    string filename;
    char separator;
    cout << "in which city is the household located? ";
    cin >> city;

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
        cout << "r read data from file" << endl;
        cout << "w write data into file" << endl;

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
                print_household(households[household_index], households[household_index]->power_price, households[household_index]->household_number);
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
                    print_household(households[i], households[i]->power_price, households[i]->household_number);
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

        case 'w':
        {
            cout << "Enter filename: ";
            cin >> filename;
            cout << "Enter separator character: ";
            cin >> separator;
            write_to_file(filename, separator, households, city);
            break;
        }
        case 'r':
        {
            cout << "input file name: ";
            cin >> filename;
            cout << "input separator character: ";
            cin >> separator;
            read_from_file(filename, separator, households);
            break;
        }

        default:
            cout << "sorry wrong choice" << endl;
        }
    }

    return 0;
}
