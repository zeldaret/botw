#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/AirOctaDataMgrTemp.h"
namespace uking::ai {

class AirOctaFlyUp :
    public ksys::act::ai::Ai {
    public: static const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfoStatic() { static const sead::RuntimeTypeInfo::Derive<ksys::act::ai::Ai> typeInfo; return &typeInfo; } static bool checkDerivedRuntimeTypeInfoStatic( const sead::RuntimeTypeInfo::Interface* typeInfo) { const sead::RuntimeTypeInfo::Interface* clsTypeInfo = AirOctaFlyUp::getRuntimeTypeInfoStatic(); if (typeInfo == clsTypeInfo) return true; return ksys::act::ai::Ai::checkDerivedRuntimeTypeInfoStatic(typeInfo); } bool checkDerivedRuntimeTypeInfo(const sead::RuntimeTypeInfo::Interface* typeInfo) const override { return checkDerivedRuntimeTypeInfoStatic(typeInfo); } const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfo() const override { return getRuntimeTypeInfoStatic(); }
    friend uking::AirOctaDataMgr;
public:
    explicit AirOctaFlyUp(const InitArg& arg);
    ~AirOctaFlyUp() override;

    bool handleMessage_(const ksys::Message& message) override;
    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    void calc_() override;
    //probably somewhere else, but it has to exist somewhere to get calc_ working
    //void sub_710115b070(ksys::as::ASList *this_, f32 a2, f32 a3, const sead::SafeString& a4, int a5, int a6, bool a7); 
protected:
    // Added
    uking::AirOctaDataMgr *getDataMgr() { return sead::DynamicCast<AirOctaDataMgr>(*mAirOctaDataMgr_a); }
    // static_param at offset 0x38
    const float* mFlyUpDuration_s{};
    // dynamic_param at offset 0x40
    float* mTargetDistance_d{};
    // aitree_variable at offset 0x48
    // for whatever reason, removing  void* mAirOctaDataMgr_a; and replacing it with 
    // AirOctaDataMgr** mAirOctaDataMgr_a{}; will make loadParams_ be not matching with a difference of 0 and make 
    // handleMessage_ go from a difference of 5 to matching.  ¯\_(ツ)_/¯ going from nonmatching to matching and 
    // making another function go from matching to not really unmatching is still net progress
    // void* mAirOctaDataMgr_a
    AirOctaDataMgr** mAirOctaDataMgr_a{};
    float AirOctaY{};
    float mElapsedTime;
    u32 UserData;
    bool mIsEnded;

};

}  // namespace uking::ai
