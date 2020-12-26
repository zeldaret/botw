#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossCreateIceSplinter : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SiteBossCreateIceSplinter, ksys::act::ai::Action)
public:
    explicit SiteBossCreateIceSplinter(const InitArg& arg);
    ~SiteBossCreateIceSplinter() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    sead::SafeString mASName_s{};
    // dynamic_param at offset 0x30
    int* mIgnitionNum_d{};
};

}  // namespace uking::action
