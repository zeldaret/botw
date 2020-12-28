#pragma once

#include "Game/AI/Action/actionEventOpenGetDemo.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventOpenGetWeaponDemo : public EventOpenGetDemo {
    SEAD_RTTI_OVERRIDE(EventOpenGetWeaponDemo, EventOpenGetDemo)
public:
    explicit EventOpenGetWeaponDemo(const InitArg& arg);
    ~EventOpenGetWeaponDemo() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
