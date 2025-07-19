#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <limits>
#include <ctime>
#include <regex>
using namespace std;

// Struct definitions
struct Person {
    string name;
    string email;
    string contact;

    Person() = default;

    Person(const string& line) {
        if (!line.empty()) {
            stringstream ss(line);
            getline(ss, name, ',');
            getline(ss, email, ',');
            getline(ss, contact);
        }
    }

    void toString(string& line) const {
        line = name + "," + email + "," + contact;
    }
};

struct Vendor {
    int vendorID = 0;
    Person person;
    string vendorType;
    float cost = 0;

    Vendor() = default;

    Vendor(const string& line) {
        if (!line.empty()) {
            stringstream ss(line);
            ss >> vendorID; ss.ignore();
            getline(ss, vendorType, ',');
            getline(ss, person.name, ',');
            getline(ss, person.email, ',');
            getline(ss, person.contact, ',');
            ss >> cost;
        }
    }

    void toString(string& line) const {
        line = to_string(vendorID) + "," + vendorType + "," + person.name + "," + person.email + "," + person.contact + "," + to_string(cost);
    }
};

struct Client {
    int clientID = 0;
    Person person;
    string partnerName;
    string weddingDate;
    string specialRequest;
    int guestCount = 0;
    int tableCount = 0;
    string selectedPackage;
    string venueBooked;
    string cateringSelected;
    vector<string> selectedVendors;
    float totalPayment = 0;
    float amountPaid = 0;
    string paymentStatus;

    Client() = default;

    Client(const string& line) {
        if (!line.empty()) {
            stringstream ss(line);
            ss >> clientID; ss.ignore();
            getline(ss, person.name, ',');
            getline(ss, person.email, ',');
            getline(ss, person.contact, ',');
            getline(ss, partnerName, ',');
            getline(ss, weddingDate, ',');
            getline(ss, specialRequest, ',');
            ss >> guestCount; ss.ignore();
            ss >> tableCount; ss.ignore();
            getline(ss, selectedPackage, ',');
            getline(ss, venueBooked, ',');
            getline(ss, cateringSelected, ',');
            string vendors;
            getline(ss, vendors, ',');
            stringstream vendorStream(vendors);
            string vendor;
            while (getline(vendorStream, vendor, ';')) {
                if (!vendor.empty()) selectedVendors.push_back(vendor);
            }
            ss >> totalPayment; ss.ignore();
            ss >> amountPaid; ss.ignore();
            getline(ss, paymentStatus);
        }
    }

    void toString(string& line) const {
        string vendors;
        for (size_t i = 0; i < selectedVendors.size(); ++i) {
            vendors += selectedVendors[i];
            if (i < selectedVendors.size() - 1) vendors += ";";
        }
        line = to_string(clientID) + "," + person.name + "," + person.email + "," + person.contact + "," +
            partnerName + "," + weddingDate + "," + specialRequest + "," +
            to_string(guestCount) + "," + to_string(tableCount) + "," +
            selectedPackage + "," + venueBooked + "," + cateringSelected + "," +
            vendors + "," + to_string(totalPayment) + "," + to_string(amountPaid) + "," +
            paymentStatus;
    }
};

struct Package {
    int packageID = 0;
    string packageName;
    string description;
    float price = 0;

    Package() = default;

    Package(const string& line) {
        if (!line.empty()) {
            stringstream ss(line);
            ss >> packageID; ss.ignore();
            getline(ss, packageName, ',');
            getline(ss, description, ',');
            ss >> price;
        }
    }

    void toString(string& line) const {
        line = to_string(packageID) + "," + packageName + "," + description + "," + to_string(price);
    }
};

struct Venue {
    int venueID = 0;
    string venueName;
    string location;
    int capacity = 0;
    float rentalCost = 0;

    Venue() = default;

    Venue(const string& line) {
        if (!line.empty()) {
            stringstream ss(line);
            ss >> venueID; ss.ignore();
            getline(ss, venueName, ',');
            getline(ss, location, ',');
            ss >> capacity; ss.ignore();
            ss >> rentalCost;
        }
    }

    void toString(string& line) const {
        line = to_string(venueID) + "," + venueName + "," + location + "," + to_string(capacity) + "," + to_string(rentalCost);
    }
};

struct Cater {
    int caterID = 0;
    string caterName;
    string menuDescription;
    float costPerPerson = 0;

    Cater() = default;

    Cater(const string& line) {
        if (!line.empty()) {
            stringstream ss(line);
            ss >> caterID; ss.ignore();
            getline(ss, caterName, ',');
            getline(ss, menuDescription, ',');
            ss >> costPerPerson;
        }
    }

    void toString(string& line) const {
        line = to_string(caterID) + "," + caterName + "," + menuDescription + "," + to_string(costPerPerson);
    }
};

struct GuestRecord {
    int guestID;
    Person person;
    string rsvpStatus;
    string mealPreference;
    int tableNumber = -1;

    GuestRecord() = default;

    GuestRecord(const string& line) {
        if (!line.empty()) {
            stringstream ss(line);
            ss >> guestID; ss.ignore();
            getline(ss, person.name, ',');
            getline(ss, person.email, ',');
            getline(ss, person.contact, ',');
            getline(ss, rsvpStatus, ',');
            getline(ss, mealPreference, ',');
            ss >> tableNumber;
        }
    }

    void toString(string& line) const {
        line = to_string(guestID) + "," + person.name + "," + person.email + "," + person.contact + "," +
            rsvpStatus + "," + mealPreference + "," + to_string(tableNumber);
    }
};

struct Admin {
    string username;
    string password;

    Admin() = default;

    Admin(const string& line) {
        if (!line.empty()) {
            stringstream ss(line);
            getline(ss, username, ',');
            getline(ss, password);
        }
    }

    void toString(string& line) const {
        line = username + "," + password;
    }
};

struct Payment {
    int paymentID = 0;
    int clientID = 0;
    float amountPaid = 0;
    string paymentDate;
    string paymentStatus;

    Payment() = default;

    Payment(const string& line) {
        if (!line.empty()) {
            stringstream ss(line);
            ss >> paymentID; ss.ignore();
            ss >> clientID; ss.ignore();
            ss >> amountPaid; ss.ignore();
            getline(ss, paymentDate, ',');
            getline(ss, paymentStatus);
        }
    }

    void toString(string& line) const {
        line = to_string(paymentID) + "," + to_string(clientID) + "," + to_string(amountPaid) + "," + paymentDate + "," + paymentStatus;
    }
};

struct EventSchedule {
    int scheduleID = 0;
    int clientID = 0;
    string weddingDate;
    string time;
    string activity;

    EventSchedule() = default;

    EventSchedule(const string& line) {
        if (!line.empty()) {
            stringstream ss(line);
            ss >> scheduleID; ss.ignore();
            ss >> clientID; ss.ignore();
            getline(ss, weddingDate, ',');
            getline(ss, time, ',');
            getline(ss, activity);
        }
    }

    void toString(string& line) const {
        line = to_string(scheduleID) + "," + to_string(clientID) + "," + weddingDate + "," + time + "," + activity;
    }
};

struct StringConst {
    const string LOGO_X =
        "                XXXXXXXXXXXXX                 \n"
        "            XXXX             XXXX             \n"
        "         XXX                     XXX          \n"
        "       XX                           XX        \n"
        "      X     XXXX             XXXX     X       \n"
        "    XX    XXXXXXXX         XXXXXXXX    XX     \n"
        "   X     XXXXXXXXXXXX   XXXXXXXXXXXX     X    \n"
        "  X     XXXXXXXXXXXXXXXXXXXXXXXXXXXXX     X   \n"
        "  X     XXXXXXXXXXXXXXXXXXXXXXXXXXXXX     X   \n"
        " X      XXXXXXXXXXXXXXXXXXXXXXXXXXXXX      X  \n"
        " X      XXXXXXXXXXXXXXXXXXXXXXXXXXXXX      X  \n"
        " X       XXXXXXXXXXXXXXXXXXXXXXXXXXX       X  \n"
        " X       XXXXXXXXXXXXXXXXXXXXXXXXXXX       X  \n"
        " X         XXXXXXXXXXXXXXXXXXXXXXX         X  \n"
        "  X         XXXXXXXXXXXXXXXXXXXXX         X   \n"
        "  X         XXXXXXXXXXXXXXXXXXXXX         X   \n"
        "   X          XXXXXXXXXXXXXXXXX          X    \n"
        "    XX           XXXXXXXXXXX           XX     \n"
        "      X            XXXXXXX            X       \n"
        "       XX            XXX            XX        \n"
        "         XXX          X          XXX          \n"
        "            XXXX             XXXX             \n"
        "                XXXXXXXXXXXXX                 \n";

    const string LOGO_O =
        "                \033[1;37mXXXXXXXXXXXXX\033[0m              \n"
        "            \033[1;37mXXXX             XXXX\033[0m          \n"
        "         \033[1;37mXXX                     XXX\033[0m       \n"
        "       \033[1;37mXX                           XX\033[0m     \n"
        "      \033[1;37mX     \033[1;31mXXXX             XXXX\033[1;37m     X\033[0m      \n"
        "    \033[1;37mXX    \033[1;31mXXXXXXXX         XXXXXXXX\033[1;37m    XX\033[0m    \n"
        "   \033[1;37mX     \033[1;31mXXXXXXXXXXXX   XXXXXXXXXXXX\033[1;37m     X\033[0m   \n"
        "  \033[1;37mX     \033[1;31mXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\033[1;37m     X\033[0m  \n"
        "  \033[1;37mX     \033[1;31mXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\033[1;37m     X\033[0m  \n"
        " \033[1;37mX      \033[1;31mXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\033[1;37m      X\033[0m \n"
        " \033[1;37mX      \033[1;31mXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\033[1;37m      X\033[0m \n"
        " \033[1;37mX       \033[1;31mXXXXXXXXXXXXXXXXXXXXXXXXXXX\033[1;37m       X\033[0m \n"
        " \033[1;37mX       \033[1;31mXXXXXXXXXXXXXXXXXXXXXXXXXXX\033[1;37m       X\033[0m \n"
        " \033[1;37mX         \033[1;31mXXXXXXXXXXXXXXXXXXXXXXX\033[1;37m         X\033[0m \n"
        "  \033[1;37mX         \033[1;31mXXXXXXXXXXXXXXXXXXXXX\033[1;37m         X\033[0m  \n"
        "  \033[1;37mX         \033[1;31mXXXXXXXXXXXXXXXXXXXXX\033[1;37m         X\033[0m  \n"
        "   \033[1;37mX          \033[1;31mXXXXXXXXXXXXXXXXX\033[1;37m          X\033[0m   \n"
        "    \033[1;37mXX           \033[1;31mXXXXXXXXXXX\033[1;37m           XX\033[0m    \n"
        "      \033[1;37mX            \033[1;31mXXXXXXX\033[1;37m            X\033[0m      \n"
        "       \033[1;37mXX            \033[1;31mXXX\033[1;37m            XX\033[0m       \n"
        "         \033[1;37mXXX          \033[1;31mX\033[1;37m          XXX\033[0m         \n"
        "            \033[1;37mXXXX             XXXX\033[0m         \n"
        "                \033[1;37mXXXXXXXXXXXXX\033[0m             \n";

    const string TITLE =
        " +-----------------------------------------+  \n"
        " | - Celestial Wedding  Event Management - |  \n"
        " +-----------------------------------------+     ";

    const string MainScMenu =
        " +-----------------------------------------+  \n"
        " | 1. Manage Client                        |  \n"
        " | 2. Manage Event                         |  \n"
        " | 3. Manage Vendors                       |  \n"
        " | 4. View Payment Records                 |  \n"
        " | 5. Manage Admin                         |  \n"
        " | 6. Event Monitoring                     |  \n"
        " | 0. Exit                                 |  \n"
        " +-----------------------------------------+    ";

    const string ClientMenu =
        " +-----------------------------------------+  \n"
        " |    Client Management                    |  \n"
        " +-----------------------------------------+  \n"
        " | 1. Create Client                        |  \n"
        " +-----------------------------------------+  \n"
        " | 2. Remove Client                        |  \n"
        " +-----------------------------------------+  \n"
        " | 3. Update Client                        |  \n"
        " +-----------------------------------------+  \n"
        " | 4. Show All Clients                     |  \n"
        " +-----------------------------------------+  \n"
        " | 0. Back to Main Menu                    |  \n"
        " +-----------------------------------------+    ";

    const string EventMenu =
        " +-----------------------------------------+  \n"
        " |    Event Management                     |  \n"
        " +-----------------------------------------+  \n"
        " | 1. Package Management                   |  \n"
        " +-----------------------------------------+  \n"
        " | 2. Venue Management                     |  \n"
        " +-----------------------------------------+  \n"
        " | 3. Catering Management                  |  \n"
        " +-----------------------------------------+  \n"
        " | 0. Back to Main Menu                    |  \n"
        " +-----------------------------------------+    ";

    const string PackageMenu =
        " +-----------------------------------------+  \n"
        " |    Wedding Package Management           |  \n"
        " +-----------------------------------------+  \n"
        " | 1. Create Package                       |  \n"
        " +-----------------------------------------+  \n"
        " | 2. Remove Package                       |  \n"
        " +-----------------------------------------+  \n"
        " | 3. Update Package                       |  \n"
        " +-----------------------------------------+  \n"
        " | 4. Show All Packages                    |  \n"
        " +-----------------------------------------+  \n"
        " | 0. Back to Event Management             |  \n"
        " +-----------------------------------------+    ";

    const string VenueMenu =
        " +-----------------------------------------+  \n"
        " |    Venue Management                     |  \n"
        " +-----------------------------------------+  \n"
        " | 1. Create Venue                         |  \n"
        " +-----------------------------------------+  \n"
        " | 2. Remove Venue                         |  \n"
        " +-----------------------------------------+  \n"
        " | 3. Update Venue                         |  \n"
        " +-----------------------------------------+  \n"
        " | 4. Show All Venues                      |  \n"
        " +-----------------------------------------+  \n"
        " | 0. Back to Event Management             |  \n"
        " +-----------------------------------------+    ";

    const string CaterMenu =
        " +-----------------------------------------+  \n"
        " |    Catering Management                  |  \n"
        " +-----------------------------------------+  \n"
        " | 1. Create Catering                      |  \n"
        " +-----------------------------------------+  \n"
        " | 2. Remove Catering                      |  \n"
        " +-----------------------------------------+  \n"
        " | 3. Update Catering                      |  \n"
        " +-----------------------------------------+  \n"
        " | 4. Show All Catering                    |  \n"
        " +-----------------------------------------+  \n"
        " | 0. Back to Event Management             |  \n"
        " +-----------------------------------------+    ";


    const string VendorMenu =
        " +-----------------------------------------+  \n"
        " |    Vendor Management                    |  \n"
        " +-----------------------------------------+  \n"
        " | 1. Create Vendor                        |  \n"
        " +-----------------------------------------+  \n"
        " | 2. Remove Vendor                        |  \n"
        " +-----------------------------------------+  \n"
        " | 3. Update Vendor                        |  \n"
        " +-----------------------------------------+  \n"
        " | 4. Show All Vendors                     |  \n"
        " +-----------------------------------------+  \n"
        " | 0. Back to Main Menu                    |  \n"
        " +-----------------------------------------+    ";


    const string PaymentMenu =
        " +-----------------------------------------+  \n"
        " |    Payment Management                   |  \n"
        " +-----------------------------------------+  \n"
        " | 1. Create Payment                       |  \n"
        " +-----------------------------------------+  \n"
        " | 2. Remove Payment                       |  \n"
        " +-----------------------------------------+  \n"
        " | 3. Update Payment                       |  \n"
        " +-----------------------------------------+  \n"
        " | 4. Show All Payments                    |  \n"
        " +-----------------------------------------+  \n"
        " | 0. Back to Main Menu                    |  \n"
        " +-----------------------------------------+    ";


    const string AdminMenu =
        " +-----------------------------------------+  \n"
        " |    Admin Management                     |  \n"
        " +-----------------------------------------+  \n"
        " | 1. Create Admin                         |  \n"
        " +-----------------------------------------+  \n"
        " | 2. Remove Admin                         |  \n"
        " +-----------------------------------------+  \n"
        " | 3. Update Admin                         |  \n"
        " +-----------------------------------------+  \n"
        " | 4. Show All Admin                       |  \n"
        " +-----------------------------------------+  \n"
        " | 0. Back to Main Menu                    |  \n"
        " +-----------------------------------------+    ";


    const string EventMonitoringMenu =
        " +-----------------------------------------+  \n"
        " |    Event Monitoring                     |  \n"
        " +-----------------------------------------+  \n"
        " | 1. Guest Management                     |  \n"
        " +-----------------------------------------+  \n"
        " | 2. Event Schedule Management            |  \n"
        " +-----------------------------------------+  \n"
        " | 0. Back to Main Menu                    |  \n"
        " +-----------------------------------------+    ";


    const string GuestMenu =
        " +-----------------------------------------+  \n"
        " |    Guest Management                     |  \n"
        " +-----------------------------------------+  \n"
        " | 1. Import Guest List                    |  \n"
        " +-----------------------------------------+  \n"
        " | 2. Update Guest RSVP                    |  \n"
        " +-----------------------------------------+  \n"
        " | 3. Show Guest List                      |  \n"
        " +-----------------------------------------+  \n"
        " | 0. Back to Event Monitoring             |  \n"
        " +-----------------------------------------+    ";


    const string ScheduleMenu =
        " +-----------------------------------------+  \n"
        " |    Event Schedule Management            |  \n"
        " +-----------------------------------------+  \n"
        " | 1. Create Schedule                      |  \n"
        " +-----------------------------------------+  \n"
        " | 2. Update Schedule                      |  \n"
        " +-----------------------------------------+  \n"
        " | 3. Remove Schedule                      |  \n"
        " +-----------------------------------------+  \n"
        " | 4. Show All Schedules                   |  \n"
        " +-----------------------------------------+  \n"
        " | 0. Back to Event Monitoring             |  \n"
        " +-----------------------------------------+    ";


    const string SearchMenu =
        " +-----------------------------------------+  \n"
        " |    Search Functionality                 |  \n"
        " +-----------------------------------------+  \n"
        " | 1. Search Client                        |  \n"
        " +-----------------------------------------+  \n"
        " | 2. Search Event                         |  \n"
        " +-----------------------------------------+  \n"
        " | 3. Search Vendor                        |  \n"
        " +-----------------------------------------+  \n"
        " | 0. Back to Main Menu                    |  \n"
        " +-----------------------------------------+    ";
};

// Template function to read things
template <typename T>
vector<T> getList(string filename) {
    ifstream file(filename);
    vector<T> list;

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            list.emplace_back(line);
        }
        file.close();
    }
    return list;
}

// Template function to save things
template <typename T>
void saveList(const vector<T>& list, const string& filename) {
    ofstream file(filename);

    if (file.is_open()) {
        for (const auto& r : list) {
            string line;
            r.toString(line);
            file << line << endl;
        }
        file.close();
    }
    else {
        cerr << "Error opening file: " << filename << endl;
    }
}

// Function declarations
bool login();
bool isValidDate(const string& date);
void showLoginScreen();
void showMainScreen();
void manageClient();
void manageEvent();
void managePackage();
void manageVenue();
void manageCatering();
void manageVendor();
void managePayment();
void manageAdmin();
void manageEventMonitoring();
void manageGuests();
void manageEventSchedule();
// void searchFun();

// Login function
bool login() {
    string username, password;
    vector<Admin> adminList = getList<Admin>("admins.csv");

    cout << "Enter Username: ";
    getline(cin, username);
    cout << "Enter Password: ";
    getline(cin, password);

    for (const auto& admin : adminList) {
        if (admin.username == username && admin.password == password) {
            cout << "Login successful!" << endl;
            return true;
        }
    }

    cout << "Invalid username or password." << endl;
    return false;
}

bool isValidDate(const string& date) {
    regex datePattern(R"(\d{4}-\d{2}-\d{2})");
    return regex_match(date, datePattern);
}

void showLoginScreen() {
    StringConst strConst;

    while (true) {
        system("cls");
        cout << strConst.LOGO_X << endl;
        cout << strConst.TITLE << endl;
        cout << "Please login to continue." << endl << endl;

        if (login()) {
            showMainScreen();
            break;
        }
        else {
            cout << "CREDENTIAL DO NOT MATCH. Press Enter to try again..." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }
}

void showMainScreen() {
    StringConst strConst;
    int x;

    system("cls");
    cout << strConst.LOGO_O << endl;
    cout << strConst.TITLE << endl << endl;
    cout << strConst.MainScMenu << endl;
    cout << "\nChoose an option: ";

    if (cin >> x) {
        switch (x) {
        case 0:
            system("cls");
            cout << strConst.LOGO_X << endl;
            cout << strConst.TITLE << endl << endl;
            cout << "\nExiting the system. Goodbye!" << endl;
            exit(0);
            break;
        case 1:
            manageClient();
            break;
        case 2:
            manageEvent();
            break;
        case 3:
            manageVendor();
            break;
        case 4:
            managePayment();
            break;
        case 5:
            manageAdmin();
            break;
        case 6:
            manageEventMonitoring();
            break;
        case 7:
            //searchFun();
            break;
        default:
            cout << "Invalid option. Please try again." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            showMainScreen();
            break;
        }
    }
}

void manageClient() {
    StringConst strConst;
    Client newClient;
    int x;

    vector<Client> clientList = getList<Client>("clients.csv");
    vector<Venue> venueList = getList<Venue>("venues.csv");
    vector<Cater> caterList = getList<Cater>("caterings.csv");
    vector<Package> packageList = getList<Package>("packages.csv");
    vector<Vendor> vendorList = getList<Vendor>("vendors.csv");
    vector<Payment> paymentList = getList<Payment>("payments.csv");

    system("cls");
    cout << strConst.ClientMenu << endl;
    cout << "\nChoose an option: ";
    cin.clear();
    while (!(cin >> x)) {
        cout << "Invalid input. Please enter a number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (x) {
    case 0: // Back to Main Menu
        showMainScreen();
        break;

    case 1: { // Create Client
        Client newClient;
        Package newPackage;
        Payment newPayment;
        system("cls");
        cout << "Enter client name: ";
        getline(cin, newClient.person.name);
        cout << "Enter partner name: ";
        getline(cin, newClient.partnerName);
        cout << "Enter client email: ";
        getline(cin, newClient.person.email);
        cout << "Enter client contact: ";
        getline(cin, newClient.person.contact);
        cout << "Enter wedding date (YYYY-MM-DD): ";
        getline(cin, newClient.weddingDate);
        while (!isValidDate(newClient.weddingDate)) {
            cout << "Invalid date format. Enter YYYY-MM-DD: ";
            getline(cin, newClient.weddingDate);
        }
        cout << "Enter special request: ";
        getline(cin, newClient.specialRequest);
        cout << "Enter estimated number of guests: ";
        cin >> newClient.guestCount;
        while (cin.fail() || newClient.guestCount <= 0) {
            cout << "Invalid guest count. Enter a positive number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> newClient.guestCount;
        }
        newClient.tableCount = (newClient.guestCount + 9) / 10;

        // Select Venue
        if (venueList.empty()) {
            cout << "\nNo venues available. Client creation cancelled." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            manageClient();
            break;
        }
        cout << "\nAvailable Venues:\n";
        for (size_t i = 0; i < venueList.size(); ++i) {
            cout << i + 1 << ". " << venueList[i].venueName << " (Location: " << venueList[i].location
                << ", Cost: $" << fixed << setprecision(2) << venueList[i].rentalCost << ")\n";
        }
        cout << "\nSelect venue number (0 to cancel): ";
        size_t venueChoice;
        cin >> venueChoice;
        if (venueChoice == 0 || venueChoice > venueList.size()) {
            cout << "\nInvalid selection. Client creation cancelled." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            manageClient();
            break;
        }
        newClient.venueBooked = venueList[venueChoice - 1].venueName;
        newClient.totalPayment += venueList[venueChoice - 1].rentalCost;

        // Select Catering
        if (caterList.empty()) {
            cout << "\nNo catering options available. Client creation cancelled." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            manageClient();
            break;
        }
        cout << "\nAvailable Catering Options:\n";
        for (size_t i = 0; i < caterList.size(); ++i) {
            cout << i + 1 << ". " << caterList[i].caterName << " (Cost per person: $"
                << fixed << setprecision(2) << caterList[i].costPerPerson << ")\n";
        }
        cout << "\nSelect catering number (0 to cancel): ";
        size_t caterChoice;
        cin >> caterChoice;
        if (caterChoice == 0 || caterChoice > caterList.size()) {
            cout << "\nInvalid selection. Client creation cancelled." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            manageClient();
            break;
        }
        newClient.cateringSelected = caterList[caterChoice - 1].caterName;
        newClient.totalPayment += caterList[caterChoice - 1].costPerPerson * newClient.guestCount;

        // Create Package
        newPackage.packageID = packageList.empty() ? 1 : packageList.back().packageID + 1;
        newPackage.packageName = newClient.person.name + "_" + newClient.weddingDate;
        newPackage.description = "Venue: " + newClient.venueBooked + ", Catering: " + newClient.cateringSelected;
        newPackage.price = newClient.totalPayment;
        newClient.selectedPackage = newPackage.packageName;
        packageList.push_back(newPackage);
        saveList(packageList, "packages.csv");

        // Select Vendors
        if (!vendorList.empty()) {
            cout << "\nAvailable Vendors:\n";
            for (size_t i = 0; i < vendorList.size(); ++i) {
                cout << i + 1 << ". " << vendorList[i].vendorType << " - " << vendorList[i].person.name
                    << " (Cost: $" << fixed << setprecision(2) << vendorList[i].cost << ")\n";
            }
            cout << "\nEnter vendor numbers to select (e.g., 1 2 3, 0 to finish): ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string vendorInput;
            getline(cin, vendorInput);
            stringstream vendorStream(vendorInput);
            size_t vendorChoice;
            while (vendorStream >> vendorChoice) {
                if (vendorChoice > 0 && vendorChoice <= vendorList.size()) {
                    newClient.selectedVendors.push_back(vendorList[vendorChoice - 1].person.name);
                    newClient.totalPayment += vendorList[vendorChoice - 1].cost;
                }
            }
        }

        // Payment Session
        cout << "\n=== Payment Session ===" << endl;
        cout << "Total Payment Required: $" << fixed << setprecision(2) << newClient.totalPayment << endl;
        cout << "Deposit Required (10%): $" << fixed << setprecision(2) << newClient.totalPayment * 0.1 << endl;
        cout << "Enter deposit amount paid (0 to cancel): ";
        float deposit;
        cin >> deposit;
        if (deposit == 0) {
            cout << "\nNo payment made. Client creation cancelled." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            manageClient();
            break;
        }
        while (cin.fail() || deposit < 0) {
            cout << "Invalid amount. Enter a non-negative number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> deposit;
        }
        newClient.amountPaid = deposit;
        if (deposit >= newClient.totalPayment) {
            newClient.paymentStatus = "Fully PAID";
        }
        else if (deposit >= newClient.totalPayment * 0.1) {
            newClient.paymentStatus = "Deposit PAID";
        }
        else {
            cout << "\nDeposit must be at least 10% ($" << fixed << setprecision(2) << newClient.totalPayment * 0.1
                << "). Client creation cancelled." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            manageClient();
            break;
        }

        // Set real-time payment date using localtime_s
        time_t now = time(0);
        struct tm ltm;
        localtime_s(&ltm, &now); // Fixed: Replaced <m with &ltm
        char dateStr[11];
        strftime(dateStr, sizeof(dateStr), "%Y-%m-%d", &ltm); // Use strftime for safer formatting
        newPayment.paymentDate = string(dateStr);

        // Create Payment Record
        newPayment.paymentID = paymentList.empty() ? 1 : paymentList.back().paymentID + 1;
        newPayment.clientID = clientList.empty() ? 1 : clientList.back().clientID + 1;
        newPayment.amountPaid = deposit;
        newPayment.paymentStatus = newClient.paymentStatus;
        paymentList.push_back(newPayment);
        saveList(paymentList, "payments.csv");

        // Simple Invoice Implementation
        cout << "\n=== INVOICE ===" << endl;
        cout << "Client: " << newClient.person.name << endl;
        cout << "Wedding Date: " << newClient.weddingDate << endl;
        cout << "Venue: " << newClient.venueBooked << endl;
        cout << "Catering: " << newClient.cateringSelected << endl;
        cout << "Vendors: ";
        if (newClient.selectedVendors.empty()) {
            cout << "None";
        }
        else {
            for (size_t i = 0; i < newClient.selectedVendors.size(); ++i) {
                cout << newClient.selectedVendors[i];
                if (i < newClient.selectedVendors.size() - 1) cout << ", ";
            }
        }
        cout << endl;
        cout << "Total Payment: $" << fixed << setprecision(2) << newClient.totalPayment << endl;
        cout << "Amount Paid: $" << fixed << setprecision(2) << newClient.amountPaid << endl;
        cout << "Payment Status: " << newClient.paymentStatus << endl;
        cout << "===============" << endl;

        // Save Client
        newClient.clientID = newPayment.clientID;
        clientList.push_back(newClient);
        saveList(clientList, "clients.csv");
        cout << "\nClient created successfully! Total Payment: $" << fixed << setprecision(2) << newClient.totalPayment
            << ", Amount Paid: $" << newClient.amountPaid << ", Status: " << newClient.paymentStatus
            << ", Tables: " << newClient.tableCount << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        manageClient();
        break;
    }

    case 2: { // Remove Client
        system("cls");
        if (clientList.empty()) {
            cout << "\nNo clients available to remove." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            manageClient();
            break;
        }
        for (size_t i = 0; i < clientList.size(); ++i) {
            cout << i + 1 << ". " << clientList[i].person.name << " (Wedding: " << clientList[i].weddingDate << ")\n";
        }
        cout << "\nEnter number to remove client (0 to cancel): ";
        size_t kill;
        cin >> kill;
        if (kill > 0 && kill <= clientList.size()) {
            clientList.erase(clientList.begin() + kill - 1);
            saveList(clientList, "clients.csv");
            cout << "\nClient removed successfully!" << endl;
        }
        else {
            cout << "\nInvalid selection. No client removed." << endl;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        manageClient();
        break;
    }

    case 3: { // Update Client
        system("cls");
        if (clientList.empty()) {
            cout << "\nNo clients available to update." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            manageClient();
            break;
        }
        for (size_t i = 0; i < clientList.size(); ++i) {
            cout << i + 1 << ". " << clientList[i].person.name << " (Wedding: " << clientList[i].weddingDate << ")\n";
        }
        cout << "\nEnter number to update client (0 to cancel): ";
        size_t updt;
        cin >> updt;
        if (updt == 0 || updt > clientList.size()) {
            cout << "\nInvalid selection. No client updated." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            manageClient();
            break;
        }
        float oldPackagePrice = clientList[updt - 1].totalPayment;
        cout << "Enter new client name: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, clientList[updt - 1].person.name);
        cout << "Enter new partner name: ";
        getline(cin, clientList[updt - 1].partnerName);
        cout << "Enter new client email: ";
        getline(cin, clientList[updt - 1].person.email);
        cout << "Enter new client contact: ";
        getline(cin, clientList[updt - 1].person.contact);
        cout << "Enter new wedding date (YYYY-MM-DD): ";
        getline(cin, clientList[updt - 1].weddingDate);
        while (!isValidDate(clientList[updt - 1].weddingDate)) {
            cout << "Invalid date format. Enter YYYY-MM-DD: ";
            getline(cin, clientList[updt - 1].weddingDate);
        }
        cout << "Enter new special request: ";
        getline(cin, clientList[updt - 1].specialRequest);
        cout << "Enter new estimated number of guests: ";
        cin >> clientList[updt - 1].guestCount;
        while (cin.fail() || clientList[updt - 1].guestCount <= 0) {
            cout << "Invalid guest count. Enter a positive number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> clientList[updt - 1].guestCount;
        }
        clientList[updt - 1].tableCount = (clientList[updt - 1].guestCount + 9) / 10;

        // Update Package and Payment
        clientList[updt - 1].totalPayment = 0;
        cout << "\nUpdate venue? (1 for Yes, 0 for No): ";
        int updateVenue;
        cin >> updateVenue;
        if (updateVenue == 1) {
            if (venueList.empty()) {
                cout << "\nNo venues available. Venue unchanged." << endl;
            }
            else {
                cout << "\nAvailable Venues:\n";
                for (size_t i = 0; i < venueList.size(); ++i) {
                    cout << i + 1 << ". " << venueList[i].venueName << " (Cost: $"
                        << fixed << setprecision(2) << venueList[i].rentalCost << ")\n";
                }
                cout << "\nSelect new venue number (0 to keep current): ";
                size_t venueChoice;
                cin >> venueChoice;
                if (venueChoice > 0 && venueChoice <= venueList.size()) {
                    clientList[updt - 1].venueBooked = venueList[venueChoice - 1].venueName;
                    clientList[updt - 1].totalPayment += venueList[venueChoice - 1].rentalCost;
                }
            }
        }
        cout << "\nUpdate catering? (1 for Yes, 0 for No): ";
        int updateCater;
        cin >> updateCater;
        if (updateCater == 1) {
            if (caterList.empty()) {
                cout << "\nNo catering options available. Catering unchanged." << endl;
            }
            else {
                cout << "\nAvailable Catering Options:\n";
                for (size_t i = 0; i < caterList.size(); ++i) {
                    cout << i + 1 << ". " << caterList[i].caterName << " (Cost per person: $"
                        << fixed << setprecision(2) << caterList[i].costPerPerson << ")\n";
                }
                cout << "\nSelect new catering number (0 to keep current): ";
                size_t caterChoice;
                cin >> caterChoice;
                if (caterChoice > 0 && caterChoice <= caterList.size()) {
                    clientList[updt - 1].cateringSelected = caterList[caterChoice - 1].caterName;
                    clientList[updt - 1].totalPayment += caterList[caterChoice - 1].costPerPerson * clientList[updt - 1].guestCount;
                }
            }
        }
        cout << "\nUpdate vendors? (1 for Yes, 0 for No): ";
        int updateVendors;
        cin >> updateVendors;
        if (updateVendors == 1 && !vendorList.empty()) { // Check if vendors exist
            cout << "\nAvailable Vendors:\n";
            for (size_t i = 0; i < vendorList.size(); ++i) {
                cout << i + 1 << ". " << vendorList[i].vendorType << " - " << vendorList[i].person.name
                    << " (Cost: $" << fixed << setprecision(2) << vendorList[i].cost << ")\n";
            }
            cout << "\nEnter vendor numbers to select (e.g., 1 2 3, 0 to finish): ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            string vendorInput;
            getline(cin, vendorInput);
            clientList[updt - 1].selectedVendors.clear(); // Clear existing vendors
            stringstream vendorStream(vendorInput);
            size_t vendorChoice;
            while (vendorStream >> vendorChoice) {
                if (vendorChoice > 0 && vendorChoice <= vendorList.size()) {
                    clientList[updt - 1].selectedVendors.push_back(vendorList[vendorChoice - 1].person.name);
                    clientList[updt - 1].totalPayment += vendorList[vendorChoice - 1].cost;
                }
            }
        }
        // Update Package
        for (auto& pkg : packageList) {
            if (pkg.packageName == clientList[updt - 1].selectedPackage) {
                pkg.description = "Venue: " + clientList[updt - 1].venueBooked + ", Catering: " + clientList[updt - 1].cateringSelected;
                pkg.price = clientList[updt - 1].totalPayment;
                break;
            }
        }
        saveList(packageList, "packages.csv");
        saveList(clientList, "clients.csv");
        cout << "\nClient updated successfully! New Total Payment: $" << fixed << setprecision(2) << clientList[updt - 1].totalPayment << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        manageClient();
        break;
    }

    case 4: { // Show All Clients
        system("cls");
        if (clientList.empty()) {
            cout << "\nNo clients available." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            manageClient();
            break;
        }
        for (size_t i = 0; i < clientList.size(); ++i) {
            cout << i + 1 << ". " << clientList[i].person.name << endl;
            cout << "   Partner: " << clientList[i].partnerName << endl;
            cout << "   Email: " << clientList[i].person.email << endl;
            cout << "   Contact: " << clientList[i].person.contact << endl;
            cout << "   Wedding Date: " << clientList[i].weddingDate << endl;
            cout << "   Special Request: " << clientList[i].specialRequest << endl;
            cout << "   Guests: " << clientList[i].guestCount << ", Tables: " << clientList[i].tableCount << endl;
            cout << "   Package: " << clientList[i].selectedPackage << endl;
            cout << "   Venue: " << clientList[i].venueBooked << endl;
            cout << "   Catering: " << clientList[i].cateringSelected << endl;
            cout << "   Vendors: ";
            if (clientList[i].selectedVendors.empty()) {
                cout << "None";
            }
            else {
                for (size_t j = 0; j < clientList[i].selectedVendors.size(); ++j) {
                    cout << clientList[i].selectedVendors[j];
                    if (j < clientList[i].selectedVendors.size() - 1) cout << ", ";
                }
            }
            cout << endl;
            cout << "   Total Payment: $" << fixed << setprecision(2) << clientList[i].totalPayment << endl;
            cout << "   Amount Paid: $" << fixed << setprecision(2) << clientList[i].amountPaid << endl;
            cout << "   Payment Status: " << clientList[i].paymentStatus << endl;
            cout << endl;
        }
        cout << "Total Clients: " << clientList.size() << endl;
        cout << "\nPress Enter to return to Client Management Menu..." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        manageClient();
        break;
    }

    default:
        cout << "Invalid option. Please try again." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        manageClient();
        break;
    }
}

void manageEvent() {
    StringConst strConst;
    int x;

    system("cls");
    cout << strConst.EventMenu << endl;
    cout << "\nChoose an option: ";
    cin.clear();
    cin >> x;

    switch (x) {
    case 0:
        showMainScreen();
        break;
    case 1:
        managePackage();
        break;
    case 2:
        manageVenue();
        break;
    case 3:
        manageCatering();
        break;
    default:
        cout << "Invalid option. Please try again." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        manageEvent();
        break;
    }
}

void managePackage() {
    StringConst strConst;
    Package newPackage;
    int x;

    vector<Package> packageList = getList<Package>("packages.csv");
    vector<Venue> venueList = getList<Venue>("venues.csv");
    vector<Cater> caterList = getList<Cater>("caterings.csv");

    system("cls");
    cout << strConst.PackageMenu << endl;
    cout << "\nChoose an option: ";
    cin.clear();
    cin >> x;

    switch (x) {
    case 0:
        manageEvent();
        break;
    case 1:
        system("cls");
        if (venueList.empty() || caterList.empty()) {
            cout << "\nCannot create package: No venues or catering options available." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            managePackage();
            break;
        }
        cout << "Available Venues:\n";
        for (size_t i = 0; i < venueList.size(); ++i) {
            cout << i + 1 << ". " << venueList[i].venueName << " (Location: " << venueList[i].location
                << ", Cost: $" << fixed << setprecision(2) << venueList[i].rentalCost << ")\n";
        }
        cout << "\nSelect venue number (0 to cancel): ";
        size_t venueChoice;
        cin >> venueChoice;
        if (venueChoice == 0 || venueChoice > venueList.size()) {
            cout << "\nInvalid selection. Package creation cancelled." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            managePackage();
            break;
        }
        cout << "\nAvailable Catering Options:\n";
        for (size_t i = 0; i < caterList.size(); ++i) {
            cout << i + 1 << ". " << caterList[i].caterName << " (Cost per person: $"
                << fixed << setprecision(2) << caterList[i].costPerPerson << ")\n";
        }
        cout << "\nSelect catering number (0 to cancel): ";
        size_t caterChoice;
        cin >> caterChoice;
        if (caterChoice == 0 || caterChoice > caterList.size()) {
            cout << "\nInvalid selection. Package creation cancelled." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            managePackage();
            break;
        }
        cout << "\nEnter package name: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, newPackage.packageName);
        cout << "Enter estimated number of guests (for catering cost calculation): ";
        int guestCount;
        cin >> guestCount;
        if (guestCount <= 0) {
            cout << "\nInvalid guest count. Package creation cancelled." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            managePackage();
            break;
        }
        newPackage.price = venueList[venueChoice - 1].rentalCost + (caterList[caterChoice - 1].costPerPerson * guestCount);
        newPackage.packageID = packageList.empty() ? 1 : packageList.back().packageID + 1;
        newPackage.description = "Venue: " + venueList[venueChoice - 1].venueName + ", Catering: " + caterList[caterChoice - 1].caterName;
        packageList.push_back(newPackage);
        saveList(packageList, "packages.csv");
        cout << "\nPackage created successfully! Total Price: $" << fixed << setprecision(2) << newPackage.price << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        managePackage();
        break;
    case 2:
        system("cls");
        if (packageList.empty()) {
            cout << "\nNo packages available to remove." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            managePackage();
            break;
        }
        if (packageList.size() == 1) {
            cout << "\nCannot remove the last package!" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            managePackage();
            break;
        }
        for (size_t i = 0; i < packageList.size(); ++i) {
            cout << i + 1 << ". " << packageList[i].packageName << " (Price: $"
                << fixed << setprecision(2) << packageList[i].price << ")\n";
        }
        cout << "\nEnter number to remove package (0 to cancel): ";
        size_t kill;
        cin >> kill;
        if (kill > 0 && kill <= packageList.size()) {
            packageList.erase(packageList.begin() + kill - 1);
            saveList(packageList, "packages.csv");
            cout << "\nPackage removed successfully!" << endl;
        }
        else {
            cout << "\nInvalid selection. No package removed." << endl;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        managePackage();
        break;
    case 3:
        system("cls");
        if (packageList.empty()) {
            cout << "\nNo packages available to update." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            managePackage();
            break;
        }
        for (size_t i = 0; i < packageList.size(); ++i) {
            cout << i + 1 << ". " << packageList[i].packageName << " (Price: $"
                << fixed << setprecision(2) << packageList[i].price << ")\n";
        }
        cout << "\nEnter number to update package (0 to cancel): ";
        size_t updt;
        cin >> updt;
        if (updt == 0 || updt > packageList.size()) {
            cout << "\nInvalid selection. No package updated." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            managePackage();
            break;
        }
        cout << "\nEnter new package name: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, packageList[updt - 1].packageName);
        cout << "Do you want to update the venue? (1 for Yes, 0 for No): ";
        int updateVenue;
        cin >> updateVenue;
        if (updateVenue == 1) {
            if (venueList.empty()) {
                cout << "\nNo venues available. Cannot update package venue." << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                managePackage();
                break;
            }
            cout << "Available Venues:\n";
            for (size_t i = 0; i < venueList.size(); ++i) {
                cout << i + 1 << ". " << venueList[i].venueName << " (Cost: $"
                    << fixed << setprecision(2) << venueList[i].rentalCost << ")\n";
            }
            cout << "\nSelect new venue number (0 to keep current): ";
            size_t venueChoice;
            cin >> venueChoice;
            if (venueChoice == 0 || venueChoice > venueList.size()) {
                cout << "\nVenue unchanged." << endl;
            }
            else {
                packageList[updt - 1].price -= packageList[updt - 1].price;
                packageList[updt - 1].price += venueList[venueChoice - 1].rentalCost;
                packageList[updt - 1].description = "Venue: " + venueList[venueChoice - 1].venueName + ", Catering: " + packageList[updt - 1].description.substr(packageList[updt - 1].description.find("Catering:"));
            }
        }
        cout << "\nDo you want to update the catering? (1 for Yes, 0 for No): ";
        int updateCater;
        cin >> updateCater;
        if (updateCater == 1) {
            if (caterList.empty()) {
                cout << "\nNo catering options available. Cannot update package catering." << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                managePackage();
                break;
            }
            cout << "Available Catering Options:\n";
            for (size_t i = 0; i < caterList.size(); ++i) {
                cout << i + 1 << ". " << caterList[i].caterName << " (Cost per person: $"
                    << fixed << setprecision(2) << caterList[i].costPerPerson << ")\n";
            }
            cout << "\nSelect new catering number (0 to keep current): ";
            size_t caterChoice;
            cin >> caterChoice;
            if (caterChoice == 0 || caterChoice > caterList.size()) {
                cout << "\nCatering unchanged." << endl;
            }
            else {
                cout << "Enter estimated number of guests for catering cost: ";
                int guestCount;
                cin >> guestCount;
                if (guestCount <= 0) {
                    cout << "\nInvalid guest count. Catering unchanged." << endl;
                }
                else {
                    packageList[updt - 1].price += (caterList[caterChoice - 1].costPerPerson * guestCount);
                    packageList[updt - 1].description = packageList[updt - 1].description.substr(0, packageList[updt - 1].description.find("Catering:")) + "Catering: " + caterList[caterChoice - 1].caterName;
                }
            }
        }
        saveList(packageList, "packages.csv");
        cout << "\nPackage updated successfully! New Price: $" << fixed << setprecision(2) << packageList[updt - 1].price << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        managePackage();
        break;
    case 4:
        system("cls");
        if (packageList.empty()) {
            cout << "\nNo packages available." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            managePackage();
            break;
        }
        for (size_t i = 0; i < packageList.size(); ++i) {
            cout << i + 1 << ". " << packageList[i].packageName << endl;
            cout << "   Description: " << packageList[i].description << endl;
            cout << "   Price: $" << fixed << setprecision(2) << packageList[i].price << endl;
            cout << endl;
        }
        cout << "Total Packages: " << packageList.size() << endl;
        cout << "\nPress Enter to return to Package Management Menu..." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        managePackage();
        break;
    default:
        cout << "Invalid option. Please try again." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        managePackage();
        break;
    }
}

void manageVenue() {
    StringConst strConst;
    Venue newVenue;

    vector<Venue> venueList = getList<Venue>("venues.csv");

    while (true) {
        system("cls");
        cout << strConst.VenueMenu << endl;
        cout << "\nChoose an option: ";
        int x;
        while (!(cin >> x)) {
            cout << "Invalid input. Please enter a number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (x) {
        case 0:
            manageEvent();
            break;
        case 1:
            system("cls");
            cout << "Enter venue name: ";
            getline(cin, newVenue.venueName);
            cout << "Enter venue location: ";
            getline(cin, newVenue.location);
            cout << "Enter venue capacity: ";
            cin >> newVenue.capacity;
            while (cin.fail() || newVenue.capacity <= 0) {
                cout << "Invalid capacity. Enter a positive number: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> newVenue.capacity;
            }
            cout << "Enter venue rental cost: ";
            cin >> newVenue.rentalCost;
            while (cin.fail() || newVenue.rentalCost < 0) {
                cout << "Invalid cost. Enter a non-negative number: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> newVenue.rentalCost;
            }
            newVenue.venueID = venueList.empty() ? 1 : venueList.back().venueID + 1;
            venueList.push_back(newVenue);
            saveList(venueList, "venues.csv");
            cout << "\nVenue created successfully!" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            manageVenue();
            break;
        case 2:
            system("cls");
            if (venueList.empty()) {
                cout << "\nNo venues available to remove." << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                manageVenue();
                break;
            }
            if (venueList.size() == 1) {
                cout << "\nCannot remove the last venue!" << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                manageVenue();
                break;
            }
            for (size_t i = 0; i < venueList.size(); ++i) {
                cout << i + 1 << ". " << venueList[i].venueName << endl;
            }
            cout << "\nEnter number to remove venue (0 to cancel): ";
            size_t kill;
            cin >> kill;
            if (kill > 0 && kill <= venueList.size()) {
                venueList.erase(venueList.begin() + kill - 1);
                saveList(venueList, "venues.csv");
                cout << "\nVenue removed successfully!" << endl;
            }
            else {
                cout << "\nInvalid selection. No venue removed." << endl;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            manageVenue();
            break;
        case 3:
            system("cls");
            if (venueList.empty()) {
                cout << "\nNo venues available to update." << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                manageVenue();
                break;
            }
            for (size_t i = 0; i < venueList.size(); ++i) {
                cout << i + 1 << ". " << venueList[i].venueName << endl;
            }
            cout << "\nEnter number to update venue (0 to cancel): ";
            size_t updt;
            cin >> updt;
            if (updt > 0 && updt <= venueList.size()) {
                cout << "Enter new venue name: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, venueList[updt - 1].venueName);
                cout << "Enter new venue location: ";
                getline(cin, venueList[updt - 1].location);
                cout << "Enter new venue capacity: ";
                cin >> venueList[updt - 1].capacity;
                while (cin.fail() || venueList[updt - 1].capacity <= 0) {
                    cout << "Invalid capacity. Enter a positive number: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin >> venueList[updt - 1].capacity;
                }
                cout << "Enter new venue rental cost: ";
                cin >> venueList[updt - 1].rentalCost;
                while (cin.fail() || venueList[updt - 1].rentalCost < 0) {
                    cout << "Invalid cost. Enter a non-negative number: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin >> venueList[updt - 1].rentalCost;
                }
                saveList(venueList, "venues.csv");
                cout << "\nVenue updated successfully!" << endl;
            }
            else {
                cout << "\nInvalid selection. No venue updated." << endl;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            manageVenue();
            break;
        case 4:
            system("cls");
            if (venueList.empty()) {
                cout << "\nNo venues available." << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                manageVenue();
                break;
            }
            for (size_t i = 0; i < venueList.size(); ++i) {
                cout << i + 1 << ". " << venueList[i].venueName << endl;
                cout << "   Location: " << venueList[i].location << endl;
                cout << "   Capacity: " << venueList[i].capacity << endl;
                cout << "   Rental Cost: $" << fixed << setprecision(2) << venueList[i].rentalCost << endl;
                cout << endl;
            }
            cout << "Total Venues: " << venueList.size() << endl;
            cout << "\nPress Enter to return to Venue Management Menu..." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            manageVenue();
            break;
        default:
            cout << "Invalid option. Please try again." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            manageVenue();
            break;
        }
    }
}

void manageCatering() {
    StringConst strConst;
    Cater newCater;

    vector<Cater> caterList = getList<Cater>("caterings.csv");

    while (true) {
        system("cls");
        cout << strConst.CaterMenu << endl;
        cout << "\nChoose an option: ";
        int x;
        while (!(cin >> x)) {
            cout << "Invalid input. Please enter a number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (x) {
        case 0:
            manageEvent();
            break;
        case 1:
            system("cls");
            cout << "Enter catering name: ";
            getline(cin, newCater.caterName);
            cout << "Enter menu description: ";
            getline(cin, newCater.menuDescription);
            cout << "Enter cost per person: ";
            cin >> newCater.costPerPerson;
            while (cin.fail() || newCater.costPerPerson < 0) {
                cout << "Invalid cost. Enter a non-negative number: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> newCater.costPerPerson;
            }
            newCater.caterID = caterList.empty() ? 1 : caterList.back().caterID + 1;
            caterList.push_back(newCater);
            saveList(caterList, "caterings.csv");
            cout << "\nCatering created successfully!" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            manageCatering();
            break;
        case 2:
            system("cls");
            if (caterList.empty()) {
                cout << "\nNo catering options available to remove." << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                manageCatering();
                break;
            }
            if (caterList.size() == 1) {
                cout << "\nCannot remove the last catering option!" << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                manageCatering();
                break;
            }
            for (size_t i = 0; i < caterList.size(); ++i) {
                cout << i + 1 << ". " << caterList[i].caterName << endl;
            }
            cout << "\nEnter number to remove catering (0 to cancel): ";
            size_t kill;
            cin >> kill;
            if (kill > 0 && kill <= caterList.size()) {
                caterList.erase(caterList.begin() + kill - 1);
                saveList(caterList, "caterings.csv");
                cout << "\nCatering removed successfully!" << endl;
            }
            else {
                cout << "\nInvalid selection. No catering removed." << endl;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            manageCatering();
            break;
        case 3:
            system("cls");
            if (caterList.empty()) {
                cout << "\nNo catering options available to update." << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                manageCatering();
                break;
            }
            for (size_t i = 0; i < caterList.size(); ++i) {
                cout << i + 1 << ". " << caterList[i].caterName << endl;
            }
            cout << "\nEnter number to update catering (0 to cancel): ";
            size_t updt;
            cin >> updt;
            if (updt > 0 && updt <= caterList.size()) {
                cout << "Enter new catering name: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, caterList[updt - 1].caterName);
                cout << "Enter new menu description: ";
                getline(cin, caterList[updt - 1].menuDescription);
                cout << "Enter new cost per person: ";
                cin >> caterList[updt - 1].costPerPerson;
                while (cin.fail() || caterList[updt - 1].costPerPerson < 0) {
                    cout << "Invalid cost. Enter a non-negative number: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin >> caterList[updt - 1].costPerPerson;
                }
                saveList(caterList, "caterings.csv");
                cout << "\nCatering updated successfully!" << endl;
            }
            else {
                cout << "\nInvalid selection. No catering updated." << endl;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            manageCatering();
            break;
        case 4:
            system("cls");
            if (caterList.empty()) {
                cout << "\nNo catering options available." << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                manageCatering();
                break;
            }
            for (size_t i = 0; i < caterList.size(); ++i) {
                cout << i + 1 << ". " << caterList[i].caterName << endl;
                cout << "   Menu Description: " << caterList[i].menuDescription << endl;
                cout << "   Cost per Person: $" << fixed << setprecision(2) << caterList[i].costPerPerson << endl;
                cout << endl;
            }
            cout << "Total Catering Options: " << caterList.size() << endl;
            cout << "\nPress Enter to return to Catering Management Menu..." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            manageCatering();
            break;
        default:
            cout << "Invalid option. Please try again." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            manageCatering();
            break;
        }
    }
}

void manageVendor() {
    StringConst strConst;
    Vendor newVendor;

    vector<Vendor> vendorList = getList<Vendor>("vendors.csv");

    while (true) {
        system("cls");
        cout << strConst.VendorMenu << endl;
        cout << "\nChoose an option: ";
        int x;
        while (!(cin >> x)) {
            cout << "Invalid input. Please enter a number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (x) {
        case 0:
            showMainScreen();
            break;
        case 1: { // Create Vendor
            system("cls");
            cout << "Enter vendor type: ";
            getline(cin, newVendor.vendorType);
            cout << "Enter vendor name: ";
            getline(cin, newVendor.person.name);
            cout << "Enter vendor email: ";
            getline(cin, newVendor.person.email);
            cout << "Enter vendor contact: ";
            getline(cin, newVendor.person.contact);
            cout << "Enter vendor cost: ";
            cin >> newVendor.cost;
            while (cin.fail() || newVendor.cost < 0) {
                cout << "Invalid cost. Enter a non-negative number: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> newVendor.cost;
            }
            newVendor.vendorID = vendorList.empty() ? 1 : vendorList.back().vendorID + 1;
            vendorList.push_back(newVendor);
            saveList(vendorList, "vendors.csv");
            cout << "\nVendor created successfully!" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            manageVendor();
            break;
        }
        case 2: { // Remove Vendor
            system("cls");
            if (vendorList.empty()) {
                cout << "\nNo vendors available to remove." << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                manageVendor();
                break;
            }
            for (size_t i = 0; i < vendorList.size(); ++i) {
                cout << i + 1 << ". " << vendorList[i].vendorType << " - " << vendorList[i].person.name << endl;
            }
            cout << "\nEnter number to remove vendor (0 to cancel): ";
            size_t kill;
            cin >> kill;
            if (kill > 0 && kill <= vendorList.size()) {
                vendorList.erase(vendorList.begin() + kill - 1);
                saveList(vendorList, "vendors.csv");
                cout << "\nVendor removed successfully!" << endl;
            }
            else {
                cout << "\nInvalid selection. No vendor removed." << endl;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            manageVendor();
            break;
        }
        case 3: { // Update Vendor
            system("cls");
            if (vendorList.empty()) {
                cout << "\nNo vendors available to update." << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                manageVendor();
                break;
            }
            for (size_t i = 0; i < vendorList.size(); ++i) {
                cout << i + 1 << ". " << vendorList[i].vendorType << " - " << vendorList[i].person.name << endl;
            }
            cout << "\nEnter number to update vendor (0 to cancel): ";
            size_t updt;
            cin >> updt;
            if (updt > 0 && updt <= vendorList.size()) {
                cout << "Enter new vendor type: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, vendorList[updt - 1].vendorType);
                cout << "Enter new vendor name: ";
                getline(cin, vendorList[updt - 1].person.name);
                cout << "Enter new vendor email: ";
                getline(cin, vendorList[updt - 1].person.email);
                cout << "Enter new vendor contact: ";
                getline(cin, vendorList[updt - 1].person.contact);
                cout << "Enter new vendor cost: ";
                cin >> vendorList[updt - 1].cost;
                while (cin.fail() || vendorList[updt - 1].cost < 0) {
                    cout << "Invalid cost. Enter a non-negative number: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin >> vendorList[updt - 1].cost;
                }
                saveList(vendorList, "vendors.csv");
                cout << "\nVendor updated successfully!" << endl;
            }
            else {
                cout << "\nInvalid selection. No vendor updated." << endl;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            manageVendor();
            break;
        }
        case 4: { // Show All Vendors
            system("cls");
            if (vendorList.empty()) {
                cout << "\nNo vendors available." << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                manageVendor();
                break;
            }
            for (size_t i = 0; i < vendorList.size(); ++i) {
                cout << i + 1 << ". " << vendorList[i].vendorType << " - " << vendorList[i].person.name << endl;
                cout << "   Email: " << vendorList[i].person.email << endl;
                cout << "   Contact: " << vendorList[i].person.contact << endl;
                cout << "   Cost: $" << fixed << setprecision(2) << vendorList[i].cost << endl;
                cout << endl;
            }
            cout << "Total Vendors: " << vendorList.size() << endl;
            cout << "\nPress Enter to return to Vendor Management Menu..." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            manageVendor();
            break;
        }
        default:
            cout << "Invalid option. Please try again." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            manageVendor();
            break;
        }
    }
}

void managePayment() {
    StringConst strConst;
    Payment newPayment;

    vector<Payment> paymentList = getList<Payment>("payments.csv");
    vector<Client> clientList = getList<Client>("clients.csv");

    while (true) {
        system("cls");
        cout << strConst.PaymentMenu << endl;
        cout << "\nChoose an option: ";
        int x;
        while (!(cin >> x)) {
            cout << "Invalid input. Please enter a number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (x) {
        case 0:
            showMainScreen();
            break;
        case 1: { // Create Payment
            system("cls");
            if (clientList.empty()) {
                cout << "\nNo clients available to create payment." << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                managePayment();
                break;
            }
            cout << "\nAvailable Clients:\n";
            for (size_t i = 0; i < clientList.size(); ++i) {
                cout << i + 1 << ". " << clientList[i].person.name << " (Wedding: " << clientList[i].weddingDate << ")\n";
            }
            cout << "\nSelect client number to create payment (0 to cancel): ";
            size_t clientChoice;
            cin >> clientChoice;
            if (clientChoice == 0 || clientChoice > clientList.size()) {
                cout << "\nInvalid selection. Payment creation cancelled." << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                managePayment();
                break;
            }
            newPayment.clientID = clientList[clientChoice - 1].clientID;
            cout << "Client Total Payment: $" << fixed << setprecision(2) << clientList[clientChoice - 1].totalPayment << endl;
            cout << "Current Amount Paid: $" << fixed << setprecision(2) << clientList[clientChoice - 1].amountPaid << endl;
            cout << "Enter payment amount: ";
            cin >> newPayment.amountPaid;
            while (cin.fail() || newPayment.amountPaid < 0) {
                cout << "Invalid amount. Enter a non-negative number: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin >> newPayment.amountPaid;
            }
            cout << "Enter payment date (YYYY-MM-DD): ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, newPayment.paymentDate);
            clientList[clientChoice - 1].amountPaid += newPayment.amountPaid;
            if (clientList[clientChoice - 1].amountPaid >= clientList[clientChoice - 1].totalPayment) {
                newPayment.paymentStatus = "Fully PAID";
                clientList[clientChoice - 1].paymentStatus = "Fully PAID";
            }
            else if (clientList[clientChoice - 1].amountPaid >= clientList[clientChoice - 1].totalPayment * 0.1) {
                newPayment.paymentStatus = "Deposit PAID";
                clientList[clientChoice - 1].paymentStatus = "Deposit PAID";
            }
            else {
                newPayment.paymentStatus = "NONE";
                clientList[clientChoice - 1].paymentStatus = "NONE";
            }
            newPayment.paymentID = paymentList.empty() ? 1 : paymentList.back().paymentID + 1;
            paymentList.push_back(newPayment);
            saveList(paymentList, "payments.csv");
            saveList(clientList, "clients.csv");
            cout << "\nPayment created successfully! New Client Amount Paid: $"
                << fixed << setprecision(2) << clientList[clientChoice - 1].amountPaid
                << ", Status: " << clientList[clientChoice - 1].paymentStatus << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            managePayment();
            break;
        }
        case 2: { // Remove Payment
            system("cls");
            if (paymentList.empty()) {
                cout << "\nNo payments available to remove." << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                managePayment();
                break;
            }
            for (size_t i = 0; i < paymentList.size(); ++i) {
                cout << i + 1 << ". Client ID: " << paymentList[i].clientID << ", Amount: $"
                    << fixed << setprecision(2) << paymentList[i].amountPaid
                    << ", Date: " << paymentList[i].paymentDate << endl;
            }
            cout << "\nEnter number to remove payment (0 to cancel): ";
            size_t kill;
            cin >> kill;
            if (kill > 0 && kill <= paymentList.size()) {
                int clientID = paymentList[kill - 1].clientID;
                float amountRemoved = paymentList[kill - 1].amountPaid;
                paymentList.erase(paymentList.begin() + kill - 1);
                for (auto& client : clientList) {
                    if (client.clientID == clientID) {
                        client.amountPaid -= amountRemoved;
                        if (client.amountPaid >= client.totalPayment) {
                            client.paymentStatus = "Fully PAID";
                        }
                        else if (client.amountPaid >= client.totalPayment * 0.1) {
                            client.paymentStatus = "Deposit PAID";
                        }
                        else {
                            client.paymentStatus = "NONE";
                        }
                        break;
                    }
                }
                saveList(paymentList, "payments.csv");
                saveList(clientList, "clients.csv");
                cout << "\nPayment removed successfully!" << endl;
            }
            else {
                cout << "\nInvalid selection. No payment removed." << endl;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            managePayment();
            break;
        }
        case 3: { // Update Payment
            system("cls");
            if (paymentList.empty()) {
                cout << "\nNo payments available to update." << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                managePayment();
                break;
            }
            for (size_t i = 0; i < paymentList.size(); ++i) {
                cout << i + 1 << ". Client ID: " << paymentList[i].clientID << ", Amount: $"
                    << fixed << setprecision(2) << paymentList[i].amountPaid
                    << ", Date: " << paymentList[i].paymentDate << endl;
            }
            cout << "\nEnter number to update payment (0 to cancel): ";
            size_t updt;
            cin >> updt;
            if (updt > 0 && updt <= paymentList.size()) {
                int clientID = paymentList[updt - 1].clientID;
                float oldAmount = paymentList[updt - 1].amountPaid;
                cout << "Enter new payment amount: ";
                cin >> paymentList[updt - 1].amountPaid;
                while (cin.fail() || paymentList[updt - 1].amountPaid < 0) {
                    cout << "Invalid amount. Enter a non-negative number: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin >> paymentList[updt - 1].amountPaid;
                }
                cout << "Enter new payment date (YYYY-MM-DD): ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, paymentList[updt - 1].paymentDate);
                for (auto& client : clientList) {
                    if (client.clientID == clientID) {
                        client.amountPaid = client.amountPaid - oldAmount + paymentList[updt - 1].amountPaid;
                        if (client.amountPaid >= client.totalPayment) {
                            client.paymentStatus = "Fully PAID";
                            paymentList[updt - 1].paymentStatus = "Fully PAID";
                        }
                        else if (client.amountPaid >= client.totalPayment * 0.1) {
                            client.paymentStatus = "Deposit PAID";
                            paymentList[updt - 1].paymentStatus = "Deposit PAID";
                        }
                        else {
                            client.paymentStatus = "NONE";
                            paymentList[updt - 1].paymentStatus = "NONE";
                        }
                        break;
                    }
                }
                saveList(paymentList, "payments.csv");
                saveList(clientList, "clients.csv");
                cout << "\nPayment updated successfully!" << endl;
            }
            else {
                cout << "\nInvalid selection. No payment updated." << endl;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            managePayment();
            break;
        }
        case 4: { // Show All Payments
            system("cls");
            if (paymentList.empty()) {
                cout << "\nNo payments available." << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                managePayment();
                break;
            }
            for (size_t i = 0; i < paymentList.size(); ++i) {
                cout << i + 1 << ". Client ID: " << paymentList[i].clientID << endl;
                cout << "   Amount Paid: $" << fixed << setprecision(2) << paymentList[i].amountPaid << endl;
                cout << "   Payment Date: " << paymentList[i].paymentDate << endl;
                cout << "   Payment Status: " << paymentList[i].paymentStatus << endl;
                cout << endl;
            }
            cout << "Total Payments: " << paymentList.size() << endl;
            cout << "\nPress Enter to return to Payment Management Menu..." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            managePayment();
            break;
        }
        default:
            cout << "Invalid option. Please try again." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            managePayment();
            break;
        }
    }
}

void manageAdmin() {
    StringConst strConst;
    Admin newAdmin;
    int x;

    vector<Admin> adminList = getList<Admin>("admins.csv");

    system("cls");
    cout << strConst.AdminMenu << endl;
    cout << "\nChoose an option: ";
    cin.clear();
    cin >> x;

    switch (x) {
    case 0:
        showMainScreen();
        break;
    case 1:
        system("cls");
        cout << "Enter new username: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, newAdmin.username);
        cout << "Enter new password: ";
        getline(cin, newAdmin.password);
        adminList.push_back(newAdmin);
        saveList(adminList, "admins.csv");
        cout << "\nAdmin created successfully!" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        manageAdmin();
        break;
    case 2:
        system("cls");
        if (adminList.empty()) {
            cout << "\nNo admins available to remove." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            manageAdmin();
            break;
        }
        if (adminList.size() == 1) {
            cout << "\nCannot remove the last admin!" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            manageAdmin();
            break;
        }
        for (size_t i = 0; i < adminList.size(); ++i) {
            cout << i + 1 << ". " << adminList[i].username << endl;
        }
        cout << "\nEnter number to remove admin (0 to cancel): ";
        size_t kill;
        cin >> kill;
        if (kill > 0 && kill <= adminList.size()) {
            adminList.erase(adminList.begin() + kill - 1);
            saveList(adminList, "admins.csv");
            cout << "\nAdmin removed successfully!" << endl;
        }
        else {
            cout << "\nInvalid selection. No admin removed." << endl;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        manageAdmin();
        break;
    case 3:
        system("cls");
        if (adminList.empty()) {
            cout << "\nNo admins available to update." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            manageAdmin();
            break;
        }
        for (size_t i = 0; i < adminList.size(); ++i) {
            cout << i + 1 << ". " << adminList[i].username << endl;
        }
        cout << "\nEnter number to update admin password (0 to cancel): ";
        size_t updt;
        cin >> updt;
        if (updt > 0 && updt <= adminList.size()) {
            cout << "Enter new password for " << adminList[updt - 1].username << ": ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, adminList[updt - 1].password);
            saveList(adminList, "admins.csv");
            cout << "\nAdmin updated successfully!" << endl;
        }
        else {
            cout << "\nInvalid selection. No admin updated." << endl;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        manageAdmin();
        break;
    case 4:
        system("cls");
        if (adminList.empty()) {
            cout << "\nNo admins available." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            manageAdmin();
            break;
        }
        for (size_t i = 0; i < adminList.size(); ++i) {
            cout << i + 1 << ". " << adminList[i].username << endl;
            cout << "   Password: " << adminList[i].password << endl << endl;
        }
        cout << "Total Admins: " << adminList.size() << endl;
        cout << "\nPress Enter to return to Admin Management Menu..." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        manageAdmin();
        break;
    default:
        cout << "Invalid option. Please try again." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        manageAdmin();
        break;
    }
}

void manageEventMonitoring() {
    StringConst strConst;
    int x;

    system("cls");
    cout << strConst.EventMonitoringMenu << endl;
    cout << "\nChoose an option: ";
    cin.clear();
    while (!(cin >> x)) {
        cout << "Invalid input. Please enter a number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (x) {
    case 0:
        showMainScreen();
        break;
    case 1:
        manageGuests();
        break;
    case 2:
        manageEventSchedule();
        break;
    default:
        cout << "Invalid option. Please try again." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        manageEventMonitoring();
        break;
    }
}

void manageGuests() {
    StringConst strConst;
    GuestRecord newGuest;
    vector<Client> clientList = getList<Client>("clients.csv");
    vector<GuestRecord> guestList = getList<GuestRecord>("guests.csv");

    system("cls");
    cout << strConst.GuestMenu << endl;
    cout << "\nChoose an option: ";
    int x;
    while (!(cin >> x)) {
        cout << "Invalid input. Please enter a number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (x) {
    case 0:
        manageEventMonitoring();
        break;
    case 1: { // Import Guest List
        system("cls");
        if (clientList.empty()) {
            cout << "\nNo clients available." << endl;
            cin.get();
            manageGuests();
            break;
        }
        cout << "\nAvailable Clients:\n";
        for (size_t i = 0; i < clientList.size(); ++i) {
            cout << i + 1 << ". " << clientList[i].person.name << " (Wedding: " << clientList[i].weddingDate << ")\n";
        }
        cout << "\nSelect client number to import guest list (0 to cancel): ";
        size_t clientChoice;
        cin >> clientChoice;
        if (clientChoice == 0 || clientChoice > clientList.size()) {
            cout << "\nInvalid selection. Guest import cancelled." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            manageGuests();
            break;
        }
        cout << "\nEnter guest details (name,contact,RSVP status; one per line, empty line to finish):\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        string line;
        int newGuestID = guestList.empty() ? 1 : guestList.back().guestID + 1;
        while (getline(cin, line) && !line.empty()) {
            stringstream ss(line);
            string name, contact, rsvp;
            getline(ss, name, ',');
            getline(ss, contact, ',');
            getline(ss, rsvp);
            GuestRecord guest;
            guest.guestID = newGuestID++;
            guest.person.name = name;
            guest.person.contact = contact;
            guest.rsvpStatus = rsvp;
            guest.mealPreference = "Not specified";
            guest.tableNumber = -1;
            guestList.push_back(guest);
        }
        saveList(guestList, "guests.csv");
        cout << "\nGuest list imported successfully!" << endl;
        cin.get();
        manageGuests();
        break;
    }
    case 2: { // Update Guest RSVP
        system("cls");
        if (clientList.empty()) {
            cout << "\nNo clients available." << endl;
            cin.get();
            manageGuests();
            break;
        }
        cout << "\nAvailable Clients:\n";
        for (size_t i = 0; i < clientList.size(); ++i) {
            cout << i + 1 << ". " << clientList[i].person.name << " (Wedding: " << clientList[i].weddingDate << ")\n";
        }
        cout << "\nSelect client number to update guest RSVP (0 to cancel): ";
        size_t clientChoice;
        cin >> clientChoice;
        if (clientChoice == 0 || clientChoice > clientList.size()) {
            cout << "\nInvalid selection. RSVP update cancelled." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            manageGuests();
            break;
        }
        vector<GuestRecord> clientGuests;
        for (const auto& guest : guestList) {
            if (guest.guestID >= clientList[clientChoice - 1].clientID * 1000 &&
                guest.guestID < (clientList[clientChoice - 1].clientID + 1) * 1000) {
                clientGuests.push_back(guest);
            }
        }
        if (clientGuests.empty()) {
            cout << "\nNo guests found for this client." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            manageGuests();
            break;
        }
        cout << "\nGuests for " << clientList[clientChoice - 1].person.name << ":\n";
        for (size_t i = 0; i < clientGuests.size(); ++i) {
            cout << i + 1 << ". " << clientGuests[i].person.name << " (RSVP: " << clientGuests[i].rsvpStatus << ")\n";
        }
        cout << "\nSelect guest number to update RSVP (0 to cancel): ";
        size_t guestChoice;
        cin >> guestChoice;
        if (guestChoice == 0 || guestChoice > clientGuests.size()) {
            cout << "\nInvalid selection. RSVP update cancelled." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            manageGuests();
            break;
        }
        cout << "Enter new RSVP status for " << clientGuests[guestChoice - 1].person.name << ": ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, clientGuests[guestChoice - 1].rsvpStatus);
        for (auto& guest : guestList) {
            if (guest.guestID == clientGuests[guestChoice - 1].guestID) {
                guest.rsvpStatus = clientGuests[guestChoice - 1].rsvpStatus;
                break;
            }
        }
        saveList(guestList, "guests.csv");
        cout << "\nGuest RSVP updated successfully!" << endl;
        cin.get();
        manageGuests();
        break;
    }
    case 3: { // Show Guest List
        system("cls");
        if (clientList.empty()) {
            cout << "\nNo clients available." << endl;
            cin.get();
            manageGuests();
            break;
        }
        cout << "\nAvailable Clients:\n";
        for (size_t i = 0; i < clientList.size(); ++i) {
            cout << i + 1 << ". " << clientList[i].person.name << " (Wedding: " << clientList[i].weddingDate << ")\n";
        }
        cout << "\nSelect client number to show guest list (0 to cancel): ";
        size_t clientChoice;
        cin >> clientChoice;
        if (clientChoice == 0 || clientChoice > clientList.size()) {
            cout << "\nInvalid selection." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            manageGuests();
            break;
        }
        vector<GuestRecord> clientGuests;
        for (const auto& guest : guestList) {
            if (guest.guestID >= clientList[clientChoice - 1].clientID * 1000 &&
                guest.guestID < (clientList[clientChoice - 1].clientID + 1) * 1000) {
                clientGuests.push_back(guest);
            }
        }
        if (clientGuests.empty()) {
            cout << "\nNo guests found for this client." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            manageGuests();
            break;
        }
        cout << "\nGuests for " << clientList[clientChoice - 1].person.name << ":\n";
        for (size_t i = 0; i < clientGuests.size(); ++i) {
            cout << i + 1 << ". " << clientGuests[i].person.name << endl;
            cout << "   Contact: " << clientGuests[i].person.contact << endl;
            cout << "   RSVP Status: " << clientGuests[i].rsvpStatus << endl;
            cout << "   Meal Preference: " << clientGuests[i].mealPreference << endl;
            cout << "   Table Number: " << (clientGuests[i].tableNumber == -1 ? "Not assigned" : to_string(clientGuests[i].tableNumber)) << endl;
            cout << endl;
        }
        cout << "Total Guests: " << clientGuests.size() << endl;
        cout << "\nPress Enter to return to Guest Management Menu..." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        manageGuests();
        break;
    }
    default:
        cout << "Invalid option. Please try again." << endl;
        cin.get();
        manageGuests();
        break;
    }
}

void manageEventSchedule() {
    StringConst strConst;
    EventSchedule newSchedule;
    vector<Client> clientList = getList<Client>("clients.csv");
    vector<EventSchedule> scheduleList = getList<EventSchedule>("schedules.csv");
    vector<Package> packageList = getList<Package>("packages.csv");
    vector<Vendor> vendorList = getList<Vendor>("vendors.csv");

    system("cls");
    cout << strConst.ScheduleMenu << endl;
    cout << "\nChoose an option: ";
    int x;
    while (!(cin >> x)) {
        cout << "Invalid input. Please enter a number: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    switch (x) {
    case 0:
        manageEventMonitoring();
        break;
    case 1: { // Create Schedule
        system("cls");
        if (clientList.empty()) {
            cout << "\nNo clients available." << endl;
            cin.get();
            manageEventSchedule();
            break;
        }
        cout << "\nAvailable Clients:\n";
        for (size_t i = 0; i < clientList.size(); ++i) {
            cout << i + 1 << ". " << clientList[i].person.name << " (Wedding: " << clientList[i].weddingDate << ")\n";
        }
        cout << "\nSelect client number to create schedule (0 to cancel): ";
        size_t clientChoice;
        cin >> clientChoice;
        if (clientChoice == 0 || clientChoice > clientList.size()) {
            cout << "\nInvalid selection. Schedule creation cancelled." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            manageEventSchedule();
            break;
        }
        system("cls");
        cout << "\n=== Client Details ===" << endl;
        Client& client = clientList[clientChoice - 1];
        cout << "Client: " << client.person.name << endl;
        cout << "Partner: " << client.partnerName << endl;
        cout << "Wedding Date: " << client.weddingDate << endl;
        cout << "Package: " << client.selectedPackage << endl;
        for (const auto& pkg : packageList) {
            if (pkg.packageName == client.selectedPackage) {
                cout << "Package Description: " << pkg.description << endl;
                cout << "Package Price: $" << fixed << setprecision(2) << pkg.price << endl;
                break;
            }
        }
        cout << "Vendors: ";
        if (client.selectedVendors.empty()) {
            cout << "None" << endl;
        }
        else {
            for (size_t j = 0; j < client.selectedVendors.size(); ++j) {
                cout << client.selectedVendors[j];
                if (j < client.selectedVendors.size() - 1) cout << ", ";
            }
            cout << endl;
        }
        cout << "Payment Status: " << client.paymentStatus << endl;
        cout << "Total Payment: $" << fixed << setprecision(2) << client.totalPayment << endl;
        cout << "Amount Paid: $" << fixed << setprecision(2) << client.amountPaid << endl;
        cout << "\n=== Event Schedule ===" << endl;
        cout << "Enter schedule time (HH:MM): ";
        getline(cin, newSchedule.time);
        cout << "Enter activity: ";
        getline(cin, newSchedule.activity);
        newSchedule.scheduleID = scheduleList.empty() ? 1 : scheduleList.back().scheduleID + 1;
        newSchedule.clientID = client.clientID;
        newSchedule.weddingDate = client.weddingDate;
        scheduleList.push_back(newSchedule);
        saveList(scheduleList, "schedules.csv");
        cout << "\nSchedule created successfully!" << endl;
        cin.get();
        manageEventSchedule();
        break;
    }
    case 2: { // Update Schedule
        system("cls");
        if (clientList.empty()) {
            cout << "\nNo clients available." << endl;
            cin.get();
            manageEventSchedule();
            break;
        }
        cout << "\nAvailable Clients:\n";
        for (size_t i = 0; i < clientList.size(); ++i) {
            cout << i + 1 << ". " << clientList[i].person.name << " (Wedding: " << clientList[i].weddingDate << ")\n";
        }
        cout << "\nSelect client number to update schedule (0 to cancel): ";
        size_t clientChoice;
        cin >> clientChoice;
        if (clientChoice == 0 || clientChoice > clientList.size()) {
            cout << "\nInvalid selection. Schedule update cancelled." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            manageEventSchedule();
            break;
        }
        vector<EventSchedule> clientSchedules;
        for (const auto& schedule : scheduleList) {
            if (schedule.clientID == clientList[clientChoice - 1].clientID) {
                clientSchedules.push_back(schedule);
            }
        }
        if (clientSchedules.empty()) {
            cout << "\nNo schedules found for this client." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            manageEventSchedule();
            break;
        }
        system("cls");
        cout << "\n=== Client Details ===" << endl;
        Client& client = clientList[clientChoice - 1];
        cout << "Client: " << client.person.name << endl;
        cout << "Partner: " << client.partnerName << endl;
        cout << "Wedding Date: " << client.weddingDate << endl;
        cout << "Package: " << client.selectedPackage << endl;
        for (const auto& pkg : packageList) {
            if (pkg.packageName == client.selectedPackage) {
                cout << "Package Description: " << pkg.description << endl;
                cout << "Package Price: $" << fixed << setprecision(2) << pkg.price << endl;
                break;
            }
        }
        cout << "Vendors: ";
        if (client.selectedVendors.empty()) {
            cout << "None" << endl;
        }
        else {
            for (size_t j = 0; j < client.selectedVendors.size(); ++j) {
                cout << client.selectedVendors[j];
                if (j < client.selectedVendors.size() - 1) cout << ", ";
            }
            cout << endl;
        }
        cout << "Payment Status: " << client.paymentStatus << endl;
        cout << "Total Payment: $" << fixed << setprecision(2) << client.totalPayment << endl;
        cout << "Amount Paid: $" << fixed << setprecision(2) << client.amountPaid << endl;
        cout << "\n=== Event Schedule ===" << endl;
        for (size_t i = 0; i < clientSchedules.size(); ++i) {
            cout << i + 1 << ". " << clientSchedules[i].time << " - " << clientSchedules[i].activity << endl;
        }
        cout << "\nSelect schedule number to update (0 to cancel): ";
        size_t scheduleChoice;
        cin >> scheduleChoice;
        if (scheduleChoice == 0 || scheduleChoice > clientSchedules.size()) {
            cout << "\nInvalid selection. Schedule update cancelled." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            manageEventSchedule();
            break;
        }
        cout << "Enter new schedule time (HH:MM): ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, clientSchedules[scheduleChoice - 1].time);
        cout << "Enter new activity: ";
        getline(cin, clientSchedules[scheduleChoice - 1].activity);
        for (auto& schedule : scheduleList) {
            if (schedule.scheduleID == clientSchedules[scheduleChoice - 1].scheduleID) {
                schedule.time = clientSchedules[scheduleChoice - 1].time;
                schedule.activity = clientSchedules[scheduleChoice - 1].activity;
                break;
            }
        }
        saveList(scheduleList, "schedules.csv");
        cout << "\nSchedule updated successfully!" << endl;
        cin.get();
        manageEventSchedule();
        break;
    }
    case 3: { // Remove Schedule
        system("cls");
        if (clientList.empty()) {
            cout << "\nNo clients available." << endl;
            cin.get();
            manageEventSchedule();
            break;
        }
        cout << "\nAvailable Clients:\n";
        for (size_t i = 0; i < clientList.size(); ++i) {
            cout << i + 1 << ". " << clientList[i].person.name << " (Wedding: " << clientList[i].weddingDate << ")\n";
        }
        cout << "\nSelect client number to remove schedule (0 to cancel): ";
        size_t clientChoice;
        cin >> clientChoice;
        if (clientChoice == 0 || clientChoice > clientList.size()) {
            cout << "\nInvalid selection. Schedule removal cancelled." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            manageEventSchedule();
            break;
        }
        vector<EventSchedule> clientSchedules;
        for (const auto& schedule : scheduleList) {
            if (schedule.clientID == clientList[clientChoice - 1].clientID) {
                clientSchedules.push_back(schedule);
            }
        }
        if (clientSchedules.empty()) {
            cout << "\nNo schedules found for this client." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            manageEventSchedule();
            break;
        }
        system("cls");
        cout << "\n=== Client Details ===" << endl;
        Client& client = clientList[clientChoice - 1];
        cout << "Client: " << client.person.name << endl;
        cout << "Partner: " << client.partnerName << endl;
        cout << "Wedding Date: " << client.weddingDate << endl;
        cout << "Package: " << client.selectedPackage << endl;
        for (const auto& pkg : packageList) {
            if (pkg.packageName == client.selectedPackage) {
                cout << "Package Description: " << pkg.description << endl;
                cout << "Package Price: $" << fixed << setprecision(2) << pkg.price << endl;
                break;
            }
        }
        cout << "Vendors: ";
        if (client.selectedVendors.empty()) {
            cout << "None" << endl;
        }
        else {
            for (size_t j = 0; j < client.selectedVendors.size(); ++j) {
                cout << client.selectedVendors[j];
                if (j < client.selectedVendors.size() - 1) cout << ", ";
            }
            cout << endl;
        }
        cout << "Payment Status: " << client.paymentStatus << endl;
        cout << "Total Payment: $" << fixed << setprecision(2) << client.totalPayment << endl;
        cout << "Amount Paid: $" << fixed << setprecision(2) << client.amountPaid << endl;
        cout << "\n=== Event Schedule ===" << endl;
        for (size_t i = 0; i < clientSchedules.size(); ++i) {
            cout << i + 1 << ". " << clientSchedules[i].time << " - " << clientSchedules[i].activity << endl;
        }
        cout << "\nSelect schedule number to remove (0 to cancel): ";
        size_t scheduleChoice;
        cin >> scheduleChoice;
        if (scheduleChoice == 0 || scheduleChoice > clientSchedules.size()) {
            cout << "\nInvalid selection. Schedule removal cancelled." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            manageEventSchedule();
            break;
        }
        scheduleList.erase(remove_if(scheduleList.begin(), scheduleList.end(),
            [&clientSchedules, &scheduleChoice](const EventSchedule& s) {
                return s.scheduleID == clientSchedules[scheduleChoice - 1].scheduleID;
            }), scheduleList.end());
        saveList(scheduleList, "schedules.csv");
        cout << "\nSchedule removed successfully!" << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        manageEventSchedule();
        break;
    }
    case 4: { // Show All Schedules
        system("cls");
        if (clientList.empty()) {
            cout << "\nNo clients available." << endl;
            cin.get();
            manageEventSchedule();
            break;
        }
        cout << "\nAvailable Clients:\n";
        for (size_t i = 0; i < clientList.size(); ++i) {
            cout << i + 1 << ". " << clientList[i].person.name << " (Wedding: " << clientList[i].weddingDate << ")\n";
        }
        cout << "\nSelect client number to show schedules (0 to cancel): ";
        size_t clientChoice;
        cin >> clientChoice;
        if (clientChoice == 0 || clientChoice > clientList.size()) {
            cout << "\nInvalid selection." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            manageEventSchedule();
            break;
        }
        vector<EventSchedule> clientSchedules;
        for (const auto& schedule : scheduleList) {
            if (schedule.clientID == clientList[clientChoice - 1].clientID) {
                clientSchedules.push_back(schedule);
            }
        }
        system("cls");
        cout << "\n=== Client Details ===" << endl;
        Client& client = clientList[clientChoice - 1];
        cout << "Client: " << client.person.name << endl;
        cout << "Partner: " << client.partnerName << endl;
        cout << "Wedding Date: " << client.weddingDate << endl;
        cout << "Package: " << client.selectedPackage << endl;
        for (const auto& pkg : packageList) {
            if (pkg.packageName == client.selectedPackage) {
                cout << "Package Description: " << pkg.description << endl;
                cout << "Package Price: $" << fixed << setprecision(2) << pkg.price << endl;
                break;
            }
        }
        cout << "Vendors: ";
        if (client.selectedVendors.empty()) {
            cout << "None" << endl;
        }
        else {
            for (size_t j = 0; j < client.selectedVendors.size(); ++j) {
                cout << client.selectedVendors[j];
                if (j < client.selectedVendors.size() - 1) cout << ", ";
            }
            cout << endl;
        }
        cout << "Payment Status: " << client.paymentStatus << endl;
        cout << "Total Payment: $" << fixed << setprecision(2) << client.totalPayment << endl;
        cout << "Amount Paid: $" << fixed << setprecision(2) << client.amountPaid << endl;
        cout << "\n=== Event Schedule ===" << endl;
        if (clientSchedules.empty()) {
            cout << "\nNo schedules found for this client." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            manageEventSchedule();
            break;
        }
        for (size_t i = 0; i < clientSchedules.size(); ++i) {
            cout << i + 1 << ". " << clientSchedules[i].time << " - " << clientSchedules[i].activity << endl;
        }
        cout << "Total Schedules: " << clientSchedules.size() << endl;
        cout << "\nPress Enter to return to Schedule Management Menu..." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        manageEventSchedule();
        break;
    }
    default:
        cout << "Invalid option. Please try again." << endl;
        cin.get();
        manageEventSchedule();
        break;
    }
}

int main() {
    showLoginScreen();
    system("pause");
    return 0;
}