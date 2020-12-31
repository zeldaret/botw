#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RemainsLithograph : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(RemainsLithograph, ksys::act::ai::Ai)
public:
    explicit RemainsLithograph(const InitArg& arg);
    ~RemainsLithograph() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
