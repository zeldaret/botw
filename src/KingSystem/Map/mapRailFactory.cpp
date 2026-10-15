#include "KingSystem/Map/mapRailFactory.h"

namespace ksys::map {

RailFactory::~RailFactory() {
    if (this == gRailFactoryDisposer) {
        gRailFactoryDisposer = nullptr;
        gRailFactory = nullptr;
    }
}

RailFactory* createRailFactory(sead::Heap* heap) {
    if (!gRailFactory) {
        auto* storage = new (heap, 4) u8[sizeof(RailFactory)];
        auto* factory = new (storage) RailFactory(heap);
        gRailFactoryDisposer = factory;
        gRailFactory = factory;
    }
    return gRailFactory;
}

void destroyRailFactory() {
    if (gRailFactoryDisposer) {
        auto* disposer = gRailFactoryDisposer;
        gRailFactoryDisposer = nullptr;
        disposer->~RailFactory();
        if (gRailFactory)
            operator delete(gRailFactory);
        gRailFactory = nullptr;
    }
}

}  // namespace ksys::map
