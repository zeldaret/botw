#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <container/seadListImpl.h>
#include <container/seadSafeArray.h>
#include <cstddef>
#include <prim/seadBitFlag.h>
#include <prim/seadNamable.h>
#include <prim/seadSafeString.h>
#include <thread/seadAtomic.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {

class ContactPointInfoBase : public sead::INamable {
public:
    // FIXME: parameter names
    ContactPointInfoBase(const sead::SafeString& name, int a, int b, int c)
        : sead::INamable(name), _2c(a), _30(b), _34(c) {}
    virtual ~ContactPointInfoBase() = default;
    virtual void freePoints() = 0;

    void set30(u32 value) { _30 = value; }

    bool isLinked() const { return mListNode.isLinked(); }
    static constexpr size_t getListNodeOffset() {
        return offsetof(ContactPointInfoBase, mListNode);
    }

protected:
    sead::Atomic<int> _18;
    sead::SafeArray<sead::BitFlag32, 2> mLayerMask;
    sead::SafeArray<sead::BitFlag32, 2> mLayerMask2;
    u32 _2c{};
    u32 _30{};
    u32 _34{};
    sead::ListNode mListNode{};
};

class ContactPointInfo : public ContactPointInfoBase {
public:
    static ContactPointInfo* make(sead::Heap* heap, int num, const sead::SafeString& name, int a,
                                  int b, int c);
    static void free(ContactPointInfo* instance);

    ContactPointInfo(const sead::SafeString& name, int a, int b, int c);
    ~ContactPointInfo() override;
    void freePoints() override;
    virtual void allocPoints(sead::Heap* heap, int num);

private:
    sead::Buffer<void*> mPoints{};
    void* _58{};
};
KSYS_CHECK_SIZE_NX150(ContactPointInfo, 0x60);

}  // namespace ksys::phys
