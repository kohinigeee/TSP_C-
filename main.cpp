#include<iostream>
#include<cstdio>

#include "utility/util.h"

using namespace std;

int main() {

    string foldaPath = "problems";
    string fileName = "berlin52";
    string filePath = foldaPath + "\\" + fileName + ".tsp";

    
    FILE* file;

    file = fopen(filePath.c_str(), "r");

    if ( file == nullptr ) {
        cerr << "Error: file not found : " << filePath <<endl;
        return 1;
    }

    char buffer[1000];

    while (fgets(buffer, sizeof(buffer), file) != nullptr) {
        string str(buffer);
        cout << str;
        if ( str == "NODE_COORD_SECTION\n") {
            break;
        }

        vector<string> tokens = split(str, ':');

        for ( string s : tokens ) {
            string tmps = trim(s);
        }
    }

    while (fgets(buffer, sizeof(buffer), file) != nullptr) {
        string pointStr(buffer);

        if ( pointStr == "EOF\n" ) {
            break;
        }

        pointStr = trim(string(buffer));
        cout << "Point Str = " << pointStr << endl;
        const vector<string> tokens = split(pointStr, ' ');
        try {
            const int idx = stoi(tokens[0]);
            const double x = stod(tokens[1]);
            const double y = stod(tokens[2]);

            printf("idx = %d, x = %f, y = %f\n", idx, x, y);
        } catch ( exception e ) {
            cerr << "Error: " << e.what() << endl;
        }
    }

    fclose(file);

    return 0;
}