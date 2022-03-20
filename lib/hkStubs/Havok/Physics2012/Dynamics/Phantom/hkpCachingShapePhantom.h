#pragma once

#include <Havok/Physics2012/Dynamics/Phantom/hkpShapePhantom.h>

class hkpCollisionAgent;

class hkpCachingShapePhantom : public hkpShapePhantom {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpCachingShapePhantom)
    HK_DECLARE_REFLECTION()

    hkpCachingShapePhantom(const hkpShape* shape, const hkTransform& transform,
                           hkUint32 m_collisionFilterInfo = 0);
    explicit hkpCachingShapePhantom(hkFinishLoadedObjectFlag flag) : hkpShapePhantom(flag) {}

    ~hkpCachingShapePhantom() override;

    hkpPhantomType getType() const override;

    void setPositionAndLinearCast(const hkVector4& position, const hkpLinearCastInput& input,
                                  hkpCdPointCollector& castCollector,
                                  hkpCdPointCollector* startCollector) override;

    void setTransformAndLinearCast(const hkTransform& transform, const hkpLinearCastInput& input,
                                   hkpCdPointCollector& castCollector,
                                   hkpCdPointCollector* startCollector) override;

    hkpPhantom* clone() const override;

    void getClosestPoints(hkpCdPointCollector& collector, const hkpCollisionInput* input) override;

    void ensureDeterministicOrder() override;

    void getPenetrations(hkpCdBodyPairCollector& collector,
                         const hkpCollisionInput* input) override;

    struct CollisionDetail {
        HK_DECLARE_CLASS_ALLOCATOR(CollisionDetail)

        hkpCollisionAgent* m_agent;
        hkpCollidable* m_collidable;
    };

    inline hkArray<CollisionDetail>& getCollisionDetails();

    void addOverlappingCollidable(hkpCollidable* collidable) override;
    void removeOverlappingCollidable(hkpCollidable* collidable) override;
    hkBool isOverlappingCollidableAdded(const hkpCollidable* collidable) override;
    void updateShapeCollectionFilter() override;

protected:
    hkArray<CollisionDetail> m_collisionDetails;

public:
    void deallocateInternalArrays() override;

    hkBool m_orderDirty;

    class OrderByUid;
};

inline hkArray<hkpCachingShapePhantom::CollisionDetail>&
hkpCachingShapePhantom::getCollisionDetails() {
    return m_collisionDetails;
}
