#pragma once

#include "Game/AI/Action/actionPlayASForDemo.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DragonPlayASForDemo : public PlayASForDemo {
    SEAD_RTTI_OVERRIDE(DragonPlayASForDemo, PlayASForDemo)
public:
    explicit DragonPlayASForDemo(const InitArg& arg);
    ~DragonPlayASForDemo() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xb0
    const sead::Vector3f* mPosition_s{};
    // static_param at offset 0xb8
    const sead::Vector3f* mRotate_s{};
};

}  // namespace uking::action
