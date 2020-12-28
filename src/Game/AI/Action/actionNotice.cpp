#include "Game/AI/Action/actionNotice.h"

namespace uking::action {

Notice::Notice(const InitArg& arg) : ActionWithAS(arg) {}

void Notice::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithAS::enter_(params);
}

}  // namespace uking::action
