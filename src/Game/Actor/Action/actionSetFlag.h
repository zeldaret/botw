#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SetFlag : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(SetFlag, ksys::act::ai::Action)
public:
    explicit SetFlag(const InitArg& arg);
    ~SetFlag() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::action
