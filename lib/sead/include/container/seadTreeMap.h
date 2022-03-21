#pragma once

#include "basis/seadRawPrint.h"
#include "container/seadFreeList.h"
#include "prim/seadBitUtil.h"
#include "prim/seadDelegate.h"
#include "prim/seadSafeString.h"

namespace sead
{
template <typename Key>
class TreeMapNode;

/// Sorted associative container, implemented using a left-leaning red-black tree.
/// For an explanation of the algorithm, see https://www.cs.princeton.edu/~rs/talks/LLRB/LLRB.pdf
template <typename Key>
class TreeMapImpl
{
public:
    using Node = TreeMapNode<Key>;

    void insert(Node* node);
    void erase(const Key& key);
    void clear();

    Node* find(const Key& key) const { return find(mRoot, key); }

    template <typename Callable>
    void forEach(const Callable& callable) const
    {
        if (mRoot)
            forEach(mRoot, callable);
    }

    Node* startIterating() const
    {
        if (!mRoot)
            return nullptr;
        return startIterating(mRoot);
    }

    Node* nextNode(Node* node) const
    {
        if (!node)
            return nullptr;

        // If there is a right child node, explore that branch first.
        if (node->mRight)
        {
            node->mRight->setParent(node);
            return startIterating(node->mRight);
        }

        // Otherwise, walk back up to the node P from which we reached this node
        // by following P's left child pointer.
        while (auto* const parent = node->getParent())
        {
            if (parent->mLeft == node)
                return parent;
            node = parent;
        }
        return nullptr;
    }

protected:
    /// Returns the left most child of a given node, marking each node with its parent
    /// along the way.
    static Node* startIterating(Node* node)
    {
        while (node->mLeft)
        {
            node->mLeft->setParent(node);
            node = node->mLeft;
        }
        return node;
    }

    Node* insert(Node* root, Node* node);
    Node* erase(Node* root, const Key& key);
    Node* find(Node* root, const Key& key) const;

    static inline Node* rotateLeft(Node* node);
    static inline Node* rotateRight(Node* node);
    static inline Node* moveRedLeft(Node* node);
    static inline Node* moveRedRight(Node* node);
    static Node* findMin(Node* node);
    static Node* eraseMin(Node* node);
    static inline Node* fixUp(Node* node);
    static bool isRed(const Node* node) { return node && node->isRed(); }
    static inline void flipColors(Node* node);

    template <typename Callable>
    static void forEach(Node* start, const Callable& callable);

    Node* mRoot = nullptr;
};

/// Requires Key to have a compare() member function, which returns -1 if lhs < rhs, 0 if lhs = rhs
/// and 1 if lhs > rhs.
template <typename Key>
class TreeMapNode
{
public:
    TreeMapNode()
    {
        mLeft = mRight = nullptr;
        mColorAndPtr = 0;
    }

    virtual ~TreeMapNode() = default;
    virtual void erase_() = 0;

    const Key& key() const { return mKey; }

protected:
    friend class TreeMapImpl<Key>;

    enum class Color
    {
        Red = 0,
        Black = 1,
    };

    void flipColor() { BitUtil::bitCastWrite(mColorAndPtr ^ 1u, &mColorAndPtr); }
    void setColor(Color color) { mColorAndPtr = uintptr_t(color); }

    void setParent(TreeMapNode* parent) { mColorAndPtr = (mColorAndPtr & 1) | uintptr_t(parent); }
    /// @warning Only valid if setParent has been called!
    TreeMapNode* getParent() const { return reinterpret_cast<TreeMapNode*>(mColorAndPtr & ~1); }

    bool isRed() const { return (mColorAndPtr & 1u) == bool(Color::Red); }

    TreeMapNode* mLeft;
    TreeMapNode* mRight;
    uintptr_t mColorAndPtr;
    Key mKey;
};

/// Requires Key to have operator< defined
/// This can be specialized, but all specializations must define `compare` and `key` as follows.
template <typename Key>
struct TreeMapKeyImpl
{
    TreeMapKeyImpl() = default;
    TreeMapKeyImpl(const Key& key_) : key(key_) {}
    TreeMapKeyImpl& operator=(const Key& key_)
    {
        key = key_;
        return *this;
    }

    /// Returns -1 if mKey < rhs, 0 if mKey = rhs and 1 if mKey > rhs.
    s32 compare(const TreeMapKeyImpl& rhs) const
    {
        if (key < rhs.key)
            return -1;
        if (rhs.key < key)
            return 1;
        return 0;
    }

    Key key;
};

/// Sorted associative container.
/// This is essentially std::map<Key, Value>
template <typename Key, typename Value>
class TreeMap : public TreeMapImpl<TreeMapKeyImpl<Key>>
{
public:
    using MapImpl = TreeMapImpl<TreeMapKeyImpl<Key>>;
    class Node : public MapImpl::Node
    {
    public:
        Node(TreeMap* map, const Key& key, const Value& value) : mValue(value), mMap(map)
        {
            this->mKey = key;
        }

        void erase_() override;

        Value& value() { return mValue; }
        const Value& value() const { return mValue; }

    private:
        friend class TreeMap;

        Value mValue;
        TreeMap* mMap;
    };

    ~TreeMap();

    void allocBuffer(s32 node_max, Heap* heap, s32 alignment = sizeof(void*));
    void setBuffer(s32 node_max, void* buffer);
    void freeBuffer();

    Value* insert(const Key& key, const Value& value);
    void clear();

    Node* find(const Key& key) const;

    // Callable must have the signature Key&, Value&
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

template <typename Key, typename Node>
class IntrusiveTreeMap : public TreeMapImpl<Key>
{
public:
    using MapImpl = TreeMapImpl<Key>;

    Node* find(const Key& key) const { return static_cast<Node*>(MapImpl::find(key)); }

    // Callable must have the signature Node*
    template <typename Callable>
    void forEach(const Callable& delegate) const
    {
        MapImpl::forEach([delegate](auto* base_node) {
            auto* node = static_cast<Node*>(base_node);
            delegate(node);
        });
    }

    Node* startIterating() const { return static_cast<Node*>(MapImpl::startIterating()); }
    Node* nextNode(Node* node) const { return static_cast<Node*>(MapImpl::nextNode(node)); }
};

template <typename Key>
inline void TreeMapImpl<Key>::insert(Node* node)
{
    mRoot = insert(mRoot, node);
    mRoot->setColor(Node::Color::Black);
}

template <typename Key>
inline TreeMapNode<Key>* TreeMapImpl<Key>::insert(Node* root, Node* node)
{
    if (!root)
    {
        node->mLeft = node->mRight = nullptr;
        node->setColor(Node::Color::Red);
        return node;
    }

    const s32 cmp = node->key().compare(root->key());

    if (cmp < 0)
    {
        root->mLeft = insert(root->mLeft, node);
    }
    else if (cmp > 0)
    {
        root->mRight = insert(root->mRight, node);
    }
    else if (root != node)
    {
        node->mRight = root->mRight;
        node->mLeft = root->mLeft;
        node->mColorAndPtr = root->mColorAndPtr;
        root->erase_();
        root = node;
    }

    if (isRed(root->mRight) && !isRed(root->mLeft))
        root = rotateLeft(root);

    if (isRed(root->mLeft) && isRed(root->mLeft->mLeft))
        root = rotateRight(root);

    if (isRed(root->mLeft) && isRed(root->mRight))
        flipColors(root);

    return root;
}

template <typename Key>
inline void TreeMapImpl<Key>::erase(const Key& key)
{
    mRoot = erase(mRoot, key);
    if (mRoot)
        mRoot->setColor(Node::Color::Black);
}

template <typename Key>
inline TreeMapNode<Key>* TreeMapImpl<Key>::erase(Node* root, const Key& key)
{
    if (key.compare(root->key()) < 0)
    {
        if (!isRed(root->mLeft) && !isRed(root->mLeft->mLeft))
            root = moveRedLeft(root);
        root->mLeft = erase(root->mLeft, key);
    }
    else
    {
        if (isRed(root->mLeft))
            root = rotateRight(root);

        if (key.compare(root->key()) == 0 && !root->mRight)
        {
            root->erase_();
            return nullptr;
        }

        if (!isRed(root->mRight) && !isRed(root->mRight->mLeft))
            root = moveRedRight(root);

        if (key.compare(root->key()) == 0)
        {
            Node* const min_node = findMin(root->mRight);

            Node* target = root->mRight;
            if (root->mRight)
                target = find(root->mRight, min_node->key());

            target->mRight = eraseMin(root->mRight);
            target->mLeft = root->mLeft;
            target->mColorAndPtr = root->mColorAndPtr;
            root->erase_();
            root = target;
        }
        else
        {
            root->mRight = erase(root->mRight, key);
        }
    }
    return fixUp(root);
}

template <typename Key>
inline void TreeMapImpl<Key>::clear()
{
    mRoot = nullptr;
}

template <typename Key>
inline TreeMapNode<Key>* TreeMapImpl<Key>::find(Node* root, const Key& key) const
{
    Node* node = root;
    while (node)
    {
        const s32 cmp = key.compare(node->key());
        if (cmp < 0)
            node = node->mLeft;
        else if (cmp > 0)
            node = node->mRight;
        else
            return node;
    }

    return nullptr;
}

template <typename Key>
template <typename Callable>
inline void TreeMapImpl<Key>::forEach(Node* start, const Callable& callable)
{
    Node* i = start;
    do
    {
        Node* node = i;
        if (i->mLeft)
            forEach(i->mLeft, callable);
        i = i->mRight;
        callable(node);
    } while (i);
}

template <typename Key>
inline TreeMapNode<Key>* TreeMapImpl<Key>::rotateLeft(Node* node)
{
    TreeMapNode<Key>* j = node->mRight;
    node->mRight = j->mLeft;
    j->mLeft = node;
    j->mColorAndPtr = node->mColorAndPtr;
    node->setColor(Node::Color::Red);
    return j;
}

template <typename Key>
inline TreeMapNode<Key>* TreeMapImpl<Key>::rotateRight(Node* node)
{
    TreeMapNode<Key>* j = node->mLeft;
    node->mLeft = j->mRight;
    j->mRight = node;
    j->mColorAndPtr = node->mColorAndPtr;
    node->setColor(Node::Color::Red);
    return j;
}

// NON_MATCHING: this version matches the LLRB tree implementation and is better optimized;
// there is a useless store to node->mRight in the original version
template <typename Key>
inline TreeMapNode<Key>* TreeMapImpl<Key>::moveRedLeft(Node* node)
{
    flipColors(node);
    if (isRed(node->mRight->mLeft))
    {
        node->mRight = rotateRight(node->mRight);
        node = rotateLeft(node);
        flipColors(node);
    }
    return node;
}

template <typename Key>
inline TreeMapNode<Key>* TreeMapImpl<Key>::moveRedRight(Node* node)
{
    flipColors(node);
    if (isRed(node->mLeft->mLeft))
    {
        node = rotateRight(node);
        flipColors(node);
    }
    return node;
}

template <typename Key>
inline TreeMapNode<Key>* TreeMapImpl<Key>::findMin(Node* node)
{
    while (node->mLeft)
        node = node->mLeft;
    return node;
}

// NON_MATCHING: this version matches the LLRB tree implementation and is better optimized
template <typename Key>
inline TreeMapNode<Key>* TreeMapImpl<Key>::eraseMin(Node* node)
{
    if (!node->mLeft)
        return nullptr;

    if (!isRed(node->mLeft) && !isRed(node->mLeft->mLeft))
        node = moveRedLeft(node);

    node->mLeft = eraseMin(node->mLeft);
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    return fixUp(node);
}

template <typename Key>
inline TreeMapNode<Key>* TreeMapImpl<Key>::fixUp(Node* node)
{
    if (isRed(node->mRight))
        node = rotateLeft(node);

    if (isRed(node->mLeft) && isRed(node->mLeft->mLeft))
        node = rotateRight(node);

    if (isRed(node->mLeft) && isRed(node->mRight))
        flipColors(node);

    return node;
}

template <typename Key>
inline void TreeMapImpl<Key>::flipColors(Node* node)
{
    node->flipColor();
    node->mLeft->flipColor();
    node->mRight->flipColor();
}

template <typename Key, typename Value>
inline void TreeMap<Key, Value>::Node::erase_()
{
    TreeMap* const map = mMap;
    void* const this_ = this;
    // Note: Nintendo does not call the destructor, which is dangerous...
    map->mFreeList.free(this_);
    --map->mSize;
}

template <typename Key, typename Value>
inline TreeMap<Key, Value>::~TreeMap()
{
    void* work = mFreeList.work();
    if (!work)
        return;

    clear();
    freeBuffer();
}

template <typename Key, typename Value>
inline void TreeMap<Key, Value>::allocBuffer(s32 node_max, Heap* heap, s32 alignment)
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

template <typename Key, typename Value>
inline void TreeMap<Key, Value>::setBuffer(s32 node_max, void* buffer)
{
    mCapacity = node_max;
    mFreeList.setWork(buffer, sizeof(Node), node_max);
}

template <typename Key, typename Value>
inline void TreeMap<Key, Value>::freeBuffer()
{
    void* buffer = mFreeList.work();
    if (!buffer)
        return;

    ::operator delete[](buffer);
    mCapacity = 0;
    mFreeList.reset();
}

template <typename Key, typename Value>
inline Value* TreeMap<Key, Value>::insert(const Key& key, const Value& value)
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

template <typename Key, typename Value>
inline void TreeMap<Key, Value>::clear()
{
    Delegate1<TreeMap<Key, Value>, typename MapImpl::Node*> delegate(this,
                                                                     &TreeMap::eraseNodeForClear_);
    MapImpl::forEach(delegate);
    mSize = 0;
    MapImpl::clear();
}

template <typename Key, typename Value>
inline typename TreeMap<Key, Value>::Node* TreeMap<Key, Value>::find(const Key& key) const
{
    return static_cast<Node*>(MapImpl::find(key));
}

template <typename Key, typename Value>
template <typename Callable>
inline void TreeMap<Key, Value>::forEach(const Callable& delegate) const
{
    MapImpl::forEach([&delegate](auto* base_node) {
        auto* node = static_cast<Node*>(base_node);
        delegate(node->key(), node->value());
    });
}

template <typename Key, typename Value>
inline void TreeMap<Key, Value>::eraseNodeForClear_(typename MapImpl::Node* node)
{
    // Note: Nintendo does not call the destructor, which is dangerous...
    mFreeList.free(node);
}
}  // namespace sead
