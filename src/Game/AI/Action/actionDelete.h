#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Delete : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(Delete, ksys::act::ai::Action)
public:
    explicit Delete(const InitArg& arg);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mDeleteType_s{};
};

}  // namespace uking::action
