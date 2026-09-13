#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DeleteInGround : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DeleteInGround, ksys::act::ai::Action)
public:
    explicit DeleteInGround(const InitArg& arg);
    ~DeleteInGround() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
