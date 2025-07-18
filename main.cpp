#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib>      // for system("cls")
#include <limits>
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

struct Client {
    int clientID = 0;
    Person person;

    string partnerName;
    string weddingDate;
    string selectedPackage;
    string venueBooked;

    float totalPayment = 0;
    float amountPaid = 0;
    string paymentStatus;
    string specialRequest;

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
            getline(ss, selectedPackage, ',');
            getline(ss, venueBooked, ',');
            ss >> totalPayment; ss.ignore();
            ss >> amountPaid; ss.ignore();
            getline(ss, paymentStatus, ',');
            getline(ss, specialRequest);
        }
    }

    void toString(string& line) const {
        line = to_string(clientID) + "," + person.name + "," + person.email + "," + person.contact + "," + partnerName + "," + weddingDate + "," +
            selectedPackage + "," + venueBooked + "," +
            to_string(totalPayment) + "," + to_string(amountPaid) + "," +
            paymentStatus + "," + specialRequest;
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
    };
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

struct VendorRecord {
    int vendorID;
    Person contactPerson;

    string companyName;
    string serviceType;
    float serviceCost = 0;

    VendorRecord() = default;

    VendorRecord(const string& line) {
        if (!line.empty()) {
            stringstream ss(line);
            ss >> vendorID; ss.ignore();
            getline(ss, contactPerson.name, ',');
            getline(ss, contactPerson.email, ',');
            getline(ss, contactPerson.contact, ',');
            getline(ss, companyName, ',');
            getline(ss, serviceType, ',');
            ss >> serviceCost;
        }
    }

    void toString(string& line) const {
        line = to_string(vendorID) + "," + contactPerson.name + "," + contactPerson.email + "," + contactPerson.contact + "," +
            companyName + "," + serviceType + "," + to_string(serviceCost);
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

struct EventManage {

};

struct MonitorManage {
    string name;
    string guestContact;
    string rsvpStatus;
    string time;
    string date;
    string activity;
};

struct PaymentRecord {
    bool paid;
    double amount;
    string status;
};

struct PaymentManage {
    string paymentInvoice;
    vector<PaymentRecord> paymentRecords;
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
        " | 4. Show All Client                      |  \n"
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
};




// Functions
bool login();



// Screens
void showLoginScreen();

void showMainScreen();

void manageClient();

void manageEvent();

void managePackage();       // Package = Venue + Catering = Payment Bill
void manageVenue();
void manageCatering();

void manageAdmin();




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



void showLoginScreen() {
    StringConst strConst;

    while (true) {
        system("cls");
        cout << strConst.LOGO_X << endl;
        cout << strConst.TITLE << endl;
        cout << "Please login to continue." << endl << endl;

        if (login()) {
            showMainScreen();
            break; // Exit loop on successful login
        }
        else {
            cout << "CREDENTIAL DO NOT MATCH. Press Enter to try again..." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
            cin.get();
        }
    }
}

void showMainScreen() {
    StringConst strConst;
    int x;

    system("cls"); // Clear console for Windows
    cout << strConst.LOGO_O << endl;
    cout << strConst.TITLE << endl << endl;

    // Menu 
    cout << strConst.MainScMenu << endl;
    cout << "\nChoose an option: ";

    if (cin >> x) {
        switch (x) {
        case 0:
            system("cls");
            cout << strConst.LOGO_X << endl;
            cout << strConst.TITLE << endl << endl;
            cout << "\nExiting the system. Goodbye!" << endl;
            exit(0); // Exit the program
            break;

        case 1:
            manageClient();
            break;

        case 2:
            manageEvent();
            break;

        case 3:
            //manageVendor()
            break;

        case 4:
            //managePayment();
            break;

        case 5:
            manageAdmin();
            break;

        default:
            cout << "Invalid option. Please try again." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
            cin.get(); // Wait for user input before retrying
            showMainScreen(); // Show main screen again
            break;
        }
    }
}

void manageClient() {
    StringConst strConst;
    Client newClient;
    int x;

    vector <Client> clientList = getList <Client>("clients.csv");

    system("cls");
    cout << strConst.ClientMenu << endl;
    cout << "\nChoose an option: ";
    cin.clear();
    cin >> x;

    switch (x) {
    case 0: // Back to Main Menu
        showMainScreen();
        break;

    case 1: // Create Client
        system("cls");

        cout << "Enter client name: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, newClient.person.name);
        cout << "Enter client email: ";
        getline(cin, newClient.person.email);
        cout << "Enter client contact: ";
        getline(cin, newClient.person.contact);
        cout << "Enter partner name: ";
        getline(cin, newClient.partnerName);
        cout << "Enter wedding date (YYYY-MM-DD): ";
        getline(cin, newClient.weddingDate);

        clientList.push_back(newClient);
        saveList(clientList, "clients.csv");
        cout << "\nClient created successfully!" << endl;
        newClient.clientID = clientList.size();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
    case 0: // Back to Main Menu
        showMainScreen();
        break;

    case 1: // Manage Wedding Package
        managePackage();
        break;

    case 2: // Manage Venue
        manageVenue();
        break;

    case 3: // Manage Catering
        manageCatering();
        break;

    default:
        cout << "Invalid option. Please try again." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        manageEvent(); // Show event management menu again
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
    case 0: // Back to Event Management
        manageEvent();
        break;

    case 1: // Create Package
        system("cls");
        if (venueList.empty() || caterList.empty()) {
            cout << "\nCannot create package: No venues or catering options available." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            managePackage();
            break;
        }

        // Display available venues
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

        // Display available catering options
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

        // Input package details
        cout << "\nEnter package name: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, newPackage.packageName);
        cout << "Enter package description: ";
        getline(cin, newPackage.description);
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

        // Calculate total price
        newPackage.price = venueList[venueChoice - 1].rentalCost + (caterList[caterChoice - 1].costPerPerson * guestCount);
        newPackage.packageID = packageList.empty() ? 1 : packageList.back().packageID + 1;

        // Combine venue and catering names in description for clarity
        newPackage.description += " (Venue: " + venueList[venueChoice - 1].venueName +
            ", Catering: " + caterList[caterChoice - 1].caterName + ")";

        packageList.push_back(newPackage);
        saveList(packageList, "packages.csv");
        cout << "\nPackage created successfully! Total Price: $" << fixed << setprecision(2) << newPackage.price << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        managePackage();
        break;

    case 2: // Remove Package
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

        // Display all packages
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

    case 3: // Update Package
        system("cls");
        if (packageList.empty()) {
            cout << "\nNo packages available to update." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            managePackage();
            break;
        }

        // Display all packages
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

        // Update package details
        cout << "\nEnter new package name: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, packageList[updt - 1].packageName);
        cout << "Enter new package description: ";
        getline(cin, packageList[updt - 1].description);

        // Optionally update venue and catering
        cout << "\nDo you want to update the venue? (1 for Yes, 0 for No): ";
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
            cin >> venueChoice;
            if (venueChoice == 0 || venueChoice > venueList.size()) {
                cout << "\nVenue unchanged." << endl;
            }
            else {
                packageList[updt - 1].price -= packageList[updt - 1].price; // Reset price (simplified)
                packageList[updt - 1].price += venueList[venueChoice - 1].rentalCost;
                packageList[updt - 1].description += " (Venue: " + venueList[venueChoice - 1].venueName + ")";
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
                    packageList[updt - 1].description += " (Catering: " + caterList[caterChoice - 1].caterName + ")";
                }
            }
        }

        saveList(packageList, "packages.csv");
        cout << "\nPackage updated successfully! New Price: $" << fixed << setprecision(2) << packageList[updt - 1].price << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        managePackage();
        break;

    case 4: // Show All Packages
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
        case 0: // Back to Event Management
            manageEvent();
            break;

        case 1: // Create Venue
            system("cls");
            cout << "Enter venue name: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
            newVenue.venueID = venueList.empty() ? 1 : venueList.back().venueID + 1; // Assign new ID

            venueList.push_back(newVenue);
            saveList(venueList, "venues.csv");
            cout << "\nVenue created successfully!" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get(); // Wait for user input before proceeding
            manageVenue();
            break;

        case 2: // Remove Venue
            system("cls");
            size_t kill;

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

            // Display all the venues
            for (size_t i = 0; i < venueList.size(); ++i) {
                cout << i + 1 << ". " << venueList[i].venueName << endl;
            }
            cout << "\nEnter number to remove venue (0 to cancel): ";
            cin >> kill;
            if (kill > 0 && kill <= venueList.size()) {
                venueList.erase(venueList.begin() + kill - 1); // Remove the selected venue
                saveList(venueList, "venues.csv");
                cout << "\nVenue removed successfully!" << endl;
            }
            else {
                cout << "\nInvalid selection. No venue removed." << endl;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get(); // Wait for user input before proceeding
            manageVenue();
            break;

        case 3: // Update Venue
            system("cls");
            size_t updt;
            if (venueList.empty()) {
                cout << "\nNo venues available to update." << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                manageVenue();
                break;
            }
            // Display all the venues
            for (size_t i = 0; i < venueList.size(); ++i) {
                cout << i + 1 << ". " << venueList[i].venueName << endl;
            }
            cout << "\nEnter number to update venue (0 to cancel): ";
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

        case 4: // Show All Venues
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
        case 0: // Back to Event Management
            manageEvent();
            break;

        case 1: // Create Catering
            system("cls");
            cout << "Enter catering name: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
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

        case 2: // Remove Catering
            system("cls");
            size_t kill;
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

            // Display all the caterings
            for (size_t i = 0; i < caterList.size(); ++i) {
                cout << i + 1 << ". " << caterList[i].caterName << endl;
            }
            cout << "\nEnter number to remove catering (0 to cancel): ";
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

        case 3: // Update Catering
            system("cls");
            size_t updt;

            if (caterList.empty()) {
                cout << "\nNo catering options available to update." << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.get();
                manageCatering();
                break;
            }
            // Display all the caterings
            for (size_t i = 0; i < caterList.size(); ++i) {
                cout << i + 1 << ". " << caterList[i].caterName << endl;
            }
            cout << "\nEnter number to update catering (0 to cancel): ";
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

        case 4: // Show All Catering
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

void manageAdmin() {
    StringConst strConst;
    Admin newAdmin;
    int x;

    vector<Admin> adminList = getList <Admin>("admins.csv");

    system("cls");
    cout << strConst.AdminMenu << endl;
    cout << "\nChoose an option: ";
    cin.clear();
    cin >> x;

    switch (x) {
    case 0: // Back to Main Menu
        showMainScreen();
        break;

    case 1: // Create Admin
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
        manageAdmin();
        break;

    case 2: // Remove Admin
        size_t kill;
        system("cls");


        // Validations
        if (adminList.empty()) {
            cout << "\nNo admins available to remove." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            manageAdmin();
        }

        if (adminList.size() == 1) {
            cout << "\nCannot remove the last admin!" << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            manageAdmin();
        }


        // START display all the admins
        for (size_t i = 0; i < adminList.size(); ++i) {
            cout << i + 1 << ". " << adminList[i].username << endl;
        }

        cout << "\nEnter number to remove admin (0 to cancel): ";
        cin >> kill;

        if (kill > 0 && kill <= adminList.size()) {
            adminList.erase(adminList.begin() + kill - 1); // Remove the selected admin
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

    case 3: // Update Admin
        size_t updt;
        system("cls");

        for (size_t i = 0; i < adminList.size(); ++i) {
            cout << i + 1 << ". " << adminList[i].username << endl;
        }

        cout << "\nEnter number to update admin password (0 to cancel): ";
        cin >> updt;

        if (updt > 0 && updt <= adminList.size()) {

            cout << "Enter new password for " << adminList[updt - 1].username << ": "; // Update the selected admin's password
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
            getline(cin, adminList[updt - 1].password); // Update password


            saveList(adminList, "admins.csv");
            cout << "\nAdmin updated successfully!" << endl;
        }
        else {
            cout << "\nInvalid selection. No admin updated." << endl;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        manageAdmin();
        break;

    case 4: // Show All Admin
        system("cls");

        for (size_t i = 0; i < adminList.size(); ++i) {
            cout << i + 1 << ". " << adminList[i].username << "" << endl;
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
        manageAdmin(); // Show admin management menu again
        break;
    }

}


// Starting Point
int main() {
    showLoginScreen();
    system("pause");
    return 0;
}