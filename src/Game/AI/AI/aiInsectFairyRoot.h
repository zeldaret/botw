#pragma once

#include "Game/AI/AI/aiInsectRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class InsectFairyRoot : public InsectRoot {
    SEAD_RTTI_OVERRIDE(InsectFairyRoot, InsectRoot)
public:
    explicit InsectFairyRoot(const InitArg& arg);
    ~InsectFairyRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
