#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class Person {
protected:
    string name;
    int id;
    int age;

public:
    Person(string n="", int i=0, int a=0) {
        name = n;
        id = i;
        age = a;
    }

    virtual void display() = 0;

    int getId() { return id; }
    string getName() { return name; }
    int getAge() { return age; }

    virtual ~Person() {}
};

class Billable {
public:
    virtual double generateBill() = 0;
};

class items {
    string name;
    double price;

public:
    items(string n="", double p=0) {
        name = n;
        price = p;
    }

    double getprice() { return price; }
};

class patient;

class bill : public Billable {
    vector<items> items_list;

public:
    void addItem(items i) {
        items_list.push_back(i);
    }

    double generateBill() override {
        double total = 0;
        for (auto &i : items_list) {
            total += i.getprice();
        }
        return total;
    }
};

class doctor : public Person {
    string speciality;
    vector<patient*> patients;

public:
    doctor(string n="", int a=0, int i=0, string s="")
        : Person(n,i,a) {
        speciality = s;
    }

    string getspeciality() { return speciality; }

    void addpatient(patient* p) {
        patients.push_back(p);
    }

    void removepatient(int pid);

    void display() override {
        cout << "Doctor: " << name << " | ID: " << id
             << " Age: " << age
             << " Speciality: " << speciality << endl;
    }
};

class appointment {
    string date, day, time;
    friend class patient;

public:
    appointment(string d="", string dy="", string t="") {
        date = d;
        day = dy;
        time = t;
    }

    void show() {
        cout << "Appointment -> " << date << " " << day << " at " << time << endl;
    }
};

class patient : public Person {
    string illness;
    doctor* d1;
    bill b1;
    vector<appointment> appointments;
    bool istreated;
    friend class appointment;

public:
    static int totalPatients;

    patient(string n="", int i=0, int a=0, string ill="")
        : Person(n,i,a) {
        illness = ill;
        d1 = nullptr;
        istreated = false;
        totalPatients++;
    }

    string getillness() { return illness; }

    void assigndoctor(doctor &d) {
        if (d.getspeciality() == illness) {
            d1 = &d;
            d.addpatient(this);
            cout << "Doctor assigned successfully\n";
        } else {
            cout << "Speciality mismatch!\n";
        }
    }

    void addItem(items i) {
        b1.addItem(i);
    }

    void createappointment(string date, string day, string time) {
        appointments.push_back(appointment(date, day, time));
    }

    void marktreated() {
        istreated = true;
        if (d1 != nullptr) {
            d1->removepatient(id);
        }
    }

    double calculatebill() {
        return b1.generateBill();
    }

    void display() override {
        cout << "Patient: " << name << " | ID: " << id
             << " Age: " << age
             << " Illness: " << illness << endl;

        cout << "Treated: " << (istreated ? "Yes" : "No") << endl;

        for (auto &a : appointments) {
            a.show();
        }
    }
};

int patient::totalPatients = 0;

void doctor::removepatient(int pid) {
    for (size_t i = 0; i < patients.size(); ++i) {
        if (patients[i]->getId() == pid) {
            patients.erase(patients.begin() + i);
            break;
        }
    }
}

//////////////////////////////////////////////////
// FILE HANDLING FUNCTIONS
//////////////////////////////////////////////////

void savePatients(vector<patient> &patients) {
    ofstream file("patients.txt");

    for (auto &p : patients) {
        file << p.getName() << " "
             << p.getId() << " "
             << p.getAge() << " "
             << p.getillness() << endl;
    }

    file.close();
}

void loadPatients(vector<patient> &patients) {
    ifstream file("patients.txt");

    string name, illness;
    int id, age;

    while (file >> name >> id >> age >> illness) {
        patients.push_back(patient(name, id, age, illness));
    }

    file.close();
}

void saveDoctors(vector<doctor> &doctors) {
    ofstream file("doctors.txt");

    for (auto &d : doctors) {
        file << d.getName() << " "
             << d.getId() << " "
             << d.getAge() << " "
             << d.getspeciality() << endl;
    }

    file.close();
}

void loadDoctors(vector<doctor> &doctors) {
    ifstream file("doctors.txt");

    string name, spec;
    int id, age;

    while (file >> name >> id >> age >> spec) {
        doctors.push_back(doctor(name, age, id, spec));
    }

    file.close();
}

//////////////////////////////////////////////////

int main() {
    vector<patient> patients;
    vector<doctor> doctors;

    // LOAD DATA AT START
    loadPatients(patients);
    loadDoctors(doctors);

    int choice;

    do {
        cout << "\n==== Hospital Management System ====\n";
        cout << "1. Add Patient\n";
        cout << "2. Add Doctor\n";
        cout << "3. Assign Doctor\n";
        cout << "4. Display Patient\n";
        cout << "5. Create Appointment\n";
        cout << "6. Mark Treated\n";
        cout << "7. Add Item & Generate Bill\n";
        cout << "8. Show Doctor List\n";
        cout << "9. Show All\n";
        cout << "0. Exit\n";
        cout << "====================================\n";
        cout << "Enter Your Choice: ";
        cin >> choice;

        if (choice == 1) {
            string n, ill;
            int id, age;
            cout << "Enter age: ";
            cin >> age;
            cout << "Enter name: ";
            cin >> n;
            cout << "Enter id: ";
            cin >> id;
            cout << "Enter illness: ";
            cin >> ill;
            patients.push_back(patient(n, id, age, ill));
        }

        else if (choice == 2) {
            string n, spec;
            int id, age;
            cout << "Enter age: ";
            cin >> age;
            cout << "Enter name: ";
            cin >> n;
            cout << "Enter id: ";
            cin >> id;
            cout << "Enter speciality: ";
            cin >> spec;
            doctors.push_back(doctor(n, age, id, spec));
        }

        else if (choice == 3) {
            int pid;
            cout << "Enter patient id: ";
            cin >> pid;

            for (auto &p : patients) {
                if (p.getId() == pid) {
                    for (auto &d : doctors) {
                        p.assigndoctor(d);
                    }
                }
            }
        }

        else if (choice == 4) {
            int pid;
            cout << "Enter patient id: ";
            cin >> pid;
            bool found = false;
            for (auto &p : patients) {
                if (p.getId() == pid) {
                    p.display();
                    found = true;
                    break;
                }
            }
            if (!found) cout << "Patient not found\n";
        }

        else if (choice == 5) {
            int pid;
            cout << "Enter patient id: ";
            cin >> pid;
            for (auto &p : patients) {
                if (p.getId() == pid) {
                    string d, dy, t;
                    cout << "Enter date, day and time of appointment: ";
                    cin >> d >> dy >> t;
                    p.createappointment(d, dy, t);
                }
            }
        }

        else if (choice == 6) {
            int pid;
            cout << "Enter patient id: ";
            cin >> pid;
            for (auto &p : patients) {
                if (p.getId() == pid) {
                    p.marktreated();
                }
            }
        }

        else if (choice == 7) {
            int pid;
            cout << "Enter patient id: ";
            cin >> pid;
            for (auto &p : patients) {
                if (p.getId() == pid) {
                    string itemName;
                    double price;
                    cout << "Enter item name and price: ";
                    cin >> itemName >> price;
                    p.addItem(items(itemName, price));
                    cout << "Total Bill: " << p.calculatebill() << endl;
                }
            }
        }

        else if (choice == 8) {
            for (auto &d : doctors) d.display();
        }

        else if (choice == 9) {
            for (auto &p : patients) p.display();
            for (auto &d : doctors) d.display();
        }

    } while (choice != 0);

    // SAVE DATA BEFORE EXIT
    savePatients(patients);
    saveDoctors(doctors);

    return 0;
}
