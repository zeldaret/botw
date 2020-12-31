#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class MasquaradeSubTargetSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(MasquaradeSubTargetSelect, ksys::act::ai::Ai)
public:
    explicit MasquaradeSubTargetSelect(const InitArg& arg);
    ~MasquaradeSubTargetSelect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x38
    ksys::act::BaseProcLink* mTargetActor_d{};
};

}  // namespace uking::ai
