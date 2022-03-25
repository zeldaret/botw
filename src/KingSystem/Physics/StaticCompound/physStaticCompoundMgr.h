#pragma once

#include <container/seadPtrArray.h>
#include <hostio/seadHostIONode.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <thread/seadCriticalSection.h>

class hkpStaticCompoundShape;

namespace ksys::map {
class Object;
}

namespace ksys::phys {

class RigidBody;
class StaticCompound;
class StaticCompoundRigidBodyGroup;
class SystemGroupHandler;

/// Provides convenient access to all loaded StaticCompounds.
class StaticCompoundMgr : public sead::hostio::Node {
public:
    StaticCompoundMgr();
    virtual ~StaticCompoundMgr();

    bool init();

    void addStaticCompound(StaticCompound* sc);
    void removeStaticCompound(StaticCompound* sc);

    void resetExtraTransformsAndApply();
    StaticCompoundRigidBodyGroup* getBodyGroup(int group_index) const;
    bool hasBodyGroup(const StaticCompoundRigidBodyGroup* group) const;
    void processUpdates();
    void recomputeTransformMatrix();

    sead::Matrix34f getTransformedMatrix(StaticCompoundRigidBodyGroup* const& p_group,
                                         const sead::Matrix34f& mtx) const;
    sead::Matrix34f getInvTransformedMatrix(StaticCompoundRigidBodyGroup* const& p_group,
                                            const sead::Matrix34f& mtx) const;
    sead::Vector3f getTransformedPos(StaticCompoundRigidBodyGroup* const& p_group,
                                     const sead::Vector3f& pos) const;
    sead::Vector3f getRotatedDir(StaticCompoundRigidBodyGroup* const& p_group,
                                 const sead::Vector3f& dir) const;

    void setExtraTransform(StaticCompoundRigidBodyGroup* const& p_group,
                           const sead::Matrix34f& transform, int index);

    const sead::Matrix34f& getExtraTransform(StaticCompoundRigidBodyGroup* const& p_group,
                                             int index) const;

    RigidBody* getRigidBody(StaticCompoundRigidBodyGroup* const& p_group) const;

    void getBodyGroupAndMapObject(StaticCompoundRigidBodyGroup** p_group,
                                  map::Object** p_map_object, const hkpStaticCompoundShape& shape,
                                  const u32* shape_key) const;

    SystemGroupHandler* getGroupHandler() const { return mGroupHandler; }

    // TODO: more functions

private:
    sead::FixedPtrArray<StaticCompound, 0x40> mStaticCompounds;
    mutable sead::CriticalSection mCS;
    SystemGroupHandler* mGroupHandler{};
};

}  // namespace ksys::phys
