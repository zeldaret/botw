#include "Game/AI/Action/actionForkAlwaysTurnUDLimit.h"

namespace uking::action {

ForkAlwaysTurnUDLimit::ForkAlwaysTurnUDLimit(const InitArg& arg) : ForkAlwaysTurn(arg) {}

ForkAlwaysTurnUDLimit::~ForkAlwaysTurnUDLimit() = default;

bool ForkAlwaysTurnUDLimit::init_(sead::Heap* heap) {
    return ForkAlwaysTurn::init_(heap);
}

void ForkAlwaysTurnUDLimit::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkAlwaysTurn::enter_(params);
}

void ForkAlwaysTurnUDLimit::leave_() {
    ForkAlwaysTurn::leave_();
}

void ForkAlwaysTurnUDLimit::loadParams_() {
    ForkAlwaysTurn::loadParams_();
    getStaticParam(&mLimitUD_s, "LimitUD");
}

void ForkAlwaysTurnUDLimit::calc_() {
    ForkAlwaysTurn::calc_();
}

}  // namespace uking::action
