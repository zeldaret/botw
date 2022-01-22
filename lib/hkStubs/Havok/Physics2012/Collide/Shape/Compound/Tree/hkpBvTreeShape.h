#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics2012/Collide/Shape/hkpShape.h>

class hkpAabbCastCollector;

class hkpBvTreeShape : public hkpShape {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpBvTreeShape)
    HKCD_DECLARE_SHAPE_TYPE(hkcdShapeType::BV_TREE)

    enum BvTreeType {
        BVTREE_MOPP,
        BVTREE_TRISAMPLED_HEIGHTFIELD,
        BVTREE_STATIC_COMPOUND,
        BVTREE_COMPRESSED_MESH,
        BVTREE_USER,
        BVTREE_MAX
    };

    HK_FORCE_INLINE hkpBvTreeShape() {}

    inline hkpBvTreeShape(ShapeType type, BvTreeType bvType)
        : hkpShape(type), m_bvTreeType(bvType) {}

    explicit hkpBvTreeShape(hkFinishLoadedObjectFlag flag);

    virtual void queryAabb(const hkAabb& aabb, hkArray<hkpShapeKey>& hits) const = 0;
    inline hkUint32 queryAabb(const hkAabb& aabb, hkpShapeKey* hits, int maxNumKeys) const;
    inline void castAabb(const hkAabb& from, hkVector4Parameter to,
                         hkpAabbCastCollector& collector) const;
    virtual void castAabbImpl(const hkAabb& from, hkVector4Parameter to,
                              hkpAabbCastCollector& collector) const;
    const hkpShapeContainer* getContainer() const override = 0;
    virtual hkUint32 queryAabbImpl(const hkAabb& aabb, hkpShapeKey* hits, int maxNumKeys) const = 0;

    hkEnum<BvTreeType, hkUint8> m_bvTreeType;
};

inline hkUint32 hkpBvTreeShape::queryAabb(const hkAabb& aabb, hkpShapeKey* hits,
                                          int maxNumKeys) const {
    return queryAabbImpl(aabb, hits, maxNumKeys);
}

inline void hkpBvTreeShape::castAabb(const hkAabb& from, hkVector4Parameter to,
                                     hkpAabbCastCollector& collector) const {
    castAabbImpl(from, to, collector);
}
