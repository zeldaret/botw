#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkASTrgRemainsHowl : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkASTrgRemainsHowl, ksys::act::ai::Action)
public:
    explicit ForkASTrgRemainsHowl(const InitArg& arg);
    ~ForkASTrgRemainsHowl() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mSeqBank_s{};
    // static_param at offset 0x28
    const int* mTargetBone_s{};
    // dynamic_param at offset 0x30
    bool* mIsTargetLost_d{};
};

}  // namespace uking::action
