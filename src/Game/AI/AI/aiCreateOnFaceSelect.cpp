#include "Game/AI/AI/aiCreateOnFaceSelect.h"

namespace uking::ai {

CreateOnFaceSelect::CreateOnFaceSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

CreateOnFaceSelect::~CreateOnFaceSelect() = default;

bool CreateOnFaceSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void CreateOnFaceSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void CreateOnFaceSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void CreateOnFaceSelect::loadParams_() {
    getMapUnitParam(&mIsCreateOnFace_m, "IsCreateOnFace");
}

}  // namespace uking::ai
