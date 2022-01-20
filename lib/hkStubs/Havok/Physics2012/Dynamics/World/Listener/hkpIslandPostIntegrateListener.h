#pragma once

class hkpSimulationIsland;
class hkStepInfo;

class hkpIslandPostIntegrateListener {
public:
    virtual ~hkpIslandPostIntegrateListener() = default;

    virtual void postIntegrateCallback(hkpSimulationIsland* island, const hkStepInfo& stepInfo) = 0;
};
