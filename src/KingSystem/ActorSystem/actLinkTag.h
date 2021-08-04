#pragma once

#include "KingSystem/ActorSystem/actBaseProc.h"
#include "KingSystem/ActorSystem/actBaseProcJobHandler.h"
#include "KingSystem/Map/mapMubinIter.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::map {
class Object;
}  // namespace ksys::map

namespace ksys::act {

class LinkTag : public BaseProc {
public:
    enum Type : u8 { And, Or, NAnd, NOr, XOr, Count, Pulse, None };

    SEAD_RTTI_OVERRIDE(LinkTag, BaseProc)

    static LinkTag* construct(const BaseProc::CreateArg& arg, sead::Heap* heap);

    LinkTag(const BaseProc::CreateArg& arg);
    void calc();

    BaseProcJobHandlerT<LinkTag> mJob;
    unsigned int triggeredLinkFlags[3] = {0,0,0};
    LinkTag::Type linkTagType = And;
    char field_1DD = 0xFF;
    char field_1DE = 0;
    char field_1DF = 0xFF;
    unsigned short flags = 0;
    char tagCount = 0;
    char field_1E3 = 0;
    u32 counter = 0;
    int field_1E8 = 0;
    unsigned int mCalcFrameFlags = 0;
    int hashId = 0;
    int field_1F4 = 0;
    map::MubinIter mMubinIter;
    map::Object* mMapObj = nullptr;
};
KSYS_CHECK_SIZE_NX150(LinkTag, 0x210);

}  // namespace ksys::act
