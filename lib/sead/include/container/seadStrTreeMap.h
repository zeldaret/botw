#pragma once

#include "basis/seadTypes.h"
#include "container/seadFreeList.h"
#include "container/seadTreeMap.h"
#include "prim/seadDelegate.h"
#include "prim/seadSafeString.h"

namespace sead
{
/// Sorted associative container with fixed-length string keys.
/// This is essentially std::map<char[MaxKeyLength], Value>
template <size_t MaxKeyLength, typename Value>
class StrTreeMap : public TreeMapImpl<SafeString>
{
public:
    using MapImpl = TreeMapImpl<SafeString>;
    class Node : public MapImpl::Node
    {
    public:
        Node(StrTreeMap* map, const SafeString& key, const Value& value) : mValue(value), mMap(map)
        {
            BufferedSafeString buffer(mKeyData, MaxKeyLength + 1);
            buffer.copy(key);
            this->mKey = buffer;
        }

        void erase_() override;

        Value& value() { return mValue; }
        const Value& value() const { return mValue; }

    private:
        friend class StrTreeMap;

        Value mValue;
        StrTreeMap* mMap;
        char mKeyData[MaxKeyLength + 1];
    };

    ~StrTreeMap();

    void allocBuffer(s32 node_max, Heap* heap, s32 alignment = sizeof(void*));
    void setBuffer(s32 node_max, void* buffer);
    void freeBuffer();

    Value* insert(const SafeString& key, const Value& value);
    void clear();

    Node* find(const SafeString& key) const;

    // Callable must have the signature Key&, Value&
    template <typename Callable>
    void forEach(const Callable& delegate) const;

private:
    void eraseNodeForClear_(typename MapImpl::Node* node);

    FreeList mFreeList;
    s32 mSize = 0;
    s32 mCapacity = 0;
};

template <size_t N, typename Value>
inline void StrTreeMap<N, Value>::Node::erase_()
{
    StrTreeMap* const map = mMap;
    void* const this_ = this;
    // Note: Nintendo does not call the destructor, which is dangerous...
    map->mFreeList.free(this_);
    --map->mSize;
}

template <size_t N, typename Value>
inline StrTreeMap<N, Value>::~StrTreeMap()
{
    void* work = mFreeList.work();
    if (!work)
        return;

    clear();
    freeBuffer();
}

template <size_t N, typename Value>
inline void StrTreeMap<N, Value>::allocBuffer(s32 node_max, Heap* heap, s32 alignment)
{
    SEAD_ASSERT(mFreeList.work() == nullptr);
    if (node_max <= 0)
    {
        SEAD_ASSERT_MSG(false, "node_max[%d] must be larger than zero", node_max);
        AllocFailAssert(heap, node_max * sizeof(Node), alignment);
    }

    void* work = AllocBuffer(node_max * sizeof(Node), heap, alignment);
    if (work)
        setBuffer(node_max, work);
}

template <size_t N, typename Value>
inline void StrTreeMap<N, Value>::setBuffer(s32 node_max, void* buffer)
{
    mCapacity = node_max;
    mFreeList.setWork(buffer, sizeof(Node), node_max);
}

template <size_t N, typename Value>
inline void StrTreeMap<N, Value>::freeBuffer()
{
    void* buffer = mFreeList.work();
    if (!buffer)
        return;

    ::operator delete[](buffer);
    mCapacity = 0;
    mFreeList.reset();
}

template <size_t N, typename Value>
inline Value* StrTreeMap<N, Value>::insert(const SafeString& key, const Value& value)
{
    if (mSize >= mCapacity)
    {
        if (Node* node = find(key))
        {
            node->value() = value;
            return &node->value();
        }
        SEAD_ASSERT_MSG(false, "map is full.");
        return nullptr;
    }

    Node* node = new (mFreeList.alloc()) Node(this, key, value);
    ++mSize;
    MapImpl::insert(node);
    return &node->value();
}

template <size_t N, typename Value>
inline void StrTreeMap<N, Value>::clear()
{
    Delegate1<StrTreeMap<N, Value>, typename MapImpl::Node*> delegate(
        this, &StrTreeMap::eraseNodeForClear_);
    MapImpl::forEach(delegate);
    mSize = 0;
    MapImpl::clear();
}

template <size_t N, typename Value>
inline typename StrTreeMap<N, Value>::Node* StrTreeMap<N, Value>::find(const SafeString& key) const
{
    return static_cast<Node*>(MapImpl::find(key));
}

template <size_t N, typename Value>
template <typename Callable>
inline void StrTreeMap<N, Value>::forEach(const Callable& delegate) const
{
    MapImpl::forEach([&delegate](auto* base_node) {
        auto* node = static_cast<Node*>(base_node);
        delegate(node->key(), node->value());
    });
}

template <size_t N, typename Value>
inline void StrTreeMap<N, Value>::eraseNodeForClear_(typename MapImpl::Node* node)
{
    // Note: Nintendo does not call the destructor, which is dangerous...
    mFreeList.free(node);
}
}  // namespace sead
