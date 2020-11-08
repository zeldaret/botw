#include "KingSystem/ActorSystem/actActorCaptureMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Resource/resEntryFactory.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Resource/resResourceMgrTask.h"
#include "KingSystem/Resource/resSystem.h"
#include "KingSystem/Utils/SafeDelete.h"

namespace ksys::act {

ActorCaptureMgr::ActorCaptureMgr() {
    mRes.reset();
    mTimer.reset(30.0);
}

ActorCaptureMgr::~ActorCaptureMgr() {
    mActor = nullptr;
    mCamera = nullptr;
    res::unregisterEntryFactory(mFactory);
    util::safeDelete(mFactory);
}

void ActorCaptureMgr::init(const InitArg& arg) {
    mFactory = new (arg.heap) res::EntryFactory<res::ActorCapture>(1.0, 0x1000);
    res::registerEntryFactory(mFactory, "bactcapt");

    res::LoadRequest req;
    req.mRequester = "ActorCaptureMgr";
    req._26 = false;
    mDummyFile.load("Actor/ActorCapture/Dummy.bactcapt", &req);
}

void ActorCaptureMgr::setCamera(Camera* camera) {
    if (camera)
        mCamera = camera;
}

void ActorCaptureMgr::loadCaptureParam() {
    if (!mActor || !mActor->getParam())
        return;

    const char* name = getCapturedActorName();
    if (!name)
        return;

    res::ActorCapture* param = nullptr;

    {
        res::LoadRequest req;
        req.mRequester = "ActorCaptureMgr";
        sead::FormatFixedSafeString<128> path("Actor/ActorCapture/%s.bactcapt", name);
        res::ResourceMgrTask::instance()->controlField9c0d88(false);
        auto* file = sead::DynamicCast<res::ActorCapture>(mCaptureParamFile.load(path, &req));
        res::ResourceMgrTask::instance()->controlField9c0d88(true);
        if (file)
            param = file;
        if (!param)
            param = sead::DynamicCast<res::ActorCapture>(mDummyFile.getResource());
    }

    mRes.mCameraInfoObj.copy(param->mCameraInfoObj);
    mRes.mActorInfoObj.copy(param->mActorInfoObj);
    mRes.mLightInfoObj.copy(param->mLightInfoObj);
}

}  // namespace ksys::act
