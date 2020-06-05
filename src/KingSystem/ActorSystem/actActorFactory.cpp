#include "KingSystem/ActorSystem/actActorFactory.h"
#include "KingSystem/ActorSystem/actActorCreator.h"

namespace ksys::act {

SEAD_SINGLETON_DISPOSER_IMPL(ActorFactoryHolder)

void ActorFactory::dummy() {}

void ActorFactory::dummy2() {}

ActorFactoryHolder::~ActorFactoryHolder() {
    ActorCreator::deleteInstance();
}

void ActorFactoryHolder::init(sead::Heap* heap) {
    ActorCreator::createInstance(heap);
    ActorCreator::instance()->setActorFactory(&mFactory);
}

}  // namespace ksys::act
