#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventSuccessGet : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventSuccessGet, ksys::act::ai::Action)
public:
    explicit EventSuccessGet(const InitArg& arg);
    ~EventSuccessGet() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
