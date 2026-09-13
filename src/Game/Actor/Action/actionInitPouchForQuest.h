#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class InitPouchForQuest : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(InitPouchForQuest, ksys::act::ai::Action)
public:
    explicit InitPouchForQuest(const InitArg& arg);
    ~InitPouchForQuest() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
