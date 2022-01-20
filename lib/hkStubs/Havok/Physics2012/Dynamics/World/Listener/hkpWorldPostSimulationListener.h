#pragma once

class hkpWorld;
class hkpEntity;
class hkStepInfo;

class hkpWorldPostSimulationListener {
public:
    virtual ~hkpWorldPostSimulationListener() = default;

    virtual void postSimulationCallback(hkpWorld* world) = 0;
    virtual void inactiveEntityMovedCallback(hkpEntity* entity) {}
};
