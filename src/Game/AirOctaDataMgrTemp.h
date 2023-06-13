#pragma once
#include "KingSystem/ActorSystem/actActor.h"
namespace uking {
class AirOctaDataMgr  {
    SEAD_RTTI_BASE(AirOctaDataMgr)
    //friend uking::ai::AI::AirOctaFlyUp;
public:
    ksys::act::BaseProcLink& getProc() { return mBaseProcLink; }
    float sub_71002fb17c();
    /* 0x08 */ char unk_00[0x10];
    /* 0x18 */ ksys::act::BaseProcLink mBaseProcLink;
    char placeFiller[0xC8]; 
    /*0xf0 */ float unk_f0;
    char placeFiller2[0x8]; 
    /*0xfc*/ float unk_fc;
    char placeFiller3[0x10]; 
    /*0x110*/ float unk_110;
    /*0x114 */ float unk_114;
    /*0x118 */ float unk_118;
    /*0x11c */ float unk_11c;

};
}