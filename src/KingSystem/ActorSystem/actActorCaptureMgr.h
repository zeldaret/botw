#pragma once

#include <basis/seadTypes.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Resource/Actor/resResourceActorCapture.h"
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {
class EntryFactoryBase;
}

namespace ksys::act {

class Actor;
class Camera;

// TODO: incomplete
class ActorCaptureMgr {
public:
    struct InitArg {
        sead::Heap* heap;
    };

    ActorCaptureMgr();
    virtual ~ActorCaptureMgr();

    void init(const InitArg& arg);
    void setCamera(Camera* camera);

    void loadCaptureParam();
    const char* getCapturedActorName() const;

private:
    Actor* mActor{};
    Camera* mCamera{};
    res::EntryFactoryBase* mFactory{};
    res::Handle mDummyFile;
    res::Handle mCaptureParamFile;
    sead::FixedSafeString<64> mStr;
    sead::FixedSafeString<256> mStr2;
    res::ActorCapture mRes;
    struct Field768 {
        Field768() {
            _76c = 0;
            _768 = 0;
        }
        u32 _768;
        u8 _76c;
    } _768;
    s32 _770 = -1;
    u32 _774{};
    u32 _778{};
    Timer mTimer;
};
KSYS_CHECK_SIZE_NX150(ActorCaptureMgr, 0x788);

}  // namespace ksys::act
