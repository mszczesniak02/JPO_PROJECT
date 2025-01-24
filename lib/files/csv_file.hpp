#pragma once

#include "file.hpp"

class CSV_File : public File {
public:
    explicit CSV_File(string dir) : File(std::move(dir)) {}

    void analyze() override {
        cout << "Analyzing CSV File: " << dir_ << "\n";
        for (size_t i = 0; i < contents_.size(); ++i) {
            cout << "Row " << i + 1 << ": " << contents_[i] << "\n";
        }
    }
};