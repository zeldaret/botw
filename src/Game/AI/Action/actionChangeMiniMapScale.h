#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ChangeMiniMapScale : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ChangeMiniMapScale, ksys::act::ai::Action)
public:
    explicit ChangeMiniMapScale(const InitArg& arg);
    ~ChangeMiniMapScale() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    int* mScaleLevel_d{};
};

}  // namespace uking::action
