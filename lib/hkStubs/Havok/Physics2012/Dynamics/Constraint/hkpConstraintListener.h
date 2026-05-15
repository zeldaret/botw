#pragma once

#include <Havok/Common/Base/Types/hkBaseTypes.h>

class hkpConstraintInstance;
class hkpWorld;

struct hkpConstraintBrokenEvent {
    enum EventSource {
        EVENT_SOURCE_UNKNOWN,
        EVENT_SOURCE_BREAKABLE_CONSTRAINT,
        EVENT_SOURCE_FLEXIBLE_JOINT,
    };

    hkpConstraintBrokenEvent(hkpWorld* world, hkpConstraintInstance* i, EventSource es)
        : m_world(world), m_constraintInstance(i), m_eventSource(es), m_eventSourceDetails(0),
          m_constraintBroken(true), m_actualImpulse(0.0f), m_impulseLimit(0.0f) {}

    hkpWorld* m_world;
    hkpConstraintInstance* m_constraintInstance;

    hkEnum<EventSource, hkUint8> m_eventSource;
    hkUint8 m_eventSourceDetails;
    hkBool m_constraintBroken;
    hkReal m_actualImpulse;
    hkReal m_impulseLimit;
};

class hkpConstraintListener {
public:
    virtual ~hkpConstraintListener() {}

    virtual void constraintAddedCallback(hkpConstraintInstance* constraint) {}

    virtual void constraintRemovedCallback(hkpConstraintInstance* constraint) {}

    virtual void constraintDeletedCallback(hkpConstraintInstance* constraint) {}

    virtual void constraintBreakingCallback(const hkpConstraintBrokenEvent& event) {}
};
