#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ClusterRenderCheckTag : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ClusterRenderCheckTag, ksys::act::ai::Ai)
public:
    explicit ClusterRenderCheckTag(const InitArg& arg);
    ~ClusterRenderCheckTag() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
