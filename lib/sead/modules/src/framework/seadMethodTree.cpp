#include <framework/seadMethodTree.h>
#include <thread/seadCriticalSection.h>

namespace sead
{
void MethodTreeNode::pushBackChild(MethodTreeNode* node)
{
    lock_();
    node->detachSubTree();
    node->mCriticalSection = mCriticalSection;
    if (node->child())
    {
        auto* parent = node->child()->value();
        if (parent)
            parent->attachMutexRec_(mCriticalSection);
    }
    TreeNode::pushBackChild(node);
    unlock_();
}

void MethodTreeNode::pushFrontChild(MethodTreeNode* node)
{
    lock_();
    node->detachSubTree();
    node->mCriticalSection = mCriticalSection;
    if (node->child())
    {
        auto* parent = node->child()->value();
        if (parent)
            parent->attachMutexRec_(mCriticalSection);
    }
    TreeNode::pushFrontChild(node);
    unlock_();
}

void MethodTreeNode::attachMutexRec_(CriticalSection* m) const
{
    const MethodTreeNode* node = this;

    do
    {
        auto* child = node->child();
        node->mCriticalSection = m;
        if (child && child->value())
            child->value()->attachMutexRec_(m);
    } while (node->next() && (node = node->next()->value()));
}

void MethodTreeNode::detachAll()
{
    CriticalSection* cs = mCriticalSection;
    attachMutexRec_(NULL);
    mCriticalSection = cs;

    lock_();
    TreeNode::detachAll();
    unlock_();

    mCriticalSection = NULL;
}

void MethodTreeNode::lock_()
{
    if (mCriticalSection == NULL)
        return;

    mCriticalSection->lock();
}

void MethodTreeNode::unlock_()
{
    if (mCriticalSection == NULL)
        return;

    mCriticalSection->unlock();
}

void MethodTreeNode::call()
{
    lock_();
    callRec_();
    unlock_();
}

void MethodTreeNode::callRec_()
{
    if (!mPauseFlag.isOn(cPause_Self))
        (*mDelegateHolder.data())();

    auto* node = child();
    if (node && !mPauseFlag.isOn(cPause_Child))
    {
        while (node)
        {
            node->value()->callRec_();
            node = node->value()->next();
        }
    }
}

}  // namespace sead
