#include<iostream>
#include<cstdio>

#include "utility/util.h"
#include "tspinst/tspinst.h"
#include "tspalgo/ans.h"
#include "tspalgo/greeding.h"
#include "tspalgo/2opt.h"
#include "utility/exetimer.h"

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

        ExeTimer timer1 = startTimer();
        TspAns ans = constructWithGreedingByAllOrigin(&inst);
        ans.calcScore();
        timer1.stop();

        cout << endl;
        cout << "[Log] Finish Greeding Search" << endl;
        cout << ans.toString() << endl;
        cout << "Elapsed Time: " << timer1.elapsedMilliseconds() << "ms" << endl;

        TspAns constAns = ans;

        cout << endl;
        ExeTimer timer2 = startTimer();
        long long moveCount = localSearchBy2Opt(ans);
        timer2.stop();
        
        cout << "[Log] Finish 2-opt search. MoveCount: " << moveCount << endl;
        printf("[Log] Finish 2-opt search. MoveCount: %lld, Time: %lld\n", moveCount, timer2.elapsedMilliseconds());
        cout << ans.toString() << endl;

        long long wholeTime = timer1.elapsedMilliseconds() + timer2.elapsedMilliseconds();
        printf("[Log] All Process Was Done, Time : %lldms\n", wholeTime);

        cout << endl;
        printf("[Result 1] Construct Answer : time %lld\n", timer1.elapsedMilliseconds()); 
        cout << constAns.toString() << endl;

        cout << endl;
        printf("[Result 2] 2-opt Answer : time %lld\n", timer2.elapsedMilliseconds());
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
    cout << "Start Program" << endl;
    main1(argc, argv);
}