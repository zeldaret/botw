#pragma once

#include <container/seadPtrArray.h>
#include <hostio/seadHostIONode.h>
#include <math/seadMatrix.h>
#include <prim/seadNamable.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Physics/physDefines.h"

namespace ksys::phys {

class RigidBody;
class SystemGroupHandler;
class UserTag;

class RigidBodySet : public sead::hostio::Node {
public:
    explicit RigidBodySet(const sead::SafeString& name);
    virtual ~RigidBodySet();

    const sead::SafeString& getName() const { return mName; }

    sead::PtrArray<RigidBody>& getRigidBodies() { return mRigidBodies; }
    const sead::PtrArray<RigidBody>& getRigidBodies() const { return mRigidBodies; }
    RigidBody* getRigidBody(int idx) const { return mRigidBodies[idx]; }

    void setFixedAndPreserveImpulse(bool fixed, bool mark_linear_vel_as_dirty);
    void resetFrozenState();
    void setUseSystemTimeFactor(bool use);
    void clearFlag400000(bool clear);
    void setEntityMotionFlag200(bool set);
    void setFixed(bool fixed, bool preserve_velocities);

    void updateMotionTypeRelatedFlags();
    void triggerScheduledMotionTypeChange();

    bool hasActiveEntityBody() const;

    RigidBody* findBodyByHavokName(const sead::SafeString& name);
    const RigidBody* findBodyByHavokName(const sead::SafeString& name) const;
    int findBodyIndexByHavokName(const sead::SafeString& name) const;

    void setUserTag(UserTag* tag);

    /// Set the specified handler for all rigid bodies whose type (entity/sensor) matches
    /// the layer type of the handler.
    void setSystemGroupHandler(SystemGroupHandler* handler);

    /// Set the specified handler for all rigid bodies whose type (entity/sensor) matches
    /// both `layer_type` and the layer type of the handler.
    void setSystemGroupHandler(SystemGroupHandler* handler, ContactLayerType layer_type);

    void setTransform(const sead::Matrix34f& mtx);

    void enableContactLayer(ContactLayer layer);
    void disableContactLayer(ContactLayer layer);
    void disableAllContactLayers();

    void setScaleAndUpdateImmediately(float scale);
    void setScale(float scale);
    void addToWorld();
    void removeFromWorld();
    bool removeFromWorldAndResetLinks();
    bool hasNoRigidBodyWithFlag8(bool require_motion_flag_1_to_be_unset);
    void callRigidBody_x_7(u8 type);

private:
    sead::SafeString mName;
    sead::PtrArray<RigidBody> mRigidBodies;
};

}  // namespace ksys::phys
