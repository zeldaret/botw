#include "Game/AI/Action/actionDisappearNumKorokNuts.h"

namespace uking::action {

DisappearNumKorokNuts::DisappearNumKorokNuts(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DisappearNumKorokNuts::~DisappearNumKorokNuts() = default;

bool DisappearNumKorokNuts::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DisappearNumKorokNuts::loadParams_() {}

}  // namespace uking::action
