#pragma once

#include "Game/AI/AI/AirOcta/AirOctaDataMgr.h"
#include "KingSystem/ActorSystem/actAiAi.h"
namespace uking {
class AirOctaDataMgr;
namespace ai {
class AirOctaFlyUp : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(AirOctaFlyUp, ksys::act::ai::Ai)
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

protected:
    AirOctaDataMgr* getDataMgr() const {
        return sead::DynamicCast<AirOctaDataMgr>(*mAirOctaDataMgr_a);
    }
    // static_param at offset 0x38
    const float* mFlyUpDuration_s{};
    // dynamic_param at offset 0x40
    float* mTargetDistance_d{};
    // aitree_variable at offset 0x48
    // for whatever reason, removing  void* mAirOctaDataMgr_a; and replacing it with
    // AirOctaDataMgr** mAirOctaDataMgr_a{}; will make loadParams_ be not matching with a difference
    // of 0 and make handleMessage_ go from a difference of 5 to matching.  ¯\_(ツ)_/¯ going from
    // nonmatching to matching and making another function go from matching to not really unmatching
    // is still net progress void* mAirOctaDataMgr_a
    AirOctaDataMgr** mAirOctaDataMgr_a{};
    float AirOctaY{};
    float mElapsedTime;
    u32 mUserData;
    bool mIsEnded;
};

}  // namespace ai
}  // namespace uking
