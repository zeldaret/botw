#pragma once

#include "Game/AI/AI/aiRailMoveRemains.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RailMoveRemainsBGCamera : public RailMoveRemains {
    SEAD_RTTI_OVERRIDE(RailMoveRemainsBGCamera, RailMoveRemains)
public:
    explicit RailMoveRemainsBGCamera(const InitArg& arg);
    ~RailMoveRemainsBGCamera() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x80
    const bool* mIsAllowRotAxisX_s{};
    // static_param at offset 0x88
    sead::SafeString mDungeonName_s{};
    // static_param at offset 0x98
    sead::SafeString mRailName_s{};
};

}  // namespace uking::ai
