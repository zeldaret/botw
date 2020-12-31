#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DungeonEntranceRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(DungeonEntranceRoot, ksys::act::ai::Ai)
public:
    explicit DungeonEntranceRoot(const InitArg& arg);
    ~DungeonEntranceRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const bool* mIsCheckClear_s{};
};

}  // namespace uking::ai
