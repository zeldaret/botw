#include "Game/AI/AI/aiPauseMenuPlayerRoot.h"

namespace uking::ai {

PauseMenuPlayerRoot::PauseMenuPlayerRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PauseMenuPlayerRoot::~PauseMenuPlayerRoot() = default;

bool PauseMenuPlayerRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PauseMenuPlayerRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PauseMenuPlayerRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PauseMenuPlayerRoot::loadParams_() {}

}  // namespace uking::ai
