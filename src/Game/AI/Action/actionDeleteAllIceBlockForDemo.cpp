#include "Game/AI/Action/actionDeleteAllIceBlockForDemo.h"

namespace uking::action {

DeleteAllIceBlockForDemo::DeleteAllIceBlockForDemo(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

DeleteAllIceBlockForDemo::~DeleteAllIceBlockForDemo() = default;

bool DeleteAllIceBlockForDemo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DeleteAllIceBlockForDemo::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DeleteAllIceBlockForDemo::leave_() {
    ksys::act::ai::Action::leave_();
}

void DeleteAllIceBlockForDemo::loadParams_() {}

void DeleteAllIceBlockForDemo::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
