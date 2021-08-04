#pragma once

#include <prim/seadLongBitFlag.h>
#include "KingSystem/ActorSystem/actBaseProc.h"
#include "KingSystem/ActorSystem/actBaseProcJobHandler.h"
#include "KingSystem/Map/mapMubinIter.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::map {
class Object;
}  // namespace ksys::map

namespace ksys::act {

class LinkTag : public BaseProc {
    SEAD_RTTI_OVERRIDE(LinkTag, BaseProc)

public:
    enum class Type : u8 { And, Or, NAnd, NOr, XOr, Count, Pulse, None };
    enum class JobFlag { JOB_PLACEHOLDER };
    enum class LinkTagFlag { FLAG_PLACEHOLDER };

    static LinkTag* construct(const BaseProc::CreateArg& arg, sead::Heap* heap);

    explicit LinkTag(const BaseProc::CreateArg& arg);
    void calc();

    BaseProcJobHandlerT<LinkTag> mJob;
    sead::LongBitFlag<96> mTriggeredLinkFlags;
    Type mLinkTagType = Type::And;
    u8 _1dd = 0xFF;
    u8 _1de = 0;
    u8 _1df = 0xFF;
    sead::TypedBitFlag<LinkTagFlag, u16> mFlags = LinkTagFlag::FLAG_PLACEHOLDER;
    // u16 mFlags = 0;
    u8 mTagCount = 0;
    u8 field_1E3 = 0;
    u32 mCounter = 0;
    // int field_1E8 = 0;
    sead::TypedBitFlag<JobFlag, sead::Atomic<u32>> mJobFlags = JobFlag::JOB_PLACEHOLDER;
    u32 mCalcFrameFlags = 0;
    u32 mHashId = 0;
    int field_1F4 = 0;
    map::MubinIter mMubinIter;
    map::Object* mMapObj = nullptr;
};
KSYS_CHECK_SIZE_NX150(LinkTag, 0x210);

}  // namespace ksys::act
