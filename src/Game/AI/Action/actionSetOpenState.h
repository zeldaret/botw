#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SetOpenState : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SetOpenState, ksys::act::ai::Action)
public:
    explicit SetOpenState(const InitArg& arg);
    ~SetOpenState() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // aitree_variable at offset 0x20
    bool* mIsOpenTreasureBox_a{};
};

}  // namespace uking::action
