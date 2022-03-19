#pragma once

#include <container/seadPtrArray.h>
#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include <prim/seadDelegate.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <thread/seadAtomic.h>
#include "KingSystem/Physics/physDefines.h"
#include "KingSystem/Physics/physMaterialMask.h"

class hkpCollidable;
struct hkpShapeRayCastInput;
struct hkpShapeRayCastOutput;
struct hkpWorldRayCastInput;
struct hkpWorldRayCastOutput;

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

    using RigidBodyHitCallback = sead::IDelegate1<phys::RigidBody*>;

    RayCast(SystemGroupHandler* group_handler, GroundHit ground_hit);
    virtual ~RayCast();

    virtual void onRigidBodyHit(RigidBody* body) {}

    void reset();
    void resetCastResult();

    void enableLayer(ContactLayer layer);
    void disableLayer(ContactLayer layer);
    void setLayers(const LayerMaskBuilder& builder);
    bool isLayerEnabled(ContactLayer layer) const;

    void setGroundHit(GroundHit ground_hit);
    GroundHit getGroundHit() const;

    void setIgnoredGroundHit(GroundHit ground_hit);
    // TODO: rename
    void set9A(bool value);

    void setStart(const sead::Vector3f& start);
    void setEnd(const sead::Vector3f& end);
    void setStartAndEnd(const sead::Vector3f& start, const sead::Vector3f& end);
    void setStartAndDisplacement(const sead::Vector3f& start, const sead::Vector3f& displacement);
    void setStartAndDisplacementScaled(const sead::Vector3f& start,
                                       const sead::Vector3f& displacement,
                                       float displacement_scale);

    /// @warning Only up to 4 groups can be ignored.
    bool addIgnoredGroup(SystemGroupHandler* group_handler);
    void setRigidBody(RigidBody* body);

    void setCallback(RigidBodyHitCallback* callback) { mRigidBodyHitCallback = callback; }
    RigidBodyHitCallback* getCallback() const { return mRigidBodyHitCallback; }

    bool worldRayCast(ContactLayerType layer_type);
    bool shapeRayCast(RigidBody* rigid_body);
    // 0x0000007100fc4248
    bool phantomRayCast(void* unk);

    void getHitPosition(sead::Vector3f* position) const;
    void getHitNormal(sead::Vector3f* normal) const;
    // TODO: rename
    // 0x0000007100fc4844
    void getUnkVectors(sead::Vector3f* unk1, sead::Vector3f* unk2, void* unk3) const;

    // 0x0000007100fc4bd4
    bool x_1(sead::Vector3f* out) const;

protected:
    auto& getLayerMask(ContactLayerType type) { return mLayerMasks[int(type)]; }
    auto& getLayerMask(ContactLayerType type) const { return mLayerMasks[int(type)]; }

    void worldRayCastImpl(hkpWorldRayCastOutput* output, ContactLayerType layer_type);
    void shapeRayCastImpl(hkpWorldRayCastOutput* output, RigidBody* body);
    // 0x0000007100fc43b0
    void phantomRayCastImpl(hkpWorldRayCastOutput* output);

    // 0x0000007100fc4630
    const ActorInfo* getActorInfoMaybe(const hkpShapeRayCastOutput& output);

    // 0x0000007100fc4764
    bool x_2(sead::Vector3f* out, void* unk1, int unk2) const;

    void fillCastInput(hkpWorldRayCastInput& input, ContactLayerType layer_type);
    void fillCastInput(hkpShapeRayCastInput& input, ContactLayerType layer_type);
    u32 getFilterInfo(ContactLayerType layer_type, u32 layer_mask) const;

    void preCast();
    bool postCast(const hkpWorldRayCastOutput& output);
    void updateHitInformation(const hkpWorldRayCastOutput& output);

    sead::Vector3f mFrom = sead::Vector3f::zero;
    sead::Vector3f mTo = sead::Vector3f::zero;
    SystemGroupHandler* mGroupHandler{};
    GroundHit mGroundHit{};
    u32 _2c;
    bool mHasHit;
    sead::Vector3f mHitNormal;
    float mHitFraction;
    const hkpCollidable* mHitCollidable;
    u32 mHitShapeKey;
    bool mHasHitSpecifiedRigidBody;
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
    sead::FixedPtrArray<SystemGroupHandler, 4> mIgnoredGroups;
    RigidBodyHitCallback* mRigidBodyHitCallback{};
    GroundHit mIgnoredGroundHit = GroundHit::Ignore;
};

}  // namespace ksys::phys
