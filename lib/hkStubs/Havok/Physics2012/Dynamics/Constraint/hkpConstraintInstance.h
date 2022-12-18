#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics/Constraint/Data/hkpConstraintInfo.h>

struct hkpConstraintAtom;
class hkpConstraintData;
struct hkConstraintInternal;
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

    void disable();
    void enable();
    void setEnabled(hkBool state);
    hkBool isEnabled();

    inline hkpConstraintOwner* getOwner() const;
    inline hkpEntity* getMasterEntity() const;
    inline hkpEntity* getSlaveEntity() const;

    virtual void entityAddedCallback(hkpEntity* entity);
    virtual void entityRemovedCallback(hkpEntity* entity);
    virtual void entityDeletedCallback(hkpEntity* entity);

    inline void setOwner(hkpConstraintOwner* owner);
    inline hkConstraintInternal* getInternal();

    void pointNullsToFixedRigidBody();
    void setFixedRigidBodyPointersToZero(hkpWorld* world);

    virtual InstanceType getType() const { return TYPE_NORMAL; }

private:
    friend class hkpWorldConstraintUtil;
    friend class hkpSimpleConstraintContactMgr;
    friend class hkpSaveContactPointsUtil;

    hkpConstraintInstance() = default;

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
    hkConstraintInternal* m_internal;
    hkUint32 m_uid;
};

struct alignas(16) hkConstraintInternal {
    HK_DECLARE_CLASS_ALLOCATOR(hkConstraintInternal)

    inline hkpEntity* getOtherEntity(const hkpEntity* entity) const;
    inline hkpEntity* getMasterEntity() const;
    inline hkpEntity* getSlaveEntity() const;

    inline hkpConstraintAtom* getAtoms() const { return m_atoms; }
    inline hkUint16 getAtomsSize() const { return m_atomsSize; }

    inline void getConstraintInfo(hkpConstraintInfo& info) const;
    inline void addConstraintInfo(const hkpConstraintInfo& delta);
    inline void subConstraintInfo(const hkpConstraintInfo& delta);
    inline void clearConstraintInfo();

    hkpConstraintInstance* m_constraint;
    hkpEntity* m_entities[2];

protected:
    friend class hkpSaveContactPointsUtil;
    friend class hkpWorldConstraintUtil;

    hkpConstraintAtom* m_atoms;
    hkUint16 m_atomsSize;

public:
    hkUint8 m_callbackRequest;

    hkEnum<hkpConstraintInstance::ConstraintPriority, hkUint8> m_priority;

    hkUint16 m_sizeOfSchemas;
    hkUint16 m_numSolverResults;
    hkUint16 m_numSolverElemTemps;

    hkUint8 m_whoIsMaster;
    hkEnum<hkpConstraintInstance::InstanceType, hkUint8> m_constraintType;

    hkpConstraintRuntime* m_runtime;
    hkUint16 m_runtimeSize;
    hkObjectIndex m_slaveIndex;
};

inline const hkpConstraintData* hkpConstraintInstance::getData() const {
    return m_data;
}

inline hkpConstraintData* hkpConstraintInstance::getDataRw() const {
    return m_data;
}

inline hkpEntity* hkpConstraintInstance::getEntityA() const {
    return m_entities[0];
}

inline hkpEntity* hkpConstraintInstance::getEntity(int index) const {
    return m_entities[index];
}

inline hkpEntity* hkpConstraintInstance::getEntityB() const {
    return m_entities[1];
}

inline hkpRigidBody* hkpConstraintInstance::getRigidBodyA() const {
    return reinterpret_cast<hkpRigidBody*>(m_entities[0]);
}

inline hkpRigidBody* hkpConstraintInstance::getRigidBodyB() const {
    return reinterpret_cast<hkpRigidBody*>(m_entities[1]);
}

inline hkpEntity* hkpConstraintInstance::getOtherEntity(const hkpEntity* entity) const {
    return hkSelectOther(entity, m_entities[0], m_entities[1]);
}

inline hkpModifierConstraintAtom* hkpConstraintInstance::getConstraintModifiers() const {
    return m_constraintModifiers;
}

inline hkpConstraintRuntime* hkpConstraintInstance::getRuntime() const {
    return m_internal->m_runtime;
}

inline void hkpConstraintInstance::setWantRuntime(hkBool b) {
    m_wantRuntime = b;
}

inline hkBool hkpConstraintInstance::getWantRuntime() const {
    return m_wantRuntime;
}

inline hkUlong hkpConstraintInstance::getUserData() const {
    return m_userData;
}

inline void hkpConstraintInstance::setUserData(hkUlong data) {
    m_userData = data;
}

inline hkpConstraintInstance::ConstraintPriority hkpConstraintInstance::getPriority() const {
    return m_priority;
}

inline const char* hkpConstraintInstance::getName() const {
    return m_name;
}

inline void hkpConstraintInstance::setName(const char* name) {
    m_name = name;
}

inline hkpConstraintOwner* hkpConstraintInstance::getOwner() const {
    return m_owner;
}

inline hkpEntity* hkpConstraintInstance::getMasterEntity() const {
    return m_internal->getMasterEntity();
}

inline hkpEntity* hkpConstraintInstance::getSlaveEntity() const {
    return m_internal->getSlaveEntity();
}

inline void hkpConstraintInstance::setOwner(hkpConstraintOwner* owner) {
    m_owner = owner;
}

inline hkConstraintInternal* hkpConstraintInstance::getInternal() {
    return m_internal;
}

inline hkpEntity* hkConstraintInternal::getOtherEntity(const hkpEntity* entity) const {
    return hkSelectOther(entity, m_entities[0], m_entities[1]);
}

inline hkpEntity* hkConstraintInternal::getMasterEntity() const {
    return m_entities[m_whoIsMaster];
}

inline hkpEntity* hkConstraintInternal::getSlaveEntity() const {
    return m_entities[1 - m_whoIsMaster];
}

inline void hkConstraintInternal::getConstraintInfo(hkpConstraintInfo& info) const {
    info.m_maxSizeOfSchema = m_sizeOfSchemas;
    info.m_sizeOfSchemas = m_sizeOfSchemas;
    info.m_numSolverResults = m_numSolverResults;
    info.m_numSolverElemTemps = m_numSolverElemTemps;
}

inline void hkConstraintInternal::addConstraintInfo(const hkpConstraintInfo& delta) {
    const hkUint32 numSolverResults = m_numSolverResults + delta.m_numSolverResults;
    const hkUint32 numSolverElemTemps = m_numSolverElemTemps + delta.m_numSolverElemTemps;
    const hkUint32 sizeOfSchemas = m_sizeOfSchemas + delta.m_sizeOfSchemas;

    m_numSolverResults = hkUint16(numSolverResults);
    m_numSolverElemTemps = hkUint16(numSolverElemTemps);
    m_sizeOfSchemas = hkUint16(sizeOfSchemas);
}

inline void hkConstraintInternal::subConstraintInfo(const hkpConstraintInfo& delta) {
    const hkUint32 numSolverResults = m_numSolverResults - delta.m_numSolverResults;
    const hkUint32 numSolverElemTemps = m_numSolverElemTemps - delta.m_numSolverElemTemps;
    const hkUint32 sizeOfSchemas = m_sizeOfSchemas - delta.m_sizeOfSchemas;

    m_numSolverResults = hkUint16(numSolverResults);
    m_numSolverElemTemps = hkUint16(numSolverElemTemps);
    m_sizeOfSchemas = hkUint16(sizeOfSchemas);
}

inline void hkConstraintInternal::clearConstraintInfo() {
    m_numSolverResults = 0;
    m_numSolverElemTemps = 0;
    m_sizeOfSchemas = 0;
}
