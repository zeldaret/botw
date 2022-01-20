#pragma once

class hkpWorld;

class hkpWorldDeletionListener {
public:
    virtual ~hkpWorldDeletionListener() = default;

    virtual void worldDeletedCallback(hkpWorld* world) = 0;
    virtual void worldRemoveAllCallback(hkpWorld* world) {}
};
