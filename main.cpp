#include <iostream>
#include <string>

#include "lib/files/file_factory.cpp"

using namespace std;


int main(){

    File_Factory f;

    vector<File*> files;


    files.push_back(f.createFile("B:\\win_docs\\pulpit\\JPO\\test\\test.csv"));
    files.push_back(f.createFile("B:\\win_docs\\pulpit\\JPO\\test\\test.html"));
    files.push_back(f.createFile("B:\\win_docs\\pulpit\\JPO\\test\\test.txt"));

    files[0]->analyze();

    for (File*& f : files){
        delete f;
    }
    
    return 0;
}