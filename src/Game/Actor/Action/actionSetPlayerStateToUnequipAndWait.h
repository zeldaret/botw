#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SetPlayerStateToUnequipAndWait : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SetPlayerStateToUnequipAndWait, ksys::act::ai::Action)
public:
    explicit SetPlayerStateToUnequipAndWait(const InitArg& arg);
    ~SetPlayerStateToUnequipAndWait() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
