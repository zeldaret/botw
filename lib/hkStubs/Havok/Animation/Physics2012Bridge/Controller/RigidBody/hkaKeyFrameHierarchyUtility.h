#pragma once

#include <Havok/Common/Base/hkBase.h>

class hkpRigidBody;

class hkaKeyFrameHierarchyUtility {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkaKeyFrameHierarchyUtility)
    HK_DECLARE_REFLECTION()

    struct ControlData {
        HK_DECLARE_CLASS_ALLOCATOR(ControlData)
        HK_DECLARE_REFLECTION()

        hkReal m_hierarchyGain;
        hkReal m_velocityDamping;
        hkReal m_accelerationGain;
        hkReal m_velocityGain;
        hkReal m_positionGain;
        hkReal m_positionMaxLinearVelocity;
        hkReal m_positionMaxAngularVelocity;
        hkReal m_snapGain;
        hkReal m_snapMaxLinearVelocity;
        hkReal m_snapMaxAngularVelocity;
        hkReal m_snapMaxLinearDistance;
        hkReal m_snapMaxAngularDistance;

        ControlData()
            : m_hierarchyGain(hkReal(0.17f)), m_velocityDamping(0), m_accelerationGain(1),
              m_velocityGain(hkReal(0.6f)), m_positionGain(hkReal(0.05f)),
              m_positionMaxLinearVelocity(hkReal(1.4f)), m_positionMaxAngularVelocity(hkReal(1.8f)),
              m_snapGain(hkReal(0.1f)), m_snapMaxLinearVelocity(hkReal(0.3f)),
              m_snapMaxAngularVelocity(hkReal(0.3f)), m_snapMaxLinearDistance(hkReal(0.03f)),
              m_snapMaxAngularDistance(hkReal(0.1f)) {}

        explicit ControlData(hkFinishLoadedObjectFlag flag) {}

        hkBool isValid() const;
    };

    struct WorkElem {
        HK_DECLARE_CLASS_ALLOCATOR(WorkElem)

        hkVector4 m_prevPosition;
        hkQuaternion m_prevRotation;
        hkVector4 m_prevLinearVelocity;
        hkVector4 m_prevAngularVelocity;
    };

    struct KeyFrameData {
        HK_DECLARE_CLASS_ALLOCATOR(KeyFrameData)

        hkQsTransform m_worldFromRoot;
        /// The desired pose in local space, one transform for each rigid body
        const hkQsTransform* m_desiredPoseLocalSpace;
        WorkElem* m_internalReferencePose;
    };

    struct BodyData {
        HK_DECLARE_CLASS_ALLOCATOR(BodyData)

        int m_numRigidBodies;
        hkpRigidBody* const* m_rigidBodies;
        const hkInt16* m_parentIndices;
        int* m_controlDataIndices = nullptr;
        const hkReal* m_boneWeights = nullptr;
    };

    struct Output {
        HK_DECLARE_CLASS_ALLOCATOR(Output)

        hkReal m_stressSquared;
    };

    static void initialize(const hkpRigidBody* rb, WorkElem& workElem);

    static void initialize(const BodyData& bodies, WorkElem* internalReferencePose);

    static void applyKeyFrame(hkReal m_deltaTime, const KeyFrameData& pose, const BodyData& body,
                              const ControlData* controlPalette, Output* outputArray = nullptr);
};
