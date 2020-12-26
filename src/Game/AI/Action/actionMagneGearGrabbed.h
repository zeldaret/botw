#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class MagneGearGrabbed : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(MagneGearGrabbed, ksys::act::ai::Action)
public:
    explicit MagneGearGrabbed(const InitArg& arg);
    ~MagneGearGrabbed() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mConnectDistance_s{};
};

}  // namespace uking::action
