#pragma once

#include <prim/seadLongBitFlag.h>
#include <prim/seadTypedBitFlag.h>
#include <thread/seadAtomic.h>
#include "KingSystem/ActorSystem/actBaseProc.h"
#include "KingSystem/ActorSystem/actBaseProcJobHandler.h"
#include "KingSystem/Map/mapMubinIter.h"
#include "KingSystem/Map/mapObjectLink.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::map {
class Object;
}  // namespace ksys::map

namespace ksys::act {

class LinkTag : public BaseProc {
    SEAD_RTTI_OVERRIDE(LinkTag, BaseProc)

public:
    enum class Type { And, Or, NAnd, NOr, XOr, Count, Pulse, None };
    enum class JobFlag {};
    enum class LinkTagFlag : u16 {
        _1 = 0x1,
        _4 = 0x4,
        _8 = 0x8,
        _10 = 0x10,
        _20 = 0x20,
        _40 = 0x40,
        _100 = 0x100,
        _200 = 0x200,
        _400 = 0x400,
        _800 = 0x800,
        _1000 = 0x1000,

        _30 = _10 | _20,
        _C00 = _400 | _800
    };

    static LinkTag* construct(const BaseProc::CreateArg& arg, sead::Heap* heap);

    explicit LinkTag(const BaseProc::CreateArg& arg);
    void calc();
    void calcPulse(bool update);
    void calcCount(bool update);
    void calcOther(bool update);
    bool init();
    void finalizeInit(BaseProc::InitContext* context);
    void updateIsFlagSetFlag(bool isFlagSet, bool a3, bool a4);
    bool isTriggered(map::ObjectLink* link, u32 linkIdx);

    // this doesn't even belong in this namespace, but is used as a placeholder for init()
    void isFlagSet(bool* isSet, int unk, map::Object* object);

    BaseProcJobHandlerT<LinkTag> mJob;
    sead::LongBitFlag<96> mTriggeredLinkFlags;
    sead::SizedEnum<Type, s8> mLinkTagType = Type::And;
    u8 _1dd = 0xFF;
    sead::Atomic<u8> _1de = 0;
    u8 _1df = 0xFF;
    sead::TypedBitFlag<LinkTagFlag> mFlags;
    s8 mTagCount = 0;
    u8 _1E3 = 0;
    s32 mCounter = 0;
    int _1E8 = 0;
    sead::Atomic<u32> mJobFlags;
    u32 mHashId = 0;
    map::MubinIter mMubinIter;
    map::Object* mMapObj = nullptr;
};
KSYS_CHECK_SIZE_NX150(LinkTag, 0x210);

}  // namespace ksys::act
