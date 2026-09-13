#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SetPartBind : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(SetPartBind, ksys::act::ai::Ai)
public:
    explicit SetPartBind(const InitArg& arg);
    ~SetPartBind() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    sead::SafeString mBaseNodeName_s{};
    // static_param at offset 0x48
    sead::SafeString mPartialNodeName_s{};
};

}  // namespace uking::ai
