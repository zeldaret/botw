#pragma once

#include <Havok/Physics2012/Dynamics/Phantom/hkpPhantom.h>

class hkpPhantomListener {
public:
    virtual ~hkpPhantomListener() = default;

    virtual void phantomAddedCallback(hkpPhantom* phantom) {}

    virtual void phantomRemovedCallback(hkpPhantom* phantom) {}

    virtual void phantomShapeSetCallback(hkpPhantom* phantom) {
        if (phantom->getWorld()) {
            phantomRemovedCallback(phantom);
            phantomAddedCallback(phantom);
        }
    }

    virtual void phantomDeletedCallback(hkpPhantom* phantom) {}
};
