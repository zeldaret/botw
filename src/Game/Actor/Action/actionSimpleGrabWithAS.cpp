#include "Game/Actor/Action/actionSimpleGrabWithAS.h"

namespace uking::action {

SimpleGrabWithAS::SimpleGrabWithAS(const InitArg& arg) : SimpleGrabBase(arg) {}

SimpleGrabWithAS::~SimpleGrabWithAS() = default;

void SimpleGrabWithAS::loadParams_() {
    SimpleGrabBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

}  // namespace uking::action
