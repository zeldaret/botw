#include "Game/AI/Action/actionAppearNumKorokNuts.h"

namespace uking::action {

AppearNumKorokNuts::AppearNumKorokNuts(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AppearNumKorokNuts::~AppearNumKorokNuts() = default;

bool AppearNumKorokNuts::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AppearNumKorokNuts::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AppearNumKorokNuts::leave_() {
    ksys::act::ai::Action::leave_();
}

void AppearNumKorokNuts::loadParams_() {}

void AppearNumKorokNuts::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
