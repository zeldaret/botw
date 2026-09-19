#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class KeeseHangOnCeil : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(KeeseHangOnCeil, ksys::act::ai::Ai)
public:
    bool isChangeable() const override { return false; }
    explicit KeeseHangOnCeil(const InitArg& arg);
    ~KeeseHangOnCeil() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
};

}  // namespace uking::ai
