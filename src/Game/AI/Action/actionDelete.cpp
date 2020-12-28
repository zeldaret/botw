#include "Game/AI/Action/actionDelete.h"

namespace uking::action {

Delete::Delete(const InitArg& arg) : ksys::act::ai::Action(arg) {}

void Delete::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void Delete::leave_() {
    ksys::act::ai::Action::leave_();
}

void Delete::loadParams_() {
    getStaticParam(&mDeleteType_s, "DeleteType");
}

void Delete::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
