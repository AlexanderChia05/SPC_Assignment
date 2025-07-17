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

    struct Client {
        string specialRequest;

        Client() = default;
        Client(const string& line) {
            if (!line.empty()) {
                stringstream ss(line);
                getline(ss, specialRequest);
            }
        }
    };

    struct Guest {
        string rsvpStatus;

        Guest() = default;
        Guest(const string& line) {
            if (!line.empty()) {
                stringstream ss(line);
                getline(ss, rsvpStatus);
            }
        }
    };

    struct Vendor {
        string companyName;
        string contactPerson;
        string contactNumber;

        Vendor() = default;
        Vendor(const string& line) {
            if (!line.empty()) {
                stringstream ss(line);
                getline(ss, companyName, ',');
                getline(ss, contactPerson, ',');
                getline(ss, contactNumber);
            }
        }

        void toString(string& line) const {
            line = companyName + "," + contactPerson + "," + contactNumber;
        }
    };
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
    string packageName;
    double price;
    string venueName;
    int capacity;
    int numOfTables;
    double cost;
    string menuName;
    double pricePerTable;
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
        "                XXXXXXXXXXXXX                          \n"
        "            XXXX             XXXX                      \n"
        "         XXX                     XXX                   \n"
        "       XX                           XX                 \n"
        "      X     XXXX             XXXX     X                \n"
        "    XX    XXXXXXXX         XXXXXXXX    XX              \n"
        "   X     XXXXXXXXXXXX   XXXXXXXXXXXX     X             \n"
        "  X     XXXXXXXXXXXXXXXXXXXXXXXXXXXXX     X            \n"
        "  X     XXXXXXXXXXXXXXXXXXXXXXXXXXXXX     X            \n"
        " X      XXXXXXXXXXXXXXXXXXXXXXXXXXXXX      X           \n"
        " X      XXXXXXXXXXXXXXXXXXXXXXXXXXXXX      X           \n"
        " X       XXXXXXXXXXXXXXXXXXXXXXXXXXX       X           \n"
        " X       XXXXXXXXXXXXXXXXXXXXXXXXXXX       X           \n"
        " X         XXXXXXXXXXXXXXXXXXXXXXX         X           \n"
        "  X         XXXXXXXXXXXXXXXXXXXXX         X            \n"
        "  X         XXXXXXXXXXXXXXXXXXXXX         X            \n"
        "   X          XXXXXXXXXXXXXXXXX          X             \n"
        "    XX           XXXXXXXXXXX           XX              \n"
        "      X            XXXXXXX            X                \n"
        "       XX            XXX            XX                 \n"
        "         XXX          X          XXX                   \n"
        "            XXXX             XXXX                      \n"
        "                XXXXXXXXXXXXX                          \n";

    const string LOGO_O = 
        "                \033[1;37mXXXXXXXXXXXXX\033[0m                                              \n"
        "            \033[1;37mXXXX             XXXX\033[0m                                          \n"
        "         \033[1;37mXXX                     XXX\033[0m                                       \n"
        "       \033[1;37mXX                           XX\033[0m                                     \n"
        "      \033[1;37mX     \033[1;31mXXXX             XXXX\033[1;37m     X\033[0m                \n"
        "    \033[1;37mXX    \033[1;31mXXXXXXXX         XXXXXXXX\033[1;37m    XX\033[0m              \n"
        "   \033[1;37mX     \033[1;31mXXXXXXXXXXXX   XXXXXXXXXXXX\033[1;37m     X\033[0m             \n"
        "  \033[1;37mX     \033[1;31mXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\033[1;37m     X\033[0m            \n"
        "  \033[1;37mX     \033[1;31mXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\033[1;37m     X\033[0m            \n"
        " \033[1;37mX      \033[1;31mXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\033[1;37m      X\033[0m           \n"
        " \033[1;37mX      \033[1;31mXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\033[1;37m      X\033[0m           \n"
        " \033[1;37mX       \033[1;31mXXXXXXXXXXXXXXXXXXXXXXXXXXX\033[1;37m       X\033[0m           \n"
        " \033[1;37mX       \033[1;31mXXXXXXXXXXXXXXXXXXXXXXXXXXX\033[1;37m       X\033[0m           \n"
        " \033[1;37mX         \033[1;31mXXXXXXXXXXXXXXXXXXXXXXX\033[1;37m         X\033[0m           \n"
        "  \033[1;37mX         \033[1;31mXXXXXXXXXXXXXXXXXXXXX\033[1;37m         X\033[0m            \n"
        "  \033[1;37mX         \033[1;31mXXXXXXXXXXXXXXXXXXXXX\033[1;37m         X\033[0m            \n"
        "   \033[1;37mX          \033[1;31mXXXXXXXXXXXXXXXXX\033[1;37m          X\033[0m             \n"
        "    \033[1;37mXX           \033[1;31mXXXXXXXXXXX\033[1;37m           XX\033[0m              \n"
        "      \033[1;37mX            \033[1;31mXXXXXXX\033[1;37m            X\033[0m                \n"
        "       \033[1;37mXX            \033[1;31mXXX\033[1;37m            XX\033[0m                 \n"
        "         \033[1;37mXXX          \033[1;31mX\033[1;37m          XXX\033[0m                   \n"
        "            \033[1;37mXXXX             XXXX\033[0m                                          \n"
        "                \033[1;37mXXXXXXXXXXXXX\033[0m                                              \n";

    const string TITLE =
        " +-----------------------------------------+   \n"
        " | - Celestial Wedding  Event Management - |   \n"
        " +-----------------------------------------+     ";


	const string MainScMenu =
		" +-----------------------------------------+   \n"
		" | 1. Manage Events                        |   \n"
		" | 2. Manage Guests                        |   \n"
		" | 3. Manage Vendors                       |   \n"
		" | 4. View Payment Records                 |   \n"
        " | 5. Manage Admin                         |   \n"
		" | 6. Exit                                 |   \n"
		" +-----------------------------------------+     ";


    const string AdminMenu = 
        " +-----------------------------------------+   \n"
        " |    Admin Management                     |   \n"
        " +-----------------------------------------+   \n"
        " | 1. Create Admin                         |   \n"
        " +-----------------------------------------+   \n"
        " | 2. Remove Admin                         |   \n"
        " +-----------------------------------------+   \n"
        " | 3. Update Admin                         |   \n"
        " +-----------------------------------------+   \n"
        " | 4. Show All Admin                       |   \n"
        " +-----------------------------------------+   \n"
        " | 0. Back to Main Menu                    |   \n"
        " +-----------------------------------------+     ";
};




// Functions
bool login();




// Screens
void showLoginScreen();

void showMainScreen();

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
    } else {
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





// Show login screen with retry loop
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
        } else {
            cout << "CREDENTIAL DO NOT MATCH. Press Enter to try again..." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
            cin.get();
        }
    }
}

// Show main screen with menu options
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
        case 1:
            //manageEvent();
            break;
        case 2:
            //manageGuest();
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
        case 6:
            system("cls");
            cout << strConst.LOGO_X << endl;
            cout << strConst.TITLE << endl << endl;
            cout << "\nExiting the system. Goodbye!" << endl;
            exit(0); // Exit the program
        default:
            cout << "Invalid option. Please try again." << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
            cin.get(); // Wait for user input before retrying
            showMainScreen(); // Show main screen again
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

    switch(x) {
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
            cin.get();
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
            cin.get();
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