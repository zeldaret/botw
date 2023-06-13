#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actActor.h"
namespace uking::ai {
class AirOctaDataMgr {
    SEAD_RTTI_BASE(AirOctaDataMgr)

public:
    ksys::act::BaseProcLink& getProc() { return mBaseProcLink; }
    void sub_71002FB17C();
    /* 0x08 */ char unk_00[0x10];
    /* 0x18 */ ksys::act::BaseProcLink mBaseProcLink;
    char placeFiller[0xEC]; 
    /*0x114 */ u32 unk_114;
    /*0x118 */ float unk_118;
};

class AirOctaFlyUp : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(AirOctaFlyUp, ksys::act::ai::Ai)
    friend uking::ai::AirOctaDataMgr;
public:
    explicit AirOctaFlyUp(const InitArg& arg);
    ~AirOctaFlyUp() override;

    bool handleMessage_(const ksys::Message& message) override;
    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    float sub_71002FB17C();
protected:
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
};

}  // namespace uking::ai
