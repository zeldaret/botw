#include "KingSystem/GameData/gdtTriggerParam.h"

namespace ksys::gdt {

TriggerParam::TriggerParam() {
    mCriticalSections.constructDefault();
    mFlags.constructDefault();
    mCounts.fill(0);
}

}  // namespace ksys::gdt
