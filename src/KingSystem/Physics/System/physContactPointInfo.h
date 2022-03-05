#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <container/seadListImpl.h>
#include <container/seadSafeArray.h>
#include <cstddef>
#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include <prim/seadDelegate.h>
#include <prim/seadNamable.h>
#include <prim/seadSafeString.h>
#include <thread/seadAtomic.h>
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {

struct ContactPoint;

class ContactPointInfoBase : public sead::INamable {
public:
    using Points = sead::Buffer<ContactPoint*>;

    // FIXME: parameter names
    ContactPointInfoBase(const sead::SafeString& name, int a, int b, int c)
        : sead::INamable(name), _2c(a), _30(b), _34(c) {}
    virtual ~ContactPointInfoBase() = default;
    virtual void freePoints() = 0;

    u32 get30() const { return _30; }
    void set30(u32 value) { _30 = value; }

    u32 get34() const { return _34; }
    void set34(u32 value) { _34 = value; }

    bool isLayerSubscribed(ContactLayer layer) const {
        const auto type = getContactLayerType(layer);
        return mSubscribedLayers[int(type)].isOnBit(int(getContactLayerBaseRelativeValue(layer)));
    }

    // TODO: rename
    bool isLayerInMask2(ContactLayer layer) const {
        const auto type = getContactLayerType(layer);
        return mLayerMask2[int(type)].isOnBit(int(getContactLayerBaseRelativeValue(layer)));
    }

public:
    // For internal use by the physics system.

    bool isLinked() const { return mListNode.isLinked(); }

    static constexpr size_t getListNodeOffset() {
        return offsetof(ContactPointInfoBase, mListNode);
    }

protected:
    friend class ContactMgr;

    sead::Atomic<int> mContactPointIndex;
    sead::SafeArray<sead::BitFlag32, 2> mSubscribedLayers;
    // TODO: rename
    sead::SafeArray<sead::BitFlag32, 2> mLayerMask2;
    u32 _2c{};
    u32 _30{};
    u32 _34{};
    sead::ListNode mListNode{};
};

class ContactPointInfo : public ContactPointInfoBase {
public:
    enum class ShouldDisableContact : bool {
        Yes = true,
        No = false,
    };

    struct Event {
        RigidBody* body;
        const sead::Vector3f* position;
        const sead::Vector3f* separating_normal;
        const RigidBody::CollisionMasks* collision_masks;
    };

    using ContactCallback = sead::IDelegate2R<ShouldDisableContact*, const Event&, bool>;

    static ContactPointInfo* make(sead::Heap* heap, int num, const sead::SafeString& name, int a,
                                  int b, int c);
    static void free(ContactPointInfo* instance);

    ContactPointInfo(const sead::SafeString& name, int a, int b, int c);
    ~ContactPointInfo() override;
    void freePoints() override;
    virtual void allocPoints(sead::Heap* heap, int num);

    ContactCallback* getContactCallback() const { return mContactCallback; }
    void setContactCallback(ContactCallback* cb) { mContactCallback = cb; }

private:
    friend class ContactMgr;

    Points mPoints;
    ContactCallback* mContactCallback{};
};
KSYS_CHECK_SIZE_NX150(ContactPointInfo, 0x60);

}  // namespace ksys::phys
