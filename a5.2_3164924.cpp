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
#include <stack>

using namespace std;

const int annual_average_cpp = 200;
const int annual_average_psm = 9.0;
const int annual_average_ped = 200;
const int annual_avverage_cpp_with_ewh = 550;
const int column_width = 35;

enum Use
{
    once,
    daily,
    mo_fr,
    sa_su,
    weekly
};

class Consumer
{
private:
    string description;
    float watt;
    float watt_standby;
    float hours;
    Use use;
    Consumer *next;
    static int total_consumers;

public:
    Consumer() : next(nullptr)
    {
        total_consumers++;
    }

    ~Consumer()
    {
        cout << "Consumer " << get_description() << " at address " << this << " is deleted." << endl;
        total_consumers--;
    }

    string get_description() const
    {
        return description;
    }

    void set_description(const string &desc)
    {
        description = desc;
    }

    float get_watt() const
    {
        return watt;
    }

    void setWatt(float w)
    {
        watt = w;
    }

    float get_watt_standby() const
    {
        return watt_standby;
    }

    void set_watt_standby(float ws)
    {
        watt_standby = ws;
    }

    float get_hours() const
    {
        return hours;
    }

    void set_hours(float h)
    {
        hours = h;
    }

    Use get_use() const
    {
        return use;
    }

    void set_use(Use u)
    {
        use = u;
    }

    Consumer *get_next() const
    {
        return next;
    }

    void set_next(Consumer *n)
    {
        next = n;
    }

    static int get_total_consumers()
    {
        return total_consumers;
    }

    float annual_hours_of_use()
    {
        switch (use)
        {
        case once:
            return hours;
        case daily:
            return hours * 365.0;
        case mo_fr:
            return hours * 260.0;
        case sa_su:
            return hours * 104.0;
        case weekly:
            return hours * 52.0;
        default:
            return 0.0;
        }
    }

    float annual_hours_of_standby()
    {
        return 8760.0 - annual_hours_of_use();
    }

    float annual_kWh()
    {
        float annual_use_hours = annual_hours_of_use();
        float annual_standby_hours = annual_hours_of_standby();
        float consumption = (annual_use_hours * watt + annual_standby_hours * watt_standby) / 1000.0;
        return consumption;
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

    void input()
    {
        cout << "What is the description of the power consumer? ";
        cin.ignore();
        getline(cin, description);
        cout << "How many watts will it have? ";
        cin >> watt;
        cout << "How many watts standby will it have? ";
        cin >> watt_standby;

        input_use("How often will it be used?", use);

        cout << "How many hours will it be operating then? ";
        cin >> hours;
        // add_consumer_to_household(households[household_index], consumer1);
    }

    void print(int number, float powerPrice)
    {
        cout << setw(column_width) << number << ": " << right << get_description() << endl;
        cout << setw(column_width) << "(this"
             << ": " << right << this << ")" << endl;
        cout << setw(column_width) << "power consumption "
             << ": " << right << get_watt() << " W" << endl;

        cout << setw(column_width) << "power consumption standby "
             << ": " << right << get_watt_standby() << " W" << endl;

        cout << setw(column_width) << "annual hours of use "
             << ": " << right << annual_hours_of_use() << " h" << endl;

        cout << setw(column_width) << "annual hours of standby "
             << ": " << right << annual_hours_of_standby() << " h" << endl;

        cout << setw(column_width) << "annual consumption "
             << ": " << right << annual_kWh() << " kWh" << endl;

        cout << setw(column_width) << "annual costs "
             << ": " << right << annual_kWh() * powerPrice << " EUR" << endl;
    }
};

int Consumer::total_consumers = 0;

class Household
{
private:
    int household_number;
    int persons;
    int sqr;
    bool hot_water_electric;
    Consumer *consumers;
    float power_price;
    string power_supplier;

public:
    Household() : consumers(nullptr) {}

    ~Household()
    {
        delete_consumers();
        cout << "Household at address " << this << " is deleted." << endl;
    }

    void delete_consumers()
    {
        Consumer *currentConsumer = consumers;
        while (currentConsumer != nullptr)
        {
            Consumer *nextConsumer = currentConsumer->get_next();
            delete currentConsumer;
            currentConsumer = nextConsumer;
        }
        consumers = nullptr;
    }

    int getHouseholdNumber() const
    {
        return household_number;
    }

    void setHouseholdNumber(int number)
    {
        household_number = number;
    }

    int get_persons() const
    {
        return persons;
    }

    void set_persons(int num_people)
    {
        persons = num_people;
    }

    int get_square_metres() const
    {
        return sqr;
    }

    void set_square_metres(int square)
    {
        sqr = square;
    }

    bool get_electric_water_heating() const
    {
        return hot_water_electric;
    }

    void set_electric_water_heating(bool electric)
    {
        hot_water_electric = electric;
    }

    float get_price_KWh() const
    {
        return power_price;
    }

    void set_price_KWh(float price)
    {
        power_price = price;
    }

    string get_power_supplier() const
    {
        return power_supplier;
    }

    void set_power_supplier(const string &supplier)
    {
        power_supplier = supplier;
    }

    Consumer *get_consumers() const
    {
        return consumers;
    }

    void add_consumer_to_household(Consumer *consumer)
    {
        if (consumer == nullptr)
        {
            cerr << "Invalid consumer pointer." << endl;
            return;
        }

        consumer->set_next(consumers);
        consumers = consumer;
    }

    void copy_consumers(const Household *source, Household *destination)
    {

        std::stack<Consumer *> tempStack;
        Consumer *sourceConsumer = source->get_consumers();

        while (sourceConsumer != nullptr)
        {
            Consumer *newConsumer = new Consumer;
            newConsumer->set_description(sourceConsumer->get_description());
            newConsumer->setWatt(sourceConsumer->get_watt());
            newConsumer->set_watt_standby(sourceConsumer->get_watt_standby());
            newConsumer->set_hours(sourceConsumer->get_hours());
            newConsumer->set_use(sourceConsumer->get_use());

            tempStack.push(newConsumer);
            sourceConsumer = sourceConsumer->get_next();
        }

        while (!tempStack.empty())
        {
            Consumer *newConsumer = tempStack.top();
            tempStack.pop();

            newConsumer->set_next(destination->get_consumers());
            destination->consumers = newConsumer;
        }
    }

    Consumer *move_up(int k)
    {
        if (consumers == nullptr || k <= 1)
        {
            return consumers;
        }

        Consumer *prevPrev = nullptr;
        Consumer *prev = consumers;
        Consumer *current = consumers->get_next();

        for (int pos = 2; current != nullptr && pos < k; ++pos)
        {
            prevPrev = prev;
            prev = current;
            current = current->get_next();
        }

        if (current == nullptr || prev == nullptr)
        {
            return consumers;
        }

        if (prevPrev != nullptr)
        {
            prevPrev->set_next(current);
        }
        prev->set_next(current->get_next());
        current->set_next(prev);

        if (k == 2)
        {
            consumers = current;
        }

        return consumers;
    }

    void add_consumer_to_end(Consumer *newConsumer)
    {
        if (newConsumer == nullptr)
        {
            cerr << "Invalid consumer pointer." << endl;
            return;
        }

        if (consumers == nullptr)
        {
            consumers = newConsumer;
        }
        else
        {
            Consumer *current = consumers;
            while (current->get_next() != nullptr)
            {
                current = current->get_next();
            }
            current->set_next(newConsumer);
        }
    }

    void input()
    {
        cout << "how many square meters does the household have? ";
        cin >> sqr;

        cout << "how many persons live in this household? ";
        cin >> persons;

        cout << "is hot water heated using electricity? (y(es) or n(o)) ";
        char hot_water_choice;
        cin >> hot_water_choice;
        hot_water_electric = (hot_water_choice == 'y');

        cout << "what is the price for one kWh in EUR? ";
        cin >> power_price;

        cout << "who is the power supplier? ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, power_supplier);

        consumers = nullptr;
    }

    void print(int household_number, float price_of_one_kilowatt)
    {
        cout << "H O U S E H O L D   N O  " << household_number << "  P O W E R   C O N S U M P T I O N" << endl;
        cout << "-------------------------------------------------- --------------------" << endl;
        cout << setw(column_width) << "(this"
             << ": " << right << this << ")" << endl;
        cout << setw(column_width) << "price for one kWh"
             << ": " << fixed << setprecision(2) << right << power_price * 100 << " ct/kWh" << endl;
        cout << setw(column_width) << "power supplier"
             << ": " << fixed << setprecision(2) << right << power_supplier << "" << endl;
        cout << setw(column_width) << "square metres"
             << ": " << fixed << setprecision(2) << right << sqr << " qm" << endl;

        cout << setw(column_width) << "persons"
             << ": " << right << persons << endl;

        cout << setw(column_width) << "water heated using electricity"
             << ": " << right;
        cout << (hot_water_electric ? "yes" : "no") << endl;

        cout << setw(column_width) << "list of consumers" << right << endl;
        cout << "-------------------------------------------------- --------------------" << endl;

        Consumer *currentConsumer = consumers;
        int consumerNumber = 1;

        while (currentConsumer != nullptr)
        {
            currentConsumer->print(consumerNumber, price_of_one_kilowatt);
            currentConsumer = currentConsumer->get_next();
            consumerNumber++;
        }

        float sqr_consumption = sqr * annual_average_psm;
        cout << "-------------------------------------------------- --------------------" << endl;
        cout << setw(column_width) << "power consumption square metres"
             << ": " << fixed << setprecision(1) << right << sqr_consumption << " kWh" << endl;

        float person_consumption;
        if (hot_water_electric)
        {
            person_consumption = persons * annual_avverage_cpp_with_ewh;
        }
        else
        {
            person_consumption = persons * annual_average_cpp;
        }

        cout << setw(column_width) << "power consumption all persons"
             << ": " << fixed << setprecision(1) << right << person_consumption << " kWh" << endl;

        float total_consumption = sqr_consumption + person_consumption;

        currentConsumer = consumers;
        while (currentConsumer != nullptr)
        {
            total_consumption += currentConsumer->annual_kWh();
            currentConsumer = currentConsumer->get_next();
        }

        cout << setw(column_width) << "total annual power consumption"
             << ": " << fixed << setprecision(1) << right << total_consumption << " kWh" << endl;

        cout << setw(column_width) << "total annual power costs"
             << ": " << fixed << setprecision(1) << right << total_consumption * price_of_one_kilowatt << " EUR" << endl;
    }
};

class Address
{
private:
    string street, no, zip, city;

public:
    Address(string street = "", string no = "", string zip = "", string city = "")
        : street(street), no(no), zip(zip), city(city) {}

    ~Address()
    {
        cout << "Address " << to_string() << " at address " << this << " is deleted." << endl;
    }

    string get_street() const { return street; }
    string get_no() const { return no; }
    string get_zip() const { return zip; }
    string get_city() const { return city; }

    void input()
    {
        cout << "what is the street name? ";
        cin.ignore();
        getline(cin, street);

        cout << "what is house number? ";
        cin >> no;

        cout << "what is zip code? ";
        cin >> zip;

        cout << "what is the city name? ";
        cin.ignore();
        getline(cin, city);
    }

    string to_string() const
    {
        return street + " " + no + ", " + zip + " " + city;
    }
};

class House
{
private:
    int number_of_households;
    Household **households;
    Address address;

public:
    House(int number_of_households, const Address &address)
        : number_of_households(number_of_households), address(address)
    {
        households = new Household *[number_of_households];
        for (int i = 0; i < number_of_households; ++i)
        {
            households[i] = nullptr;
        }
    }

    ~House()
    {

        for (int i = 0; i < number_of_households; ++i)
        {
            delete households[i];
        }
        delete[] households;
        cout << "House at address " << this << " is deleted." << endl;
    }

    Household *get_household(int n)
    {
        if (n >= 0 && n < number_of_households)
        {
            return households[n];
        }
        return nullptr;
    }

    Household *operator[](int n)
    {
        return get_household(n);
    }

    int get_number_Of_households() const
    {
        return number_of_households;
    }

    void set_household(Household *household, int n)
    {
        if (n >= 0 && n < number_of_households)
        {
            households[n] = household;
        }
    }

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

    void print_all()
    {
        cout << "======================================================================" << endl;
        cout << setw(column_width) << "H O U S E" << endl;
        cout << "======================================================================" << endl;
        cout << setw(column_width) << "(this"
             << ": " << right << this << ")" << endl;

        cout << setw(column_width) << "address"
             << ": " << right << address.to_string() << endl;
        cout << setw(column_width) << "number of households"
             << ": " << right << number_of_households << endl;

        cout << setw(column_width) << "total number of all consumers"
             << ": " << right << Consumer::get_total_consumers() << endl;

        for (int i = 0; i < number_of_households; ++i)
        {
            Household *currentHousehold = households[i];
            if (currentHousehold != nullptr)
            {

                                currentHousehold->print(i, currentHousehold->get_price_KWh());
            }
        }
        cout << "======================================================================" << endl;
    }

    void write_to_file(const string &filename, char separator)
    {
        ofstream outFile(filename);

        if (!outFile.is_open())
        {
            cerr << "Error opening file for writing: " << filename << endl;
            return;
        }

        cout << "Output file \"" << filename << "\" opened..." << endl;

        outFile << "A5" << separator << number_of_households << separator << address.get_street() << separator << address.get_no() << separator << address.get_zip() << separator << address.get_city() << "\n";

        for (int i = 0; i < number_of_households; ++i)
        {
            Household *currentHousehold = households[i];
            if (currentHousehold != nullptr)
            {
                outFile << "household" << separator << i << separator
                        << (currentHousehold->get_electric_water_heating() ? "true" : "false") << separator
                        << currentHousehold->get_persons() << separator << currentHousehold->get_square_metres() << separator
                        << currentHousehold->get_price_KWh() << separator << currentHousehold->get_power_supplier() << "\n";

                Consumer *currentConsumer = currentHousehold->get_consumers();
                while (currentConsumer != nullptr)
                {
                    outFile << "consumer" << separator << currentConsumer->get_description() << separator
                            << currentConsumer->get_hours() << separator
                            << useToString(currentConsumer->get_use()) << separator
                            << currentConsumer->get_watt() << separator
                            << currentConsumer->get_watt_standby() << "\n";
                    currentConsumer = currentConsumer->get_next();
                }
            }
        }

        outFile.close();

        cout << "Output file \"" << filename << "\" closed" << endl;
    }

    void read_from_file(House *&house, const string &filename, char separator)
    {
        ifstream inFile(filename);

        if (!inFile.is_open())
        {
            cerr << "Error opening file for reading: " << filename << endl;
            return;
        }

        cout << "Input file \"" << filename << "\" opened..." << endl;

        int current_index_to_insert = -1;

        string line;

        while (getline(inFile, line))
        {
            if (line.find("A5") != string::npos)
            {

                istringstream iss(line);
                string type, totalHousehold, street, houseno, zip, city;
                getline(iss, type, separator);
                getline(iss, totalHousehold, separator);
                getline(iss, street, separator);
                getline(iss, houseno, separator);
                getline(iss, zip, separator);
                getline(iss, city, separator);

                Address address(street, houseno, zip, city);

                if (house != nullptr)
                {
                    int number_of_households = stoi(totalHousehold);
                    house = new House(number_of_households, address);
                    // cout << "here" << endl;
                }
            }
            else if (line.find("household") != string::npos)
            {

                istringstream iss(line);
                string type, householdNumberStr, hotWaterElectricStr, numberOfPeopleStr, squareMetresStr, powerPriceStr, powerSupplier;

                getline(iss, type, separator);
                getline(iss, householdNumberStr, separator);
                getline(iss, hotWaterElectricStr, separator);
                getline(iss, numberOfPeopleStr, separator);
                getline(iss, squareMetresStr, separator);
                getline(iss, powerPriceStr, separator);
                getline(iss, powerSupplier, separator);

                int householdNumber = stoi(householdNumberStr);
                bool hotWaterElectric = (hotWaterElectricStr == "true");
                int numberOfPeople = stoi(numberOfPeopleStr);
                int squareMetres = stoi(squareMetresStr);
                float powerPrice = stof(powerPriceStr);

                int number_of_households = house->get_number_Of_households();

                if (householdNumber >= 0 && householdNumber < number_of_households)
                {

                    if (house->get_household(householdNumber) == nullptr)
                    {
                        house->set_household(new Household(), householdNumber);
                    }

                    Household *currentHousehold = house->get_household(householdNumber);
                    currentHousehold->setHouseholdNumber(householdNumber);
                    currentHousehold->set_square_metres(squareMetres);
                    currentHousehold->set_persons(numberOfPeople);
                    currentHousehold->set_electric_water_heating(hotWaterElectric);
                    currentHousehold->set_price_KWh(powerPrice);
                    currentHousehold->set_power_supplier(powerSupplier);

                    current_index_to_insert = householdNumber;
                }
                else
                {
                    cerr << "Invalid household number in the file: " << householdNumber << endl;
                }
            }
            else if (line.find("consumer") != string::npos && current_index_to_insert != -1)
            {
                istringstream iss(line);
                string type, description, hours_str, use, watt_str, watt_standby_str;

                getline(iss, type, separator);
                getline(iss, description, separator);
                getline(iss, hours_str, separator);
                getline(iss, use, separator);
                getline(iss, watt_str, separator);
                getline(iss, watt_standby_str, separator);

                double hours = stod(hours_str);
                double watt = stod(watt_str);
                double watt_standby = stod(watt_standby_str);

                Consumer *consumer1 = new Consumer();
                consumer1->set_description(description);
                consumer1->setWatt(watt);
                consumer1->set_watt_standby(watt_standby);
                consumer1->set_hours(hours);

                if (use == "daily")
                {
                    consumer1->set_use(Use::daily);
                }
                else if (use == "weekly")
                {
                    consumer1->set_use(Use::weekly);
                }
                else if (use == "Monday to Friday")
                {
                    consumer1->set_use(Use::mo_fr);
                }
                else if (use == "Saturday and Sunday")
                {
                    consumer1->set_use(Use::sa_su);
                }
                else
                {
                    cerr << "Invalid use type in the file: " << use << endl;
                }

                house->get_household(current_index_to_insert)->add_consumer_to_end(consumer1);
            }
        }

        inFile.close();

        cout << "Input file \"" << filename << "\" closed" << endl;
    }
};

int main()
{

    House *house = nullptr;

    cout << "CALCULATION OF AVERAGE POWER COSTS FOR A HOUSE - CLASS VERSION" << endl;
    while (true)
    {
        cout << "q quit" << endl;
        cout << "d delete house" << endl;
        cout << "h house initialisation" << endl;
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

        case 'd':
        {
            delete house;
            house = nullptr; // Ensure the pointer is set to nullptr after deletion
            break;
        }

        case 'h':
        {
            if (house != nullptr)
            {
                cerr << "House already initialized." << endl;
            }
            else
            {
                int number_households;
                cout << "how many households does the house have? ";
                cin >> number_households;
                Address address;
                address.input();
                house = new House(number_households, address);
            }
        }
        break;

        case 'i':
        {
            int household_index;
            cout << "number of household? ";
            cin >> household_index;

            if (house != nullptr && household_index >= 0 && household_index < house->get_number_Of_households())

            {
                Household *currentHousehold = house->get_household(household_index);

                if (currentHousehold != nullptr)
                {
                    Consumer *consumer1 = new Consumer;
                    consumer1->input();

                    currentHousehold->add_consumer_to_household(consumer1);
                }
            }
        }
        break;

        case 'p':
        {

            int household_index;
            cout << "number of household? ";
            cin >> household_index;

            if (house != nullptr && household_index >= 0 && household_index < house->get_number_Of_households())
            {
                Household *currentHousehold = house->get_household(household_index);
                if (currentHousehold != nullptr)
                {

                    currentHousehold->print(household_index, currentHousehold->get_price_KWh());
                }
                else
                {
                    cout << "Household at index " << household_index << " does not exist." << endl;
                }
            }
        }
        break;

        case 'u':
        {
            int household_index;
            cout << "Number of household? ";
            cin >> household_index;

            if (household_index >= 0 && household_index < house->get_number_Of_households())
            {
                int k;
                cout << "Which consumer do you want to move up? ";
                cin >> k;

                house->get_household(household_index)->move_up(k);
            }
            else
            {
                cout << "Invalid household index." << endl;
            }
        }
        break;

        case 'n':
        {
            int household_index;
            cout << "Number of household? ";
            cin >> household_index;

            if (house != nullptr && household_index >= 0 && household_index < house->get_number_Of_households())

            {
                if (house->get_household(household_index) == nullptr)
                {
                    house->set_household(new Household(), household_index);
                }
                else
                {
                    cout << "Household already exists at index " << household_index << "." << endl;
                    break;
                }

                house->get_household(household_index)->setHouseholdNumber(household_index);
                house->get_household(household_index)->input();
            }
        }
        break;

        case 'a':
            if (house != nullptr)
            {
                house->print_all();
            }
            else
            {
                cerr << "house is a nullptr, please first choose h to initialise a new house" << endl;
            }
            break;

        case 'c':
        {

            int source_household, destination_household;
            cout << "number of household from which to copy consumers? ";
            cin >> source_household;
            cout << "number of household to copy to? ";
            cin >> destination_household;

            if (house->get_household(source_household) != nullptr && house->get_household(destination_household) != nullptr)
            {
                Household *sourceHousehold = house->get_household(source_household);
                Household *destinationHousehold = house->get_household(destination_household);

                destinationHousehold->copy_consumers(sourceHousehold, destinationHousehold);
            }
            else
            {
                cout << "Invalid household indices or null households." << endl;
            }

            break;
        }

        case 'w':
        {
            string filename;
            char separator;
            cout << "Enter filename: ";
            cin >> filename;
            cout << "Enter separator character: ";
            cin >> separator;
            house->write_to_file(filename, separator);

            break;
        }
        case 'r':
        {
            string filename;
            char separator;
            cout << "input file name: ";
            cin >> filename;
            cout << "input separator character: ";
            cin >> separator;

            if (house == nullptr)
            {
                cout << "house is a nullptr, please first choose h to initialise a new house" << endl;
            }
            else
            {
                house->read_from_file(house, filename, separator);
            }

            break;
        }

        default:
            cout << "sorry wrong choice" << endl;
        }
    }
    return 0;
}