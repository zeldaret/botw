#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class NPCRoam : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(NPCRoam, ksys::act::ai::Ai)
public:
    explicit NPCRoam(const InitArg& arg);
    ~NPCRoam() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mWaitFrame_s{};
    // static_param at offset 0x40
    const int* mWaitFrameRand_s{};
    // static_param at offset 0x48
    const float* mRadius_s{};
    // static_param at offset 0x50
    const float* mWalkDistMin_s{};
    // static_param at offset 0x58
    const float* mWalkDistMax_s{};
    // dynamic_param at offset 0x60
    sead::SafeString* mWaitASName_d{};
    // dynamic_param at offset 0x70
    sead::Vector3f* mBasisPos_d{};
};

}  // namespace uking::ai
