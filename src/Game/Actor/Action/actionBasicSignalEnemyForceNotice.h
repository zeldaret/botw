#pragma once

#include "Game/Actor/Action/actionBasicSignalEnemyNotice.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BasicSignalEnemyForceNotice : public BasicSignalEnemyNotice {
    SEAD_RTTI_OVERRIDE(BasicSignalEnemyForceNotice, BasicSignalEnemyNotice)
public:
    explicit BasicSignalEnemyForceNotice(const InitArg& arg);
    ~BasicSignalEnemyForceNotice() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mInterval_s{};
};

}  // namespace uking::action
