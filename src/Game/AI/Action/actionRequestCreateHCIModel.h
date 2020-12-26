#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class RequestCreateHCIModel : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(RequestCreateHCIModel, ksys::act::ai::Action)
public:
    explicit RequestCreateHCIModel(const InitArg& arg);
    ~RequestCreateHCIModel() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
