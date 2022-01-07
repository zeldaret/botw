#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics2012/Collide/Agent/Collidable/hkpCollidable.h>

struct hkpAgentNnEntry;

class hkpLinkedCollidable : public hkpCollidable {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpLinkedCollidable)
    HK_DECLARE_REFLECTION()

    struct CollisionEntry {
        HK_DECLARE_CLASS_ALLOCATOR(CollisionEntry)

        hkpAgentNnEntry* m_agentEntry;
        hkpLinkedCollidable* m_partner;
    };

    inline hkpLinkedCollidable(const hkpShape* shape, const hkMotionState* ms, int type = 0);
    explicit hkpLinkedCollidable(hkFinishLoadedObjectFlag flag) : hkpCollidable(flag) {}
    inline ~hkpLinkedCollidable();

    void getCollisionEntriesSorted(hkArray<CollisionEntry>& entries) const;

    hkArray<CollisionEntry>& getCollisionEntriesDeterministicUnchecked();
    const hkArray<CollisionEntry>& getCollisionEntriesDeterministicUnchecked() const;

    hkArray<CollisionEntry>& getCollisionEntriesNonDeterministic();
    const hkArray<CollisionEntry>& getCollisionEntriesNonDeterministic() const;

    void sortEntries();

protected:
    hkArray<CollisionEntry> m_collisionEntries;
};

inline hkpLinkedCollidable::hkpLinkedCollidable(const hkpShape* shape, const hkMotionState* ms,
                                                int type)
    : hkpCollidable(shape, ms, type) {}

inline hkpLinkedCollidable::~hkpLinkedCollidable() = default;

inline hkArray<hkpLinkedCollidable::CollisionEntry>&
hkpLinkedCollidable::getCollisionEntriesNonDeterministic() {
    return m_collisionEntries;
}

inline const hkArray<hkpLinkedCollidable::CollisionEntry>&
hkpLinkedCollidable::getCollisionEntriesNonDeterministic() const {
    return m_collisionEntries;
}
