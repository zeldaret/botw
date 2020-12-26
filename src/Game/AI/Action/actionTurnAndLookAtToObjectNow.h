#pragma once

#include "Game/AI/Action/actionLookAtObject.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class TurnAndLookAtToObjectNow : public LookAtObject {
    SEAD_RTTI_OVERRIDE(TurnAndLookAtToObjectNow, LookAtObject)
public:
    explicit TurnAndLookAtToObjectNow(const InitArg& arg);
    ~TurnAndLookAtToObjectNow() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0xc8
    bool* mIsConfront_d{};
};

}  // namespace uking::action
