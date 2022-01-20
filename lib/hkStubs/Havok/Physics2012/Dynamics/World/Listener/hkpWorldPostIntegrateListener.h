#pragma once

class hkpWorld;
class hkpEntity;
class hkStepInfo;

class hkpWorldPostIntegrateListener {
public:
    virtual ~hkpWorldPostIntegrateListener() = default;

    virtual void postIntegrateCallback(hkpWorld* world, const hkStepInfo& stepInfo) = 0;
};
