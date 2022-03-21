#include <basis/seadRawPrint.h>
#include <container/seadListImpl.h>

namespace sead
{
void ListNode::insertBack_(ListNode* node)
{
    SEAD_ASSERT_MSG(!node->isLinked(), "node is already linked.");
    ListNode* next = mNext;
    mNext = node;
    node->mPrev = this;
    node->mNext = next;

    if (next)
        next->mPrev = node;
}

void ListNode::insertFront_(ListNode* node)
{
    SEAD_ASSERT_MSG(!node->isLinked(), "node is already linked.");
    ListNode* prev = mPrev;
    this->mPrev = node;
    node->mPrev = prev;
    node->mNext = this;
    if (prev == NULL)
        return;

    prev->mNext = node;
}

void ListNode::erase_()
{
    SEAD_ASSERT_MSG(isLinked(), "node is not linked.");
    if (mPrev != nullptr)
        mPrev->mNext = mNext;

    if (mNext != nullptr)
        mNext->mPrev = mPrev;

    mPrev = mNext = NULL;
}

ListNode* ListImpl::popBack()
{
    if (mCount < 1)
        return nullptr;

    ListNode* back = mStartEnd.mPrev;
    back->erase_();
    --mCount;
    return back;
}

ListNode* ListImpl::popFront()
{
    if (mCount < 1)
        return nullptr;

    ListNode* front = mStartEnd.mNext;
    front->erase_();
    --mCount;
    return front;
}

ListNode* ListImpl::nth(s32 index) const
{
    if (u32(mCount) <= u32(index))
    {
        SEAD_ASSERT_MSG(false, "index exceeded[%d/%d]", index, mCount);
        return nullptr;
    }

    ListNode* node = mStartEnd.mNext;
    for (s32 i = 0; i < index; ++i)
        node = node->mNext;
    return node;
}

s32 ListImpl::indexOf(const ListNode* n) const
{
    ListNode* node = mStartEnd.mNext;
    s32 index = 0;
    while (node != &mStartEnd)
    {
        if (node == n)
            return index;
        ++index;
        node = node->mNext;
    }
    return -1;
}

void ListImpl::clear()
{
    ListNode* node = mStartEnd.mNext;
    while (node != &mStartEnd)
    {
        ListNode* next = node->mNext;
        node->init_();
        node = next;
    }

    mCount = 0;
    mStartEnd.mPrev = &mStartEnd;
    mStartEnd.mNext = &mStartEnd;
}

void ListImpl::swap(ListNode* n1, ListNode* n2)
{
    SEAD_ASSERT(n1->mPrev && n1->mNext && n2->mPrev && n2->mNext);
    if (n1 == n2)
        return;

    ListNode* n1_prev = n1->mPrev;
    ListNode* n2_prev = n2->mPrev;

    if (n2_prev != n1)
    {
        n1->erase_();
        n2_prev->insertBack_(n1);
    }

    if (n1_prev != n2)
    {
        n2->erase_();
        n1_prev->insertBack_(n2);
    }
}

}  // namespace sead
