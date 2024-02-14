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

tspFileInfos newTspFileInfos( std::map<std::string, std::string> &tokens ) {
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

    std::string to_string() noexcept;
    Point point( pointIndexT i ) noexcept;
    ecDistancT pointDistance( pointIndexT i, pointIndexT j ) {
        Point p1 = point(i);
        Point p2 = point(j);
        return p1.distance(p2);
    }
};

string TspInst::to_string() noexcept {
    std::string str = "TspInst: ";
    char buffer[100];
    sprintf(buffer, "problemName : %s, pointsDim : %d\n", problemnName.c_str(), pointsDim);
    str += string(buffer);
    str += "Points { ";
    for ( int i = 0; i < pointsDim; i++ ) {
        sprintf(buffer, "(%d, %d, %d)", points[i].originalIndex, points[i].x, points[i].y);
        str += string(buffer);
        if ( i < pointsDim-1 ) {
            str += ", ";
        }
    }
    str += " }";

    return str; 
}

Point TspInst::point( pointIndexT i ) noexcept {
    return points[i];
}


TspInst loadTspInst( std::string filePath) {
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
        char buffer[256];
        sprintf(buffer, "[loadTspInst] Error: %s", e.c_str());
        throw string(buffer);
    } catch ( exception e ) {
        char buffer[256];
        sprintf(buffer, "[loadTspInst] Error: %s", e.what());
        throw string(buffer);
    }

    fclose(file);

    return TspInst(infos.problemName, points);
}


#endif