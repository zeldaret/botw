#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class AlarmLynelTag : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(AlarmLynelTag, ksys::act::ai::Action)
public:
    explicit AlarmLynelTag(const InitArg& arg);
    ~AlarmLynelTag() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // map_unit_param at offset 0x20
    const int* mAlarmPoint_m{};
};

}  // namespace uking::action
