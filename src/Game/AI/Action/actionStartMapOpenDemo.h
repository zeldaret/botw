#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class StartMapOpenDemo : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(StartMapOpenDemo, ksys::act::ai::Action)
public:
    explicit StartMapOpenDemo(const InitArg& arg);
    ~StartMapOpenDemo() override;

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
