#include "KingSystem/Map/mapPlacementGlobal.h"

#include <mc/seadCoreInfo.h>
#include <nn/os.h>
#include "KingSystem/System/VFR.h"

namespace ksys::map {

SEAD_SINGLETON_DISPOSER_IMPL(PlacementGlobal);

PlacementGlobal::~PlacementGlobal() = default;

void PlacementGlobal::init() {
    vfrTimer = 0;
    frameCounterB = 0;
    vfrTimer2 = 0;
    frameCounterB2 = 0;
    frameCounter = 0;
    frameCounter2 = 0;
}

void PlacementGlobal::__auto() {
    vfrTimer = 0;
    frameCounterB = 0;
    vfrTimer2 = 0;
    frameCounterB2 = 0;
    frameCounter = 0;
    frameCounter2 = 0;
}

void PlacementGlobal::prepareStageUnload() {}

void PlacementGlobal::incrementCountersAndUpdate() {
    frameCounter++;
    frameCounter2++;
    f32 deltaTime = VFR::instance()->getDeltaTime();
    vfrTimer += deltaTime;

    while (vfrTimer >= 1) {
        frameCounterB++;
        vfrTimer--;
    }

    vfrTimer2 += deltaTime;
    while (vfrTimer2 >= 1) {
        frameCounterB2++;
        vfrTimer2--;
    }
}

void PlacementGlobal::incrementCounters() {
    frameCounter++;
    frameCounterB++;
}

}  // namespace ksys::map
