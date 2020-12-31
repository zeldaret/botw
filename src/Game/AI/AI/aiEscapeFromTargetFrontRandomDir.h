#pragma once

#include "Game/AI/AI/aiEscapeFromTargetFront.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EscapeFromTargetFrontRandomDir : public EscapeFromTargetFront {
    SEAD_RTTI_OVERRIDE(EscapeFromTargetFrontRandomDir, EscapeFromTargetFront)
public:
    explicit EscapeFromTargetFrontRandomDir(const InitArg& arg);
    ~EscapeFromTargetFrontRandomDir() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x60
    const int* mInverseDirRatio_s{};
};

}  // namespace uking::ai
