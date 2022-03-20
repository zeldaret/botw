#pragma once

#include <Havok/Common/Base/Types/Physics/MotionState/hkMotionState.h>
#include <Havok/Physics2012/Dynamics/Phantom/hkpPhantom.h>

class hkpCdBodyPairCollector;
class hkpCdPointCollector;
struct hkpCollisionInput;
struct hkpLinearCastInput;

class hkpShapePhantom : public hkpPhantom {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpShapePhantom)
    HK_DECLARE_REFLECTION()

    hkpShapePhantom(const hkpShape* shape, const hkTransform& transform);
    explicit hkpShapePhantom(hkFinishLoadedObjectFlag flag) : hkpPhantom(flag) {}

    virtual void setPositionAndLinearCast(const hkVector4& position,
                                          const hkpLinearCastInput& input,
                                          hkpCdPointCollector& castCollector,
                                          hkpCdPointCollector* startCollector) = 0;

    virtual void setTransformAndLinearCast(const hkTransform& transform,
                                           const hkpLinearCastInput& input,
                                           hkpCdPointCollector& castCollector,
                                           hkpCdPointCollector* startCollector) = 0;

    virtual void getClosestPoints(hkpCdPointCollector& collector,
                                  const hkpCollisionInput* input) = 0;
    void getClosestPoints(hkpCdPointCollector& collector) { getClosestPoints(collector, nullptr); }

    virtual void getPenetrations(hkpCdBodyPairCollector& collector,
                                 const hkpCollisionInput* input) = 0;
    void getPenetrations(hkpCdBodyPairCollector& collector) { getPenetrations(collector, nullptr); }

    inline const hkTransform& getTransform() const;
    void setTransform(const hkTransform& transform);

    void setPosition(const hkVector4& position, hkReal extraTolerance = 0.0f);

    hkWorldOperation::Result setShape(const hkpShape* shape) override;

    void calcAabb(hkAabb& aabb) override;

    hkMotionState* getMotionState() override;

    hkMotionState m_motionState;

public:
    void deallocateInternalArrays() override;
};

inline const hkTransform& hkpShapePhantom::getTransform() const {
    return m_motionState.getTransform();
}
