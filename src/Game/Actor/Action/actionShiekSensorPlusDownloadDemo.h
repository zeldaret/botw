#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ShiekSensorPlusDownloadDemo : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ShiekSensorPlusDownloadDemo, ksys::act::ai::Action)
public:
    explicit ShiekSensorPlusDownloadDemo(const InitArg& arg);
    ~ShiekSensorPlusDownloadDemo() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    bool* mIsPlayerClose_d{};
};

}  // namespace uking::action
