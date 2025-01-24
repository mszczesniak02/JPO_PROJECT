#pragma once

#include "file.hpp"

class TXT_File : public File {
public:
    explicit TXT_File(string dir) : File(std::move(dir)) {}

    void analyze() override {
        cout << "Analyzing TXT File: " << dir_ << "\n";
        for (size_t i = 0; i < contents_.size(); ++i) {
            cout << "Row " << i + 1 << ": " << contents_[i] << "\n";
        }
    }
};