#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerSetWakeUpMtx : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(PlayerSetWakeUpMtx, ksys::act::ai::Action)
public:
    explicit PlayerSetWakeUpMtx(const InitArg& arg);
    ~PlayerSetWakeUpMtx() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
