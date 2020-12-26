#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ReceiveTerror : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ReceiveTerror, ksys::act::ai::Action)
public:
    explicit ReceiveTerror(const InitArg& arg);
    ~ReceiveTerror() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
