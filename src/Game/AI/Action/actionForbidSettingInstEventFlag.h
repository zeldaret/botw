#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForbidSettingInstEventFlag : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForbidSettingInstEventFlag, ksys::act::ai::Action)
public:
    explicit ForbidSettingInstEventFlag(const InitArg& arg);
    ~ForbidSettingInstEventFlag() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
