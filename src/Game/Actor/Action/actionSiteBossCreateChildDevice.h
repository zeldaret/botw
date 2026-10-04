#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SiteBossCreateChildDevice : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SiteBossCreateChildDevice, ksys::act::ai::Action)
public:
    explicit SiteBossCreateChildDevice(const InitArg& arg);
    ~SiteBossCreateChildDevice() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    bool* mIsCreateA_d{};
    // dynamic_param at offset 0x28
    bool* mIsCreateB_d{};
    // dynamic_param at offset 0x30
    bool* mIsCreateC_d{};
    // dynamic_param at offset 0x38
    bool* mIsCreateD_d{};
};

}  // namespace uking::action
