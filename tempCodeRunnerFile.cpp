 else if (current_index_to_insert != -1)
            {
                istringstream iss(line);
                string type, description, hours_str, use, watt_str, watt_standby_str;
                getline(iss, type, separator);
                Device *newDevice = nullptr;

                if (type == "Immobile")
                {
                    newDevice = new Immobile();
                    getline(iss, description, separator);
                    getline(iss, hours_str, separator);
                    getline(iss, use, separator);
                    getline(iss, watt_str, separator);
                    getline(iss, watt_standby_str, separator);

                    double hours = stod(hours_str);
                    double watt = stod(watt_str);
                    double watt_standby = stod(watt_standby_str);

                    newDevice->set_description(description);
                    newDevice->set_Watt(watt);
                    newDevice->set_watt_standby(watt_standby);
                    newDevice->set_hours(hours);
                    if (use == "daily")
                    {
                        newDevice->set_use(Use::daily);
                    }
                    else if (use == "weekly")
                    {
                        newDevice->set_use(Use::weekly);
                    }
                    else if (use == "Monday to Friday")
                    {
                        newDevice->set_use(Use::mo_fr);
                    }
                    else if (use == "Saturday and Sunday")
                    {
                        newDevice->set_use(Use::sa_su);
                    }
                    else
                    {
                        cerr << "Invalid use type in the file: " << use << endl;
                    }

                    house->get_household(current_index_to_insert)->add_device_to_household(newDevice);

                }
                else if (type == "Mobile")
                {
                    newDevice = new Mobile();
                }
                else if (type == "Solar")
                {
                    newDevice = new Solar();
                }