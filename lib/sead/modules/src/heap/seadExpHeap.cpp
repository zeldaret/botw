#include <heap/seadExpHeap.h>

namespace sead
{
bool ExpHeap::isEmpty() const
{
    return this->mUseList.size() == 0;
}

bool ExpHeap::isFreeable() const
{
    return true;
}

bool ExpHeap::isResizable() const
{
    return true;
}

bool ExpHeap::isAdjustable() const
{
    return true;
}
}  // namespace sead