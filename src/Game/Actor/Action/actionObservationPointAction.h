#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ObservationPointAction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ObservationPointAction, ksys::act::ai::Action)
public:
    explicit ObservationPointAction(const InitArg& arg);
    ~ObservationPointAction() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // map_unit_param at offset 0x20
    sead::SafeString mPointName_m{};
};

}  // namespace uking::action
