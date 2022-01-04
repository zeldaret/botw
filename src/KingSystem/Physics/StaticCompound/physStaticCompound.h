#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <hostio/seadHostIONode.h>
#include <math/seadMatrix.h>
#include <prim/seadSafeString.h>
#include <prim/seadTypedBitFlag.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {

class FieldBodyGroup;

class StaticCompound : public res::Resource, public sead::hostio::Node {
    SEAD_RTTI_OVERRIDE(StaticCompound, res::Resource)

public:
    StaticCompound();
    ~StaticCompound() override;

    FieldBodyGroup* getFieldBodyGroup(int idx);
    bool hasFieldBodyGroup(FieldBodyGroup* group) const;

    // res::Resource interface
    void doCreate_(u8* buffer, u32 buffer_size, sead::Heap* heap) override;
    bool needsParse() const override { return true; }
    bool finishParsing_() override;
    bool m7_() override;

private:
    enum class Flag {
        Initialised = 1 << 0,
    };

    sead::TypedBitFlag<Flag> mFlags;
    sead::Heap* mHeap{};
    void* _50{};
    void* mData{};
    int _60{};
    void* _68{};
    int _70{};
    sead::Buffer<FieldBodyGroup> mFieldBodyGroups;
    sead::FixedSafeString<32> mName;
    sead::Matrix34f mMtx = sead::Matrix34f::ident;
    sead::Buffer<void*> _f0{};
    sead::CriticalSection mCS;
};
KSYS_CHECK_SIZE_NX150(StaticCompound, 0x140);

}  // namespace ksys::phys
