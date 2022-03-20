#pragma once

#include <Havok/Common/Base/Types/Geometry/Aabb/hkAabb.h>
#include <Havok/Physics2012/Dynamics/Phantom/hkpPhantom.h>

class hkpCdPointCollector;
struct hkpLinearCastInput;
struct hkpWorldRayCastInput;
struct hkpWorldRayCastOutput;

class hkpAabbPhantom : public hkpPhantom {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpAabbPhantom)
    HK_DECLARE_REFLECTION()

    explicit hkpAabbPhantom(const hkAabb& aabb, hkUint32 collisionFilterInfo = 0);
    explicit hkpAabbPhantom(hkFinishLoadedObjectFlag flag);
    ~hkpAabbPhantom() override;

    hkpPhantomType getType() const override;

    inline hkArray<hkpCollidable*>& getOverlappingCollidables();

    void castRay(const hkpWorldRayCastInput& input, hkpRayHitCollector& collector) const;
    void castRay(const hkpWorldRayCastInput& input, hkpWorldRayCastOutput& output) const;

    void linearCast(const hkpCollidable* const toBeCast, const hkpLinearCastInput& input,
                    hkpCdPointCollector& castCollector, hkpCdPointCollector* startCollector) const;

    void calcAabb(hkAabb& aabb) override;
    void addOverlappingCollidable(hkpCollidable* collidable) override;
    hkBool isOverlappingCollidableAdded(const hkpCollidable* collidable) override;
    void removeOverlappingCollidable(hkpCollidable* collidable) override;
    hkpPhantom* clone() const override;

    void setAabb(const hkAabb& newAabb);
    inline const hkAabb& getAabb() const;

protected:
    hkMotionState* getMotionState() override { return nullptr; }

    friend class hkpPhantomBatchMoveUtil;

    hkAabb m_aabb;
    hkArray<hkpCollidable*> m_overlappingCollidables;

public:
    void ensureDeterministicOrder() override;

    class OrderByUid;
    hkBool m_orderDirty;

public:
    // Internal.
    void deallocateInternalArrays() override;
};

inline hkArray<hkpCollidable*>& hkpAabbPhantom::getOverlappingCollidables() {
    return m_overlappingCollidables;
}

inline const hkAabb& hkpAabbPhantom::getAabb() const {
    return m_aabb;
}
