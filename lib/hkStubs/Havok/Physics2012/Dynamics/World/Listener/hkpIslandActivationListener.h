#pragma once

class hkpSimulationIsland;

class hkpIslandActivationListener {
public:
    virtual ~hkpIslandActivationListener() = default;

    virtual void islandActivatedCallback(hkpSimulationIsland* island) = 0;
    virtual void islandDeactivatedCallback(hkpSimulationIsland* island) = 0;
};
