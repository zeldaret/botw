#pragma once

#include <container/seadBuffer.h>
#include <prim/seadTypedBitFlag.h>
#include <thread/seadAtomic.h>
#include "KingSystem/Physics/RigidBody/Shape/physShape.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyParam.h"

class hkpListShape;

namespace ksys::phys {

struct BoxShapeParam;
struct CapsuleShapeParam;
struct CharacterPrismShapeParam;
struct CylinderShapeParam;
struct PolytopeShapeParam;
struct SphereShapeParam;

class MaterialMask;

struct ListShapeParam {
    u8 num_shapes = 4;
};

class ListShape : public Shape {
    SEAD_RTTI_OVERRIDE(ListShape, Shape)
public:
    static ListShape* make(const ListShapeParam& param, sead::Heap* heap);
    ListShape* clone(sead::Heap* heap) const;

    ListShape(const ListShapeParam& param, hkpListShape* shape, sead::Heap* heap);
    ~ListShape() override;

    /// Replace the shape at the specified index with a clone of `shape_to_clone`.
    /// The shape that is being replaced will be deleted.
    /// @return the cloned heap
    Shape* replaceWithClone(int index, const Shape* shape_to_clone, sead::Heap* heap);

    /// Replace the shape at the specified index with a new sphere shape.
    /// The shape that is being replaced will be deleted.
    Shape* replaceWithNewSphere(int index, const SphereShapeParam& param, sead::Heap* heap);

    /// Replace the shape at the specified index with a new capsule shape.
    /// The shape that is being replaced will be deleted.
    Shape* replaceWithNewCapsule(int index, const CapsuleShapeParam& param, sead::Heap* heap);

    /// Replace the shape at the specified index with a new cylinder shape.
    /// The shape that is being replaced will be deleted.
    Shape* replaceWithNewCylinder(int index, const CylinderShapeParam& param, sead::Heap* heap);

    /// Replace the shape at the specified index with a new box shape.
    /// The shape that is being replaced will be deleted.
    Shape* replaceWithNewBox(int index, const BoxShapeParam& param, sead::Heap* heap);

    /// Replace the shape at the specified index with a new polytope shape.
    /// The shape that is being replaced will be deleted.
    Shape* replaceWithNewPolytope(int index, const PolytopeShapeParam& param, sead::Heap* heap);

    /// Replace the shape at the specified index with a new character prism.
    /// The shape that is being replaced will be deleted.
    Shape* replaceWithNewCharacterPrism(int index, const CharacterPrismShapeParam& param,
                                        sead::Heap* heap);

    /// Set the material mask for the shape at the specified index.
    void setMaterialMask(const MaterialMask& mask, int index);

    /// Get the material mask for the shape at the specified index.
    const MaterialMask& getMaterialMask(int index) const;

    ShapeType getType() const override { return ShapeType::List; }
    float getVolume() const override;
    hkpShape* getHavokShape() override;
    const hkpShape* getHavokShape() const override;
    const hkpShape* updateHavokShape() override;
    void setScale(float scale) override;

private:
    enum class Flag {
        /// Whether the Havok list shape needs to be recreated.
        NeedsHavokShapeUpdate = 1 << 0,
    };

    template <typename T, typename ParamType>
    Shape* replaceWithNewShape(int index, const ParamType& param, sead::Heap* heap) {
        delete mShapes[index];
        auto* shape = T::make(param, heap);
        mShapes[index] = shape;
        mFlags.set(Flag::NeedsHavokShapeUpdate);
        return shape;
    }

    /// Child shapes. These are owned by this class.
    sead::Buffer<Shape*> mShapes;
    /// The Havok list shape. This is owned by this class.
    hkpListShape* mHavokShape{};
    sead::TypedBitFlag<Flag, sead::Atomic<u32>> mFlags{Flag::NeedsHavokShapeUpdate};
};

class ListShapeRigidBodyParam : public RigidBodyInstanceParam, public ListShapeParam {
    SEAD_RTTI_OVERRIDE(ListShapeRigidBodyParam, RigidBodyInstanceParam)
public:
    ListShapeRigidBodyParam() : RigidBodyInstanceParam(ShapeType::List) {}
};

}  // namespace ksys::phys
