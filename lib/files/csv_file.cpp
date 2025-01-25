#include "csv_file.hpp"


vector<string> CSV_File::split(string s, const string& delimiter) {
    
    vector<string> tokens;
    size_t pos = 0;
    string token;
    while ((pos = s.find(delimiter)) != string::npos) {
            token = s.substr(0, pos);
            tokens.push_back(token);
            s.erase(0, pos + delimiter.length());
    }
    tokens.push_back(s);
    return tokens;
};


void CSV_File::analyze(){    
    if (contents_.empty()) {
        print_error("File is empty.");
    }else{
        vector<vector<string>> contents_expoded; // split each row by a separator
        for (int i = 0; i< contents_.size();i++){
            contents_expoded.push_back( split(contents_[i], ","));
        }
        // contents_.clear(); // free some space
        // contents_.shrink_to_fit(); 

        // read lines in another functions, that way itll be faster
        int records = contents_expoded.size() - 1;
        int columns = contents_expoded[0].size();

        int current_col = 0;
        int most_amount;        // 
        int least_amount = 999; // if anything accures more then once, change the least_amout to that 
        while ( current_col != columns){ // go through every column and analyze the most/least frequent cells
            

            string least_word;
            string most_word;
        
            map<string, int> frequency;
            for (int i = 1; i< records; i++){ 
                if (i == 1){
                    most_amount     = frequency[contents_expoded[i][current_col]] ;
                    least_amount    = frequency[contents_expoded[records - i][current_col]];
                }
                if (frequency.find(contents_expoded[i][current_col]) != frequency.end()) {
                    frequency[contents_expoded[i][current_col]]++;
                
                }else    frequency[contents_expoded[i][current_col]] = 1;

                
            
            }// after analyzing the column, find the most used, the least used
            
            for(auto const& [k,v] : frequency){
                if (v >= most_amount) {
                    most_amount = v;
                    most_word = k;
                }else if (v <= least_amount++) {
                    least_amount = v;
                    least_word = k;
                }
            }
            
            // get the stats, return the statistics
            tuple<int,string>   most  = make_tuple(most_amount, most_word), 
                                least = make_tuple(least_amount, least_word);


            // stats_ vector is empty at first, that fixes it
            if( stats_.size() == 0) stats_.resize(columns); 
            stats_[current_col].column_name_ = contents_expoded[0][current_col];

            swap(stats_[current_col].most_popular_,  most);
            swap(stats_[current_col].least_popular_, least);
            
            current_col++;

        }

    }
}
