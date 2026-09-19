#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Tumble : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(Tumble, ksys::act::ai::Action)
public:
    bool isChangeable() const override { return false; }
    explicit Tumble(const InitArg& arg);
    ~Tumble() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    bool handleMessage_(const ksys::Message& message) override { return true; }
    void calc_() override;
};

}  // namespace uking::action
