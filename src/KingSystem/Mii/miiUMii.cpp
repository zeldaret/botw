#include "KingSystem/Mii/miiUMii.h"
#include <container/seadSafeArray.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActorParamMgr.h"
#include "KingSystem/Mii/miiModelCreator.h"
#include "KingSystem/Resource/Actor/resResourceUMii.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace ksys::mii {

struct Constants {
    util::InitConstants init_constants;
    sead::Vector3f eye_ctrl_base_offset{0.0, 0.03, 0.0};
    sead::SafeArray<sead::SafeString, 4> rot_names{{
        "rot_cravicle",
        "rot_arm",
        "rot_leg",
        "rot_crotch",
    }};
};
static Constants s_constants;
constexpr sead::SafeArray<float, 4> s_eye_highlight_values{{1.0, 0.5, 0.2, 0.0}};

UMii::UMii() : agl::utl::IParameterIO("umii", 0) {
    mUser = "Dummy";

    addObj(&ffsd, "ffsd");
    ffsd.no_use_ffsd.init(false, "no_use_ffsd", "Miiデータを使用しない(NPCプロフィールとして扱う)",
                          &ffsd);
    ffsd.type.init(0, "type", "参照先", &ffsd);

    addObj(&body, "body");
    body.race.init(0, "race", "種族", &body);
    body.type.init(0, "type", "種類", &body);
    body.number.init(0, "number", "番号", &body);
    body.weight.init(1, "weight", "体重", &body);
    body.height.init(0, "height", "身長", &body);

    addObj(&personal, "personal");
    personal.sex_age.init(1, "sex_age", "性別世代", &personal);
    personal.fav_color.init(0, "fav_color", "お気に入りカラー", &personal);
    personal.sub_color_1.init(-1, "sub_color_1", "サブカラー1", &personal);
    personal.sub_color_2.init(-1, "sub_color_2", "サブカラー2", &personal);
    personal.head_fav_color.init(-1, "head_fav_color", "お気に入りカラー（帽子）", &personal);
    personal.shoulder_fav_color.init(-1, "shoulder_fav_color", "お気に入りカラー（リュック）",
                                     &personal);
    personal.shoulder_sub_color_1.init(-1, "shoulder_sub_color_1", "サブカラー1（リュック）",
                                       &personal);
    personal.personality.init(sead::SafeString::cEmptyString, "personality", "性格", &personal);
    personal.voice_type.init("Normal1", "voice_type", "ボイスタイプ", &personal);

    addObj(&common, "common");
    common.backpack.init(-1, "backpack", "背負いもの", &common);
    common.hat.init(-1, "hat", "帽子", &common);
    common.no_hat_always.init(false, "no_hat_always", "常時帽子Off", &common);
    common.body_correct.init(false, "body_correct", "体形補正", &common);
    common.is_mid_age.init(false, "is_mid_age", "中年扱い（ゲルド用）", &common);
    common.rot_cravicle.init(0.0, s_constants.rot_names[0], s_rot_labels[0], &common);
    common.rot_arm.init(0.0, s_constants.rot_names[1], s_rot_labels[1], &common);
    common.rot_leg.init(0.0, s_constants.rot_names[2], s_rot_labels[2], &common);
    common.rot_crotch.init(0.0, s_constants.rot_names[3], s_rot_labels[3], &common);

    addObj(&face.shape, "shape");
    face.shape.jaw.init(0, "jaw", "顎形状", &face.shape);
    face.shape.wrinkle.init(0, "wrinkle", "しわ", &face.shape);
    face.shape.make.init(0, "make", "化粧", &face.shape);
    face.shape.trans_v.init(0, "trans_v", "縦移動", &face.shape);
    face.shape.scale.init(1.0, "scale", "拡縮", &face.shape);
    face.shape.skin_color.init(0, "skin_color", "肌の色", &face.shape);

    addObj(&face.hair, "hair");
    face.hair.type.init(Hair::Type_Invalid, "type", "髪型", &face.hair);
    face.hair.color.init(1, "color", "髪の色", &face.hair);
    face.hair.flip.init(false, "flip", "反転", &face.hair);

    addObj(&face.eye, "eye");
    face.eye.type.init(2, "type", "種類", &face.eye);
    face.eye.color.init(0, "color", "瞳の色", &face.eye);
    face.eye.trans_v.init(12.0, "trans_v", "縦移動", &face.eye);
    face.eye.trans_u.init(2.0, "trans_u", "横移動", &face.eye);
    face.eye.rotate.init(0.0, "rotate", "回転", &face.eye);
    face.eye.scale.init(4.0, "scale", "拡縮", &face.eye);
    face.eye.aspect.init(3.0, "aspect", "縦拡縮", &face.eye);
    face.eye.eyeball_trans_u.init(0.0, "eyeball_trans_u", "瞳上下オフセット", &face.eye);
    face.eye.eyeball_trans_v.init(0.0, "eyeball_trans_v", "瞳左右オフセット", &face.eye);
    face.eye.eyeball_scale.init(0.0, "eyeball_scale", "瞳拡縮オフセット", &face.eye);
    face.eye.highlight_bright.init(0, "highlight_bright", "ハイライトの明るさ", &face.eye);
    face.eye.highlight_value = s_eye_highlight_values[0];

    addObj(&face.eye_ctrl, "eye_ctrl");
    face.eye_ctrl.base_offset.init(s_constants.eye_ctrl_base_offset, "base_offset",
                                   "基準位置オフセット", &face.eye_ctrl);
    face.eye_ctrl.translim_out.init(0.2, "translim_out", "外移動量上限", &face.eye_ctrl);
    face.eye_ctrl.translim_in.init(0.12, "translim_in", "内移動量上限", &face.eye_ctrl);
    face.eye_ctrl.translim_d.init(0.3, "translim_d", "下移動量上限", &face.eye_ctrl);
    face.eye_ctrl.translim_u.init(0.1, "translim_u", "上移動量上限", &face.eye_ctrl);
    face.eye_ctrl.neck_offset_ud.init(0.0, "neck_offset_ud", "首向け上下角オフセット",
                                      &face.eye_ctrl);

    addObj(&face.eyebrow, "eyebrow");
    face.eyebrow.type.init(0, "type", "種類", &face.eyebrow);
    face.eyebrow.color.init(1, "color", "色", &face.eyebrow);
    face.eyebrow.trans_v.init(7.0, "trans_v", "縦移動", &face.eyebrow);
    face.eyebrow.trans_u.init(2.0, "trans_u", "横移動", &face.eyebrow);
    face.eyebrow.rotate.init(0.0, "rotate", "回転", &face.eyebrow);
    face.eyebrow.scale.init(4.0, "scale", "拡縮", &face.eyebrow);
    face.eyebrow.aspect.init(3.0, "aspect", "縦拡縮", &face.eyebrow);

    addObj(&face.nose, "nose");
    face.nose.type.init(1, "type", "種類", &face.nose);
    face.nose.trans_v.init(9.0, "trans_v", "縦移動", &face.nose);
    face.nose.scale.init(4.0, "scale", "拡縮", &face.nose);

    addObj(&face.mouth, "mouth");
    face.mouth.type.init(3, "type", "種類", &face.mouth);
    face.mouth.color.init(0, "color", "口紅の色", &face.mouth);
    face.mouth.trans_v.init(13.0, "trans_v", "縦移動", &face.mouth);
    face.mouth.scale.init(4.0, "scale", "拡縮", &face.mouth);
    face.mouth.aspect.init(3.0, "aspect", "縦拡縮", &face.mouth);

    addObj(&face.beard, "beard");
    face.beard.mustache.init(0, "mustache", "口髭の種類", &face.beard);
    face.beard.scale.init(0.0, "scale", "口髭拡縮", &face.beard);
    face.beard.type.init(0, "type", "アゴ髭の種類", &face.beard);
    face.beard.color.init(0, "color", "髭の色", &face.beard);

    addObj(&face.glass, "glass");
    face.glass.type.init(0, "type", "種類", &face.glass);
    face.glass.color.init(0, "color", "色", &face.glass);

    addObj(&korok, "korog");  // sic
    korok.mask.init(0, "mask", "お面", &korok);
    korok.skin_color.init(0, "skin_color", "肌の色", &korok);
    korok.left_plant.init(0, "left_plant", "手持ち枝(左)", &korok);
    korok.right_plant.init(0, "right_plant", "手持ち枝(右)", &korok);

    addObj(&goron, "goron");
    goron.skin_color.init(0, "skin_color", "肌の色", &goron);

    addObj(&gerudo, "gerudo");
    gerudo.hair.init(0, "hair", "髪", &gerudo);
    gerudo.hair_color.init(0, "hair_color", "髪の色", &gerudo);
    gerudo.glass.init(0, "glass", "眼鏡", &gerudo);
    gerudo.glass_color.init(0, "glass_color", "眼鏡の色", &gerudo);
    gerudo.skin_color.init(0, "skin_color", "肌の色", &gerudo);
    gerudo.lip_color.init(0, "lip_color", "唇の色", &gerudo);

    addObj(&rito, "rito");
    rito.body_color.init(0, "body_color", "身体の色", &rito);
    rito.hair_color.init(-1, "hair_color", "髪の色", &rito);

    addObj(&zora, "zora");
    zora.body_color.init(0, "body_color", "身体の色", &zora);
}

UMii::~UMii() {
    mActor = nullptr;
    if (mActorParam) {
        act::ActorParamMgr::instance()->unloadParam(mActorParam);
        mActorParam = nullptr;
    }
}

void UMii::load(agl::utl::ResParameterArchive archive, const sead::SafeString& user,
                const u32& load_req_c) {
    reset();
    applyResParameterArchive(archive);
    mUser = user;
    doLoad(load_req_c);
    face.eye.highlight_value = s_eye_highlight_values[face.eye.highlight_bright.ref()];
}

void UMii::reset() {
    mUser = "Dummy";

    ffsd.no_use_ffsd = false;
    ffsd.type = 0;

    body.race = 0;
    body.type = 0;
    body.number = 0;
    body.weight = 1;
    body.height = 0;

    personal.sex_age = Personal::SexAge_Man;
    personal.fav_color = 0;
    personal.sub_color_1 = -1;
    personal.sub_color_2 = -1;
    personal.head_fav_color = -1;
    personal.shoulder_fav_color = -1;
    personal.shoulder_sub_color_1 = -1;
    personal.personality = sead::SafeString::cEmptyString;
    personal.voice_type = "Normal1";

    common.backpack = -1;
    common.hat = -1;

    korok.mask = 0;
    korok.skin_color = 0;
    korok.left_plant = 0;
    korok.right_plant = 0;

    goron.skin_color = 0;

    gerudo.hair = 0;
    gerudo.hair_color = 0;
    gerudo.glass = 0;
    gerudo.glass_color = 0;
    gerudo.skin_color = 0;
    gerudo.lip_color = 0;

    rito.body_color = 0;
    rito.hair_color = -1;

    zora.body_color = 0;
}

void UMii::doLoad(const u32& load_req_c) {
    if (ffsd.type.ref() == FFSD::Type_1) {
        mActorName = ModelCreator::instance()->getActorName({isFemale()});

        void* x;
        mActorParam = act::ActorParamMgr::instance()->loadParam(mActorName.cstr(), &mResHandle, &x,
                                                                load_req_c);

        if (mActorParam) {
            res::UMii* umii = nullptr;
            if (!mActorParam->isA()) {
                umii = act::ActorParam::sDummyResources.mUMii;
                if (!umii)
                    umii = mActorParam->getRes().mUMii;
            }

            if (umii) {
                applyResParameterArchive(umii->getArchive());

                static const char* voice_types[2] = {
                    "Hylia_Man_Young_Normal04",
                    "Hylia_Woman_Young_Normal04",
                };
                personal.voice_type.ref() = voice_types[isFemale()];
            } else {
                act::ActorParamMgr::instance()->unloadParam(mActorParam);
                mActorParam = nullptr;
                mResHandle.requestUnload();
            }
        }
    }

    if (korok.mask.ref() == Korok::Mask_Random)
        korok.mask = sead::GlobalRandom::instance()->getU32(Korok::Mask_Random);

    if (korok.skin_color.ref() == Korok::SkinColor_Random)
        korok.skin_color = sead::GlobalRandom::instance()->getU32(Korok::SkinColor_Random);

    if (korok.left_plant.ref() == Korok::LeftPlant_Random)
        korok.left_plant = sead::GlobalRandom::instance()->getU32(Korok::LeftPlant_Random);

    if (korok.right_plant.ref() == Korok::RightPlant_Random)
        korok.right_plant = sead::GlobalRandom::instance()->getU32(Korok::RightPlant_Random);
}

bool UMii::isFemale() const {
    return personal.sex_age.ref() > Personal::SexAge_OldMan;
}

int UMii::getHeightWeightIndex() const {
    return 3 * *body.height + *body.weight;
}

UMii::Personal::Age UMii::getAge() const {
    if (getSexAge() == Personal::SexAge_Boy || getSexAge() == Personal::SexAge_Girl)
        return Personal::Age_Child;

    if (getSexAge() == Personal::SexAge_Man || getSexAge() == Personal::SexAge_Woman)
        return Personal::Age_Adult;

    return Personal::Age_OldAdult;
}

void UMii::setKorokValues(const UMii::Korok& info) {
    korok.mask = *info.mask;
    korok.skin_color = *info.skin_color;
    korok.left_plant = *info.left_plant;
    korok.right_plant = *info.right_plant;
}

int UMii::sub_7100F4BE94() const {
    const auto age = getAge();

    if (age == Personal::Age_Child)
        return 0;

    if (age == Personal::Age_OldAdult)
        return 3;

    if (*body.race == Body::Race_Gerudo) {
        if (*ffsd.no_use_ffsd) {
            if (*common.is_mid_age)
                return 1;
        } else {
            if (*body.number == 1)
                return 1;
        }
    }

    return isFemale() + 1;
}

int UMii::sub_7100F4BF0C() const {
    switch (getSexAge()) {
    case Personal::SexAge_Boy:
        return 0;
    case Personal::SexAge_Man:
        return 1;
    case Personal::SexAge_OldMan:
    case Personal::SexAge_Woman:
        return 2;
    case Personal::SexAge_Girl:
        return 0;
    default:
        return 2;
    }
}

}  // namespace ksys::mii
