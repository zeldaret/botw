#ifndef SEAD_TREENODE_H_
#define SEAD_TREENODE_H_

#include <basis/seadTypes.h>

namespace sead
{
class TreeNode
{
public:
    TreeNode();

    void clearLinks();
    s32 countChildren() const;
    void detachAll();
    void detachSubTree();
    TreeNode* findRoot();
    const TreeNode* findRoot() const;
    void insertAfterSelf(TreeNode* node);
    void insertBeforeSelf(TreeNode* node);
    void pushBackChild(TreeNode* node);
    void pushBackSibling(TreeNode* node);
    void pushFrontChild(TreeNode* node);

protected:
    void clearChildLinksRecursively_();

    TreeNode* mParent;
    TreeNode* mChild;
    TreeNode* mNext;
    TreeNode* mPrev;
};

template <typename T>
class TTreeNode : public TreeNode
{
public:
    TTreeNode() = default;
    explicit TTreeNode(T data) : mData(data) {}

    T& value() { return mData; }
    const T& value() const { return mData; }

    TTreeNode* parent() const { return static_cast<TTreeNode*>(mParent); }
    TTreeNode* child() const { return static_cast<TTreeNode*>(mChild); }
    TTreeNode* next() const { return static_cast<TTreeNode*>(mNext); }
    TTreeNode* prev() const { return static_cast<TTreeNode*>(mPrev); }
    TTreeNode* findRoot() { return static_cast<TTreeNode*>(TreeNode::findRoot()); }
    const TTreeNode* findRoot() const { return static_cast<TTreeNode*>(TreeNode::findRoot()); }
    void insertAfterSelf(TTreeNode* node) { TreeNode::insertAfterSelf(node); }
    void insertBeforeSelf(TTreeNode* node) { TreeNode::insertBeforeSelf(node); }
    void pushBackChild(TTreeNode* node) { TreeNode::pushBackChild(node); }
    void pushBackSibling(TTreeNode* node) { TreeNode::pushBackSibling(node); }
    void pushFrontChild(TTreeNode* node) { TreeNode::pushFrontChild(node); }

    // TODO: probably iterators

protected:
    T mData;
};

}  // namespace sead

#endif  // SEAD_TREENODE_H_
