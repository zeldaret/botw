#include "Game/AI/Action/actionNPCSaleReception.h"

namespace uking::action {

NPCSaleReception::NPCSaleReception(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCSaleReception::~NPCSaleReception() = default;

bool NPCSaleReception::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCSaleReception::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCSaleReception::loadParams_() {
    getDynamicParam(&mTableName_d, "TableName");
}

void NPCSaleReception::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
