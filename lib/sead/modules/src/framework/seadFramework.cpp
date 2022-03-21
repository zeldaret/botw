#include <framework/seadFramework.h>
#include <framework/seadMethodTreeMgr.h>
#include <framework/seadTaskMgr.h>
#include <heap/seadHeap.h>

namespace sead
{
Framework::CreateSystemTaskArg::CreateSystemTaskArg()
    : hostio_parameter(NULL), infloop_detection_span()
{
}

Framework::Framework()
    : mReserveReset(false), mResetParameter(NULL), mResetEvent(), mTaskMgr(NULL),
      mMethodTreeMgr(NULL), mMethodTreeMgrHeap(NULL)
{
}

Framework::~Framework()
{
    if (mTaskMgr != NULL)
    {
        mTaskMgr->finalize();
        delete mTaskMgr;
        mTaskMgr = NULL;
    }

    if (mMethodTreeMgr != NULL)
    {
        delete mMethodTreeMgr;
        mMethodTreeMgr = NULL;
    }

    if (mMethodTreeMgrHeap != NULL)
        mMethodTreeMgrHeap->destroy();
}

}  // namespace sead
