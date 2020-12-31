#include "Game/AI/AI/aiEscapeFromTargetFrontRandomDir.h"

namespace uking::ai {

EscapeFromTargetFrontRandomDir::EscapeFromTargetFrontRandomDir(const InitArg& arg)
    : EscapeFromTargetFront(arg) {}

EscapeFromTargetFrontRandomDir::~EscapeFromTargetFrontRandomDir() = default;

bool EscapeFromTargetFrontRandomDir::init_(sead::Heap* heap) {
    return EscapeFromTargetFront::init_(heap);
}

void EscapeFromTargetFrontRandomDir::enter_(ksys::act::ai::InlineParamPack* params) {
    EscapeFromTargetFront::enter_(params);
}

void EscapeFromTargetFrontRandomDir::leave_() {
    EscapeFromTargetFront::leave_();
}

void EscapeFromTargetFrontRandomDir::loadParams_() {
    EscapeFromTargetFront::loadParams_();
    getStaticParam(&mInverseDirRatio_s, "InverseDirRatio");
}

}  // namespace uking::ai
