#ifndef SEAD_METHODTREEMGR_H_
#define SEAD_METHODTREEMGR_H_

//#include <framework/seadMethodTree.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <thread/seadCriticalSection.h>

namespace sead
{
class MethodTreeNode;

class MethodTreeMgr
{
    SEAD_RTTI_BASE(MethodTreeMgr)

public:
    MethodTreeMgr();
    virtual ~MethodTreeMgr();

    virtual void attachMethod(s32, MethodTreeNode*) = 0;
    virtual MethodTreeNode* getRootMethodTreeNode(s32) = 0;
    virtual void pauseAll(bool) = 0;
    virtual void pauseAppCalc(bool) = 0;

    CriticalSection mCS;
};

}  // namespace sead

#endif  // SEAD_METHODTREEMGR_H_
