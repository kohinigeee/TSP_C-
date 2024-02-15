#ifndef TSPALGO_2OPT_HEADER
#define TSPALGO_2OPT_HEADER

#include "./ans.h"
#include "../tspinst/point.h"
#include "../utility/util.h"

ecDistancT calc2OptScoreDif(TspAns&  ans, orderIndexT idx1, orderIndexT idx2) noexcept {

    const ecDistancT NULL_SCORE = 0;

    if (!ans.isValidOrder(idx1) || !ans.isValidOrder(idx2)) {
        std::cout << "[calc2OptScoreDif] Invalid index" << std::endl;
        return NULL_SCORE;
    }

    if ( idx1 == idx2 ) {
        return NULL_SCORE;
    }

    orderIndexT next1 = ans.nextOrder(idx1);
    orderIndexT next2 = ans.nextOrder(idx2);

    if ( next1 == idx2 || next2 == idx1 ) {
        return NULL_SCORE;
    }

    Point point1 = ans.point(idx1);
    Point point2 = ans.point(idx2);

    Point nextPoint1 = ans.point(next1);
    Point nextPoint2 = ans.point(next2);

    // 2-opt前のスコア
    ecDistancT beforeScore = point1.distance(nextPoint1) + point2.distance(nextPoint2);

    // 2-opt後のスコア
    ecDistancT afterScore = point1.distance(point2) + nextPoint1.distance(nextPoint2);

    return afterScore - beforeScore;
}

void Do2Opt(TspAns& ans, orderIndexT idx1, orderIndexT idx2) noexcept {
    if (!ans.isValidOrder(idx1) || !ans.isValidOrder(idx2)) {
        std::cout << "[Do2Opt] Invalid index" << std::endl;
        return;
    }

    if ( idx1 == idx2 ) {
        return;
    }

    orderIndexT next1 = ans.nextOrder(idx1);
    orderIndexT next2 = ans.nextOrder(idx2);

    if ( next1 == idx2 || next2 == idx1 ) {
        return;
    }

    if ( !ans.isScoreCalculated() ) {
        ans.calcScore();
    }

    std::vector<pointIndexT> newOrder;
    
    const ecDistancT scoreDif = calc2OptScoreDif(ans, idx1, idx2);
    ans.score += scoreDif;

    if ( next1 < idx2 ) {
        reverseItem(ans.order, next1, idx2);        
    } else {
        reverseItem(ans.order, next2, idx1);
    }
}

bool moveBestNeighborBy2Opt(TspAns& ans) noexcept {
    if ( !ans.isScoreCalculated() ) {
        ans.calcScore();
    }

    const orderIndexT n = ans.pointDim();
    ecDistancT bestDif = 0;
    orderIndexT bestIdx1 = -1;
    orderIndexT bestIdx2 = -1;

    for ( int i = 0; i < n; i++ ) {
        for ( int j = 0; j < n; j++ ) {
            orderIndexT idx1 = i, idx2 = j;
            ecDistancT scoreDif = calc2OptScoreDif(ans, idx1, idx2);

            if (scoreDif < bestDif) {
                bestDif = scoreDif;
                bestIdx1 = idx1;
                bestIdx2 = idx2;
            }
        }
    }

    if ( bestDif == 0 ) {
        return false;
    }

    Do2Opt(ans, bestIdx1, bestIdx2);
    return true;
}

long long localSearchBy2Opt(TspAns& ans) noexcept {
    long long cnt = 0;
    while ( moveBestNeighborBy2Opt(ans) ) {
        cnt++;
        cout << endl;
        cout << "[Log] 2-opt move count: " << cnt << endl;
        cout << ans.toString() << endl;
    }
    return cnt;
}

#endif