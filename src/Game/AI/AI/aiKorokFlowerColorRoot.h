#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class KorokFlowerColorRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(KorokFlowerColorRoot, ksys::act::ai::Ai)
public:
    explicit KorokFlowerColorRoot(const InitArg& arg);
    ~KorokFlowerColorRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x38
    const int* mKorokFlowerColorNum_m{};
};

}  // namespace uking::ai
