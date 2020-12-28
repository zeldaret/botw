#include "Game/AI/Action/actionNPCSale.h"

namespace uking::action {

NPCSale::NPCSale(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCSale::~NPCSale() = default;

bool NPCSale::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCSale::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCSale::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCSale::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
