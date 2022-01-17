#pragma once

#include <Havok/Common/Base/hkBase.h>

class hkpConstraintData;
class hkpConstraintListener;
class hkpConstraintOwner;
struct hkpConstraintRuntime;
class hkpEntity;
class hkpRigidBody;
class hkpSimulationIsland;
class hkpWorld;

class hkpConstraintInstance : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpConstraintInstance)
    HK_DECLARE_REFLECTION()

    enum ConstraintPriority {
        PRIORITY_INVALID,
        PRIORITY_PSI,
        PRIORITY_SIMPLIFIED_TOI_UNUSED,
        PRIORITY_TOI,
        PRIORITY_TOI_HIGHER,
        PRIORITY_TOI_FORCED,
        NUM_PRIORITIES
    };

    enum InstanceType { TYPE_NORMAL = 0, TYPE_CHAIN = 1, TYPE_DISABLE_SPU = 2 };

    enum AddReferences {
        DO_NOT_ADD_REFERENCES,
        DO_ADD_REFERENCES,
    };

    enum CloningMode {
        CLONE_SHALLOW_IF_NOT_CONSTRAINED_TO_WORLD,
        CLONE_DATAS_WITH_MOTORS,
        CLONE_FORCE_SHALLOW
    };

    enum OnDestructionRemapInfo {
        ON_DESTRUCTION_REMAP = 0,
        ON_DESTRUCTION_REMOVE = 1,
        ON_DESTRUCTION_RESET_REMOVE = 2,
    };

    hkpConstraintInstance(hkpEntity* entityA, hkpEntity* entityB, hkpConstraintData* data,
                          ConstraintPriority priority = PRIORITY_PSI);
    explicit hkpConstraintInstance(hkFinishLoadedObjectFlag f)
        : hkReferencedObject(f), m_name(f), m_uid(0xfffffff0) {}
    ~hkpConstraintInstance() override;

    hkpConstraintInstance* clone(hkpEntity* newEntityA, hkpEntity* newEntityB,
                                 CloningMode mode) const;

    inline hkpEntity* getEntityA() const;
    inline hkpEntity* getEntity(int index) const;
    void replaceEntity(hkpEntity* oldEntity, hkpEntity* newEntity);
    inline hkpEntity* getEntityB() const;
    inline hkpRigidBody* getRigidBodyA() const;
    inline hkpRigidBody* getRigidBodyB() const;
    hkBool isConstrainedToWorld() const;
    inline hkpEntity* getOtherEntity(const hkpEntity* entity) const;
    hkpSimulationIsland* getSimulationIsland();
    inline const hkpConstraintData* getData() const;
    inline hkpConstraintData* getDataRw() const;
    void getPivotsInWorld(hkVector4& pivotAinW, hkVector4& pivotBinW) const;

    void addConstraintListener(hkpConstraintListener* listener);
    void removeConstraintListener(hkpConstraintListener* listener);

    void transform(const hkTransform& transformation);
    inline struct hkpModifierConstraintAtom* getConstraintModifiers() const;

    inline hkpConstraintRuntime* getRuntime() const;
    inline void setWantRuntime(hkBool b);
    inline hkBool getWantRuntime() const;

    inline hkUlong getUserData() const;
    inline void setUserData(hkUlong data);

    inline ConstraintPriority getPriority() const;
    void setPriority(ConstraintPriority priority);

    inline const char* getName() const;
    inline void setName(const char* name);

    void setVirtualMassInverse(const hkVector4& invMassA, const hkVector4& invMassB);

    void disable(void);
    void enable(void);
    void setEnabled(hkBool state);
    hkBool isEnabled(void);

    inline hkpConstraintOwner* getOwner() const;
    inline hkpEntity* getMasterEntity() const;
    inline hkpEntity* getSlaveEntity() const;

    virtual void entityAddedCallback(hkpEntity* entity);
    virtual void entityRemovedCallback(hkpEntity* entity);
    virtual void entityDeletedCallback(hkpEntity* entity);

    inline void setOwner(hkpConstraintOwner* island);
    inline struct hkConstraintInternal* getInternal();

    void pointNullsToFixedRigidBody();
    void setFixedRigidBodyPointersToZero(hkpWorld* world);

    virtual InstanceType getType() const { return TYPE_NORMAL; }

private:
    friend class hkpWorldConstraintUtil;
    friend class hkpSimpleConstraintContactMgr;
    friend class hkpSaveContactPointsUtil;

    hkpConstraintInstance() {}

protected:
    explicit hkpConstraintInstance(ConstraintPriority priority);

    friend class hkpSimpleContactConstraintData;
    friend class hkpSimulationIsland;

    hkpConstraintOwner* m_owner;
    hkpConstraintData* m_data;
    struct hkpModifierConstraintAtom* m_constraintModifiers;
    hkpEntity* m_entities[2];

public:
    hkEnum<ConstraintPriority, hkUint8> m_priority;

protected:
    hkBool m_wantRuntime;

public:
    hkEnum<OnDestructionRemapInfo, hkUint8> m_destructionRemapInfo;
    hkSmallArray<hkpConstraintListener*> m_listeners;
    hkStringPtr m_name;
    hkUlong m_userData;
    struct hkConstraintInternal* m_internal;
    hkUint32 m_uid;
};

inline const hkpConstraintData* hkpConstraintInstance::getData() const {
    return m_data;
}

inline hkpConstraintData* hkpConstraintInstance::getDataRw() const {
    return m_data;
}
