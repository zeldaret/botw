#pragma once

class hkpSimulationIsland;
class hkStepInfo;

class hkpIslandPostCollideListener {
public:
    virtual ~hkpIslandPostCollideListener() = default;

    virtual void postCollideCallback(hkpSimulationIsland* Island, const hkStepInfo& stepInfo) = 0;
};
