#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventDisappearGolfCount : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventDisappearGolfCount, ksys::act::ai::Action)
public:
    explicit EventDisappearGolfCount(const InitArg& arg);
    ~EventDisappearGolfCount() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
