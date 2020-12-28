#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RestorePouchForQuest : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(RestorePouchForQuest, ksys::act::ai::Action)
public:
    explicit RestorePouchForQuest(const InitArg& arg);
    ~RestorePouchForQuest() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
