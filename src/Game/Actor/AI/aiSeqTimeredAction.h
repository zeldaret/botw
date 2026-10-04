#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SeqTimeredAction : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SeqTimeredAction, ksys::act::ai::Ai)
public:
    explicit SeqTimeredAction(const InitArg& arg);
    ~SeqTimeredAction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mActionTime_s{};
};

}  // namespace uking::ai
