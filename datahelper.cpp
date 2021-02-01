
// STILL IN DEVELOPMENT, DO NOT USE

#include "datahelper.h"

DataHelper::DataHelper() {
    filename_ = "";
}

DataHelper::DataHelper(const string & filename) {
    filename_ = filename;
}

vector<vector<string>> DataHelper::getColumns() {
    vector<vector<string>> result; 

    //read file contents into a single string
    std::ifstream text(filename_);
	stringstream strStream;
	if (text.is_open()) {
		strStream << text.rdbuf();
	}
    string test = strStream.str();

    //converts string of file contents into vector of strings, where each element is one row
    vector <string> vofrows;
    unsigned index = 0;
    for (unsigned i = 0; i < test.size(); i++){ //loops through every char of the string, looking for the newline char
        if (test[i] == '\n'){
            string row = test.substr(index, i-index);
            vofrows.push_back(row); //add each row
            index = i + 1;
        }
    }
    vofrows.push_back(test.substr(index, test.size()-index)); //push back last line in the file
    
    int countcommas = 0;
    bool isAirportfile = true;
    string top = vofrows[0];
    for (unsigned i = 0; i < top.size(); i++){
        if (top[i] == ','){
            countcommas++;
        }
    }
    if (countcommas > 10) isAirportfile = true;
    else isAirportfile = false;

    for (unsigned i = 0; i < vofrows.size(); i++){ //loop through every row
        string temprow = vofrows[i];
        vector <string> colcontents;
        unsigned strindex = 0;
        for (unsigned j = 0; j < temprow.size(); j++){ //loop through the string in each row
            if (temprow[j] == ','){
                if (isAirportfile && (colcontents.size() == 1 || colcontents.size() == 2)){ 
                    //used to check if there are any commas in the airport or city name
                    if (temprow[j-1] == '"'){ //check to see if comma is properly seperating elements
                        string token = temprow.substr(strindex, j-strindex);
                        colcontents.push_back(token); //add each element in the row
                        strindex = j + 1;   
                    }
                }else{
                    string token = temprow.substr(strindex, j-strindex); 
                    colcontents.push_back(token); //add each element in the row
                    strindex = j + 1;
                }
            }
        }
        colcontents.push_back(temprow.substr(strindex, temprow.size()-strindex) );//add last element of each row
        result.push_back(colcontents);
    }

    return result;
}