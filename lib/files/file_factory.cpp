#include "file.hpp"
#include "csv_file.hpp"
#include "text_file.hpp"
#include "html_file.hpp"
#include "css_file.hpp"
#include <filesystem>
#include <string>
#include <stdexcept>

namespace fs = std::filesystem;

class File_Factory {
public:
    static File* createFile(const std::string& dir) {
        const std::string extension = fs::path(dir).extension().string();

        if (extension == ".txt") {
            return new TXT_File(dir);  // Create a new TXT_File object and return a raw pointer
        } else if (extension == ".csv") {
            return new CSV_File(dir);  // Create a new CSV_File object and return a raw pointer
        } else if (extension == ".css") {
            return new CSS_File(dir);  // Create a new CSS_File object and return a raw pointer
        } else if (extension == ".html") {
            return new HTML_File(dir);  // Create a new HTML_File object and return a raw pointer
        }

        // Unsupported file type:
        throw std::invalid_argument("Unsupported file type: " + extension);
    }
};
