#pragma once

#include "Game/Actor/AI/aiTargetActorPos.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class TargetPartsPos : public TargetActorPos {
    SEAD_RTTI_OVERRIDE(TargetPartsPos, TargetActorPos)
public:
    explicit TargetPartsPos(const InitArg& arg);
    ~TargetPartsPos() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x40
    sead::SafeString mPartsName_s{};
};

}  // namespace uking::ai
