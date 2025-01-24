#include "file.hpp"
#include "csv_file.hpp"
#include "text_file.hpp"
#include "code_file.hpp"
#include "html_file.hpp"
#include "tsv_file.hpp"
#include "css_file.hpp"


class File_Factory {
public:
    static std::unique_ptr<File> createFile(const string& dir) {
        const string extension = fs::path(dir).extension().string();

        if (extension == ".txt") {
            return std::make_unique<TXT_File>(dir);
        } else if (extension == ".csv") {
            return std::make_unique<CSV_File>(dir);
        } else if (extension == ".c" || extension == ".h") {
            return std::make_unique<CODE_File>(dir);
        }else if (extension == ".css" ) {
            return std::make_unique<CSS_File>(dir);
        }else if (extension == ".html") {
            return std::make_unique<HTML_File>(dir);
        }else if (extension == ".tsv") {
            return std::make_unique<TSV_File>(dir);
        }

        // type not supported:
        throw std::invalid_argument("Unsupported file type: " + extension);
    }
};
