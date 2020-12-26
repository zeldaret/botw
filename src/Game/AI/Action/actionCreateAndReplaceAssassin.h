#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CreateAndReplaceAssassin : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(CreateAndReplaceAssassin, ksys::act::ai::Action)
public:
    explicit CreateAndReplaceAssassin(const InitArg& arg);
    ~CreateAndReplaceAssassin() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    sead::Vector3f* mOffset_d{};
};

}  // namespace uking::action
