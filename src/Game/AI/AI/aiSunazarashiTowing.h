#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SunazarashiTowing : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SunazarashiTowing, ksys::act::ai::Ai)
public:
    explicit SunazarashiTowing(const InitArg& arg);
    ~SunazarashiTowing() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
