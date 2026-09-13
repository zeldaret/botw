#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SetInstEventFlag : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SetInstEventFlag, ksys::act::ai::Action)
public:
    explicit SetInstEventFlag(const InitArg& arg);
    ~SetInstEventFlag() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
