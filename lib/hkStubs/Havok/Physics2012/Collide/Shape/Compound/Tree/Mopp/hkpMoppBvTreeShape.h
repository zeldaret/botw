#pragma once

#include <Havok/Physics2012/Collide/Shape/Compound/Collection/hkpShapeCollection.h>
#include <Havok/Physics2012/Collide/Shape/Compound/Tree/hkpBvTreeShape.h>
#include <Havok/Physics2012/Collide/Shape/hkpShapeContainer.h>
#include <Havok/Physics2012/Internal/Collide/Mopp/Code/hkpMoppCode.h>

class hkMoppBvTreeShapeBase : public hkpBvTreeShape {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkMoppBvTreeShapeBase)
    HK_DECLARE_REFLECTION()

    HK_FORCE_INLINE hkMoppBvTreeShapeBase() {}

    hkMoppBvTreeShapeBase(ShapeType type, const hkpMoppCode* code);
    explicit hkMoppBvTreeShapeBase(hkFinishLoadedObjectFlag flag);
    ~hkMoppBvTreeShapeBase() override;

    virtual void queryObb(const hkTransform& obbToMopp, const hkVector4& extent, hkReal tolerance,
                          hkArray<hkpShapeKey>& hits) const;

    void queryAabb(const hkAabb& aabb, hkArray<hkpShapeKey>& hits) const override;
    hkUint32 queryAabbImpl(const hkAabb& aabb, hkpShapeKey* hits, int maxNumKeys) const override;

    const hkpMoppCode* m_code;
    const hkUint8* m_moppData;
    hkUint32 m_moppDataSize;
    hkVector4 m_codeInfoCopy;
};

class hkpMoppBvTreeShape : public hkMoppBvTreeShapeBase {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpMoppBvTreeShape)
    HK_DECLARE_REFLECTION()
    HKCD_DECLARE_SHAPE_TYPE(hkcdShapeType::MOPP)

    HK_FORCE_INLINE hkpMoppBvTreeShape() {}
    hkpMoppBvTreeShape(const hkpShapeCollection* collection, const hkpMoppCode* code);
    HK_FORCE_INLINE explicit hkpMoppBvTreeShape(hkFinishLoadedObjectFlag flag);
    ~hkpMoppBvTreeShape() override;

    void getAabb(const hkTransform& localToWorld, hkReal tolerance, hkAabb& out) const override;

    hkBool castRay(const hkpShapeRayCastInput& input,
                   hkpShapeRayCastOutput& results) const override;

    void castRayWithCollector(const hkpShapeRayCastInput& input, const hkpCdBody& cdBody,
                              hkpRayHitCollector& collector) const override;

    hkVector4Comparison castRayBundle(const hkpShapeRayBundleCastInput& input,
                                      hkpShapeRayBundleCastOutput& results,
                                      hkVector4ComparisonParameter mask) const override;

    inline const hkpMoppCode* getMoppCode() const;
    inline void setMoppCode(const hkpMoppCode* code);

    inline const hkpShapeCollection* getShapeCollection() const;
    inline const hkpShapeContainer* getContainer() const override;
    inline const hkpShape* getChild() const;

    int calcSizeForSpu(const CalcSizeForSpuInput& input, int spuBufferSizeLeft) const override;

protected:
    hkpSingleShapeContainer m_child;

public:
    mutable int m_childSize;
};

inline hkMoppBvTreeShapeBase::hkMoppBvTreeShapeBase(hkFinishLoadedObjectFlag flag)
    : hkpBvTreeShape(flag) {
    if (flag.m_finishing) {
        m_bvTreeType = BVTREE_MOPP;
    }
}

inline hkMoppBvTreeShapeBase::~hkMoppBvTreeShapeBase() {
    m_code->removeReference();
}

inline hkpMoppBvTreeShape::hkpMoppBvTreeShape(hkFinishLoadedObjectFlag flag)
    : hkMoppBvTreeShapeBase(flag), m_child(flag) {
    if (flag.m_finishing == 1) {
        setType(HKCD_SHAPE_TYPE_FROM_CLASS(hkpMoppBvTreeShape));
        m_codeInfoCopy = m_code->m_info.m_offset;
        m_moppData = m_code->m_data.begin();
        m_moppDataSize = m_code->getCodeSize();
    }
}

inline const hkpShapeCollection* hkpMoppBvTreeShape::getShapeCollection() const {
    return static_cast<const hkpShapeCollection*>(m_child.getChild());
}

inline const hkpMoppCode* hkpMoppBvTreeShape::getMoppCode() const {
    return m_code;
}

inline void hkpMoppBvTreeShape::setMoppCode(const hkpMoppCode* code) {
    code->addReference();
    m_code->removeReference();
    m_code = code;
    m_codeInfoCopy = code->m_info.m_offset;
    m_moppData = code->m_data.begin();
    m_moppDataSize = code->getCodeSize();
}

inline const hkpShapeContainer* hkpMoppBvTreeShape::getContainer() const {
    return getShapeCollection()->getContainer();
}

inline const hkpShape* hkpMoppBvTreeShape::getChild() const {
    return m_child.getChild();
}
