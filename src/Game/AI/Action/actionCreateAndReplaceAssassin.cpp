#include "Game/AI/Action/actionCreateAndReplaceAssassin.h"

namespace uking::action {

CreateAndReplaceAssassin::CreateAndReplaceAssassin(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

CreateAndReplaceAssassin::~CreateAndReplaceAssassin() = default;

bool CreateAndReplaceAssassin::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CreateAndReplaceAssassin::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void CreateAndReplaceAssassin::leave_() {
    ksys::act::ai::Action::leave_();
}

void CreateAndReplaceAssassin::loadParams_() {
    getDynamicParam(&mOffset_d, "Offset");
}

void CreateAndReplaceAssassin::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
