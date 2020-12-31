#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class FldObjIvyBurnRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(FldObjIvyBurnRoot, ksys::act::ai::Ai)
public:
    explicit FldObjIvyBurnRoot(const InitArg& arg);
    ~FldObjIvyBurnRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
