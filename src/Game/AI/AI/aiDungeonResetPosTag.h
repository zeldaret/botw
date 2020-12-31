#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DungeonResetPosTag : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(DungeonResetPosTag, ksys::act::ai::Ai)
public:
    explicit DungeonResetPosTag(const InitArg& arg);
    ~DungeonResetPosTag() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
