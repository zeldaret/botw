#include "Game/AI/Action/actionNPCSellHorse.h"

namespace uking::action {

NPCSellHorse::NPCSellHorse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCSellHorse::~NPCSellHorse() = default;

bool NPCSellHorse::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCSellHorse::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCSellHorse::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCSellHorse::loadParams_() {}

void NPCSellHorse::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
