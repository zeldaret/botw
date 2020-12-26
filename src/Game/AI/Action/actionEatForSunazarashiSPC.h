#pragma once

#include "Game/AI/Action/actionHorseEatAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EatForSunazarashiSPC : public HorseEatAction {
    SEAD_RTTI_OVERRIDE(EatForSunazarashiSPC, HorseEatAction)
public:
    explicit EatForSunazarashiSPC(const InitArg& arg);
    ~EatForSunazarashiSPC() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // aitree_variable at offset 0x70
    sead::SafeString* mPrevEatActorName_a{};
};

}  // namespace uking::action
