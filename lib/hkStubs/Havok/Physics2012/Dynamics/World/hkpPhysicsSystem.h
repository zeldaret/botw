#pragma once

#include <Havok/Common/Base/hkBase.h>

class hkpRigidBody;
class hkpConstraintInstance;
class hkpAction;
class hkpPhantom;

class hkpPhysicsSystem : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpPhysicsSystem)
    HK_DECLARE_REFLECTION()

    hkpPhysicsSystem();

    explicit hkpPhysicsSystem(hkFinishLoadedObjectFlag f)
        : hkReferencedObject(f), m_rigidBodies(f), m_constraints(f), m_actions(f), m_phantoms(f),
          m_name(f) {}

    ~hkpPhysicsSystem() override;

    enum CloneConstraintMode {
        CLONE_SHALLOW_IF_NOT_CONSTRAINED_TO_WORLD = 0,
        CLONE_DEEP_WITH_MOTORS = 1,
        CLONE_FORCE_SHALLOW = 2,
        CLONE_DEFAULT = 0,
    };

    virtual hkpPhysicsSystem* clone(CloneConstraintMode cloneMode = CLONE_DEFAULT) const;

    void removeAll();

    void copy(const hkpPhysicsSystem& toCopy);

    void addRigidBody(hkpRigidBody* rb);
    void addPhantom(hkpPhantom* p);
    void addConstraint(hkpConstraintInstance* c);
    void addAction(hkpAction* a);

    void removeRigidBody(int i);
    void removePhantom(int i);
    void removeConstraint(int i);
    void removeAction(int i);

    void removeNullPhantoms();

    inline const hkArray<hkpRigidBody*>& getRigidBodies() const;
    inline const hkArray<hkpPhantom*>& getPhantoms() const;
    inline const hkArray<hkpConstraintInstance*>& getConstraints() const;
    inline const hkArray<hkpAction*>& getActions() const;

    inline const char* getName() const;
    inline void setName(const char* name);

    inline hkUlong getUserData() const;
    inline void setUserData(hkUlong d);

    inline hkBool isActive() const;
    inline void setActive(hkBool active);

    virtual hkBool hasContacts() { return false; }

    void transform(const hkTransform& transformation);

protected:
    hkArray<hkpRigidBody*> m_rigidBodies;
    hkArray<hkpConstraintInstance*> m_constraints;
    hkArray<hkpAction*> m_actions;
    hkArray<hkpPhantom*> m_phantoms;
    hkStringPtr m_name;
    hkUlong m_userData;
    hkBool m_active;
};

inline const hkArray<hkpRigidBody*>& hkpPhysicsSystem::getRigidBodies() const {
    return m_rigidBodies;
}

inline const hkArray<hkpPhantom*>& hkpPhysicsSystem::getPhantoms() const {
    return m_phantoms;
}

inline const hkArray<hkpConstraintInstance*>& hkpPhysicsSystem::getConstraints() const {
    return m_constraints;
}

inline const hkArray<hkpAction*>& hkpPhysicsSystem::getActions() const {
    return m_actions;
}

inline const char* hkpPhysicsSystem::getName() const {
    return m_name;
}

inline void hkpPhysicsSystem::setName(const char* name) {
    m_name = name;
}

inline hkUlong hkpPhysicsSystem::getUserData() const {
    return m_userData;
}

inline void hkpPhysicsSystem::setUserData(hkUlong d) {
    m_userData = d;
}

inline hkBool hkpPhysicsSystem::isActive() const {
    return m_active;
}

inline void hkpPhysicsSystem::setActive(hkBool active) {
    m_active = active;
}
