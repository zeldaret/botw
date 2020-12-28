#pragma once

#include "Game/AI/Action/actionAreaTagAction.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class OwnedHorseObserveAction : public AreaTagAction {
    SEAD_RTTI_OVERRIDE(OwnedHorseObserveAction, AreaTagAction)
public:
    explicit OwnedHorseObserveAction(const InitArg& arg);
    ~OwnedHorseObserveAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    void calc_() override;

    // map_unit_param at offset 0x38
    sead::SafeString mSaveFlag_m{};
};

}  // namespace uking::action
