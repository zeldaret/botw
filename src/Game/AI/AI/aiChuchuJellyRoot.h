#pragma once

#include "Game/AI/AI/aiItemRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ChuchuJellyRoot : public ItemRoot {
    SEAD_RTTI_OVERRIDE(ChuchuJellyRoot, ItemRoot)
public:
    explicit ChuchuJellyRoot(const InitArg& arg);
    ~ChuchuJellyRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
