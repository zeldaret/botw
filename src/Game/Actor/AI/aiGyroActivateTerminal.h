#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GyroActivateTerminal : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GyroActivateTerminal, ksys::act::ai::Ai)
public:
    explicit GyroActivateTerminal(const InitArg& arg);
    ~GyroActivateTerminal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
