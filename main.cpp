#include<iostream>
#include<cstdio>

#include "utility/util.h"
#include "tspinst/tspinst.h"
#include "tspalgo/ans.h"
#include "tspalgo/greeding.h"

using namespace std;

int main() {

    string foldaPath = "problems";
    string fileName = "berlin52";
    string filePath = foldaPath + "\\" + fileName + ".tsp";

    try {
        TspInst inst = loadTspInst(filePath);

        cout << "[Log] TSP Instance loaded" << endl;
        cout << "ProblemName: " << inst.problemnName << ", PointsDim:" << inst.pointsDim << endl;

        TspAns ans = constructWithGreedingByAllOrigin(&inst);
        ans.calcScore();

        cout << endl;
        cout << ans.toString() << endl;


    } catch ( myTspErrT e ) {
        cout << e << endl;
    }
}