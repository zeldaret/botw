#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics2012/Collide/Shape/hkpShapeBase.h>

#define HK_INVALID_SHAPE_KEY 0xffffffff
#define HK_INVALID_VERTEX_ID 0xffff

class hkpShapeContainer;

class hkpShape : public hkpShapeBase {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpShape)
    HKCD_DECLARE_SHAPE_TYPE(hkcdShapeType::INVALID)

    struct CalcSizeForSpuInput;

    HK_FORCE_INLINE hkpShape() = default;
    HK_FORCE_INLINE explicit hkpShape(ShapeType type) : hkpShapeBase(type), m_userData(0) {}
    explicit hkpShape(hkFinishLoadedObjectFlag flag);

    virtual const hkpShapeContainer* getContainer() const { return nullptr; }
    virtual hkReal getMaximumProjection(const hkVector4& direction) const;
    virtual int calcSizeForSpu(const CalcSizeForSpuInput& input, int spuBufferSizeLeft) const;
    inline hkUlong getUserData() const { return m_userData; }
    inline void setUserData(hkUlong data) { m_userData = data; }

    hkVector4Comparison castRayBundle(const hkpShapeRayBundleCastInput& input,
                                      hkpShapeRayBundleCastOutput& output,
                                      hkVector4ComparisonParameter mask) const override;

    hkUlong m_userData;
};

class hkpShapeKeyPair {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpShapeKeyPair)

    hkpShapeKey m_shapeKeyA;
    hkpShapeKey m_shapeKeyB;

    HK_FORCE_INLINE bool operator==(const hkpShapeKeyPair& p1) const {
        return m_shapeKeyB == p1.m_shapeKeyB && m_shapeKeyA == p1.m_shapeKeyA;
    }

    HK_FORCE_INLINE bool operator<(const hkpShapeKeyPair& p1) const {
        return (m_shapeKeyA < p1.m_shapeKeyA) ||
               (m_shapeKeyA == p1.m_shapeKeyA && m_shapeKeyB < p1.m_shapeKeyB);
    }
};

class hkpShapeModifier {
public:
    virtual ~hkpShapeModifier() = default;
    virtual void modifyShape(hkpShape* shapeInOut) = 0;
};
