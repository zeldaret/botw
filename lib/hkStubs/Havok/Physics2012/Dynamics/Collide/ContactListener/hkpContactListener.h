#pragma once

class hkpCollisionEvent;
class hkpContactPointAddedEvent;
class hkpContactPointEvent;
class hkpContactPointRemovedEvent;
class hkpContactProcessEvent;

class hkpContactListener {
public:
    virtual void contactPointCallback(const hkpContactPointEvent& event) {}

    virtual void collisionAddedCallback(const hkpCollisionEvent& event) {}

    virtual void collisionRemovedCallback(const hkpCollisionEvent& event) {}

    void registerForEndOfStepContactPointCallbacks(const hkpCollisionEvent& event);

    void unregisterForEndOfStepContactPointCallbacks(const hkpCollisionEvent& event);

    virtual ~hkpContactListener() = default;

public:
    // Deprecated.
    virtual void contactPointAddedCallback(hkpContactPointAddedEvent& event) {}
    // Deprecated.
    virtual void contactPointRemovedCallback(hkpContactPointRemovedEvent& event) {}
    // Deprecated.
    virtual void contactProcessCallback(hkpContactProcessEvent& event) {}
};
