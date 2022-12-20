#pragma once

#include <Havok/Animation/Physics2012Bridge/Controller/RigidBody/hkaKeyFrameHierarchyUtility.h>
#include <Havok/Common/Base/hkBase.h>

class hkaRagdollInstance;

class hkaRagdollRigidBodyController {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkaRagdollRigidBodyController)

    explicit hkaRagdollRigidBodyController(hkaRagdollInstance* ragdoll);
    ~hkaRagdollRigidBodyController();

    void driveToPose(hkReal deltaTime, const hkQsTransform* poseLocalSpace,
                     const hkQsTransform& worldFromModel,
                     hkaKeyFrameHierarchyUtility::Output* stressOut);

    void reinitialize();
    void reinitialize(int boneIndex);

    const hkaRagdollInstance* getRagdollInstance() const;

    void setBoneWeights(const hkReal* boneWeights);

    hkArray<hkaKeyFrameHierarchyUtility::ControlData> m_controlDataPalette;
    hkArray<int> m_bodyIndexToPaletteIndex;

protected:
    hkaKeyFrameHierarchyUtility::BodyData m_bodyData;
    hkArray<hkaKeyFrameHierarchyUtility::WorkElem> m_internalData;
    hkaRagdollInstance* m_ragdollInstance;
    hkArray<hkInt16> m_rbParentIndices;
};
