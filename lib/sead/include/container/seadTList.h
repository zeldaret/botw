#ifndef SEAD_TLIST_H_
#define SEAD_TLIST_H_

#include <container/seadListImpl.h>

namespace sead
{
template <typename T>
class TListNode;

template <typename T>
class TList : public ListImpl
{
public:
    using CompareCallback = int (*)(const T*, const T*);

    TList() : ListImpl() {}

    void pushBack(TListNode<T>* item)
    {
        item->erase();
        item->mList = this;
        ListImpl::pushBack(item);
    }

    void pushFront(TListNode<T>* item)
    {
        item->erase();
        item->mList = this;
        ListImpl::pushFront(item);
    }

    TListNode<T>* popBack() { return static_cast<TListNode<T>*>(ListImpl::popBack()); }
    TListNode<T>* popFront() { return static_cast<TListNode<T>*>(ListImpl::popFront()); }

    void insertBefore(TListNode<T>* node, TListNode<T>* node_to_insert)
    {
        ListImpl::insertBefore(node, node_to_insert);
    }

    void insertAfter(TListNode<T>* node, TListNode<T>* node_to_insert)
    {
        ListImpl::insertAfter(node, node_to_insert);
    }

    void erase(TListNode<T>* item)
    {
        if (!item->mList)
            return;
        item->mList = nullptr;
        ListImpl::erase(item);
    }

    TListNode<T>* front() const { return static_cast<TListNode<T>*>(ListImpl::front()); }
    TListNode<T>* back() const { return static_cast<TListNode<T>*>(ListImpl::back()); }
    TListNode<T>* nth(int n) const { return static_cast<TListNode<T>*>(ListImpl::nth(n)); }
    s32 indexOf(const TListNode<T>* node) const { return ListImpl::indexOf(node); }

    void swap(TListNode<T>* n1, TListNode<T>* n2) { ListImpl::swap(n1, n2); }
    void moveAfter(TListNode<T>* basis, TListNode<T>* n) { ListImpl::moveAfter(basis, n); }
    void moveBefore(TListNode<T>* basis, TListNode<T>* n) { ListImpl::moveBefore(basis, n); }

    void sort(s32 offset, CompareCallback cmp) { ListImpl::sort<T>(offset, cmp); }
    void mergeSort(s32 offset, CompareCallback cmp) { ListImpl::mergeSort<T>(offset, cmp); }

    TListNode<T>* find(const void* ptr, s32 offset, CompareCallback cmp) const
    {
        return static_cast<TListNode<T>*>(ListImpl::find(ptr, offset, cmp));
    }
    void uniq(s32 offset, CompareCallback cmp) { ListImpl::uniq(offset, cmp); }
    void clear() { ListImpl::clear(); }

    TListNode<T>* prev(const TListNode<T>* node) const
    {
        auto prev_node = static_cast<TListNode<T>*>(node->prev());
        if (prev_node == &mStartEnd)
            return nullptr;
        return prev_node;
    }

    TListNode<T>* next(const TListNode<T>* node) const
    {
        auto next_node = static_cast<TListNode<T>*>(node->next());
        if (next_node == &mStartEnd)
            return nullptr;
        return next_node;
    }

    class iterator
    {
    public:
        iterator(TListNode<T>* ptr) : mPtr(ptr) {}

        iterator& operator++()
        {
            mPtr = static_cast<TListNode<T>*>(mPtr->next());
            return *this;
        }

        iterator& operator--()
        {
            mPtr = static_cast<TListNode<T>*>(mPtr->prev());
            return *this;
        }

        T& operator*() const { return mPtr->mData; }
        T* operator->() const { return &mPtr->mData; }

        friend bool operator==(iterator it1, iterator it2) { return it1.mPtr == it2.mPtr; }
        friend bool operator!=(iterator it1, iterator it2) { return !(it1 == it2); }

    private:
        TListNode<T>* mPtr;
    };

    iterator begin() const { return iterator(static_cast<TListNode<T>*>(mStartEnd.next())); }

    iterator end() const
    {
        return iterator(static_cast<TListNode<T>*>(const_cast<ListNode*>(&mStartEnd)));
    }

    /// An iterator that is safe to use even if the list is mutated during iteration.
    /// Unlike the regular iterator class, this exposes ListNode<T> rather than T
    /// to make it easier to modify the list.
    class robustIterator
    {
    public:
        explicit robustIterator(TListNode<T>* ptr) : mPtr(ptr)
        {
            mPtrNext = static_cast<TListNode<T>*>(mPtr->next());
        }

        robustIterator& operator++()
        {
            mPtr = mPtrNext;
            mPtrNext = static_cast<TListNode<T>*>(mPtrNext->next());
            return *this;
        }

        robustIterator operator++(int)
        {
            robustIterator copy = *this;
            mPtr = mPtrNext;
            mPtrNext = static_cast<TListNode<T>*>(mPtr->next());
            return copy;
        }

        TListNode<T>& operator*() const { return *mPtr; }
        TListNode<T>* operator->() const { return mPtr; }

        friend bool operator==(robustIterator it1, robustIterator it2)
        {
            return it1.mPtr == it2.mPtr;
        }
        friend bool operator!=(robustIterator it1, robustIterator it2) { return !(it1 == it2); }

    private:
        TListNode<T>* mPtr;
        TListNode<T>* mPtrNext;
    };

    robustIterator robustBegin() const
    {
        return robustIterator(static_cast<TListNode<T>*>(mStartEnd.next()));
    }

    robustIterator robustEnd() const
    {
        return robustIterator(static_cast<TListNode<T>*>(const_cast<ListNode*>(&mStartEnd)));
    }

    struct RobustRange
    {
        auto begin() const { return mList.robustBegin(); }
        auto end() const { return mList.robustEnd(); }
        const TList& mList;
    };
    RobustRange robustRange() const { return {*this}; }

private:
    static int compareT(const T* a, const T* b)
    {
        if (*a < *b)
            return -1;
        if (*a > *b)
            return 1;
        return 0;
    }
};

template <typename T>
class TListNode : public ListNode
{
public:
    TListNode() : ListNode()
    {
        mData = nullptr;
        mList = NULL;
    }

    TListNode(T data) : ListNode(), mData(data), mList(nullptr) {}

    void erase()
    {
        TList<T>* list = mList;
        if (list != NULL)
            list->erase(this);
    }

    T mData;
    TList<T>* mList;
};

}  // namespace sead

#endif  // SEAD_TLIST_H_
