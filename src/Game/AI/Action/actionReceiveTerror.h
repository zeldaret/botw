#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ReceiveTerror : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ReceiveTerror, ksys::act::ai::Action)
public:
    explicit ReceiveTerror(const InitArg& arg);
    ~ReceiveTerror() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
