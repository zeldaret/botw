#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics2012/Collide/Shape/hkpShape.h>
#include <Havok/Physics2012/Collide/Shape/hkpShapeContainer.h>
#include <Havok/Physics2012/Collide/Util/Welding/hkpWeldingUtility.h>

class hkpShapeCollection : public hkpShape, public hkpShapeContainer {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpShapeCollection)
    HKCD_DECLARE_SHAPE_TYPE(hkcdShapeType::COLLECTION)

    enum CollectionType {
        COLLECTION_LIST,
        COLLECTION_EXTENDED_MESH,
        COLLECTION_TRISAMPLED_HEIGHTFIELD,
        COLLECTION_USER,
        COLLECTION_SIMPLE_MESH,
        COLLECTION_MESH_SHAPE,
        COLLECTION_COMPRESSED_MESH,
        COLLECTION_MAX
    };

    HK_FORCE_INLINE hkpShapeCollection() = default;
    hkpShapeCollection(ShapeType type, CollectionType collectionType);
    explicit hkpShapeCollection(hkFinishLoadedObjectFlag flag);

    void getAabb(const hkTransform& localToWorld, hkReal tolerance, hkAabb& out) const override;

    hkBool castRay(const hkpShapeRayCastInput& input,
                   hkpShapeRayCastOutput& results) const override;

    void castRayWithCollector(const hkpShapeRayCastInput& input, const hkpCdBody& cdBody,
                              hkpRayHitCollector& collector) const override;

    hkReal getMaximumProjection(const hkVector4& direction) const override;

    const hkpShapeContainer* getContainer() const override;

    virtual void initWeldingInfo(hkpWeldingUtility::WeldingType weldingType);
    virtual void setWeldingInfo(hkpShapeKey key, hkInt16 weldingInfo);

    bool isWeldingEnabled() const override { return !m_disableWelding; }

    hkBool m_disableWelding;
    hkEnum<CollectionType, hkUint8> m_collectionType;
};
