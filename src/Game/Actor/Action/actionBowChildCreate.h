#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BowChildCreate : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(BowChildCreate, ksys::act::ai::Action)
public:
    explicit BowChildCreate(const InitArg& arg);
    ~BowChildCreate() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    int* mID_d{};
    // dynamic_param at offset 0x28
    ksys::act::BaseProcLink* mParentActor_d{};
};

}  // namespace uking::action
