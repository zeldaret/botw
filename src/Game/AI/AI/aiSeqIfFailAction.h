#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SeqIfFailAction : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SeqIfFailAction, ksys::act::ai::Ai)
public:
    explicit SeqIfFailAction(const InitArg& arg);
    ~SeqIfFailAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const bool* mIsEndChangeable_s{};
};

}  // namespace uking::ai
