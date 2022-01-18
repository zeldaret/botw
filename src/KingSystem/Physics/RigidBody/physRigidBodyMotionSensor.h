#pragma once

#include <prim/seadTypedBitFlag.h>
#include <thread/seadAtomic.h>
#include "KingSystem/Physics/RigidBody/physMotionAccessor.h"

namespace ksys::phys {

/// A MotionAccessor that uses the RigidBody's internal motion instance directly.
class RigidBodyMotionSensor : public MotionAccessor {
    SEAD_RTTI_OVERRIDE(RigidBodyMotionSensor, MotionAccessor)
public:
    enum class Flag {
        _40000 = 1 << 18,
        HasExtraTranslateForLinkedRigidBody = 1 << 19,
        HasExtraRotateForLinkedRigidBody = 1 << 20,
        HasLinkedRigidBodyWithoutFlag10 = 1 << 21,
        _400000 = 1 << 22,
    };

    explicit RigidBodyMotionSensor(RigidBody* body);

    void setTransform(const sead::Matrix34f& mtx, bool propagate_to_linked_motions) override;
    void setPosition(const sead::Vector3f& position, bool propagate_to_linked_motions) override;
    void setTransformFromLinkedBody(const sead::Matrix34f& mtx);
    void setTransformFromLinkedBody(const hkVector4f& hk_translate, const hkQuaternionf& hk_rotate);
    void getPosition(sead::Vector3f* position) override;
    void getRotation(sead::Quatf* rotation) override;
    void getTransform(sead::Matrix34f* mtx) override;

    void setCenterOfMassInLocal(const sead::Vector3f& center) override;
    void getCenterOfMassInLocal(sead::Vector3f* center) override;

    bool setLinearVelocity(const sead::Vector3f& velocity, float epsilon) override;
    bool setLinearVelocity(const hkVector4f& velocity, float epsilon) override;
    void getLinearVelocity(sead::Vector3f* velocity) override;
    bool setAngularVelocity(const sead::Vector3f& velocity, float epsilon) override;
    bool setAngularVelocity(const hkVector4f& velocity, float epsilon) override;
    void getAngularVelocity(sead::Vector3f* velocity) override;

    void setMaxLinearVelocity(float max) override;
    float getMaxLinearVelocity() override;
    void setMaxAngularVelocity(float max) override;
    float getMaxAngularVelocity() override;

    void setLinkedRigidBody(RigidBody* body);
    void resetLinkedRigidBody();
    RigidBody* getLinkedRigidBody() const;
    bool isFlag40000Set() const;
    void copyMotionFromLinkedRigidBody();

    ~RigidBodyMotionSensor() override;

    bool init(const RigidBodyInstanceParam& params, sead::Heap* heap) override;
    void getRotation(hkQuaternionf* quat) override;
    void setTimeFactor(float factor) override;
    float getTimeFactor() override;

    void freeze(bool freeze, bool preserve_velocities, bool preserve_max_impulse) override;
    void resetFrozenState() override {
        mFrozenLinearVelocity.set(0, 0, 0);
        mFrozenAngularVelocity.set(0, 0, 0);
    }

    bool hasFlag(Flag flag) const { return mFlags.isOn(flag); }

private:
    void setTransformImpl(const sead::Matrix34f& mtx);

    sead::Vector3f mFrozenLinearVelocity = sead::Vector3f::zero;
    sead::Vector3f mFrozenAngularVelocity = sead::Vector3f::zero;
    sead::Vector3f mLinearVelocity = sead::Vector3f::zero;
    float mMaxLinearVelocity{};
    sead::Vector3f mAngularVelocity = sead::Vector3f::zero;
    float mMaxAngularVelocity{};
    sead::Vector3f mCenterOfMassInLocal = sead::Vector3f::zero;
    RigidBody* mLinkedRigidBody{};
    sead::Matrix34f mTransform = sead::Matrix34f::ident;
    float mTimeFactor = 1.0f;
    sead::Vector3f mLinkedBodyExtraTranslate = sead::Vector3f::zero;
    sead::Quatf mLinkedBodyExtraRotate = sead::Quatf::unit;
    sead::TypedBitFlag<Flag, sead::Atomic<u32>> mFlags{};
};

}  // namespace ksys::phys
