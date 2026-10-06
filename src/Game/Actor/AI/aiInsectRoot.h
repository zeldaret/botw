#pragma once

#include "Game/Actor/AI/aiCapturedActorRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class InsectRoot : public CapturedActorRoot {
    SEAD_RTTI_OVERRIDE(InsectRoot, CapturedActorRoot)
public:
    explicit InsectRoot(const InitArg& arg);
    ~InsectRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0xf8
    const bool* mIsEscapeInWater_s{};
};

}  // namespace uking::ai
