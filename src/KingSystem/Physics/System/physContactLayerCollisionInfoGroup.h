#pragma once

#include <container/seadBuffer.h>
#include <container/seadListImpl.h>
#include <container/seadPtrArray.h>
#include <prim/seadNamable.h>
#include "KingSystem/Physics/physDefines.h"

namespace ksys::phys {

struct CollidingBodies;
class ContactLayerCollisionInfo;

/// Container for ContactLayerCollisionInfo instances that pertain to a contact layer
/// paired with other layers.
class ContactLayerCollisionInfoGroup : public sead::INamable {
public:
    class CollidingBodiesIterator;
    struct CollidingBodiesRange;

    struct LayerInfo {
        ContactLayer layer;
        /// Is `layer` greater than the layer of the group?
        bool layer_gt;
        /// Is `layer` lower or equal to the layer of the group?
        bool layer_le;
    };

    static ContactLayerCollisionInfoGroup* make(sead::Heap* heap, ContactLayer layer, int capacity,
                                                const sead::SafeString& name);
    static void free(ContactLayerCollisionInfoGroup* group);

    ContactLayerCollisionInfoGroup(ContactLayer layer, const sead::SafeString& name);
    virtual ~ContactLayerCollisionInfoGroup();

    /// @param capacity The maximum number of layers that can be added to this group.
    void init(sead::Heap* heap, int capacity);
    void finalize();

    /// Add (mLayer, layer) to the list of layer pairs in this group.
    void addLayer(ContactLayer layer);

    /// Call this to ensure that all layer pairs in this group are being tracked by
    /// the relevant contact listener. This may be necessary if the listener has been reset.
    void ensureLayersAreTracked();

    CollidingBodiesIterator collidingBodiesBegin() const;
    CollidingBodiesIterator collidingBodiesEnd() const;
    CollidingBodiesRange getCollidingBodies() const;

    const sead::PtrArray<ContactLayerCollisionInfo>& getCollisionInfo() const {
        return mCollisionInfoInstances;
    }

    static constexpr size_t getListNodeOffset() {
        return offsetof(ContactLayerCollisionInfoGroup, mListNode);
    }

private:
    ContactLayer mLayer;
    sead::PtrArray<ContactLayerCollisionInfo> mCollisionInfoInstances;
    sead::Buffer<LayerInfo> mLayers;
    sead::ListNode mListNode;
};

class ContactLayerCollisionInfoGroup::CollidingBodiesIterator {
public:
    enum class IsStart : bool { Yes = true, No = false };

    CollidingBodiesIterator(const ContactLayerCollisionInfoGroup* group, int index, IsStart start);
    ~CollidingBodiesIterator();

    const LayerInfo& getLayerInfo() const { return mGroup->mLayers[mInfoIndex]; }

    const CollidingBodies& operator*() const { return *mCollidingBodiesEntry; }
    const CollidingBodies* operator->() const { return mCollidingBodiesEntry; }
    CollidingBodiesIterator& operator++();

    bool operator==(const CollidingBodiesIterator& other) const {
        return mInfoIndex == other.mInfoIndex &&
               mCollidingBodiesEntry == other.mCollidingBodiesEntry;
    }

    bool operator!=(const CollidingBodiesIterator& other) const { return !operator==(other); }

private:
    void initIterator(const ContactLayerCollisionInfoGroup* group);

    const ContactLayerCollisionInfoGroup* mGroup{};
    ContactLayerCollisionInfo* mInfo{};
    /// The current CollidingBodies pair within the current ContactLayerCollisionInfo (mInfo).
    const CollidingBodies* mCollidingBodiesEntry{};
    int mInfoIndex{};
};

struct ContactLayerCollisionInfoGroup::CollidingBodiesRange {
    auto begin() const { return group->collidingBodiesBegin(); }
    auto end() const { return group->collidingBodiesEnd(); }

    const ContactLayerCollisionInfoGroup* group;
};

inline ContactLayerCollisionInfoGroup::CollidingBodiesIterator
ContactLayerCollisionInfoGroup::collidingBodiesBegin() const {
    return {this, 0, CollidingBodiesIterator::IsStart::Yes};
}

inline ContactLayerCollisionInfoGroup::CollidingBodiesIterator
ContactLayerCollisionInfoGroup::collidingBodiesEnd() const {
    return {this, mCollisionInfoInstances.size(), CollidingBodiesIterator::IsStart::No};
}

inline ContactLayerCollisionInfoGroup::CollidingBodiesRange
ContactLayerCollisionInfoGroup::getCollidingBodies() const {
    return {this};
}

}  // namespace ksys::phys
