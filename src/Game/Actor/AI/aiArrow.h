#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class Arrow : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(Arrow, ksys::act::ai::Ai)
public:
    explicit Arrow(const InitArg& arg);
    ~Arrow() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
