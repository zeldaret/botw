#pragma once

#include <Havok/Animation/Animation/Rig/hkaSkeleton.h>
#include <Havok/Common/Base/hkBase.h>

class hkaPose {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkaPose)

    enum PoseSpace { MODEL_SPACE, LOCAL_SPACE };

    HK_FORCE_INLINE explicit hkaPose(const hkaSkeleton* skeleton);
    HK_FORCE_INLINE hkaPose(const hkaSkeleton* skeleton, void* preallocatedMemory);

    HK_FORCE_INLINE static int getRequiredMemorySize(const hkaSkeleton* skeleton);

    hkaPose(PoseSpace space, const hkaSkeleton* skeleton, const hkArrayBase<hkQsTransform>& pose);
    hkaPose(PoseSpace space, const hkaSkeleton* skeleton, const hkQsTransform* pose, int numBones);

    enum PropagateOrNot { DONT_PROPAGATE = 0, PROPAGATE = 1 };

    HK_FORCE_INLINE const hkaSkeleton* getSkeleton() const;

    const hkArray<hkQsTransform>& getSyncedPoseLocalSpace() const;
    const hkArray<hkQsTransform>& getSyncedPoseModelSpace() const;

    HK_FORCE_INLINE const hkArray<hkReal>& getFloatSlotValues() const;

    void setPoseLocalSpace(const hkArrayBase<hkQsTransform>& poseLocal);
    void setPoseModelSpace(const hkArrayBase<hkQsTransform>& poseModel);

    HK_FORCE_INLINE void setFloatSlotValues(const hkArrayBase<hkReal>& floatSlotValues);

    HK_FORCE_INLINE const hkQsTransform& getBoneLocalSpace(int boneIdx) const;
    HK_FORCE_INLINE const hkQsTransform& getBoneModelSpace(int boneIdx) const;

    HK_FORCE_INLINE hkReal getFloatSlotValue(int floatSlotIdx) const;

    HK_FORCE_INLINE void setBoneLocalSpace(int boneIdx, const hkQsTransform& boneLocal);
    HK_FORCE_INLINE void setBoneModelSpace(int boneIdx, const hkQsTransform& boneModel,
                                           PropagateOrNot propagateOrNot);

    HK_FORCE_INLINE void setFloatSlotValue(int floatSlotIdx, hkReal value);

    void syncLocalSpace() const;
    void syncModelSpace() const;
    inline void syncAll() const;

    hkQsTransform& accessBoneLocalSpace(int boneIdx);
    hkQsTransform& accessBoneModelSpace(int boneIdx,
                                        PropagateOrNot propagateOrNot = DONT_PROPAGATE);

    hkArray<hkQsTransform>& accessSyncedPoseLocalSpace();
    hkArray<hkQsTransform>& accessSyncedPoseModelSpace();

    hkArray<hkQsTransform>& accessUnsyncedPoseLocalSpace();
    hkArray<hkQsTransform>& accessUnsyncedPoseModelSpace();

    HK_FORCE_INLINE hkArray<hkReal>& getFloatSlotValues();

    void setToReferencePose();

    void enforceSkeletonConstraintsLocalSpace();
    void enforceSkeletonConstraintsModelSpace();

    void getModelSpaceAabb(class hkAabb& aabbOut) const;

    inline hkaPose& operator=(const hkaPose& other);

private:
    void init(PoseSpace space, const hkaSkeleton* skeleton, const hkArrayBase<hkQsTransform>& pose);

    using hkaPoseFlag = hkUint32;

    const hkaSkeleton* m_skeleton;

    mutable hkArray<hkQsTransform> m_localPose;
    mutable hkArray<hkQsTransform> m_modelPose;
    mutable hkArray<hkaPoseFlag> m_boneFlags;

    mutable hkBool m_modelInSync;
    mutable hkBool m_localInSync;

    hkArray<hkReal> m_floatSlotValues;

    enum {
        F_BONE_LOCAL_DIRTY = 0x1,
        F_BONE_MODEL_DIRTY = 0x2,
        F_BONE_INTERNAL_FLAG1 = 0x4,
        F_BONE_INTERNAL_FLAG2 = 0x8,
        F_BONE_INTERNAL_FLAG3 = 0x10,
    };

    enum {
        M_BONE_INTERNAL_FLAGS =
            F_BONE_INTERNAL_FLAG1 | F_BONE_INTERNAL_FLAG2 | F_BONE_INTERNAL_FLAG3
    };

    HK_FORCE_INLINE int isFlagOn(int boneIdx, hkaPoseFlag enumToCheck) const;
    HK_FORCE_INLINE void setFlag(int boneIdx, hkaPoseFlag enumToCheck) const;
    HK_FORCE_INLINE void clearFlag(int boneIdx, hkaPoseFlag enumToCheck) const;

    HK_FORCE_INLINE int isFlagOnExplicit(hkaPoseFlag flag, hkaPoseFlag enumToCheck) const;
    HK_FORCE_INLINE void setFlagExplicit(hkaPoseFlag& flag, hkaPoseFlag enumToCheck) const;
    HK_FORCE_INLINE void clearFlagExplicit(hkaPoseFlag& flag, hkaPoseFlag enumToCheck) const;

    HK_FORCE_INLINE void clearInternalFlags() const;

    HK_FORCE_INLINE void makeAllChildrenLocalSpace(int boneIdx) const;
    HK_FORCE_INLINE void makeFirstChildrenModelSpace(int boneIdx) const;

    const hkQsTransform& calculateBoneModelSpace(int boneIdx) const;

    void setNonInitializedFlags();
    hkBool checkInternalFlagIsClear(hkaPoseFlag flag) const;

public:
    hkBool checkPoseValidity() const;
    hkBool checkPoseTransformsValidity() const;
};

inline hkaPose::hkaPose(const hkaSkeleton* skeleton)
    : m_skeleton(skeleton), m_modelInSync(false), m_localInSync(false) {
    const int numBones = m_skeleton->m_bones.getSize();
    const int numBonesRoundedUp = HK_NEXT_MULTIPLE_OF(4, numBones);

    m_modelPose.reserveExactly(numBonesRoundedUp);
    m_localPose.reserveExactly(numBonesRoundedUp);
    m_boneFlags.reserveExactly(numBonesRoundedUp);
    m_modelPose.setSize(numBones);
    m_localPose.setSize(numBones);
    m_boneFlags.setSize(numBones);

    const int numSlots = m_skeleton->m_floatSlots.getSize();
    const int numSlotsRoundedUp = HK_NEXT_MULTIPLE_OF(4, numSlots);
    m_floatSlotValues.reserveExactly(numSlotsRoundedUp);
    m_floatSlotValues.setSize(numSlots, hkReal(0));
}

inline hkaPose::hkaPose(const hkaSkeleton* skeleton, void* preallocatedMemory)
    : m_skeleton(skeleton), m_localPose(reinterpret_cast<hkQsTransform*>(preallocatedMemory),
                                        skeleton->m_bones.getSize(), skeleton->m_bones.getSize()),
      m_modelPose(m_localPose.begin() + skeleton->m_bones.getSize(), skeleton->m_bones.getSize(),
                  skeleton->m_bones.getSize()),
      m_boneFlags(reinterpret_cast<hkaPoseFlag*>(m_modelPose.begin() + skeleton->m_bones.getSize()),
                  skeleton->m_bones.getSize(), skeleton->m_bones.getSize()),
      m_modelInSync(false), m_localInSync(false),
      m_floatSlotValues(
          reinterpret_cast<hkReal*>(m_boneFlags.begin() + skeleton->m_bones.getSize()),
          skeleton->m_floatSlots.getSize(),
          HK_NEXT_MULTIPLE_OF(4, skeleton->m_floatSlots.getSize())) {}

inline int hkaPose::getRequiredMemorySize(const hkaSkeleton* skeleton) {
    const int numBonesRoundedUp = HK_NEXT_MULTIPLE_OF(4, skeleton->m_bones.getSize());

    const int floatSizeRoundedUp = HK_NEXT_MULTIPLE_OF(4, skeleton->m_floatSlots.getSize());

    const int totalSize =
        numBonesRoundedUp * (2 * hkSizeOf(hkQsTransform) + hkSizeOf(hkaPoseFlag)) +
        floatSizeRoundedUp * hkSizeOf(hkReal);

    return totalSize;
}

inline const hkaSkeleton* hkaPose::getSkeleton() const {
    return m_skeleton;
}

inline const hkArray<hkReal>& hkaPose::getFloatSlotValues() const {
    return m_floatSlotValues;
}

inline void hkaPose::setFloatSlotValues(const hkArrayBase<hkReal>& floatSlotValues) {
    m_floatSlotValues = floatSlotValues;
}

inline const hkQsTransform& hkaPose::getBoneLocalSpace(int boneIdx) const {
    if (!isFlagOn(boneIdx, F_BONE_LOCAL_DIRTY))
        return m_localPose[boneIdx];

    const hkQsTransform& modelFromBone = m_modelPose[boneIdx];

    const hkInt16 parentIdx = m_skeleton->m_parentIndices[boneIdx];

    if (parentIdx != -1) {
        const hkQsTransform& modelFromParent = getBoneModelSpace(parentIdx);
        m_localPose[boneIdx].setMulInverseMul(modelFromParent, modelFromBone);
    } else {
        m_localPose[boneIdx] = modelFromBone;
    }

    clearFlag(boneIdx, F_BONE_LOCAL_DIRTY);

    return m_localPose[boneIdx];
}

inline const hkQsTransform& hkaPose::getBoneModelSpace(int boneIdx) const {
    if (isFlagOn(boneIdx, F_BONE_MODEL_DIRTY))
        return calculateBoneModelSpace(boneIdx);
    return m_modelPose[boneIdx];
}

inline hkReal hkaPose::getFloatSlotValue(int floatSlotIdx) const {
    return m_floatSlotValues[floatSlotIdx];
}

inline void hkaPose::setBoneLocalSpace(int boneIdx, const hkQsTransform& boneLocal) {
    makeAllChildrenLocalSpace(boneIdx);
    m_localPose[boneIdx] = boneLocal;
    m_boneFlags[boneIdx] = F_BONE_MODEL_DIRTY;
    m_modelInSync = false;
}

inline void hkaPose::setBoneModelSpace(int boneIdx, const hkQsTransform& boneModel,
                                       hkaPose::PropagateOrNot propagateOrNot) {
    if (propagateOrNot)
        makeAllChildrenLocalSpace(boneIdx);
    else
        makeFirstChildrenModelSpace(boneIdx);

    m_modelPose[boneIdx] = boneModel;
    m_boneFlags[boneIdx] = F_BONE_LOCAL_DIRTY;
    m_localInSync = false;
}

inline void hkaPose::setFloatSlotValue(int floatSlotIdx, hkReal value) {
    m_floatSlotValues[floatSlotIdx] = value;
}

inline void hkaPose::syncAll() const {
    syncLocalSpace();
    syncModelSpace();
}

inline hkArray<hkReal>& hkaPose::getFloatSlotValues() {
    return m_floatSlotValues;
}

inline hkaPose& hkaPose::operator=(const hkaPose& other) {
    m_skeleton = other.m_skeleton;
    m_localPose = other.m_localPose;
    m_modelPose = other.m_modelPose;
    m_boneFlags = other.m_boneFlags;
    m_modelInSync = other.m_modelInSync;
    m_localInSync = other.m_localInSync;
    m_floatSlotValues = other.m_floatSlotValues;

    return *this;
}

inline int hkaPose::isFlagOn(int boneIdx, hkaPose::hkaPoseFlag enumToCheck) const {
    return m_boneFlags[boneIdx] & enumToCheck;
}

inline void hkaPose::setFlag(int boneIdx, hkaPose::hkaPoseFlag enumToCheck) const {
    m_boneFlags[boneIdx] |= enumToCheck;
}

inline void hkaPose::clearFlag(int boneIdx, hkaPose::hkaPoseFlag enumToCheck) const {
    m_boneFlags[boneIdx] &= static_cast<hkaPoseFlag>(~enumToCheck);
}

inline int hkaPose::isFlagOnExplicit(hkaPose::hkaPoseFlag flag,
                                     hkaPose::hkaPoseFlag enumToCheck) const {
    return int(flag & enumToCheck);
}

inline void hkaPose::setFlagExplicit(hkaPose::hkaPoseFlag& flag,
                                     hkaPose::hkaPoseFlag enumToCheck) const {
    flag |= enumToCheck;
}

inline void hkaPose::clearFlagExplicit(hkaPose::hkaPoseFlag& flag,
                                       hkaPose::hkaPoseFlag enumToCheck) const {
    flag &= static_cast<hkaPoseFlag>(~enumToCheck);
}

inline void hkaPose::clearInternalFlags() const {
    const int numBones = m_boneFlags.getSize();
    for (int i = 0; i < numBones; ++i)
        m_boneFlags[i] &= (~M_BONE_INTERNAL_FLAGS);
}

inline void hkaPose::makeAllChildrenLocalSpace(int boneIdx) const {
    const int numBones = m_skeleton->m_bones.getSize();

    setFlag(boneIdx, F_BONE_INTERNAL_FLAG1);

    for (int i = boneIdx + 1; i < numBones; ++i) {
        const hkInt16 parentId = m_skeleton->m_parentIndices[i];
        if (parentId != -1 && isFlagOn(parentId, F_BONE_INTERNAL_FLAG1)) {
            getBoneLocalSpace(i);
            setFlag(i, F_BONE_INTERNAL_FLAG1);
            m_modelInSync = false;
        }
    }

    for (int i = boneIdx + 1; i < numBones; ++i) {
        hkaPoseFlag f = m_boneFlags[i];
        if (isFlagOnExplicit(f, F_BONE_INTERNAL_FLAG1)) {
            setFlagExplicit(f, F_BONE_MODEL_DIRTY);
            clearFlagExplicit(f, F_BONE_INTERNAL_FLAG1);
            m_boneFlags[i] = f;
        }
    }
}

inline void hkaPose::makeFirstChildrenModelSpace(int boneIdx) const {
    const int numBones = m_skeleton->m_bones.getSize();

    for (int i = boneIdx + 1; i < numBones; ++i) {
        const hkInt16 parentId = m_skeleton->m_parentIndices[i];
        if (parentId == boneIdx) {
            getBoneModelSpace(i);  // sync model
            m_boneFlags[i] = F_BONE_LOCAL_DIRTY;
            m_localInSync = false;
        }
    }
}
