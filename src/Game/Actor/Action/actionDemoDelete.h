#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DemoDelete : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DemoDelete, ksys::act::ai::Action)
public:
    explicit DemoDelete(const InitArg& arg);
    ~DemoDelete() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
