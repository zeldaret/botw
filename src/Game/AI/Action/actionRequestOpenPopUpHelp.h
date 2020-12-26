#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RequestOpenPopUpHelp : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(RequestOpenPopUpHelp, ksys::act::ai::Action)
public:
    explicit RequestOpenPopUpHelp(const InitArg& arg);
    ~RequestOpenPopUpHelp() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    int* mHelpType_d{};
};

}  // namespace uking::action
