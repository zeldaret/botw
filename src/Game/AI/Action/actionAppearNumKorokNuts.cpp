#include "Game/AI/Action/actionAppearNumKorokNuts.h"

namespace uking::action {

AppearNumKorokNuts::AppearNumKorokNuts(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AppearNumKorokNuts::~AppearNumKorokNuts() = default;

bool AppearNumKorokNuts::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AppearNumKorokNuts::loadParams_() {}

}  // namespace uking::action
