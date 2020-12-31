#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class StoneStickRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(StoneStickRoot, ksys::act::ai::Ai)
public:
    explicit StoneStickRoot(const InitArg& arg);
    ~StoneStickRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const sead::Vector3f* mFixPoint_s{};
};

}  // namespace uking::ai
