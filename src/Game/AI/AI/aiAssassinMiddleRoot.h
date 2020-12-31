#pragma once

#include "Game/AI/AI/aiEnemyRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AssassinMiddleRoot : public EnemyRoot {
    SEAD_RTTI_OVERRIDE(AssassinMiddleRoot, EnemyRoot)
public:
    explicit AssassinMiddleRoot(const InitArg& arg);
    ~AssassinMiddleRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x1d8
    const int* mPodModelUnitIdx_s{};
    // static_param at offset 0x1e0
    sead::SafeString mPodNodeName_s{};
    // static_param at offset 0x1f0
    sead::SafeString mMagicUsePartsName_s{};
    // static_param at offset 0x200
    const sead::Vector3f* mSheathOffset_s{};
};

}  // namespace uking::ai
