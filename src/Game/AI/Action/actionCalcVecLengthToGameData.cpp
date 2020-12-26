#include "Game/AI/Action/actionCalcVecLengthToGameData.h"

namespace uking::action {

CalcVecLengthToGameData::CalcVecLengthToGameData(const InitArg& arg) : ksys::act::ai::Action(arg) {}

CalcVecLengthToGameData::~CalcVecLengthToGameData() = default;

bool CalcVecLengthToGameData::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CalcVecLengthToGameData::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void CalcVecLengthToGameData::leave_() {
    ksys::act::ai::Action::leave_();
}

void CalcVecLengthToGameData::loadParams_() {
    getDynamicParam(&mCalcY_d, "CalcY");
    getDynamicParam(&mGameDataVec3fSrcName_d, "GameDataVec3fSrcName");
    getDynamicParam(&mGameDataFloatToName_d, "GameDataFloatToName");
}

void CalcVecLengthToGameData::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
