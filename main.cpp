#include<iostream>
#include<cstdio>

#include "utility/util.h"
#include "tspinst/tspinst.h"
#include "tspalgo/ans.h"
#include "tspalgo/greeding.h"
#include "tspalgo/2opt.h"

using namespace std;

int main1(int argc, char** argv) {
    if ( argc < 2 ) {
        cout << "Usage: " << argv[0] << " <tspfile>" << endl;
        return 1;
    }


    string foldaPath = "problems";
    string fileName = string(argv[1]);
    string filePath = foldaPath + "\\" + fileName + ".tsp";

    try {
        TspInst inst = loadTspInst(filePath);

        cout << "[Log] TSP Instance loaded" << endl;
        cout << "ProblemName: " << inst.problemnName << ", PointsDim:" << inst.pointsDim << endl;

        TspAns ans = constructWithGreedingByAllOrigin(&inst);
        ans.calcScore();

        cout << endl;
        cout << "[Log] Finish Greeding Search" << endl;
        cout << ans.toString() << endl;

        cout << endl;
        long long moveCount = localSearchBy2Opt(ans);
        cout << "[Log] Finish 2-opt search. MoveCount: " << moveCount << endl;
        cout << ans.toString() << endl;

    } catch ( myTspErrT e ) {
        cout << e << endl;
    }

    return 0;
}

int mainTest() {
    vector<int> v = {1, 2, 3, 4, 5};
    reverseItem(v, 1, 3);

    for ( auto i : v ) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}

int main(int argc, char** argv) {
    main1(argc, argv);
}