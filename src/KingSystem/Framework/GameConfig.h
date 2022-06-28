#pragma once

#include <prim/seadSafeString.h>

class GameConfig {
public:
    static GameConfig* getInstance() { return sInstancePtr; }

    char _0[0x3dd];
    bool _3dd;
    char _3de[0x3b];
    bool _419;
    sead::SafeString mPatrolFeatures;

private:
    static GameConfig* sInstancePtr;
};
