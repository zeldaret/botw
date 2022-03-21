
#include "hostio/seadHostIONode.h"
#include "hostio/seadHostIOReflexible.h"
#include "hostio/seadHostIOThreadLock.h"

namespace sead::hostio
{
Node::Node()
{
    mTreeNode.value() = this;
}

Node::Node(Heap* heap, IDisposer::HeapNullOption heap_null_option)
    : Reflexible(heap, heap_null_option)
{
    mTreeNode.value() = this;
}

void Node::detachAll()
{
    ThreadLock lock;
    mTreeNode.detachAll();
}

void Node::detach()
{
    ThreadLock lock;
    mTreeNode.detachSubTree();
}

Node* Node::getParentNode() const
{
    TTreeNode<Node*>* node = mTreeNode.parent();
    if (node)
        return node->value();
    return nullptr;
}

Node* Node::getChildNode() const
{
    TTreeNode<Node*>* node = mTreeNode.child();
    if (node)
        return node->value();
    return nullptr;
}

Node* Node::getNextNode() const
{
    TTreeNode<Node*>* node = mTreeNode.next();
    if (node)
        return node->value();
    return nullptr;
}

Node* Node::getPrevNode() const
{
    TTreeNode<Node*>* parent = mTreeNode.parent();
    if (parent && parent->child() == &mTreeNode)
        return nullptr;

    TTreeNode<Node*>* node = mTreeNode.prev();
    if (node)
        return node->value();
    return nullptr;
}

bool Node::isAppended() const
{
    return mTreeNode.parent() || mTreeNode.next() || mTreeNode.prev();
}

void Node::disposeHostIOImpl_()
{
    destroy();
}
}  // namespace sead::hostio
