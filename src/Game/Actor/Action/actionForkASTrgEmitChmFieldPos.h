#pragma once

#include "Game/Actor/Action/actionForkTrgEmitChmFieldBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkASTrgEmitChmFieldPos : public ForkTrgEmitChmFieldBase {
    SEAD_RTTI_OVERRIDE(ForkASTrgEmitChmFieldPos, ForkTrgEmitChmFieldBase)
public:
    explicit ForkASTrgEmitChmFieldPos(const InitArg& arg);
    ~ForkASTrgEmitChmFieldPos() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xa8
    const sead::Vector3f* mOffsetPos_s{};
};

}  // namespace uking::action
