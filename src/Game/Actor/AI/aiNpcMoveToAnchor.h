#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class NpcMoveToAnchor : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(NpcMoveToAnchor, ksys::act::ai::Ai)
public:
    explicit NpcMoveToAnchor(const InitArg& arg);
    ~NpcMoveToAnchor() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // dynamic_param at offset 0x38
    bool* mIsTurnToAnchorDir_d{};
    // dynamic_param at offset 0x40
    bool* mIsAlignmentAnchor_d{};
    // dynamic_param at offset 0x48
    sead::SafeString* mAnchorName_d{};
    // dynamic_param at offset 0x58
    sead::SafeString* mAnchorUniqueName_d{};
    // dynamic_param at offset 0x68
    sead::SafeString* mASKeyName_d{};
};

}  // namespace uking::ai
