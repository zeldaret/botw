#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkSetCustomPallete : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkSetCustomPallete, ksys::act::ai::Action)
public:
    explicit ForkSetCustomPallete(const InitArg& arg);
    ~ForkSetCustomPallete() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mPalleteType_s{};
};

}  // namespace uking::action
