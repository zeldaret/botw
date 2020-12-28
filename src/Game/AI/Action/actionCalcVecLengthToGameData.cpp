#include "Game/AI/Action/actionCalcVecLengthToGameData.h"

namespace uking::action {

CalcVecLengthToGameData::CalcVecLengthToGameData(const InitArg& arg) : ksys::act::ai::Action(arg) {}

CalcVecLengthToGameData::~CalcVecLengthToGameData() = default;

bool CalcVecLengthToGameData::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CalcVecLengthToGameData::loadParams_() {
    getDynamicParam(&mCalcY_d, "CalcY");
    getDynamicParam(&mGameDataVec3fSrcName_d, "GameDataVec3fSrcName");
    getDynamicParam(&mGameDataFloatToName_d, "GameDataFloatToName");
}

}  // namespace uking::action
