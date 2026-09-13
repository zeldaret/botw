#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SandfallWithSound : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SandfallWithSound, ksys::act::ai::Ai)
public:
    explicit SandfallWithSound(const InitArg& arg);
    ~SandfallWithSound() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
