#pragma once

#include "Game/AI/Action/actionActionWithPosAngReduce.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Mimic : public ActionWithPosAngReduce {
    SEAD_RTTI_OVERRIDE(Mimic, ActionWithPosAngReduce)
public:
    explicit Mimic(const InitArg& arg);
    ~Mimic() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    const int* mMimicTime_s{};
    // static_param at offset 0x38
    const float* mMimicRate_s{};
    // static_param at offset 0x40
    sead::SafeString mMimicStartASName_s{};
    // static_param at offset 0x50
    sead::SafeString mMimicLoopASName_s{};
    // static_param at offset 0x60
    sead::SafeString mMimicEndASName_s{};
    // aitree_variable at offset 0x70
    int* mMimicryMaterial_a{};
    // aitree_variable at offset 0x78
    bool* mIsStartResetMimicry_a{};
};

}  // namespace uking::action
