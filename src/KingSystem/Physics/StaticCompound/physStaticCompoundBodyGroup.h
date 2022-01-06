#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <container/seadPtrArray.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <thread/seadAtomic.h>
#include "KingSystem/Utils/Types.h"

class hkpPhysicsSystem;

namespace ksys::phys {

enum class BodyLayerType;
class RigidBody;
class StaticCompound;

class BodyGroup {
public:
    BodyGroup();
    ~BodyGroup();

    BodyGroup(const BodyGroup&) = delete;
    auto operator=(const BodyGroup&) = delete;

    void init(const hkpPhysicsSystem& system, sead::Matrix34f* mtx, StaticCompound* sc,
              sead::Heap* heap);

    void disableCollision(BodyLayerType body_layer_type, int instance_id, bool x);

    sead::Atomic<u32> _0;
    sead::Atomic<u32> _4;
    sead::Buffer<void*> _8;
    sead::Buffer<void*> _18;
    sead::Buffer<void*> _28;
    sead::Buffer<void*> _38;
    sead::Matrix34f mMtx0 = sead::Matrix34f::ident;
    sead::Matrix34f mMtx1 = sead::Matrix34f::ident;
    sead::Matrix34f* mMtxPtr{};
    sead::PtrArray<RigidBody> mRigidBodies;
    StaticCompound* mStaticCompound{};
    sead::Vector3f _c8 = sead::Vector3f::zero;
    sead::Vector3f _d4 = sead::Vector3f::zero;
    u32 _e0{};
    sead::Buffer<void*> _e8;
};
KSYS_CHECK_SIZE_NX150(BodyGroup, 0xf8);

}  // namespace ksys::phys
