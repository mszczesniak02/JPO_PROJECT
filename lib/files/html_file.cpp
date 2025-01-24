#pragma once

#include "file.hpp"

class HTML_File : public File {
public:
    explicit HTML_File(string dir) : File(std::move(dir)) {}

    void analyze() override {
        cout << "Analyzing HTML File: " << dir_ << "\n";
        for (size_t i = 0; i < contents_.size(); ++i) {
            cout << "Row " << i + 1 << ": " << contents_[i] << "\n";
        }
    }
};