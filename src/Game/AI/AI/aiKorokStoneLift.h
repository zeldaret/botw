#pragma once

#include "Game/AI/AI/aiSimpleLiftable.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class KorokStoneLift : public SimpleLiftable {
    SEAD_RTTI_OVERRIDE(KorokStoneLift, SimpleLiftable)
public:
    explicit KorokStoneLift(const InitArg& arg);
    ~KorokStoneLift() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
