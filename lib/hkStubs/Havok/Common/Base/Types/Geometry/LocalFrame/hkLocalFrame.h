#pragma once

#include <Havok/Common/Base/hkBase.h>

class hkLocalFrameCollector;
class hkLocalFrameGroup;

class hkLocalFrame : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkLocalFrame)
    HK_DECLARE_REFLECTION()

    hkLocalFrame() {}
    explicit hkLocalFrame(hkFinishLoadedObjectFlag flag) : hkReferencedObject(flag) {}

    void getTransformToRoot(hkTransform& transform) const;

    void getPositionInRoot(hkVector4& position) const;

    virtual void getLocalTransform(hkTransform& transform) const = 0;
    virtual void setLocalTransform(const hkTransform& transform) = 0;

    virtual void getLocalPosition(hkVector4& position) const;

    virtual void getNearbyFrames(const hkVector4& target, hkReal maxDistance,
                                 hkLocalFrameCollector& collector) const = 0;

    virtual const char* getName() const = 0;

    virtual const hkLocalFrame* getParentFrame() const = 0;
    virtual void setParentFrame(const hkLocalFrame* parentFrame) = 0;

    virtual int getNumChildFrames() const = 0;
    virtual hkLocalFrame* getChildFrame(int i) const = 0;

    virtual const hkLocalFrameGroup* getGroup() const = 0;
    virtual void setGroup(const hkLocalFrameGroup* localFrameGroup) = 0;

    virtual void getDescendants(hkArrayBase<const hkLocalFrame*>& descendants,
                                hkMemoryAllocator& a) const;

    HK_FORCE_INLINE void getDescendants(hkArray<const hkLocalFrame*>& descendants) const {
        getDescendants(descendants, hkContainerHeapAllocator::get());
    }
};

class hkLocalFrameCollector : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkLocalFrameCollector)

    virtual void addFrame(const hkLocalFrame* frame, hkReal distance) = 0;
};

class hkLocalFrameGroup : public hkReferencedObject {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkLocalFrameGroup)
    HK_DECLARE_REFLECTION()

    explicit hkLocalFrameGroup(const char* name) : m_name(name) {}

    explicit hkLocalFrameGroup(hkFinishLoadedObjectFlag flag)
        : hkReferencedObject(flag), m_name(flag) {}

    const char* getName() const { return m_name; }

private:
    hkStringPtr m_name;
};

class hkSimpleLocalFrame : public hkLocalFrame {
public:
    HK_DECLARE_CLASS_ALLOCATOR(hkSimpleLocalFrame)
    HK_DECLARE_REFLECTION()

    hkSimpleLocalFrame() : m_parentFrame(nullptr), m_group(nullptr), m_name(nullptr) {}

    explicit hkSimpleLocalFrame(hkFinishLoadedObjectFlag flag)
        : hkLocalFrame(flag), m_children(flag), m_name(flag) {}

    ~hkSimpleLocalFrame() override;

    void getLocalTransform(hkTransform& transform) const override;
    void setLocalTransform(const hkTransform& transform) override;
    void getLocalPosition(hkVector4& position) const override;
    void getNearbyFrames(const hkVector4& target, hkReal maxDistance,
                         hkLocalFrameCollector& collector) const override;
    const char* getName() const override { return m_name; }
    const hkLocalFrame* getParentFrame() const override { return m_parentFrame; }
    void setParentFrame(const hkLocalFrame* parentFrame) override { m_parentFrame = parentFrame; }
    int getNumChildFrames() const override;
    hkLocalFrame* getChildFrame(int i) const override;
    const hkLocalFrameGroup* getGroup() const override { return m_group; }
    void setGroup(const hkLocalFrameGroup* group) override;

    hkTransform m_transform;
    hkArray<hkLocalFrame*> m_children;
    const hkLocalFrame* m_parentFrame;
    const hkLocalFrameGroup* m_group;
    hkStringPtr m_name;
};
