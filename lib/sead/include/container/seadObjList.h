#pragma once

#include <algorithm>
#include "basis/seadNew.h"
#include "basis/seadRawPrint.h"
#include "basis/seadTypes.h"
#include "container/seadFreeList.h"
#include "container/seadListImpl.h"
#include "prim/seadPtrUtil.h"

namespace sead
{
template <typename T>
class ObjList : public ListImpl
{
public:
    ObjList() = default;
    ObjList(s32 max_num, void* buf) { setBuffer(max_num, buf); }

    void allocBuffer(s32 capacity, Heap* heap, s32 alignment = sizeof(void*))
    {
        if (capacity < 1)
            return;

        setBuffer(capacity,
                  new (heap, alignment, std::nothrow) u8[calculateWorkBufferSize(capacity)]);
    }

    bool tryAllocBuffer(s32 capacity, Heap* heap, s32 alignment = sizeof(void*))
    {
        if (capacity < 1)
            return false;

        auto* buf = new (heap, alignment, std::nothrow) u8[calculateWorkBufferSize(capacity)];
        if (!buf)
            return false;

        setBuffer(capacity, buf);
        return true;
    }

    void setBuffer(s32 max_num, void* buf)
    {
        if (!buf)
        {
            SEAD_ASSERT_MSG(false, "buf is null");
            return;
        }

        mFreeList.setWork(buf, ElementSize, max_num);
        mMaxNum = max_num;
    }

    void freeBuffer()
    {
        if (!isBufferReady())
            return;

        clear();

        if (mFreeList.work())
            delete[] static_cast<u8*>(mFreeList.work());

        mMaxNum = 0;
        mFreeList.reset();
    }

    bool isBufferReady() const { return mFreeList.work() != nullptr; }

    bool isFull() const { return size() >= mMaxNum; }

    T* front() const { return listNodeToObjWithNullCheck(ListImpl::front()); }
    T* back() const { return listNodeToObjWithNullCheck(ListImpl::back()); }

    T popBack()
    {
        auto* item = back();
        if (!item)
            return {};

        T copy = *item;
        erase(item);
        return copy;
    }

    T popFront()
    {
        auto* item = front();
        if (!item)
            return {};

        T copy = *item;
        erase(item);
        return copy;
    }

    template <class... Args>
    T* emplaceBack(Args&&... args)
    {
        if (isFull())
        {
            SEAD_ASSERT_MSG(false, "buffer full.");
            return nullptr;
        }
        Node* item = new (mFreeList.alloc()) Node{T{std::forward<Args>(args)...}, {}};
        ListImpl::pushBack(&item->node);
        return &item->item;
    }

    void erase(T* item)
    {
        ListImpl::erase(objToListNode(item));
        item->~T();
        mFreeList.free(item);
    }

    void clear()
    {
        ListNode* node = mStartEnd.next();
        while (node != &mStartEnd)
        {
            // Fetch the next pointer before erasing the item from the linked list.
            ListNode* next = node->next();
            ListImpl::erase(node);

            auto* item = listNodeToObj(node);
            item->~T();
            mFreeList.free(item);

            node = next;
        }
    }

    T* prev(const T* obj) const
    {
        ListNode* prev_node = objToListNode(obj)->prev();
        if (prev_node == &mStartEnd)
            return nullptr;
        return listNodeToObj(prev_node);
    }

    T* next(const T* obj) const
    {
        ListNode* next_node = objToListNode(obj)->next();
        if (next_node == &mStartEnd)
            return nullptr;
        return listNodeToObj(next_node);
    }

    T* nth(s32 n) const { return listNodeToObjWithNullCheck(ListImpl::nth(n)); }

    s32 indexOf(const T* obj) const { return ListImpl::indexOf(objToListNode(obj)); }

    bool isNodeLinked(const T* obj) const { return objToListNode(obj)->isLinked(); }

    class iterator
    {
    public:
        explicit iterator(T* ptr) : mPtr{ptr} {}
        bool operator==(const iterator& other) const { return mPtr == other.mPtr; }
        bool operator!=(const iterator& other) const { return !operator==(other); }
        iterator& operator++()
        {
            constexpr auto offset = Node::getListNodeOffset();
            auto* node = static_cast<ListNode*>(PtrUtil::addOffset(mPtr, offset))->next();
            mPtr = static_cast<T*>(PtrUtil::addOffset(node, -offset));
            return *this;
        }
        T& operator*() const { return *mPtr; }
        T* operator->() const { return mPtr; }

    private:
        T* mPtr;
    };

    iterator begin() const { return iterator(listNodeToObj(mStartEnd.next())); }
    iterator end() const { return iterator(listNodeToObj(const_cast<ListNode*>(&mStartEnd))); }
    iterator begin(T* ptr) const { return iterator(ptr); }

    static constexpr size_t calculateWorkBufferSize(size_t n) { return n * ElementSize; }

private:
    struct Node
    {
        static constexpr auto getListNodeOffset() { return offsetof(Node, node); }
        T item;
        ListNode node;
    };
    static_assert(offsetof(Node, item) == 0, "item must be at offset 0 in Node");

    ListNode* objToListNode(T* obj) const
    {
        return static_cast<ListNode*>(PtrUtil::addOffset(obj, Node::getListNodeOffset()));
    }

    const ListNode* objToListNode(const T* obj) const
    {
        return static_cast<const ListNode*>(PtrUtil::addOffset(obj, Node::getListNodeOffset()));
    }

    T* listNodeToObj(ListNode* node) const
    {
        return static_cast<T*>(PtrUtil::addOffset(node, -Node::getListNodeOffset()));
    }

    const T* listNodeToObj(const ListNode* node) const
    {
        return static_cast<const T*>(PtrUtil::addOffset(node, -Node::getListNodeOffset()));
    }

    T* listNodeToObjWithNullCheck(ListNode* node) const
    {
        return node ? listNodeToObj(node) : nullptr;
    }

    const T* listNodeToObjWithNullCheck(const ListNode* node) const
    {
        return node ? listNodeToObj(node) : nullptr;
    }

    static constexpr size_t ElementSize = std::max(sizeof(Node), FreeList::cPtrSize);

    sead::FreeList mFreeList;
    s32 mMaxNum = 0;
};

template <typename T, s32 N>
class FixedObjList : public ObjList<T>
{
public:
    FixedObjList() : ObjList<T>(N, &mWork) {}

    // These do not make sense for a *fixed* array.
    void setBuffer(s32 ptrNumMax, void* buf) = delete;
    void allocBuffer(s32 ptrNumMax, Heap* heap, s32 alignment = sizeof(void*)) = delete;
    bool tryAllocBuffer(s32 ptrNumMax, Heap* heap, s32 alignment = sizeof(void*)) = delete;
    void freeBuffer() = delete;

private:
    std::aligned_storage_t<ObjList<T>::calculateWorkBufferSize(N),
                           std::max(alignof(T), alignof(T*))>
        mWork;
};

}  // namespace sead
