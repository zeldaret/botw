#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DemoGetItem : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DemoGetItem, ksys::act::ai::Action)
public:
    explicit DemoGetItem(const InitArg& arg);
    ~DemoGetItem() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
