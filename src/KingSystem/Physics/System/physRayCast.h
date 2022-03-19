#pragma once

#include <container/seadPtrArray.h>
#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include <prim/seadDelegate.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <thread/seadAtomic.h>
#include "KingSystem/Physics/physDefines.h"
#include "KingSystem/Physics/physMaterialMask.h"

namespace ksys::phys {

struct ActorInfo;
class LayerMaskBuilder;
class RigidBody;
class SystemGroupHandler;

class RayCast {
    SEAD_RTTI_BASE(RayCast)
public:
    enum class NormalCheckingMode {
        _0 = 0,
        _1 = 1,
        DoNotCheck = 2,
    };

    // TODO: what kind of callback is this?
    using Callback = sead::IDelegate1<phys::RigidBody*>;

    RayCast(SystemGroupHandler* group_handler, GroundHit ground_hit);
    virtual ~RayCast();

    virtual void m4(void*) {}

    void reset();
    void resetCastResult();

    void enableLayer(ContactLayer layer);
    void disableLayer(ContactLayer layer);
    void setLayers(const LayerMaskBuilder& builder);
    bool isLayerEnabled(ContactLayer layer) const;

    void setGroundHit(GroundHit ground_hit);
    GroundHit getGroundHit() const;

    // TODO: rename
    void setD8(int value);
    void set9A(bool value);

    void setStart(const sead::Vector3f& start);
    void setEnd(const sead::Vector3f& end);
    void setStartAndEnd(const sead::Vector3f& start, const sead::Vector3f& end);
    void setStartAndDisplacement(const sead::Vector3f& start, const sead::Vector3f& displacement);
    void setStartAndDisplacementScaled(const sead::Vector3f& start,
                                       const sead::Vector3f& displacement,
                                       float displacement_scale);

    bool addGroupHandler(SystemGroupHandler* group_handler);
    void setRigidBody(RigidBody* body);

    void setCallback(Callback* callback) { mCallback = callback; }
    Callback* getCallback() const { return mCallback; }

    // 0x0000007100fc39b4
    bool worldRayCast(ContactLayerType layer_type);
    // 0x0000007100fc3da4
    bool shapeRayCast(RigidBody* rigid_body);
    // 0x0000007100fc4248
    bool phantomRayCast(void* unk);

    void getHitPosition(sead::Vector3f* out) const;
    // TODO: rename
    void get34(sead::Vector3f* out) const;
    // TODO: rename
    // 0x0000007100fc4844
    void getUnkVectors(sead::Vector3f* unk1, sead::Vector3f* unk2, void* unk3) const;

    // 0x0000007100fc4bd4
    bool x_1(sead::Vector3f* out) const;

private:
    auto& getLayerMask(ContactLayerType type) { return mLayerMasks[int(type)]; }
    auto& getLayerMask(ContactLayerType type) const { return mLayerMasks[int(type)]; }

    // 0x0000007100fc3b1c
    void worldRayCastImpl(void* arg, ContactLayerType layer_type);
    // 0x0000007100fc3f0c
    void shapeRayCastImpl(void* arg, RigidBody* rigid_body);
    // 0x0000007100fc43b0
    void phantomRayCastImpl(void* unk);

    // 0x0000007100fc4630
    const ActorInfo* getActorInfoMaybe(void* unk);

    // 0x0000007100fc4764
    bool x_2(sead::Vector3f* out, void* unk1, int unk2) const;

    sead::Vector3f mFrom = sead::Vector3f::zero;
    sead::Vector3f mTo = sead::Vector3f::zero;
    SystemGroupHandler* mGroupHandler{};
    GroundHit mGroundHit{};
    u32 _2c;
    bool _30;
    sead::Vector3f _34;
    float mHitFraction;
    void* _48;
    u32 _50;
    bool _54;
    void* _58{};
    void* _60;
    sead::SafeArray<sead::BitFlag32, NumContactLayerTypes> mLayerMasks{};
    sead::Atomic<u32> _70;
    NormalCheckingMode mNormalCheckingMode;
    MaterialMask mMaterialMask;
    RigidBody* mRigidBody{};
    sead::Atomic<bool> _98;
    bool _99{};
    bool _9a{};
    sead::FixedPtrArray<SystemGroupHandler, 4> mExtraGroupHandlers;
    // TODO: rename once we figure out what kind of callback this is
    Callback* mCallback{};
    u32 _d8 = 0x10;
};

}  // namespace ksys::phys
