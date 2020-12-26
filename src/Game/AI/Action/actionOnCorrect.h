#pragma once

#include "Game/AI/Action/actionOn.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class OnCorrect : public On {
    SEAD_RTTI_OVERRIDE(OnCorrect, On)
public:
    explicit OnCorrect(const InitArg& arg);
    ~OnCorrect() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
