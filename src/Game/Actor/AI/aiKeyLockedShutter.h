#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class KeyLockedShutter : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(KeyLockedShutter, ksys::act::ai::Ai)
public:
    explicit KeyLockedShutter(const InitArg& arg);
    ~KeyLockedShutter() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
