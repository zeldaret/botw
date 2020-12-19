#include "KingSystem/ActorSystem/aiDummyAi.h"

namespace ksys::act::ai {

DummyAi::DummyAi(const ActionBase::InitArg& arg) : Ai(arg) {}

void DummyAi::enter_(InlineParamPack* params) {}

void DummyAi::calc_() {}

}  // namespace ksys::act::ai
