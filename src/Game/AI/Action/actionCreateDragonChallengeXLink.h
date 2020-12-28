#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CreateDragonChallengeXLink : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(CreateDragonChallengeXLink, ksys::act::ai::Action)
public:
    explicit CreateDragonChallengeXLink(const InitArg& arg);
    ~CreateDragonChallengeXLink() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x20
    int* mXLinkHandleIndex_d{};
};

}  // namespace uking::action
