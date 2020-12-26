#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DisappearNumTargets : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DisappearNumTargets, ksys::act::ai::Action)
public:
    explicit DisappearNumTargets(const InitArg& arg);
    ~DisappearNumTargets() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
