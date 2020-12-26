#include "Game/AI/Action/actionSimpleUniqueTalk.h"

namespace uking::action {

SimpleUniqueTalk::SimpleUniqueTalk(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SimpleUniqueTalk::~SimpleUniqueTalk() = default;

bool SimpleUniqueTalk::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SimpleUniqueTalk::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SimpleUniqueTalk::leave_() {
    ksys::act::ai::Action::leave_();
}

void SimpleUniqueTalk::loadParams_() {
    getDynamicParam(&mMstxtName_d, "MstxtName");
}

void SimpleUniqueTalk::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
