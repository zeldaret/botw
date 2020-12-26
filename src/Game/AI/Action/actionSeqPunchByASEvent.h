#pragma once

#include "Game/AI/Action/actionActionWithAS.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SeqPunchByASEvent : public ActionWithAS {
    SEAD_RTTI_OVERRIDE(SeqPunchByASEvent, ActionWithAS)
public:
    explicit SeqPunchByASEvent(const InitArg& arg);
    ~SeqPunchByASEvent() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    const int* mAttackIntensity_s{};
    // static_param at offset 0x38
    const bool* mIsHammer_s{};
    // static_param at offset 0x40
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
