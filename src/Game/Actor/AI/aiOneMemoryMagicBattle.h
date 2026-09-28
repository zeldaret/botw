#pragma once

#include "Game/Actor/AI/aiMagicBattle.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class OneMemoryMagicBattle : public MagicBattle {
    SEAD_RTTI_OVERRIDE(OneMemoryMagicBattle, MagicBattle)
public:
    explicit OneMemoryMagicBattle(const InitArg& arg);
    ~OneMemoryMagicBattle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0xe0
    sead::SafeString mMemoryPartsName_s{};
};

}  // namespace uking::ai
