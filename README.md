Hospital Management System (C++ OOP Project)
A console-based Hospital Management System built in C++ demonstrating core
Object-Oriented Programming concepts, with an additional web-based GUI for
interactive demonstration.

👥 Group Members
Ibtasam Qamar
Syeda Ritaj Yaseen
Abdul Hai Adnan
✨ Features
Add / register patients and doctors
Assign a doctor to a patient (speciality must match illness)
Schedule appointments (date, day, time)
Mark a patient as treated
Add billable items and generate the total bill
Show doctor list / show all records
File handling (data persists in patients.txt and doctors.txt)
Input validation for invalid/non-numeric input
🧠 OOP Concepts Demonstrated
Concept	Where
Abstraction	Person, Billable (abstract classes / pure virtual functions)
Inheritance	patient, doctor ← Person; bill ← Billable
Polymorphism	overridden display(), virtual functions
Encapsulation	private/protected data + getters
Composition	patient has a bill and appointments
Static members	patient::totalPatients
Friend classes	appointment friend of patient
📁 Project Structure
text

HospitalProject/
├── src/
│   └── HospitalManagementSystem.cpp   # main C++ source
├── HospitalManagementSystem.html      # web GUI (open in browser)
├── diagrams/
│   ├── uml_class_diagram.png          # UML class diagram
│   └── make_uml.py                    # script that generates it
├── report/
│   ├── Hospital_Management_System_Report.pdf
│   ├── validation_log.txt             # captured test outputs
│   └── make_report.py
└── README.md
▶️ How to Run
C++ console version
Bash

g++ -std=c++17 src/HospitalManagementSystem.cpp -o hms
./hms
GUI version
Open HospitalManagementSystem.html in any web browser (just double-click it).

🔗 Links
GitHub Repo:https://github.com/AbdulHai564/Hosptial_management_system
Live GUI Link: https://share.google/8em3c645UR87lMp9e
Developed as an Object-Oriented Programming course project.
