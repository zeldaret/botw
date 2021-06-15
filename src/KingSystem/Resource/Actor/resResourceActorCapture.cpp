#include "KingSystem/Resource/Actor/resResourceActorCapture.h"

namespace ksys::res {

static ActorCapture::ActorCaptureConstants sConstants;

const ActorCapture::ActorCaptureConstants& ActorCapture::getConstants() {
    return sConstants;
}

ActorCapture::ActorCapture() : ParamIO("actcapt", 0) {
    addObj(&mCameraInfoObj, "camera_info");
    mCameraInfoObj.position.init(sConstants.camera_position, "pos", "カメラ位置", &mCameraInfoObj);
    mCameraInfoObj.direction.init(sConstants.camera_direction, "at", "カメラ注視点",
                                  &mCameraInfoObj);
    mCameraInfoObj.fov.init(50.0, "fovy", "カメラ画角", &mCameraInfoObj);
    mCameraInfoObj.tilt.init(0.0, "twist", "カメラひねり", &mCameraInfoObj);

    addObj(&mActorInfoObj, "actor_info");
    mActorInfoObj.position.init(sConstants.actor_position, "pos", "アクタ位置", &mActorInfoObj);
    mActorInfoObj.rotation.init(sConstants.actor_rotation, "rotate", "アクタRotate",
                                &mActorInfoObj);
    mActorInfoObj.as_name.init(sead::SafeString::cEmptyString, "as_name", "適用するASのKey名",
                               &mActorInfoObj);
    mActorInfoObj.apply_skel_anim.init(false, "apply_skl_anim",
                                       "スケルタルアニメを検索して直接適用する", &mActorInfoObj);
    mActorInfoObj.frame.init(0.0, "as_frame", "ASのフレーム・経過時間指定", &mActorInfoObj);
    mActorInfoObj.bounding_adjustment.init(false, "adjust_bounding",
                                           "バウンディングを元に位置を調整する", &mActorInfoObj);
    mActorInfoObj.force_idle.init(false, "force_idle", "強制待機", &mActorInfoObj);
    mActorInfoObj.disable_cloth.init(false, "disable_cloth", "クロスを切る", &mActorInfoObj);

    addObj(&mLightInfoObj, "light_info");
    mLightInfoObj.direction.init(sConstants.light_direction, "dir", "ライト方向", &mLightInfoObj);
}

bool ActorCapture::parse_(u8* data, size_t, sead::Heap*) {
    if (data)
        applyResParameterArchive(agl::utl::ResParameterArchive(data));
    return true;
}

void ActorCapture::reset() {
    mCameraInfoObj.position.ref() = sConstants.camera_position;
    mCameraInfoObj.direction.ref() = sConstants.camera_direction;
    mCameraInfoObj.fov.ref() = 50;
    mCameraInfoObj.tilt.ref() = 0;

    mActorInfoObj.position.ref() = sConstants.actor_position;
    mActorInfoObj.rotation.ref() = sConstants.actor_rotation;
    mActorInfoObj.as_name.ref().copy(sead::FixedSafeString<32>(sead::SafeString::cEmptyString));
    mActorInfoObj.apply_skel_anim.ref() = false;
    mActorInfoObj.frame.ref() = 0;
    mActorInfoObj.bounding_adjustment.ref() = false;
    mActorInfoObj.force_idle.ref() = false;
    mActorInfoObj.disable_cloth.ref() = false;

    mLightInfoObj.direction.ref() = sConstants.light_direction;
}

}  // namespace ksys::res
