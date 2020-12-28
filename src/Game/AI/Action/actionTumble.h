#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Tumble : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(Tumble, ksys::act::ai::Action)
public:
    explicit Tumble(const InitArg& arg);
    ~Tumble() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
