#include "rating.h"
#include <iomanip>
#include <algorithm>
#include <limits>

using namespace std;

void rateVendor(vector<Vendor>& vendorList, const string& filename) {
    if (vendorList.empty()) {
        cout << "No vendors available to rate.\n";
        return;
    }

    cout << "\nAvailable Vendors:\n";
    for (size_t i = 0; i < vendorList.size(); ++i) {
        cout << i + 1 << ". " << vendorList[i].vendorType 
             << " - " << vendorList[i].person.name
             << " (Current Rating: " << fixed << setprecision(1)
             << vendorList[i].rating << " / 5 from "
             << vendorList[i].ratingCount << " reviews)\n";
    }

    int choice;
    string input;
    while (true) {
        cout << "\nSelect vendor number to rate (0 to cancel): ";
        cin >> input;

        // Check if input is all digits (or "0")
        bool valid = !input.empty() && all_of(input.begin(), input.end(), ::isdigit);

        if (!valid) {
            cout << "Invalid input. Please enter a whole number between 1 and " << vendorList.size() << " (0 to cancel).\n";
            continue;
        }

        // Convert to int
        choice = stoi(input);

        if (choice == 0) {
            cout << "Cancelled!\n";
            return;
        }
        else if (choice < 0 || choice > (int)vendorList.size()) {
            cout << "Invalid input. Enter a number between 1 and " << (int)vendorList.size() << " (0 to cancel).\n ";
            continue;
        }
        else 
            break;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    double stars;
    while (true) {
        cout << "Enter rating (1-5) [0 to cancel]: ";
        if (!(cin >> stars)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter a number between 1 and 5 (0 to cancel).\n";
            continue;
        }
        else if (stars == 0) {
            cout << "Rating cancelled\n";
            return;
        }
        else if (stars < 1 || stars > 5) {
            cout << "Invalid range. Enter a number between 1 and 5 (0 to cancel).\n";
            continue;
        }
        else 
            break;
    }

    Vendor& v = vendorList[choice - 1];
    v.rating = (v.rating * v.ratingCount + stars) / (v.ratingCount + 1);
    v.ratingCount++;

    cout << "Thank you! New average rating: " << fixed << setprecision(1)
         << v.rating << " / 5 (" << v.ratingCount << " reviews)\n";

    saveList(vendorList, filename);  // write back to CSV
}

void showTopVendors(const vector<Vendor>& vendorList) {
    if (vendorList.empty()) {
        cout << "No vendors available.\n";
        return;
    }

    vector<Vendor> sortedList = vendorList;
    sort(sortedList.begin(), sortedList.end(),
        [](const Vendor& a, const Vendor& b) {
            return a.rating > b.rating;  // highest first
        });

    cout << "\n===== Top Rated Vendors =====\n";
    for (size_t i = 0; i < sortedList.size(); ++i) {
        cout << i + 1 << ". " << sortedList[i].vendorType 
             << " - " << sortedList[i].person.name
             << " | Rating: " << fixed << setprecision(1)
             << sortedList[i].rating << " / 5 (" 
             << sortedList[i].ratingCount << " reviews)\n";
    }
}
