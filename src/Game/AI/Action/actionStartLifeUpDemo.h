#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class StartLifeUpDemo : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(StartLifeUpDemo, ksys::act::ai::Action)
public:
    explicit StartLifeUpDemo(const InitArg& arg);
    ~StartLifeUpDemo() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
