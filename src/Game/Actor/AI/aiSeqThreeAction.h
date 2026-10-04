#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SeqThreeAction : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SeqThreeAction, ksys::act::ai::Ai)
public:
    explicit SeqThreeAction(const InitArg& arg);
    ~SeqThreeAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const bool* mIsFinishedByFailAction_s{};
    // static_param at offset 0x40
    const bool* mIsEndChangeable_s{};
    // static_param at offset 0x48
    const bool* mIsNoChangeable_s{};
};

}  // namespace uking::ai
