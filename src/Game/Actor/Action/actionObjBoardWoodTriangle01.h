#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ObjBoardWoodTriangle01 : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ObjBoardWoodTriangle01, ksys::act::ai::Action)
public:
    explicit ObjBoardWoodTriangle01(const InitArg& arg);
    ~ObjBoardWoodTriangle01() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
};

}  // namespace uking::action
