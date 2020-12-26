#pragma once

#include "Game/AI/Action/actionDragonPlayASForDemo.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class FirstRunelGrudgeDemo : public DragonPlayASForDemo {
    SEAD_RTTI_OVERRIDE(FirstRunelGrudgeDemo, DragonPlayASForDemo)
public:
    explicit FirstRunelGrudgeDemo(const InitArg& arg);
    ~FirstRunelGrudgeDemo() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
