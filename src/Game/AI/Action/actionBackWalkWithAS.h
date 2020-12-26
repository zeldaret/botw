#pragma once

#include "Game/AI/Action/actionBackWalkEx.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BackWalkWithAS : public BackWalkEx {
    SEAD_RTTI_OVERRIDE(BackWalkWithAS, BackWalkEx)
public:
    explicit BackWalkWithAS(const InitArg& arg);
    ~BackWalkWithAS() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xc0
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
