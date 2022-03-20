#pragma once

#include <Havok/Physics2012/Dynamics/Phantom/hkpShapePhantom.h>

class hkpSimpleShapePhantom : public hkpShapePhantom {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpSimpleShapePhantom)
    HK_DECLARE_REFLECTION()

    hkpSimpleShapePhantom(const hkpShape* shape, const hkTransform& transform,
                          hkUint32 m_collisionFilterInfo = 0);
    explicit hkpSimpleShapePhantom(hkFinishLoadedObjectFlag flag) : hkpShapePhantom(flag) {}
    ~hkpSimpleShapePhantom() override;

    hkpPhantomType getType() const override;

    void setPositionAndLinearCast(const hkVector4& position, const hkpLinearCastInput& input,
                                  hkpCdPointCollector& castCollector,
                                  hkpCdPointCollector* startCollector) override;

    void setTransformAndLinearCast(const hkTransform& transform, const hkpLinearCastInput& input,
                                   hkpCdPointCollector& castCollector,
                                   hkpCdPointCollector* startCollector) override;

    void getClosestPoints(hkpCdPointCollector& collector, const hkpCollisionInput* input) override;

    void ensureDeterministicOrder() override;

    void getPenetrations(hkpCdBodyPairCollector& collector,
                         const hkpCollisionInput* input) override;

    hkpPhantom* clone() const override;

public:
    void addOverlappingCollidable(hkpCollidable* collidable) override;
    hkBool isOverlappingCollidableAdded(const hkpCollidable* collidable) override;
    void removeOverlappingCollidable(hkpCollidable* collidable) override;

    struct CollisionDetail {
        HK_DECLARE_CLASS_ALLOCATOR(CollisionDetail)
        HK_DECLARE_REFLECTION()

        hkpCollidable* m_collidable;
    };

    inline hkArray<CollisionDetail>& getCollisionDetails();

protected:
    hkArray<CollisionDetail> m_collisionDetails;

public:
    void deallocateInternalArrays() override;

    hkBool m_orderDirty;

    class OrderByUid;
};

inline hkArray<hkpSimpleShapePhantom::CollisionDetail>&
hkpSimpleShapePhantom::getCollisionDetails() {
    return m_collisionDetails;
}
