#pragma once

class hkpWorld;
class hkStepInfo;

class hkpWorldPostCollideListener {
public:
    virtual ~hkpWorldPostCollideListener() = default;

    virtual void postCollideCallback(hkpWorld* world, const hkStepInfo& stepInfo) = 0;
};
