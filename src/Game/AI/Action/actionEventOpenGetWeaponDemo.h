#pragma once

#include "Game/AI/Action/actionEventOpenGetDemo.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventOpenGetWeaponDemo : public EventOpenGetDemo {
    SEAD_RTTI_OVERRIDE(EventOpenGetWeaponDemo, EventOpenGetDemo)
public:
    explicit EventOpenGetWeaponDemo(const InitArg& arg);
    ~EventOpenGetWeaponDemo() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    bool* mIsInvalidOpenPouch_d{};
};

}  // namespace uking::action
