#pragma once
#include "KingSystem/ActorSystem/actActor.h"
namespace uking {
class AirOctaDataMgr {
    public: static const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfoStatic() { static const sead::RuntimeTypeInfo::Root typeInfo; return &typeInfo; } static bool checkDerivedRuntimeTypeInfoStatic( const sead::RuntimeTypeInfo::Interface* typeInfo) { const sead::RuntimeTypeInfo::Interface* clsTypeInfo = AirOctaDataMgr::getRuntimeTypeInfoStatic(); return typeInfo == clsTypeInfo; } virtual bool checkDerivedRuntimeTypeInfo(const sead::RuntimeTypeInfo::Interface* typeInfo) const { return checkDerivedRuntimeTypeInfoStatic(typeInfo); } virtual const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfo() const { return getRuntimeTypeInfoStatic(); }
    //friend uking::ai::AI::AirOctaFlyUp;
public:
    ksys::act::BaseProcLink& getProc() { return mBaseProcLink; }
    void sub_71002fb17c();
    /* 0x08 */ ksys::act::BaseProcLink unk_00;
    /* 0x18 */ ksys::act::BaseProcLink mBaseProcLink;
    char placeFiller[36]; 
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
}