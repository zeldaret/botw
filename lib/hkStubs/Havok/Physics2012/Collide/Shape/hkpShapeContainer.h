#pragma once

#include <Havok/Common/Base/hkBase.h>
#include <Havok/Physics2012/Collide/Shape/hkpShape.h>
#include <Havok/Physics2012/Collide/Shape/hkpShapeBuffer.h>

class hkpShapeContainer {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkpShapeContainer)

    enum ReferencePolicy {
        REFERENCE_POLICY_IGNORE,
        REFERENCE_POLICY_INCREMENT,
    };

    virtual ~hkpShapeContainer() = default;

    virtual int getNumChildShapes() const;

    virtual hkpShapeKey getFirstKey() const = 0;
    virtual hkpShapeKey getNextKey(hkpShapeKey oldKey) const = 0;
    virtual hkUint32 getCollisionFilterInfo(hkpShapeKey key) const;
    virtual const hkpShape* getChildShape(hkpShapeKey key, hkpShapeBuffer& buffer) const = 0;
    virtual bool isWeldingEnabled() const { return true; }
};

class hkpSingleShapeContainer : public hkpShapeContainer {
public:
    explicit hkpSingleShapeContainer(const hkpShape* s,
                                     ReferencePolicy ref = REFERENCE_POLICY_INCREMENT)
        : m_childShape(s) {
        if (ref == REFERENCE_POLICY_INCREMENT) {
            m_childShape->addReference();
        }
    }

    HK_DECLARE_CLASS_ALLOCATOR(hkpSingleShapeContainer)

    hkpSingleShapeContainer() {}
    explicit hkpSingleShapeContainer(hkFinishLoadedObjectFlag) {}

    ~hkpSingleShapeContainer() override {
        if (m_childShape) {
            m_childShape->removeReference();
        }
    }

    int getNumChildShapes() const override { return 1; }
    hkpShapeKey getFirstKey() const override { return 0; }
    hkpShapeKey getNextKey(hkpShapeKey oldKey) const override { return HK_INVALID_SHAPE_KEY; }
    const hkpShape* getChildShape(hkpShapeKey key, hkpShapeBuffer& buffer) const override;

    const hkpShape* getChild() const { return m_childShape; }
    const hkpShape* operator->() const { return m_childShape; }

protected:
    const hkpShape* m_childShape;
};
