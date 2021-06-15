#include "KingSystem/Resource/Actor/resResourceAISchedule.h"

namespace ksys::res {

void AISchedule::doCreate_(u8* buffer, u32 buffer_size, sead::Heap* heap) {
    mData = buffer;
}

}  // namespace ksys::res
