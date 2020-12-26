#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RemoveSensor : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(RemoveSensor, ksys::act::ai::Action)
public:
    explicit RemoveSensor(const InitArg& arg);
    ~RemoveSensor() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const bool* mAddSensorOnLeave_s{};
};

}  // namespace uking::action
