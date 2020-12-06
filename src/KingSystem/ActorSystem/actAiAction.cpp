#include "KingSystem/ActorSystem/actAiAction.h"

namespace ksys::act::ai {

Action::Action(const InitArg& arg) : ActionBase(arg) {}

bool Action::isAction() {
    return true;
}

}  // namespace ksys::act::ai
