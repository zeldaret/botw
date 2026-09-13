#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RequestCreateHCIModel : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(RequestCreateHCIModel, ksys::act::ai::Action)
public:
    explicit RequestCreateHCIModel(const InitArg& arg);
    ~RequestCreateHCIModel() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
