#include "KingSystem/ActorSystem/actActorParam.h"

namespace ksys::act {

ActorParam::Resources ActorParam::sDummyResources;

void ActorParam::resetDummyResources() {
    sDummyResources = {};
}

ActorParam::ActorParam() {
    mRes = {};
    mNumHandles1 = mNumHandles2 = 0;
    mEvent.resetSignal();
}

ActorParam::~ActorParam() {
    finalize();
}

}  // namespace ksys::act
