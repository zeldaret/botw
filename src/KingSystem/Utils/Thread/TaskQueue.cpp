#include "KingSystem/Utils/Thread/TaskQueue.h"

namespace ksys::util {

TaskQueue::TaskQueue(sead::Heap* heap) : TaskQueueBase(heap), mCS(heap) {}

}  // namespace ksys::util
