#include "Game/AI/AI/aiMoonNameTag.h"

namespace uking::ai {

MoonNameTag::MoonNameTag(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

MoonNameTag::~MoonNameTag() = default;

bool MoonNameTag::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void MoonNameTag::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void MoonNameTag::leave_() {
    ksys::act::ai::Ai::leave_();
}

void MoonNameTag::loadParams_() {
    getMapUnitParam(&mMoonNameType_m, "MoonNameType");
}

}  // namespace uking::ai
