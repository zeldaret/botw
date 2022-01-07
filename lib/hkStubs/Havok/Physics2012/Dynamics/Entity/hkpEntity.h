#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics2012/Dynamics/Common/hkpMaterial.h>
#include <Havok/Physics2012/Dynamics/Motion/Rigid/hkpKeyframedRigidMotion.h>
#include <Havok/Physics2012/Dynamics/World/hkpWorldObject.h>

struct hkConstraintInternal;
class hkLocalFrame;
class hkSpuCollisionCallbackUtil;
class hkpAction;
class hkpBreakableBody;
class hkpConstraintInstance;
class hkpContactListener;
class hkpEntityActivationListener;
class hkpEntityListener;
class hkpSimulationIsland;

class hkpEntity : public hkpWorldObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpEntity)
    HK_DECLARE_REFLECTION()

    enum SpuCollisionCallbackEventFilter {
        SPU_SEND_NONE = 0x00,
        SPU_SEND_CONTACT_POINT_ADDED = 0x01,
        SPU_SEND_CONTACT_POINT_PROCESS = 0x02,
        SPU_SEND_CONTACT_POINT_REMOVED = 0x04,
        SPU_SEND_CONTACT_POINT_ADDED_OR_PROCESS =
            SPU_SEND_CONTACT_POINT_ADDED | SPU_SEND_CONTACT_POINT_PROCESS,
    };

    class SmallArraySerializeOverrideType {
    public:
        HK_DECLARE_CLASS_ALLOCATOR(SmallArraySerializeOverrideType)
        HK_DECLARE_REFLECTION()

        void* m_data;
        hkUint16 m_size;
        hkUint16 m_capacityAndFlags;
    };

    struct SpuCollisionCallback {
        HK_DECLARE_CLASS_ALLOCATOR(hkpEntity::SpuCollisionCallback)
        HK_DECLARE_REFLECTION()

        SpuCollisionCallback()
            : m_util(nullptr), m_capacity(0),
              m_eventFilter(SPU_SEND_CONTACT_POINT_ADDED_OR_PROCESS), m_userFilter(0x01) {}
        // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init)
        explicit SpuCollisionCallback(hkFinishLoadedObjectFlag flag) {}

        hkSpuCollisionCallbackUtil* m_util;
        hkUint16 m_capacity;
        hkUint8 m_eventFilter;
        hkUint8 m_userFilter;
    };

    struct ExtendedListeners {
        HK_DECLARE_CLASS_ALLOCATOR(ExtendedListeners)
        HK_DECLARE_REFLECTION()

        hkSmallArray<hkpEntityActivationListener*> m_activationListeners;
        hkSmallArray<hkpEntityListener*> m_entityListeners;
    };

    explicit hkpEntity(hkFinishLoadedObjectFlag flag);
    ~hkpEntity() override;

    virtual void deallocateInternalArrays();
    hkMotionState* getMotionState() override { return nullptr; }

    hkpMaterial m_material;
    void* m_limitContactImpulseUtilAndFlag;
    hkReal m_damageMultiplier;
    hkpBreakableBody* m_breakableBody;
    hkUint32 m_solverData;
    hkObjectIndex m_storageIndex;
    hkUint16 m_contactPointCallbackDelay;
    hkSmallArray<hkConstraintInternal> m_constraintsMaster;
    hkArray<hkpConstraintInstance*> m_constraintsSlave;
    hkArray<hkUint8> m_constraintRuntime;
    hkpSimulationIsland* m_simulationIsland;
    hkInt8 m_autoRemoveLevel;
    hkUint8 m_numShapeKeysInContactPointProperties;
    hkUint8 m_responseModifierFlags;
    hkUint32 m_uid;
    SpuCollisionCallback m_spuCollisionCallback;
    hkpMaxSizeMotion m_motion;
    hkSmallArray<hkpContactListener*> m_contactListeners;
    hkSmallArray<hkpAction*> m_actions;
    hkRefPtr<hkLocalFrame> m_localFrame;
    mutable ExtendedListeners* m_extendedListeners;
    hkUint32 m_npData;
};
