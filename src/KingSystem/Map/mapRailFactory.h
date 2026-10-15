#pragma once

#include <heap/seadDisposer.h>
#include "KingSystem/Map/mapRailFactoryInterfaces.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::map {

// The original factory stores only its heap disposer.
class RailFactory : public sead::IDisposer {
public:
    explicit RailFactory(sead::Heap* heap)
        : sead::IDisposer(heap, HeapNullOption::UseSpecifiedOrCurrentHeap) {}
    ~RailFactory() override;
};
KSYS_CHECK_SIZE_NX150(RailFactory, 0x20);

extern RailFactory* gRailFactoryDisposer;

}  // namespace ksys::map
