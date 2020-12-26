#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WolfLinkAmiiboWarp : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(WolfLinkAmiiboWarp, ksys::act::ai::Action)
public:
    explicit WolfLinkAmiiboWarp(const InitArg& arg);
    ~WolfLinkAmiiboWarp() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    sead::Vector3f* mTargetPos_d{};
};

}  // namespace uking::action
