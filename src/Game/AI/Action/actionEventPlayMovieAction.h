#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventPlayMovieAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventPlayMovieAction, ksys::act::ai::Action)
public:
    explicit EventPlayMovieAction(const InitArg& arg);
    ~EventPlayMovieAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    sead::SafeString mFileName_d{};
};

}  // namespace uking::action
