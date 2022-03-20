#pragma once

class hkpTypedBroadPhaseHandlePair;

class hkpBroadPhaseListener {
public:
    virtual ~hkpBroadPhaseListener() = default;

    virtual void addCollisionPair(hkpTypedBroadPhaseHandlePair& pair) = 0;

    virtual void removeCollisionPair(hkpTypedBroadPhaseHandlePair& pair) = 0;
};
