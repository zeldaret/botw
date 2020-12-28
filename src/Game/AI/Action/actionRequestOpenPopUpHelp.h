#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RequestOpenPopUpHelp : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(RequestOpenPopUpHelp, ksys::act::ai::Action)
public:
    explicit RequestOpenPopUpHelp(const InitArg& arg);
    ~RequestOpenPopUpHelp() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    int* mHelpType_d{};
};

}  // namespace uking::action
