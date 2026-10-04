#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ChildFavoriteSelectorBase : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ChildFavoriteSelectorBase, ksys::act::ai::Ai)
public:
    explicit ChildFavoriteSelectorBase(const InitArg& arg);
    ~ChildFavoriteSelectorBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const bool* mIsNoChildForceEnd_s{};
    // static_param at offset 0x40
    const bool* mIsCheckEveryFrame_s{};
};

}  // namespace uking::ai
