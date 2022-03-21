#pragma once

#include "container/seadTreeMap.h"

namespace sead
{
/// Requires Value to have operator< defined
/// This can be specialized, but all specializations must define `compare` as follows.
template <typename Value>
struct OrderedSetItemImpl
{
    OrderedSetItemImpl() = default;
    // NOLINTNEXTLINE(google-explicit-constructor)
    OrderedSetItemImpl(const Value& value_) : value(value_) {}
    OrderedSetItemImpl& operator=(const Value& value_)
    {
        value = value_;
        return *this;
    }

    /// Returns -1 if this->value < rhs, 0 if this->value = rhs and 1 if this->value > rhs.
    s32 compare(const OrderedSetItemImpl& rhs) const
    {
        if (value < rhs.value)
            return -1;
        if (rhs.value < value)
            return 1;
        return 0;
    }

    Value value;
};

/// This is essentially std::set<Value>. Values are stored in a red-black tree in an order
/// determined by the partial order defined for Value (via operator<).
template <typename Value>
class OrderedSet : public TreeMapImpl<OrderedSetItemImpl<Value>>
{
public:
    using MapImpl = TreeMapImpl<OrderedSetItemImpl<Value>>;
    class Node : public MapImpl::Node
    {
    public:
        Node(OrderedSet* set, const Value& value) : mSet(set) { this->mKey = value; }

        void erase_() override;

        // Values cannot be modified.
        const Value& value() const { return this->key().value; }

    private:
        friend class OrderedSet;
        OrderedSet* mSet;
    };

    /// Clears the set and frees the allocated buffer (if needed).
    /// Should only be used if the buffer was allocated using allocBuffer.
    void finalize()
    {
        clear();
        freeBuffer();
    }

    bool allocBuffer(s32 node_max, Heap* heap, s32 alignment = sizeof(void*));
    void setBuffer(s32 node_max, void* buffer);
    /// Should only be used if the buffer was allocated using allocBuffer.
    void freeBuffer();

    const Value* insert(const Value& value);
    void clear();

    Node* find(const Value& value) const;

    // Callable must have the signature Value&
    template <typename Callable>
    void forEach(const Callable& delegate) const;

    Node* startIterating() const { return static_cast<Node*>(MapImpl::startIterating()); }
    Node* nextNode(Node* node) const { return static_cast<Node*>(MapImpl::nextNode(node)); }

private:
    void eraseNodeForClear_(typename MapImpl::Node* node);

    FreeList mFreeList;
    s32 mSize = 0;
    s32 mCapacity = 0;
};

template <typename Value>
inline bool OrderedSet<Value>::allocBuffer(s32 node_max, Heap* heap, s32 alignment)
{
    SEAD_ASSERT(mFreeList.work() == nullptr);
    if (node_max <= 0)
    {
        SEAD_ASSERT_MSG(false, "node_max[%d] must be larger than zero", node_max);
        AllocFailAssert(heap, node_max * sizeof(Node), alignment);
    }

    void* work = AllocBuffer(node_max * sizeof(Node), heap, alignment);
    if (!work)
        return false;
    setBuffer(node_max, work);
    return true;
}

template <typename Value>
inline void OrderedSet<Value>::setBuffer(s32 node_max, void* buffer)
{
    mCapacity = node_max;
    mFreeList.setWork(buffer, sizeof(Node), node_max);
}

template <typename Value>
inline void OrderedSet<Value>::freeBuffer()
{
    void* buffer = mFreeList.work();
    if (!buffer)
        return;

    mSize = 0;
    MapImpl::clear();
    ::operator delete[](buffer);
    mCapacity = 0;
    mFreeList.reset();
}

template <typename Value>
inline const Value* OrderedSet<Value>::insert(const Value& value)
{
    if (mSize >= mCapacity)
    {
        if (Node* node = find(value))
        {
            node->mKey = value;
            return &node->value();
        }
        SEAD_ASSERT_MSG(false, "map is full.");
        return nullptr;
    }

    Node* node = new (mFreeList.alloc()) Node(this, value);
    ++mSize;
    MapImpl::insert(node);
    return &node->value();
}

template <typename Value>
inline void OrderedSet<Value>::clear()
{
    Delegate1<OrderedSet<Value>, typename MapImpl::Node*> delegate(this,
                                                                   &OrderedSet::eraseNodeForClear_);
    MapImpl::forEach(delegate);
    mSize = 0;
    MapImpl::clear();
}

template <typename Value>
inline typename OrderedSet<Value>::Node* OrderedSet<Value>::find(const Value& value) const
{
    return static_cast<Node*>(MapImpl::find(value));
}

template <typename Value>
template <typename Callable>
inline void OrderedSet<Value>::forEach(const Callable& delegate) const
{
    MapImpl::forEach([&delegate](auto* base_node) {
        auto* node = static_cast<Node*>(base_node);
        delegate(node->value());
    });
}

template <typename Value>
inline void OrderedSet<Value>::eraseNodeForClear_(typename MapImpl::Node* node)
{
    // Note: Nintendo does not call the destructor, which is dangerous...
    mFreeList.free(node);
}

template <typename Value>
inline void OrderedSet<Value>::Node::erase_()
{
    OrderedSet* const map = mSet;
    void* const this_ = this;
    // Note: Nintendo does not call the destructor, which is dangerous...
    map->mFreeList.free(this_);
    --map->mSize;
}
}  // namespace sead
