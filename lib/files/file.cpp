#include "file.hpp"

namespace fs = std::filesystem;


void File::print_error(string error_msg){
    cout<<error_msg<<'\n';
}

File::File(string dir){ // opens a file and inserts its contents into a vector
    
    dir_ = dir;
    fstream f;
    f.open(dir_, fstream::in);
    if (f.is_open()){
        string line;
        while(getline(f,line)) contents_.push_back(line);
        total_files_opened_++;
        f.close();
    }else{
        print_error("FILE COULD NOT BE OPENED.\n");
    }
}
vector<string>& File::get_contents(){
    return contents_;
}
string File::get_dir(){
    return dir_;
}
unsigned int File::total_files_opened_ = 0;

Properties& File::get_file_properties(){
    return properties_;
}

void File::print_file_properties(){
    Properties p = get_file_properties();

    cout<< "File path:\t"  << p.dir_absolute_;
    cout<< "File extension:\t"  << p.extention_;
    cout<< "File size:\t"  << p.size_;
    cout << "File isFile: "<< p.is_dir_;
    cout<< "File is ReadOnly:\t"  << !p.perms_;
}

void File::file_properties(){
    // i know that the file exists, but if the file gets removed while looking at it, do sth
    const fs::path& temp_dir = dir_;
    if(fs::exists(temp_dir)){
        properties_.dir_absolute_ =  (fs::absolute(temp_dir)).generic_string(); 
        properties_.extention_ = (temp_dir.extension()).generic_string(); // insert lamba func to operate on extention names: .txt -> text file
        properties_.size_ = std::to_string((fs::file_size(temp_dir)));
        
        if (fs::is_regular_file(temp_dir)) {
            properties_.is_dir_ = false;
        } else if (fs::is_directory(temp_dir)) {
            properties_.is_dir_ = true;
        } 

        // Tylko do odczytu
        auto perms = fs::status(temp_dir).permissions();
        properties_.perms_ = (perms & fs::perms::owner_write) == fs::perms::none;
    }else{
        // set as null ? Could Not Read

    }

}