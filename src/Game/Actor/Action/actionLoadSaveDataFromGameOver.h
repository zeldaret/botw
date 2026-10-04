#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LoadSaveDataFromGameOver : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(LoadSaveDataFromGameOver, ksys::act::ai::Action)
public:
    explicit LoadSaveDataFromGameOver(const InitArg& arg);
    ~LoadSaveDataFromGameOver() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
