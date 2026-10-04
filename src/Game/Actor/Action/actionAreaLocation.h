#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AreaLocation : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AreaLocation, ksys::act::ai::Action)
public:
    explicit AreaLocation(const InitArg& arg);
    ~AreaLocation() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // map_unit_param at offset 0x20
    const int* mLocationPriority_m{};
    // map_unit_param at offset 0x28
    sead::SafeString mMessageID_m{};
};

}  // namespace uking::action
