#ifndef TSPALGO_ANS_HEADER
#define TSPALGO_ANS_HEADER   

#include <set>
#include <string>

#include "../tspinst/tspinst.h"

using orderIndexT = int;
const ecDistancT NULL_SCORE = -1;

class TspAns {
    public:
        TspInst* inst;
        vector<pointIndexT> order;
        ecDistancT score;

        TspAns(TspInst* inst, vector<pointIndexT> order) {
            this->inst = inst;
            this->score = NULL_SCORE;
            this->order = order;
        }

        bool isScoreCalculated() noexcept {
            return score != NULL_SCORE;
        }

        string toString() noexcept; 
        int pointDim() noexcept;
        Point point(pointIndexT index) noexcept;
        orderIndexT nextOrder(orderIndexT index) noexcept;
        orderIndexT prevOrder(orderIndexT index) noexcept;
        ecDistancT calcScore() noexcept;
        bool isCorrectAnswer() noexcept;
        bool isValidOrder(orderIndexT) noexcept;
};

string TspAns::toString() noexcept {
    string str = "TspAns { ";
    str += "ProblemName: " + inst->problemnName; 
    str += ", Score: " + to_string(score);
    str += "\n";

    str += "Order: [ ";
    for ( int i = 0; i < order.size(); i++ ) {
        char buffer[100];

        if ( i >= 70 ) {
            sprintf(buffer, " ...(%d)", order.size()-i);
            str += " ...";
            break;
        }
        sprintf(buffer, "%d ", order[i]);
        str += string(buffer);
    }
    str += "] }\n";
    return str;
}

Point TspAns::point( orderIndexT idx) noexcept {
    pointIndexT pointIndex = order[idx];
    return inst->point(pointIndex);
}

orderIndexT TspAns::nextOrder(orderIndexT idx) noexcept {
    return (idx+1) % inst->pointsDim;
}

orderIndexT TspAns::prevOrder(orderIndexT idx) noexcept {
    return (idx-1+inst->pointsDim) % inst->pointsDim;
}

int TspAns::pointDim() noexcept {
    return inst->pointsDim;
}

ecDistancT TspAns::calcScore() noexcept {
    if ( isScoreCalculated() ) {
        return score;
    }
    if (!isCorrectAnswer()) {
        cout << "[calcScore] Error: order is not correct" << endl;
        exit(2);
    }

    ecDistancT sumScore = 0;
    for ( int i = 0; i < order.size(); i++ ) {
        orderIndexT nextIdx = nextOrder(i);
        Point p1 = point(i);
        Point p2 = point(nextIdx);
        
        sumScore += p1.distance(p2);
    } 

    score = sumScore;
    return sumScore;
}

bool TspAns::isCorrectAnswer() noexcept {
    if ( order.size() != inst->pointsDim ) {
        cout << "[isCorrectAnswer] Error: order size is not equal to pointsDim" << endl;
        return false;
    }

    set<pointIndexT> pointSet;
    for ( pointIndexT idx : order ) {
        if ( idx < 0 || idx >= inst->pointsDim ) {
            cout << "[isCorrectAnswer] Error: order index out of range" << endl;
            return false;
        }

        if ( pointSet.find(idx) != pointSet.end() ) {
            cout << "[isCorrectAnswer] Error: duplicate index in order" << endl;
            return false;
        }

        pointSet.insert(idx);
    }

    return true;
}

bool TspAns::isValidOrder(orderIndexT idx) noexcept {
    return ( idx >= 0 ) && ( idx < inst->pointsDim );
}



#endif