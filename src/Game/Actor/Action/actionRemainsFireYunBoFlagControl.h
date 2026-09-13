#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RemainsFireYunBoFlagControl : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(RemainsFireYunBoFlagControl, ksys::act::ai::Action)
public:
    explicit RemainsFireYunBoFlagControl(const InitArg& arg);
    ~RemainsFireYunBoFlagControl() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // map_unit_param at offset 0x20
    const int* mRemainsFireYunBoFlagType_m{};
};

}  // namespace uking::action
