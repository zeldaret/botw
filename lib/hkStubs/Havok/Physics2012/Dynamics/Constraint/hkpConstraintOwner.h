#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics2012/Dynamics/Constraint/hkpConstraintInstance.h>

class hkpConstraintOwner : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpConstraintOwner)

    inline void addConstraintInfo(hkpConstraintInstance* constraint, hkpConstraintInfo& delta);
    inline void subConstraintInfo(hkpConstraintInstance* constraint, hkpConstraintInfo& delta);

    virtual void addConstraintToCriticalLockedIsland(hkpConstraintInstance* constraint) {}
    virtual void removeConstraintFromCriticalLockedIsland(hkpConstraintInstance* constraint) {}
    virtual void addCallbackRequest(hkpConstraintInstance* constraint, int request) {}
    virtual void checkAccessRw() {}

    hkpConstraintInfo m_constraintInfo;
};

inline void hkpConstraintOwner::addConstraintInfo(hkpConstraintInstance* constraint,
                                                  hkpConstraintInfo& delta) {
    if (!constraint->m_internal)
        return;

    m_constraintInfo.add(delta);
    constraint->m_internal->addConstraintInfo(delta);
    m_constraintInfo.m_maxSizeOfSchema =
        hkMath::max2(m_constraintInfo.m_maxSizeOfSchema, constraint->m_internal->m_sizeOfSchemas);
}

inline void hkpConstraintOwner::subConstraintInfo(hkpConstraintInstance* constraint,
                                                  hkpConstraintInfo& delta) {
    if (!constraint->m_internal)
        return;

    m_constraintInfo.sub(delta);
    constraint->m_internal->subConstraintInfo(delta);
}
