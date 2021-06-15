#include "KingSystem/World/worldJob.h"
#include "KingSystem/World/worldManager.h"

namespace ksys::world {

Job::Job() = default;

Job::~Job() = default;

void Job::init(sead::Heap* heap) {
    init_(heap);
}

void Job::invoke() {
    switch (Manager::instance()->getCalcType()) {
    case CalcType::_0:
        calc_();
        break;
    case CalcType::_1:
        calcType1_();
        break;
    case CalcType::_2:
        calcType2_();
        break;
    case CalcType::Invalid:
        break;
    }
}

}  // namespace ksys::world
