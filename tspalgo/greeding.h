#ifndef TSPALGO_GREEDING_HEADER
#define TSPALGO_GREEDING_HEADER

#include "../tspinst/tspinst.h"
#include "../utility/util.h"
#include "./ans.h"

orderIndexT calcNearestPoint(TspInst* inst, pointIndexT origin, vector<pointIndexT>& orderIdxs) noexcept;

TspAns constructWithGreedingByOneOrigin(TspInst* inst, pointIndexT origin) noexcept {
    vector<pointIndexT> unSelectedPointIndexs(inst->pointsDim);
    for ( int i = 0; i < inst->pointsDim; i++ ) {
        unSelectedPointIndexs[i] = i; 
    } 

    vector<pointIndexT> order;
    for ( int i = 0; i < inst->pointsDim; i++ ) {
        orderIndexT nearestOrderIdx = calcNearestPoint(inst, origin, unSelectedPointIndexs);
        pointIndexT nearestPointIndex = unSelectedPointIndexs[nearestOrderIdx];

        origin = nearestPointIndex;
        order.push_back(nearestPointIndex);
        removeItemFast(unSelectedPointIndexs, nearestOrderIdx);
    }

    return TspAns(inst, order);
}

TspAns constructWithGreedingByAllOrigin(TspInst* inst ) noexcept {
    TspAns bestAns = constructWithGreedingByOneOrigin(inst, 0);
    bestAns.calcScore();

    for ( int i = 1; i < inst->pointsDim; i++ ) {
        TspAns ans = constructWithGreedingByOneOrigin(inst, i);
        ans.calcScore();

        if ( ans.score < bestAns.score ) {
            bestAns = ans;
        }
    }
    return bestAns;
};



//戻り値：orderIdxsの中でoriginに最も近い点のインデックス
orderIndexT calcNearestPoint(TspInst* inst, pointIndexT origin, vector<pointIndexT>& orderIdxs) noexcept {
    if ( orderIdxs.size() == 0 ) {
        cout << "[calcNearestPoint] Error: orderIdxs is empty" << endl;
        exit(2);
    }

    orderIndexT nearestOrderIdx = 0;
    ecDistancT nearestDist = inst->pointDistance(origin, orderIdxs[nearestOrderIdx]);

    for ( int i = 1; i < orderIdxs.size(); i++ ) {
        ecDistancT dist = inst->pointDistance(origin, orderIdxs[i]);
        if ( dist < nearestDist ) {
            nearestDist = dist;
            nearestOrderIdx = i;
        }
    }

    return nearestOrderIdx;
} 

#endif