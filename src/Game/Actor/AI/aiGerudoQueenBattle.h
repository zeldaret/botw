#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GerudoQueenBattle : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GerudoQueenBattle, ksys::act::ai::Ai)
public:
    explicit GerudoQueenBattle(const InitArg& arg);
    ~GerudoQueenBattle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mRetireFrame_s{};
};

}  // namespace uking::ai
