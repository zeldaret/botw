#include "Game/AI/Action/actionNPCSaleAppReception.h"

namespace uking::action {

NPCSaleAppReception::NPCSaleAppReception(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCSaleAppReception::~NPCSaleAppReception() = default;

bool NPCSaleAppReception::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCSaleAppReception::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCSaleAppReception::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
