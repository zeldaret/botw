#include "Game/AI/Action/actionAmbushThrown.h"

namespace uking::action {

AmbushThrown::AmbushThrown(const InitArg& arg) : ReflectThrown(arg) {}

AmbushThrown::~AmbushThrown() = default;

bool AmbushThrown::init_(sead::Heap* heap) {
    return ReflectThrown::init_(heap);
}

void AmbushThrown::enter_(ksys::act::ai::InlineParamPack* params) {
    ReflectThrown::enter_(params);
}

void AmbushThrown::leave_() {
    ReflectThrown::leave_();
}

void AmbushThrown::loadParams_() {
    ReflectThrown::loadParams_();
}

void AmbushThrown::calc_() {
    ReflectThrown::calc_();
}

}  // namespace uking::action
