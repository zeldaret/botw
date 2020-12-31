#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class ChmCheck : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(ChmCheck, ksys::act::ai::Ai)
public:
    explicit ChmCheck(const InitArg& arg);
    ~ChmCheck() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const int* mChmType_s{};
};

}  // namespace uking::ai
