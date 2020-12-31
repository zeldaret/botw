#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class WolfLinkReaction : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WolfLinkReaction, ksys::act::ai::Ai)
public:
    explicit WolfLinkReaction(const InitArg& arg);
    ~WolfLinkReaction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
