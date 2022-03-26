#pragma once

#include <Havok/Animation/Animation/Rig/hkaSkeleton.h>
#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics2012/Dynamics/Constraint/hkpConstraintInstance.h>

class hkpRigidBody;

class hkaRagdollInstance : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkaRagdollInstance)
    HK_DECLARE_REFLECTION()

    hkaRagdollInstance(const hkArrayBase<hkpRigidBody*>& rigidBodies,
                       const hkArrayBase<hkpConstraintInstance*>& constraints,
                       const hkaSkeleton* skeleton);

    /// Same as the above constructor, but the extra bone-to-rigidbody map allows the ragdoll
    /// skeleton to have extra bones
    hkaRagdollInstance(const hkArrayBase<hkpRigidBody*>& rigidBodies,
                       const hkArrayBase<hkpConstraintInstance*>& constraints,
                       const hkaSkeleton* skeleton, const hkArrayBase<int>& boneToRigidBody);

    explicit hkaRagdollInstance(hkFinishLoadedObjectFlag f);

    ~hkaRagdollInstance() override;

    virtual hkaRagdollInstance* clone(hkpConstraintInstance::CloningMode mode) const;
    hkaRagdollInstance* clone() const { return clone(hkpConstraintInstance::CLONE_FORCE_SHALLOW); }

    inline int getNumBones() const;

    inline hkpRigidBody* getRigidBodyOfBone(int i) const;
    inline int getBoneIndexOfRigidBody(hkpRigidBody* rb) const;

    inline hkpConstraintInstance* getConstraintOfBone(int i) const;

    inline const hkaSkeleton* getSkeleton() const;

    inline int getParentOfBone(int i) const;

    inline const hkArray<hkpRigidBody*>& getRigidBodyArray() const;

    inline const hkArray<hkpConstraintInstance*>& getConstraintArray() const;

    inline hkBool hasNonRigidBodyBones() const;

    void getPoseWorldSpace(hkQsTransform* poseWorldSpaceOut) const;

    void
    getPoseWorldSpace(hkQsTransform* poseWorldSpaceOut, const hkQsTransform& worldFromModel,
                      const hkQsTransform* localSpacePoseForUnmappedBonesOptional = nullptr) const;

    void getApproxCurrentPoseWorldSpace(hkQsTransform* poseWorldSpaceOut) const;

    void getApproxPoseWorldSpaceAt(hkTime time, hkQsTransform* poseWorldSpaceOut) const;

    void setPoseWorldSpace(const hkQsTransform* poseWorldSpaceIn);

    void getPoseModelSpace(hkQsTransform* poseModelSpaceOut,
                           const hkQsTransform& worldFromModel) const;

    void setPoseModelSpace(const hkQsTransform* poseModelSpaceIn,
                           const hkQsTransform& worldFromModel);

    void setPoseAndVelocitiesModelSpace(const hkQsTransform* poseModelSpaceA,
                                        const hkQsTransform& worldFromModelA,
                                        const hkQsTransform* poseModelSpaceB,
                                        const hkQsTransform& worldFromModelB, hkReal timestep);

    hkResult addToWorld(hkpWorld* world, hkBool updateFilter) const;
    hkResult removeFromWorld() const;
    hkpWorld* getWorld() const;

    void getWorldFromBoneTransform(int i, hkQsTransform& worldFromBoneOut) const;
    void getApproxWorldFromBoneTransformAt(int i, hkTime time,
                                           hkQsTransform& worldFromBoneOut) const;

    hkArray<hkpRigidBody*> m_rigidBodies;
    hkArray<hkpConstraintInstance*> m_constraints;
    hkArray<int> m_boneToRigidBodyMap;
    hkRefPtr<const hkaSkeleton> m_skeleton;

private:
    void commonInit(const hkArrayBase<hkpRigidBody*>& rigidBodies,
                    const hkArrayBase<hkpConstraintInstance*>& constraints,
                    const hkaSkeleton* skeleton);
};

inline int hkaRagdollInstance::getNumBones() const {
    return m_skeleton->m_bones.getSize();
}

inline hkpRigidBody* hkaRagdollInstance::getRigidBodyOfBone(int i) const {
    const int index = m_boneToRigidBodyMap[i];
    return index < 0 ? nullptr : m_rigidBodies[index];
}

inline int hkaRagdollInstance::getBoneIndexOfRigidBody(hkpRigidBody* rb) const {
    int rbIndex = m_rigidBodies.indexOf(rb);
    if (rbIndex == -1)
        return -1;
    return m_boneToRigidBodyMap.indexOf(rbIndex);
}

inline hkpConstraintInstance* hkaRagdollInstance::getConstraintOfBone(int i) const {
    const int index = m_boneToRigidBodyMap[i] - 1;
    return index < 0 ? nullptr : m_constraints[index];
}

inline const hkaSkeleton* hkaRagdollInstance::getSkeleton() const {
    return m_skeleton;
}

inline int hkaRagdollInstance::getParentOfBone(int i) const {
    return m_skeleton->m_parentIndices[i];
}

inline const hkArray<hkpRigidBody*>& hkaRagdollInstance::getRigidBodyArray() const {
    return m_rigidBodies;
}

inline const hkArray<hkpConstraintInstance*>& hkaRagdollInstance::getConstraintArray() const {
    return m_constraints;
}

inline hkBool hkaRagdollInstance::hasNonRigidBodyBones() const {
    return m_rigidBodies.getSize() != m_skeleton->m_bones.getSize();
}
