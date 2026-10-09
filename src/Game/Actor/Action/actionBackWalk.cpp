#include "Game/Actor/Action/actionBackWalk.h"

namespace uking::action {

BackWalk::BackWalk(const InitArg& arg) : NormalBackWalk(arg) {}

void BackWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    NormalBackWalk::enter_(params);
}

}  // namespace uking::action
