#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

// ===== Shared Structs =====
struct Person {
    std::string name;
    std::string email;
    std::string contact;
};

struct Vendor {
    int vendorID = 0;
    Person person;
    std::string vendorType;
    float cost = 0;
    float rating = 0.0;
    int ratingCount = 0;

    Vendor() = default;

    Vendor(const std::string& line) {
        if (!line.empty()) {
            std::stringstream ss(line);
            ss >> vendorID; ss.ignore();
            getline(ss, vendorType, ',');
            getline(ss, person.name, ',');
            getline(ss, person.email, ',');
            getline(ss, person.contact, ',');
            ss >> cost; ss.ignore();
            ss >> rating; ss.ignore();
            ss >> ratingCount;
        }
    }

    void toString(std::string& line) const {
        line = std::to_string(vendorID) + "," + vendorType + "," +
               person.name + "," + person.email + "," + person.contact + "," +
               std::to_string(cost) + "," + std::to_string(rating) + "," +
               std::to_string(ratingCount);
    }
};

// ===== Shared Template Functions =====
template <typename T>
std::vector<T> getList(std::string filename) {
    std::ifstream file(filename);
    std::vector<T> list;
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            if (!line.empty()) {   // prevents blank vendors
                list.emplace_back(line);
            }
        }
        file.close();
    }
    return list;
}

template <typename T>
void saveList(const std::vector<T>& list, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& r : list) {
            std::string line;
            r.toString(line);
            file << line << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Error opening file: " << filename << std::endl;
    }
}

// ===== Rating Functions =====
void rateVendor(std::vector<Vendor>& vendorList, const std::string& filename);
void showTopVendors(const std::vector<Vendor>& vendorList);
