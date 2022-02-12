#include "KingSystem/Physics/RigidBody/Shape/List/physListShape.h"
#include <Havok/Physics2012/Collide/Shape/Compound/Collection/List/hkpListShape.h>
#include <Havok/Physics2012/Collide/Shape/Convex/Sphere/hkpSphereShape.h>
#include <basis/seadRawPrint.h>
#include <container/seadSafeArray.h>
#include "KingSystem/Physics/RigidBody/Shape/Box/physBoxShape.h"
#include "KingSystem/Physics/RigidBody/Shape/Capsule/physCapsuleShape.h"
#include "KingSystem/Physics/RigidBody/Shape/CharacterPrism/physCharacterPrismShape.h"
#include "KingSystem/Physics/RigidBody/Shape/Cylinder/physCylinderShape.h"
#include "KingSystem/Physics/RigidBody/Shape/Polytope/physPolytopeShape.h"
#include "KingSystem/Physics/RigidBody/Shape/Sphere/physSphereShape.h"
#include "KingSystem/Physics/physHeapUtil.h"

namespace ksys::phys {

ListShape* ListShape::make(const ListShapeParam& param, sead::Heap* heap) {
    auto* sphere = new hkpSphereShape(1.0);
    if (!sphere)
        return nullptr;

    auto shapes = sead::toArray<const hkpShape*>({sphere});
    auto* list_shape = new hkpListShape(shapes.getBufferPtr(), shapes.size());
    sphere->removeReference();

    if (!list_shape)
        return nullptr;

    return new (heap) ListShape(param, list_shape, heap);
}

ListShape* ListShape::clone(sead::Heap* heap) const {
    ListShapeParam param;
    param.num_shapes = static_cast<decltype(param.num_shapes)>(mShapes.size());

    auto* cloned = make(param, heap);
    if (!cloned)
        return nullptr;

    for (int i = 0, n = mShapes.size(); i < n; ++i)
        cloned->replaceWithClone(i, mShapes[i], heap);

    return cloned;
}

ListShape::ListShape(const ListShapeParam& param, hkpListShape* shape, sead::Heap* heap)
    : mHavokShape(shape) {
    mShapes.allocBufferAssert(param.num_shapes, heap);
    for (int i = 0; i < int(param.num_shapes); ++i)
        mShapes[i] = nullptr;
}

ListShape::~ListShape() {
    deleteRefCountedHavokObject(mHavokShape);

    for (int i = 0, n = mShapes.size(); i < n; ++i) {
        if (mShapes[i]) {
            delete mShapes[i];
            mShapes[i] = nullptr;
        }
    }

    mShapes.freeBuffer();
}

Shape* ListShape::replaceWithClone(int index, const Shape* shape_to_clone, sead::Heap* heap) {
    delete mShapes[index];

    switch (shape_to_clone->getType()) {
    case ShapeType::Sphere:
        mShapes[index] = sead::DynamicCast<const SphereShape>(shape_to_clone)->clone(heap);
        break;
    case ShapeType::Capsule:
        mShapes[index] = sead::DynamicCast<const CapsuleShape>(shape_to_clone)->clone(heap);
        break;
    case ShapeType::Box:
        mShapes[index] = sead::DynamicCast<const BoxShape>(shape_to_clone)->clone(heap);
        break;
    case ShapeType::Cylinder:
        mShapes[index] = sead::DynamicCast<const CylinderShape>(shape_to_clone)->clone(heap);
        break;
    case ShapeType::Polytope:
        mShapes[index] = sead::DynamicCast<const PolytopeShape>(shape_to_clone)->clone(heap);
        break;
    case ShapeType::CharacterPrism:
        mShapes[index] = sead::DynamicCast<const CharacterPrismShape>(shape_to_clone)->clone(heap);
        break;
    case ShapeType::List:
    case ShapeType::BoxWater:
    case ShapeType::CylinderWater:
    case ShapeType::Unknown:
        SEAD_ASSERT_MSG(false, "unexpected shape type");
        break;
    }

    mFlags.set(Flag::NeedsHavokShapeUpdate);
    return mShapes[index];
}

Shape* ListShape::replaceWithNewSphere(int index, const SphereShapeParam& param, sead::Heap* heap) {
    return replaceWithNewShape<SphereShape, SphereShapeParam>(index, param, heap);
}

Shape* ListShape::replaceWithNewCapsule(int index, const CapsuleShapeParam& param,
                                        sead::Heap* heap) {
    return replaceWithNewShape<CapsuleShape, CapsuleShapeParam>(index, param, heap);
}

Shape* ListShape::replaceWithNewCylinder(int index, const CylinderShapeParam& param,
                                         sead::Heap* heap) {
    return replaceWithNewShape<CylinderShape, CylinderShapeParam>(index, param, heap);
}

Shape* ListShape::replaceWithNewBox(int index, const BoxShapeParam& param, sead::Heap* heap) {
    return replaceWithNewShape<BoxShape, BoxShapeParam>(index, param, heap);
}

Shape* ListShape::replaceWithNewPolytope(int index, const PolytopeShapeParam& param,
                                         sead::Heap* heap) {
    return replaceWithNewShape<PolytopeShape, PolytopeShapeParam>(index, param, heap);
}

Shape* ListShape::replaceWithNewCharacterPrism(int index, const CharacterPrismShapeParam& param,
                                               sead::Heap* heap) {
    return replaceWithNewShape<CharacterPrismShape, CharacterPrismShapeParam>(index, param, heap);
}

void ListShape::setMaterialMask(const MaterialMask& mask, int index) {
    switch (mShapes[index]->getType()) {
    case ShapeType::Sphere:
        sead::DynamicCast<SphereShape>(mShapes[index])->setMaterialMask(mask);
        break;
    case ShapeType::Capsule:
        sead::DynamicCast<CapsuleShape>(mShapes[index])->setMaterialMask(mask);
        break;
    case ShapeType::Box:
        sead::DynamicCast<BoxShape>(mShapes[index])->setMaterialMask(mask);
        break;
    case ShapeType::Cylinder:
        sead::DynamicCast<CylinderShape>(mShapes[index])->setMaterialMask(mask);
        break;
    case ShapeType::Polytope:
        sead::DynamicCast<PolytopeShape>(mShapes[index])->setMaterialMask(mask);
        break;
    case ShapeType::CharacterPrism:
        sead::DynamicCast<CharacterPrismShape>(mShapes[index])->setMaterialMask(mask);
        break;
    case ShapeType::List:
    case ShapeType::BoxWater:
    case ShapeType::CylinderWater:
    case ShapeType::Unknown:
        SEAD_ASSERT_MSG(false, "unexpected shape type");
        break;
    }
}

const MaterialMask& ListShape::getMaterialMask(int index) const {
    if (index >= mShapes.size())
        index = 0;

    switch (mShapes[index]->getType()) {
    case ShapeType::Sphere:
        return sead::DynamicCast<SphereShape>(mShapes[index])->getMaterialMask();
    case ShapeType::Capsule:
        return sead::DynamicCast<CapsuleShape>(mShapes[index])->getMaterialMask();
    case ShapeType::Box:
        return sead::DynamicCast<BoxShape>(mShapes[index])->getMaterialMask();
    case ShapeType::Cylinder:
        return sead::DynamicCast<CylinderShape>(mShapes[index])->getMaterialMask();
    case ShapeType::Polytope:
        return sead::DynamicCast<PolytopeShape>(mShapes[index])->getMaterialMask();
    case ShapeType::CharacterPrism:
        return sead::DynamicCast<CharacterPrismShape>(mShapes[index])->getMaterialMask();
    case ShapeType::List:
    case ShapeType::BoxWater:
    case ShapeType::CylinderWater:
    case ShapeType::Unknown:
        SEAD_ASSERT_MSG(false, "unexpected shape type");
        break;
    }
    return sead::DynamicCast<SphereShape>(mShapes[index])->getMaterialMask();
}

float ListShape::getVolume() const {
    float volume = 0.0;
    for (int i = 0, n = mShapes.size(); i < n; ++i) {
        if (mShapes[i])
            volume += mShapes[i]->getVolume();
    }
    return volume;
}

hkpShape* ListShape::getHavokShape() {
    return mHavokShape;
}

const hkpShape* ListShape::getHavokShape() const {
    return mHavokShape;
}

const hkpShape* ListShape::updateHavokShape() {
    bool updated = false;

    if (mFlags.isOn(Flag::NeedsHavokShapeUpdate)) {
        hkArray<const hkpShape*> havok_shapes;
        int num_shapes = 0;

        for (int i = 0, n = mShapes.size(); i < n; ++i) {
            if (!mShapes[i])
                continue;

            const hkpShape* havok_shape = mShapes[i]->updateHavokShape();
            if (havok_shape) {
                // If one of the shapes was recreated, then we need to recreate the list shape.
                havok_shapes.pushBack(havok_shape);
                updated = true;
            } else {
                havok_shape = mShapes[i]->getHavokShapeConst();
                havok_shapes.pushBack(havok_shape);

                // Otherwise, we only need to recreate the list shape if the list has changed.
                if (!updated && mHavokShape->m_childInfo.getSize() > num_shapes &&
                    mHavokShape->getChildShapeInl(num_shapes) != havok_shapes[num_shapes]) {
                    updated = true;
                }
            }

            ++num_shapes;
        }

        if (updated) {
            const auto collision_filter_info =
                mHavokShape->getCollisionFilterInfo(mHavokShape->getFirstKey());

            mHavokShape->removeReference();
            mHavokShape = new hkpListShape(havok_shapes.data(), num_shapes);

            for (auto key = mHavokShape->getFirstKey(); key != HK_INVALID_SHAPE_KEY;
                 key = mHavokShape->getNextKey(key)) {
                mHavokShape->setCollisionFilterInfo(key, collision_filter_info);
            }
        } else {
            mHavokShape->recalcAabbExtents();
        }

        mFlags.reset(Flag::NeedsHavokShapeUpdate);
    }

    return updated ? mHavokShape : nullptr;
}

void ListShape::setScale(float scale) {
    for (int i = 0, n = mShapes.size(); i < n; ++i) {
        if (mShapes[i])
            mShapes[i]->setScale(scale);
    }

    mFlags.set(Flag::NeedsHavokShapeUpdate);
}

}  // namespace ksys::phys
