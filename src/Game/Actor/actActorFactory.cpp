#include "Game/Actor/actActorFactory.h"
#include "KingSystem/ActorSystem/actActorCreator.h"

namespace uking::act {

SEAD_SINGLETON_DISPOSER_IMPL(ActorFactoryHolder)

void ActorFactory::dummy() {}

void ActorFactory::dummy2() {}

ActorFactoryHolder::~ActorFactoryHolder() {
    ksys::act::ActorCreator::deleteInstance();
}

void ActorFactoryHolder::init(sead::Heap* heap) {
    ksys::act::ActorCreator::createInstance(heap);
    ksys::act::ActorCreator::instance()->setActorFactory(&mFactory);
}

}  // namespace uking::act
