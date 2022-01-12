#pragma once

#include <prim/seadTypedBitFlag.h>
#include <thread/seadAtomic.h>
#include "KingSystem/Physics/RigidBody/physMotionAccessor.h"

namespace ksys::phys {

/// A MotionAccessor that uses the RigidBody's internal motion instance directly.
class RigidBodyMotionProxy : public MotionAccessor {
    SEAD_RTTI_OVERRIDE(RigidBodyMotionProxy, MotionAccessor)
public:
    enum class Flag {
        _40000 = 1 << 18,
    };

    explicit RigidBodyMotionProxy(RigidBody* body);

    void setTransform(const sead::Matrix34f& mtx, bool notify) override;
    void setPosition(const sead::Vector3f& position, bool notify) override;
    // 0x0000007100fa4318
    void setTransformMaybe(const sead::Matrix34f& mtx);
    // 0x0000007100fa4594
    void setTransformMaybe(const hkVector4f& translate, const hkQuaternionf& rotate);
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

    // 0x0000007100fa4f48 - called from RigidBody, sets a secondary rigid body
    void setLinkedRigidBody(RigidBody* body);
    // 0x0000007100fa3f8c - called from RigidBody and inlined by the destructor
    void resetLinkedRigidBody();
    RigidBody* getLinkedRigidBody() const;
    bool isFlag40000Set() const;
    // 0x0000007100fa5058 - main update function? triggers shape, position, velocity updates
    void update();

    ~RigidBodyMotionProxy() override;

    bool init(const RigidBodyInstanceParam& params, sead::Heap* heap) override;
    void getRotation(hkQuaternionf* quat) override;
    void setTimeFactor(float factor) override;
    float getTimeFactor() override;
    void m25(bool a, bool b, bool c) override;
    void m26() override;

private:
    void setTransformImpl(const sead::Matrix34f& mtx);

    sead::Vector3f _18 = sead::Vector3f::zero;
    sead::Vector3f _24 = sead::Vector3f::zero;
    sead::Vector3f mLinearVelocity = sead::Vector3f::zero;
    float mMaxLinearVelocity{};
    sead::Vector3f mAngularVelocity = sead::Vector3f::zero;
    float mMaxAngularVelocity{};
    sead::Vector3f mCenterOfMassInLocal = sead::Vector3f::zero;
    RigidBody* mLinkedRigidBody{};
    sead::Matrix34f mTransform = sead::Matrix34f::ident;
    float mTimeFactor = 1.0f;
    sead::Vector3f _9c = sead::Vector3f::zero;
    sead::Quatf _a8 = sead::Quatf::unit;
    sead::TypedBitFlag<Flag, sead::Atomic<u32>> mFlags{};
};

}  // namespace ksys::phys
