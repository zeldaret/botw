#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class OpenThanksE3 : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(OpenThanksE3, ksys::act::ai::Action)
public:
    explicit OpenThanksE3(const InitArg& arg);
    ~OpenThanksE3() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
