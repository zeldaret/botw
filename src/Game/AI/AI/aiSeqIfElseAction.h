#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SeqIfElseAction : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SeqIfElseAction, ksys::act::ai::Ai)
public:
    explicit SeqIfElseAction(const InitArg& arg);
    ~SeqIfElseAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mFailType_s{};
};

}  // namespace uking::ai
