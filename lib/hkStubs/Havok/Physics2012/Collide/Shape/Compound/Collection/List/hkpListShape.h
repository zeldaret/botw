#pragma once

#include <Havok/Physics2012/Collide/Shape/Compound/Collection/hkpShapeCollection.h>

class hkBitField;

class hkpListShape : public hkpShapeCollection {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpListShape)
    HK_DECLARE_REFLECTION()
    HKCD_DECLARE_SHAPE_TYPE(hkcdShapeType::LIST)

    enum {
        MAX_CHILDREN_FOR_SPU_MIDPHASE = 252,
        MAX_DISABLED_CHILDREN = 256,
    };

    struct ChildInfo {
        HK_DECLARE_CLASS_ALLOCATOR(ChildInfo)
        HK_DECLARE_REFLECTION()

        alignas(16) const hkpShape* m_shape;
        hkUint32 m_collisionFilterInfo;
        hkUint16 m_shapeInfo;
        mutable hkInt16 m_shapeSize;
        mutable int m_numChildShapes;
    };

    enum ListShapeFlags {
        ALL_FLAGS_CLEAR = 0,
        DISABLE_SPU_CACHE_FOR_LIST_CHILD_INFO = 1 << 0,
    };

    HK_FORCE_INLINE hkpListShape() {}

    hkpListShape(
        const hkpShape* const* shapeArray, int numShapes,
        hkpShapeContainer::ReferencePolicy ref = hkpShapeContainer::REFERENCE_POLICY_INCREMENT);
    explicit hkpListShape(hkFinishLoadedObjectFlag flag);
    ~hkpListShape() override;

    const hkpShape* getChildShape(hkpShapeKey key, hkpShapeBuffer& buffer) const override;

    hkUint32 getCollisionFilterInfo(hkpShapeKey key) const override;

    void getAabb(const hkTransform& localToWorld, hkReal tolerance, hkAabb& out) const override;

    hkBool castRay(const hkpShapeRayCastInput& input,
                   hkpShapeRayCastOutput& results) const override;

    void castRayWithCollector(const hkpShapeRayCastInput& input, const hkpCdBody& cdBody,
                              hkpRayHitCollector& collector) const override;

    HK_FORCE_INLINE void setShapeInfo(hkpShapeKey shapeKey, hkUint16 newShapeInfo);
    HK_FORCE_INLINE hkUint16 getShapeInfo(hkpShapeKey shapeKey) const;

    inline const hkpShape* getChildShapeInl(int i) const { return m_childInfo[i].m_shape; }

    void recalcAabbExtents();
    void recalcAabbExtents(hkAabb& aabbOut);

    void disableChild(hkpShapeKey index);
    void enableChild(hkpShapeKey index);
    void setEnabledChildren(const hkBitField& enabledChildren);
    HK_FORCE_INLINE hkBool32 isChildEnabled(hkpShapeKey index) const;

    void setCollisionFilterInfo(hkpShapeKey index, hkUint32 filterInfo);

    int getNumChildShapes() const override { return m_childInfo.getSize() - m_numDisabledChildren; }

    hkpShapeKey getFirstKey() const override { return hkpListShape::getNextKey(hkpShapeKey(-1)); }

    hkpShapeKey getNextKey(hkpShapeKey key) const override {
        for (int i = int(key) + 1; i < m_childInfo.getSize(); i++) {
            if (isChildEnabled(i)) {
                return hkpShapeKey(i);
            }
        }
        return HK_INVALID_SHAPE_KEY;
    }

    int calcSizeForSpu(const CalcSizeForSpuInput& input, int spuBufferSizeLeft) const override;

    hkArray<ChildInfo> m_childInfo;
    hkUint16 m_flags;
    hkUint16 m_numDisabledChildren;
    hkVector4 m_aabbHalfExtents;
    hkVector4 m_aabbCenter;
    hkUint32 m_enabledChildren[MAX_DISABLED_CHILDREN / 32];

protected:
    void setShapes(
        const hkpShape* const* shapeArray, int numShapes, const hkUint32* filterInfoArray = nullptr,
        hkpShapeContainer::ReferencePolicy ref = hkpShapeContainer::REFERENCE_POLICY_INCREMENT);
};

inline void hkpListShape::setShapeInfo(hkpShapeKey shapeKey, hkUint16 newShapeInfo) {
    m_childInfo[int(shapeKey)].m_shapeInfo = newShapeInfo;
}

inline hkUint16 hkpListShape::getShapeInfo(hkpShapeKey shapeKey) const {
    return m_childInfo[int(shapeKey)].m_shapeInfo;
}

inline hkBool32 hkpListShape::isChildEnabled(hkpShapeKey index) const {
    if (index < MAX_DISABLED_CHILDREN) {
        return m_enabledChildren[index >> 5] & (1 << (index & 0x1f));
    }
    return true;
}
