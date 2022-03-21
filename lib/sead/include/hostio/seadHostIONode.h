#pragma once

#include "container/seadTreeNode.h"
#include "hostio/seadHostIOReflexible.h"

namespace sead::hostio
{
class Node : public Reflexible
{
public:
    NodeClassType getNodeClassType() const override { return Reflexible::NodeClassType::Node; }

#ifdef SEAD_DEBUG
public:
    Node();
    Node(Heap* heap, IDisposer::HeapNullOption heap_null_option);
    ~Node() override { disposeHostIOImpl_(); }

    void appendChild(Node* node);
    void insertAfterSelf(Node* node);
    void insertBeforeSelf(Node* node);
    void detachAll();
    void detach();
    void destroy() { detachAll(); }
    Node* getParentNode() const;
    Node* getChildNode() const;
    Node* getNextNode() const;
    Node* getPrevNode() const;

    bool isAppended() const;

    Reflexible* searchNode(const SafeString& name) override;
    void calcURL(BufferedSafeString* url) const override { calcURLImpl_(url, true); }

protected:
    void genChildNode(Context* context) override;
    bool isHaveChild() const override { return mTreeNode.child() != nullptr; }
    void disposeHostIO() override
    {
        disposeHostIOImpl_();
        Reflexible::disposeHostIO();
    }

private:
    void disposeHostIOImpl_();
    void calcURLImpl_(BufferedSafeString* url, bool) const;

    TTreeNode<Node*> mTreeNode;
#endif
};
}  // namespace sead::hostio
