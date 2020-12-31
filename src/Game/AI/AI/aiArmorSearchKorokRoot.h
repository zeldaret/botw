#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ArmorSearchKorokRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ArmorSearchKorokRoot, ksys::act::ai::Ai)
public:
    explicit ArmorSearchKorokRoot(const InitArg& arg);
    ~ArmorSearchKorokRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mSearchKorokDis_s{};
    // static_param at offset 0x40
    const float* mSearchRefreshFrame_s{};
};

}  // namespace uking::ai
