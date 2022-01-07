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
class hkpDynamicsContactMgr;
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

    void addEntityListener(hkpEntityListener* el);
    void removeEntityListener(hkpEntityListener* el);

    void addEntityActivationListener(hkpEntityActivationListener* el);
    void removeEntityActivationListener(hkpEntityActivationListener* el);

    void addContactListener(hkpContactListener* cl);
    void removeContactListener(hkpContactListener* cl);

    inline const hkSmallArray<hkpEntityListener*>& getEntityListeners() const;
    inline const hkSmallArray<hkpEntityActivationListener*>& getEntityActivationListeners() const;
    inline const hkSmallArray<hkpContactListener*>& getContactListeners() const;
    inline bool areContactListenersAdded() const;

    inline hkUint16 getContactPointCallbackDelay() const;
    inline void setContactPointCallbackDelay(hkUint16 delay);

    inline hkpMaterial& getMaterial();
    inline const hkpMaterial& getMaterial() const;

    inline hkBool isFixed() const;
    inline hkBool isFixedOrKeyframed() const;
    inline hkUint32 getUid() const;

    hkpDynamicsContactMgr* findContactMgrTo(const hkpEntity* entity) const;

    hkpBreakableBody* getBreakableBody() const;

    void activate();
    void requestDeactivation();
    void deactivate();
    void activateAsCriticalOperation();
    void requestDeactivationAsCriticalOperation();
    void deactivateAsCriticalOperation();
    hkBool isActive() const;

    inline int getNumActions() const;
    inline hkpAction* getAction(int i);

    int getNumConstraints() const;
    hkpConstraintInstance* getConstraint(int i);
    void getAllConstraints(hkArray<hkpConstraintInstance*>& constraints);
    const hkpConstraintInstance* getConstraint(int i) const;
    inline const hkSmallArray<struct hkConstraintInternal>& getConstraintMasters() const;
    inline hkSmallArray<struct hkConstraintInternal>& getConstraintMastersRw();
    inline const hkArray<class hkpConstraintInstance*>& getConstraintSlaves() const;

    void sortConstraintsSlavesDeterministically();

    void setCachedShapeData(const hkpWorld* world, const hkpShape* shape);

    void updateCachedAabb();

protected:
    const hkSmallArray<struct hkConstraintInternal>& getConstraintMastersImpl() const;
    hkSmallArray<struct hkConstraintInternal>& getConstraintMastersRwImpl();
    const hkArray<class hkpConstraintInstance*>& getConstraintSlavesImpl() const;

    explicit hkpEntity(const hkpShape* shape);

public:
    inline hkpMotion* getMotion();
    inline hkpSimulationIsland* getSimulationIsland() const;

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

inline const hkSmallArray<hkpEntityListener*>& hkpEntity::getEntityListeners() const {
    if (!m_extendedListeners)
        m_extendedListeners = new ExtendedListeners;
    return m_extendedListeners->m_entityListeners;
}

inline const hkSmallArray<hkpEntityActivationListener*>&
hkpEntity::getEntityActivationListeners() const {
    if (!m_extendedListeners)
        m_extendedListeners = new ExtendedListeners;
    return m_extendedListeners->m_activationListeners;
}

inline const hkSmallArray<hkpContactListener*>& hkpEntity::getContactListeners() const {
    return m_contactListeners;
}

inline bool hkpEntity::areContactListenersAdded() const {
    return m_contactListeners.getSize() > 0;
}

inline hkUint16 hkpEntity::getContactPointCallbackDelay() const {
    return m_contactPointCallbackDelay;
}

inline void hkpEntity::setContactPointCallbackDelay(hkUint16 delay) {
    m_contactPointCallbackDelay = delay;
}

inline hkpMaterial& hkpEntity::getMaterial() {
    return m_material;
}

inline const hkpMaterial& hkpEntity::getMaterial() const {
    return m_material;
}

inline hkBool hkpEntity::isFixed() const {
    return m_motion.getType() == hkpMotion::MOTION_FIXED;
}

inline hkBool hkpEntity::isFixedOrKeyframed() const {
    return isFixed() || m_motion.getType() == hkpMotion::MOTION_KEYFRAMED;
}

inline hkUint32 hkpEntity::getUid() const {
    return m_uid;
}

inline hkpBreakableBody* hkpEntity::getBreakableBody() const {
    return m_breakableBody;
}

inline const hkSmallArray<struct hkConstraintInternal>& hkpEntity::getConstraintMasters() const {
    return getConstraintMastersImpl();
}

inline hkSmallArray<struct hkConstraintInternal>& hkpEntity::getConstraintMastersRw() {
    return getConstraintMastersRwImpl();
}

inline const hkArray<class hkpConstraintInstance*>& hkpEntity::getConstraintSlaves() const {
    return getConstraintSlavesImpl();
}

inline hkpMotion* hkpEntity::getMotion() {
    return &m_motion;
}

inline hkpSimulationIsland* hkpEntity::getSimulationIsland() const {
    return m_simulationIsland;
}

inline hkpAction* hkpEntity::getAction(int i) {
    return m_actions[i];
}

inline int hkpEntity::getNumActions() const {
    return m_actions.getSize();
}
