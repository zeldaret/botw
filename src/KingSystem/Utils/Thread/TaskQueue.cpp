#include "KingSystem/Utils/Thread/TaskQueue.h"

namespace ksys {

TaskQueue::TaskQueue(sead::Heap* heap) : TaskQueueBase(heap), mCS(heap) {}

}  // namespace ksys
