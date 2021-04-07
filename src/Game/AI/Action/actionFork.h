#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Fork : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(Fork, ksys::act::ai::Action)
public:
    explicit Fork(const InitArg& arg);
    ~Fork() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void setEndState();

    void calc_() override;

    // static_param at offset 0x20
    const int* mEndState_s{};
    // static_param at offset 0x28
    const bool* mIsChangeable_s{};
};

}  // namespace uking::action
