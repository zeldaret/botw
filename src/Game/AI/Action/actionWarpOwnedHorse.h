#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class WarpOwnedHorse : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(WarpOwnedHorse, ksys::act::ai::Action)
public:
    explicit WarpOwnedHorse(const InitArg& arg);
    ~WarpOwnedHorse() override;

    void loadParams_() override;

protected:
};

}  // namespace uking::action
