#include "Game/AI/AI/aiMergedDungeonPartsRoot.h"

namespace uking::ai {

MergedDungeonPartsRoot::MergedDungeonPartsRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

MergedDungeonPartsRoot::~MergedDungeonPartsRoot() = default;

bool MergedDungeonPartsRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void MergedDungeonPartsRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void MergedDungeonPartsRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void MergedDungeonPartsRoot::loadParams_() {
    getMapUnitParam(&mTransFieldBodyGroup00_m, "TransFieldBodyGroup00");
    getMapUnitParam(&mRotateFieldBodyGroup00_m, "RotateFieldBodyGroup00");
    getMapUnitParam(&mTransFieldBodyGroup01_m, "TransFieldBodyGroup01");
    getMapUnitParam(&mRotateFieldBodyGroup01_m, "RotateFieldBodyGroup01");
    getMapUnitParam(&mTransFieldBodyGroup02_m, "TransFieldBodyGroup02");
    getMapUnitParam(&mRotateFieldBodyGroup02_m, "RotateFieldBodyGroup02");
    getMapUnitParam(&mTransFieldBodyGroup03_m, "TransFieldBodyGroup03");
    getMapUnitParam(&mRotateFieldBodyGroup03_m, "RotateFieldBodyGroup03");
    getMapUnitParam(&mTransFieldBodyGroup04_m, "TransFieldBodyGroup04");
    getMapUnitParam(&mRotateFieldBodyGroup04_m, "RotateFieldBodyGroup04");
    getMapUnitParam(&mTransFieldBodyGroup05_m, "TransFieldBodyGroup05");
    getMapUnitParam(&mRotateFieldBodyGroup05_m, "RotateFieldBodyGroup05");
    getMapUnitParam(&mTransFieldBodyGroup06_m, "TransFieldBodyGroup06");
    getMapUnitParam(&mRotateFieldBodyGroup06_m, "RotateFieldBodyGroup06");
    getMapUnitParam(&mTransFieldBodyGroup07_m, "TransFieldBodyGroup07");
    getMapUnitParam(&mRotateFieldBodyGroup07_m, "RotateFieldBodyGroup07");
    getMapUnitParam(&mTransFieldBodyGroup08_m, "TransFieldBodyGroup08");
    getMapUnitParam(&mRotateFieldBodyGroup08_m, "RotateFieldBodyGroup08");
    getMapUnitParam(&mTransFieldBodyGroup09_m, "TransFieldBodyGroup09");
    getMapUnitParam(&mRotateFieldBodyGroup09_m, "RotateFieldBodyGroup09");
    getMapUnitParam(&mTransFieldBodyGroup10_m, "TransFieldBodyGroup10");
    getMapUnitParam(&mRotateFieldBodyGroup10_m, "RotateFieldBodyGroup10");
    getMapUnitParam(&mTransFieldBodyGroup11_m, "TransFieldBodyGroup11");
    getMapUnitParam(&mRotateFieldBodyGroup11_m, "RotateFieldBodyGroup11");
    getMapUnitParam(&mTransFieldBodyGroup12_m, "TransFieldBodyGroup12");
    getMapUnitParam(&mRotateFieldBodyGroup12_m, "RotateFieldBodyGroup12");
    getMapUnitParam(&mTransFieldBodyGroup13_m, "TransFieldBodyGroup13");
    getMapUnitParam(&mRotateFieldBodyGroup13_m, "RotateFieldBodyGroup13");
    getMapUnitParam(&mTransFieldBodyGroup14_m, "TransFieldBodyGroup14");
    getMapUnitParam(&mRotateFieldBodyGroup14_m, "RotateFieldBodyGroup14");
    getMapUnitParam(&mTransFieldBodyGroup15_m, "TransFieldBodyGroup15");
    getMapUnitParam(&mRotateFieldBodyGroup15_m, "RotateFieldBodyGroup15");
}

}  // namespace uking::ai
