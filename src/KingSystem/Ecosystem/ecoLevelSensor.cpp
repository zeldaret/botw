#include "KingSystem/Ecosystem/ecoLevelSensor.h"
#include "KingSystem/Utils/Byaml.h"

namespace ksys::eco {

LevelSensor::LevelSensor() = default;

LevelSensor::~LevelSensor() {
    mResHandle.requestUnload2();
    if (mBymlIter)
        delete mBymlIter;
}

}  // namespace ksys::eco
