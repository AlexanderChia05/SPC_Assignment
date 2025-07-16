#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib>      // for clear screen 
using namespace std;

struct Person {
    string name;
    string email;
    string contact;

    Person() = default;

    Person(const string& line)
    {
        if (!line.empty())
        {
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
        Client(const string& line)
        {
            if (!line.empty())
            {
                stringstream ss(line);
                getline(ss, specialRequest);
            }
        }
    };

    struct Guest {
        string rsvpStatus;

        Guest() = default;
        Guest(const string& line)
        {
            if (!line.empty())
            {
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
        Vendor(const string& line)
        {
            if (!line.empty())
            {
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

    Admin(const string& line)
    {
        if (!line.empty())
        {
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
    // Package Level + Wedding Venue + Catering Menu
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
    // Guest List + Event Schedule + Vendor
    string name;
    string guestContact;
    string rsvpStatus;

    string time;
    string date;
    string activity;
};

struct PaymentRecord {
    bool paid;         // true if payment is made, false otherwise
    double amount;
    string status;     // e.g., "Pending", "Completed", "Failed"
};

struct PaymentManage {
    string paymentInvoice;
    vector<PaymentRecord> paymentRecords;
};

struct StringConst {
    const string LOGO_X = "                XXXXXXXXXXXXX                          \n"
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

    const string LOGO_O = "                \033[1;37mXXXXXXXXXXXXX\033[0m                          \n"
        "            \033[1;37mXXXX             XXXX\033[0m                      \n"
        "         \033[1;37mXXX                     XXX\033[0m                   \n"
        "       \033[1;37mXX                           XX\033[0m                 \n"
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
        "            \033[1;37mXXXX             XXXX\033[0m                      \n"
        "                \033[1;37mXXXXXXXXXXXXX\033[0m                          \n";
};




// Template function to read things
template <typename T>
vector<T> getList(string filename) {
    ifstream file(filename);
    vector<T> list;

    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
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
        for (auto r : list) {
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



int main() {
    vector <Admin> adminList = getList<Admin>("admins.csv");

    StringConst logo;

    system("clear");
    cout << "Guys Yongjin gay." << endl;
    cout << logo.LOGO_X << endl << endl;;
    cout << logo.LOGO_O << endl;
    cout.flush();
}
