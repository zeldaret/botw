#pragma once
#include <prim/seadSafeString.h>

class GameConfig {
public:
    static GameConfig* getInstance() { return sInstancePtr; }

    char mPad0[0x3dd];
    bool mField3dd;
    char mPad1[0x3b];
    bool mField419;
    sead::SafeString mPatrolFeatures;

private:
    static GameConfig* sInstancePtr;
};
