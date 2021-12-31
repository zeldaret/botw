#pragma once

#include <Havok/Common/Base/hkBase.h>

struct hkcdShapeType {
    HK_DECLARE_CLASS_ALLOCATOR(hkcdShapeType)

    enum ShapeTypeEnum {
        SPHERE = 0,                               ///< hkpSphereShape type.
        CYLINDER = 1,                             ///< hkpCylinderShape type.
        TRIANGLE = 2,                             ///< hkpTriangleShape type.
        BOX = 3,                                  ///< hkpBoxShape type.
        CAPSULE = 4,                              ///< hkpCapsuleShape type.
        CONVEX_VERTICES = 5,                      ///< hkpConvexVerticesShape type.
        TRI_SAMPLED_HEIGHT_FIELD_COLLECTION = 6,  ///< hkpTriSampledHeightFieldCollection type.
        TRI_SAMPLED_HEIGHT_FIELD_BV_TREE = 7,     ///< hkpTriSampledHeightFieldBvTreeShape type.
        LIST = 8,                                 ///< hkpListShape type.
        MOPP = 9,                                 ///< hkpMoppBvTreeShape type.
        CONVEX_TRANSLATE = 10,                    ///< hkpConvexTranslateShape type.
        CONVEX_TRANSFORM = 11,                    ///< hkpConvexTransformShape type.
        SAMPLED_HEIGHT_FIELD = 12,                ///< hkpSampledHeightFieldShape type.
        EXTENDED_MESH = 13,                       ///< hkpExtendedMeshShape type.
        TRANSFORM = 14,                           ///< hkpTransformShape type.
        COMPRESSED_MESH = 15,                     ///< hkpCompressedMeshShape type.
        STATIC_COMPOUND = 16,                     ///< hkpStaticCompoundShape type.
        BV_COMPRESSED_MESH = 17,                  ///< hkpBvCompressedMeshShape type.
        /// All shapes which inherit from hkpShapeCollection have this as an alternate type.
        COLLECTION = 18,
        USER0 = 19,  ///< Custom user type.
        USER1 = 20,  ///< Custom user type.
        USER2 = 21,  ///< Custom user type.
        /// All shapes which inherit from hkpBvTreeShape have this as an alternate type.
        BV_TREE = 22,
        /// All shapes which inherit from hkpConvexShape have this as an alternate type.
        CONVEX = 23,
        CONVEX_PIECE = 24,         ///< DEPRECATED - hkpConvexPieceShape type.
        MULTI_SPHERE = 25,         ///< DEPRECATED - hkpMultiSphereShape type.
        CONVEX_LIST = 26,          ///< DEPRECATED - hkpConvexListShape.
        TRIANGLE_COLLECTION = 27,  ///< A shape collection which only returns triangles as child
                                   ///< shapes, e.g., hkpMeshShape.
        HEIGHT_FIELD = 28,         ///< hkpHeightFieldShape type.
        SPHERE_REP = 29,           ///< hkpSphereRepShape type.
        BV = 30,                   ///< hkpBvShape type.
        PLANE = 31,                ///< hkpPlaneShape type.
        PHANTOM_CALLBACK = 32,     ///< hkpPhantomCallbackShape type.
        MULTI_RAY = 33,            ///< hkpMultiRayShape type.
        INVALID = 34,              ///< Invalid shape

        FIRST_SHAPE_TYPE = SPHERE,         ///< The first real shape.
        MAX_SPU_SHAPE_TYPE = USER2 + 1,    ///< Last SPU support shape type.
        MAX_PPU_SHAPE_TYPE = INVALID + 1,  ///< The end of the shape type list.
        ALL_SHAPE_TYPES = -1,              ///< All shapes flag, used by the hkpCollisionDispatcher.
    };
};

struct hkcdShapeDispatchType {
    HK_DECLARE_CLASS_ALLOCATOR(hkcdShapeDispatchType)

    enum ShapeDispatchTypeEnum {
        CONVEX_IMPLICIT,
        CONVEX,
        HEIGHT_FIELD,
        COMPOSITE,
        USER,
        NUM_DISPATCH_TYPES,
    };
};

struct hkcdShapeInfoCodecType {
    HK_DECLARE_CLASS_ALLOCATOR(hkcdShapeInfoCodecType)

    enum ShapeInfoCodecTypeEnum {
        NULL_CODEC = 0,
        UFM358 = 1,
        MAX_NUM_CODECS = 16,
    };
};

class hkcdShape : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkcdShape)

    using ShapeType = hkcdShapeType::ShapeTypeEnum;
    using DispatchType = hkcdShapeDispatchType::ShapeDispatchTypeEnum;
    using ShapeInfoCodecType = hkcdShapeInfoCodecType::ShapeInfoCodecTypeEnum;

    HK_FORCE_INLINE hkcdShape() = default;
    HK_FORCE_INLINE explicit hkcdShape(ShapeType shapeType)
        : m_type(shapeType), m_dispatchType(hkcdShapeDispatchType::USER), m_bitsPerKey(0),
          m_shapeInfoCodecType(hkcdShapeInfoCodecType::NULL_CODEC) {}

    explicit hkcdShape(hkFinishLoadedObjectFlag flag);

    HK_FORCE_INLINE hkcdShape::ShapeType getType() const { return m_type; }
    HK_FORCE_INLINE void setType(ShapeType newType) { m_type = newType; }

    hkEnum<ShapeType, hkUint8> m_type;
    hkEnum<DispatchType, hkUint8> m_dispatchType;
    hkUint8 m_bitsPerKey;
    hkEnum<ShapeInfoCodecType, hkUint8> m_shapeInfoCodecType;
};

#define HKCD_DECLARE_SHAPE_TYPE(shapeType) enum { THIS_SHAPE_TYPE = (shapeType) };
#define HKCD_SHAPE_TYPE_FROM_CLASS(ShapeClass) (hkcdShape::ShapeType) ShapeClass::THIS_SHAPE_TYPE
