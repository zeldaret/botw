#include "Game/AI/Action/actionDeleteAllIceBlockForDemo.h"

namespace uking::action {

DeleteAllIceBlockForDemo::DeleteAllIceBlockForDemo(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

DeleteAllIceBlockForDemo::~DeleteAllIceBlockForDemo() = default;

bool DeleteAllIceBlockForDemo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DeleteAllIceBlockForDemo::loadParams_() {}

}  // namespace uking::action
