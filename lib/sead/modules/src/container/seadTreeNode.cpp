#include <basis/seadRawPrint.h>
#include <container/seadTreeNode.h>

namespace sead
{
TreeNode::TreeNode()
{
    clearLinks();
}

void TreeNode::clearChildLinksRecursively_()
{
    TreeNode* node = this->mChild;
    while (node != NULL)
    {
        TreeNode* next = node->mNext;
        node->clearChildLinksRecursively_();
        node->clearLinks();
        node = next;
    }
}

void TreeNode::clearLinks()
{
    mPrev = NULL;
    mParent = NULL;
    mNext = NULL;
    mChild = NULL;
}

s32 TreeNode::countChildren() const
{
    s32 count = 0;
    TreeNode* node = mChild;
    while (node)
    {
        ++count;
        node = node->mNext;
    }
    return count;
}

void TreeNode::detachAll()
{
    detachSubTree();
    clearChildLinksRecursively_();
    clearLinks();
}

void TreeNode::detachSubTree()
{
    if (mParent && mParent->mChild == this)
    {
        mParent->mChild = mNext;
        if (mNext)
        {
            mNext->mPrev = mPrev;
            mNext = nullptr;
        }
    }
    else
    {
        if (mPrev)
            mPrev->mNext = mNext;
        if (mNext)
        {
            mNext->mPrev = mPrev;
            mNext = nullptr;
        }
        else if (mParent)
        {
            mParent->mChild->mPrev = mPrev;
        }
    }
    mPrev = nullptr;
    mParent = nullptr;
}

TreeNode* TreeNode::findRoot()
{
    if (!mParent)
        return this;

    TreeNode* p = mParent;
    TreeNode* root;
    do
    {
        root = p;
        SEAD_ASSERT(p != this);
        p = p->mParent;
    } while (p);
    return root;
}

const TreeNode* TreeNode::findRoot() const
{
    if (!mParent)
        return this;

    TreeNode* p = mParent;
    TreeNode* root;
    do
    {
        root = p;
        SEAD_ASSERT(p != this);
        p = p->mParent;
    } while (p);
    return root;
}

void TreeNode::insertAfterSelf(TreeNode* node)
{
    node->detachSubTree();

    TreeNode* next = mNext;
    mNext = node;
    node->mPrev = this;
    node->mNext = next;
    if (next)
        next->mPrev = node;
    else if (mParent)
        mParent->mChild->mPrev = node;
    node->mParent = mParent;
}

void TreeNode::insertBeforeSelf(TreeNode* node)
{
    node->detachSubTree();

    TreeNode* prev = mPrev;
    mPrev = node;
    node->mPrev = prev;
    node->mNext = this;
    if (mParent && mParent->mChild == this)
        mParent->mChild = node;
    else if (prev)
        prev->mNext = node;
    node->mParent = mParent;
}

void TreeNode::pushBackChild(TreeNode* node)
{
    node->detachSubTree();

    if (mChild)
    {
        TreeNode* n = mChild->mPrev;
        SEAD_ASSERT(n);
        n->mNext = node;
        node->mPrev = n;
        node->mParent = n->mParent;
        mChild->mPrev = node;
    }
    else
    {
        mChild = node;
        node->mParent = this;
        node->mPrev = node;
    }
}

void TreeNode::pushBackSibling(TreeNode* node)
{
    node->detachSubTree();

    TreeNode* m;
    if (mParent && mParent->mChild)
    {
        m = mParent->mChild->mPrev;
        mParent->mChild->mPrev = node;
    }
    else
    {
        m = this;
        while (m->mNext)
            m = m->mNext;
    }
    m->mNext = node;
    node->mPrev = m;
    node->mParent = m->mParent;
}

void TreeNode::pushFrontChild(TreeNode* node)
{
    node->detachSubTree();
    if (mChild)
    {
        node->mNext = mChild;
        node->mPrev = mChild->mPrev;
        mChild->mPrev = node;
        mChild = node;
        node->mParent = this;
    }
    else
    {
        mChild = node;
        node->mParent = this;
        node->mPrev = node;
    }
}
}  // namespace sead
