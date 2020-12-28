#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventEnableModelDraw : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventEnableModelDraw, ksys::act::ai::Action)
public:
    explicit EventEnableModelDraw(const InitArg& arg);
    ~EventEnableModelDraw() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
