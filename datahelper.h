
// STILL IN DEVELOPMENT, DO NOT USE

#pragma once

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;
using std::ifstream;
using std::stringstream;

/** 
 * info for routes dataset:
 * data takes the following form
 * airline, airlineID, sourceAirport, sourceAirportID, destAirport, destAirportID, codeshare, stops, equipment
 * 
 **/

class DataHelper {
    public:
        DataHelper();
        DataHelper(const string & filename);
        vector<vector<string>> getColumns(); 
        string filename_;
        string filecontent;
};