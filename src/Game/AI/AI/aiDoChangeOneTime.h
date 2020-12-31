#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class DoChangeOneTime : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(DoChangeOneTime, ksys::act::ai::Ai)
public:
    explicit DoChangeOneTime(const InitArg& arg);
    ~DoChangeOneTime() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
