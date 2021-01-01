#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CheckExistenceOfParticipant : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(CheckExistenceOfParticipant, ksys::act::ai::Action)
public:
    explicit CheckExistenceOfParticipant(const InitArg& arg);
    ~CheckExistenceOfParticipant() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    sead::SafeString mActorName_d{};
    // dynamic_param at offset 0x30
    sead::SafeString mInstanceName_d{};
};

}  // namespace uking::action
