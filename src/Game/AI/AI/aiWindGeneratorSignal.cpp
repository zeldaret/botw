#include "Game/AI/AI/aiWindGeneratorSignal.h"

namespace uking::ai {

WindGeneratorSignal::WindGeneratorSignal(const InitArg& arg) : WindGenerator(arg) {}

WindGeneratorSignal::~WindGeneratorSignal() = default;

bool WindGeneratorSignal::init_(sead::Heap* heap) {
    return WindGenerator::init_(heap);
}

void WindGeneratorSignal::enter_(ksys::act::ai::InlineParamPack* params) {
    WindGenerator::enter_(params);
}

void WindGeneratorSignal::leave_() {
    WindGenerator::leave_();
}

void WindGeneratorSignal::loadParams_() {
    WindGenerator::loadParams_();
}

}  // namespace uking::ai
