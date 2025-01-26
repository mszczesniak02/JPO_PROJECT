#include "csv_file.hpp"

// THE SAME AS IN THE TXT CLASS, BUT SEPARATOR AS PARAMETER
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
        print_error("File is empty."); // IF FILE IS EMPTY, SHOW NO RESULT
    }else{
        
        vector<vector<string>> contents_expoded; // split each row by a separator
        for (int i = 0; i< contents_.size();i++){
            contents_expoded.push_back( split(contents_[i], ","));
        }
    
        int records = contents_expoded.size() - 1;
        int columns = contents_expoded[0].size();

        // INITIAL VALUES, FOR SURE WILL BE OVERWRITTEN
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

                // COUNT THE FREQUENCIES OF EACH COLUMN
            
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
            // INSERT INTO TUPLE FOR EASIER MAINTAINING

            // stats_ vector is empty at first, that fixes it
            if( s_.size() == 0) s_.resize(columns); 
            s_[current_col].column_name_ = contents_expoded[0][current_col];

            swap(s_[current_col].most_popular_,  most);
            swap(s_[current_col].least_popular_, least); 
            // THE ONLY WAY I COULD MAKE IT WORK TO INSERT DATA INTO TUPLE IN A CLASS
            
            current_col++;

        }

    }
}
