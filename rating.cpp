#include "rating.h"
#include <iomanip>
#include <algorithm>

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

    cout << "\nSelect vendor number to rate (0 to cancel): ";
    int choice;
    cin >> choice;
    if (choice <= 0 || choice > (int)vendorList.size()) return;

    cout << "Enter rating (1–5): ";
    int stars;
    cin >> stars;
    while (stars < 1 || stars > 5) {
        cout << "Invalid. Enter rating (1–5): ";
        cin >> stars;
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
