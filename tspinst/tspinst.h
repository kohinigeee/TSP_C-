#ifndef TSPINST_TSPINST_HEADER
#define TSPINST_TSPINST_HEADER

#include "./point.h"
#include "../utility/util.h"

#include <string>
#include <vector>
#include <iostream>
#include <map>

using pointIndexT = int;
using myTspErrT = std::string; 

using namespace std;

struct tspFileInfos {
    std::string problemName;
    std::string problemType;
    std::string comment;
    int dimension;
    std::string edgeWeightType;
};

tspFileInfos newTspFileInfos( std::map<std::string, std::string> &tokens ) throw ( myTspErrT ) {
    tspFileInfos infos;

    string problemName = tokens["NAME"];
    if ( problemName == "" ) {
        throw "[newTspFileInfos] Error: NAME not found";
    }

    string problemType = tokens["TYPE"];
    string comment = tokens["COMMENT"];
    int dimension;
    try {
        dimension = stoi(tokens["DIMENSION"]);
    } catch ( exception e ) {
        throw "[newTspFileInfos] Error: DIMENSION not found";
    } 

    if ( dimension <= 0 ) {
        throw "[newTspFileInfos] Error: DIMENSION <= 0";
    }

    string edgeWeightType = tokens["EDGE_WEIGHT_TYPE"];

    infos.problemName = problemName;
    infos.problemType = problemType;
    infos.comment = comment;
    infos.dimension = dimension;
    infos.edgeWeightType = edgeWeightType;

    return infos;
}

class TspInst {

public:

    std::string problemnName;
    std::vector<Point> points;
    int pointsDim;

    TspInst( std::string problemName, std::vector<Point> points ) {
        this->problemnName = problemName;
        this->points = points;
        this->pointsDim = points.size();
    }

    std::string string();
    Point& point( pointIndexT i );
};


TspInst loadTspInst( std::string filePath) throw ( myTspErrT ) {
    FILE* file;

    file = fopen(filePath.c_str(), "r");   

    if ( file == nullptr ) {
        throw "[loadTspInst] Error: file not found : " + filePath;
    }

    char buffer[1000];
    map<string, string> infoTokens;    

    while (fgets(buffer, sizeof(buffer), file) != nullptr) {
        string str(buffer);
        if ( str == "NODE_COORD_SECTION\n") {
            break;
        }

        vector<string> tokens = split(str, ':');
        if ( tokens.size() < 2 ) {
            continue;
        }

        infoTokens[trim(tokens[0])] = trim(tokens[1]);
    }

    tspFileInfos infos;
    vector<Point> points;
    try {
        infos = newTspFileInfos(infoTokens);

        for ( int i = 0; i < infos.dimension; i++ ) {
            fgets(buffer, sizeof(buffer), file);

            const string pointStr = trim(string(buffer));
            const vector<string> tokens = split(pointStr, ' ');
            const int idx = stoi(tokens[0]);
            const double x = stod(tokens[1]);
            const double y = stod(tokens[2]);

            points.push_back(Point(x, y, idx));
        }


    } catch ( myTspErrT e ) {
        throw sprintf("[loadTspInst] Error: %s", e.c_str());
    } catch ( exception e ) {
        throw sprintf("[loadTspInst] Error: %s", e.what());
    }

    fclose(file);

    return TspInst(infos.problemName, points);
}


#endif