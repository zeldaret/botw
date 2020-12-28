#include "Game/AI/Action/actionSimpleGrabWithAS.h"

namespace uking::action {

SimpleGrabWithAS::SimpleGrabWithAS(const InitArg& arg) : SimpleGrabWithASBase(arg) {}

SimpleGrabWithAS::~SimpleGrabWithAS() = default;

void SimpleGrabWithAS::loadParams_() {
    SimpleGrabWithASBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

}  // namespace uking::action
