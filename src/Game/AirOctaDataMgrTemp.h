#pragma once
#include "KingSystem/ActorSystem/actActor.h"
namespace uking {
class AirOctaDataMgr {
    SEAD_RTTI_BASE(AirOctaDataMgr)
public:
    ksys::act::BaseProcLink& getProc() { return mBaseProcLink; }
    void sub_71002fb17c();
    /* 0x08 */ ksys::act::BaseProcLink mBaseProcLink;
    char placeFiller[52];
    /*0x3f */ float unk_3f;
    char placeFiller2[158];
    /*0xf0 */ float unk_f0;
    char placeFiller3[4];
    sead::Vector3f unk_fc;
    char placeFiller4[12];
    /*0x110 */ float unk_110;
    /*0x114 */ float unk_114;
    /*0x118 */ float unk_118;
    /*0x11c */ float unk_11c;
};
}  // namespace uking