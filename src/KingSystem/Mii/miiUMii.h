#pragma once

#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterIO.h>
#include <agl/Utils/aglParameterObj.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
class ActorParam;
}  // namespace ksys::act

namespace ksys::mii {

class UMiiBase {
public:
    virtual ~UMiiBase() = default;
};

class UMii : public agl::utl::IParameterIO, public UMiiBase {
public:
    struct FFSD : agl::utl::ParameterObj {
        enum Type {
            Type_0 = 0,
            Type_1 = 1,
        };

        agl::utl::Parameter<bool> no_use_ffsd;
        agl::utl::Parameter<int> type;
    };
    KSYS_CHECK_SIZE_NX150(FFSD, 0x70);

    struct Body : agl::utl::ParameterObj {
        enum Race {
            Race_Hylian = 0,
            Race_Korok = 1,
            Race_Goron = 2,
            Race_Sheikah = 3,
            Race_Gerudo = 4,
            Race_Zora = 5,
            Race_Rito = 6,
        };

        enum Type {
            Type_C = 0,
            Type_N = 1,
            Type_T = 2,
            Type_S = 3,
            Type_SK = 4,
        };

        agl::utl::Parameter<int> race;
        agl::utl::Parameter<int> type;
        agl::utl::Parameter<int> number;
        agl::utl::Parameter<int> weight;
        agl::utl::Parameter<int> height;
    };
    KSYS_CHECK_SIZE_NX150(Body, 0xd0);

    struct Personal : agl::utl::ParameterObj {
        enum SexAge {
            SexAge_Boy = 0,
            SexAge_Man = 1,
            SexAge_OldMan = 2,
            SexAge_Girl = 3,
            SexAge_Woman = 4,
            SexAge_OldWoman = 5,
        };

        enum Age {
            Age_Child = 0,
            Age_Adult = 1,
            Age_OldAdult = 2,
        };

        agl::utl::Parameter<int> sex_age;
        agl::utl::Parameter<int> fav_color;
        agl::utl::Parameter<int> sub_color_1;
        agl::utl::Parameter<int> sub_color_2;
        agl::utl::Parameter<int> head_fav_color;
        agl::utl::Parameter<int> shoulder_fav_color;
        agl::utl::Parameter<int> shoulder_sub_color_1;
        agl::utl::Parameter<sead::SafeString> personality;
        agl::utl::Parameter<sead::SafeString> voice_type;
    };
    KSYS_CHECK_SIZE_NX150(Personal, 0x160);

    struct Common : agl::utl::ParameterObj {
        agl::utl::Parameter<int> backpack;
        agl::utl::Parameter<int> hat;
        agl::utl::Parameter<bool> no_hat_always;
        agl::utl::Parameter<int> body_correct;
        agl::utl::Parameter<bool> is_mid_age;
        agl::utl::Parameter<float> rot_cravicle;
        agl::utl::Parameter<float> rot_arm;
        agl::utl::Parameter<float> rot_leg;
        agl::utl::Parameter<float> rot_crotch;
    };
    KSYS_CHECK_SIZE_NX150(Common, 0x150);

    struct Shape : agl::utl::ParameterObj {
        agl::utl::Parameter<int> jaw;
        agl::utl::Parameter<int> wrinkle;
        agl::utl::Parameter<int> make;
        agl::utl::Parameter<float> trans_v;
        agl::utl::Parameter<float> scale;
        agl::utl::Parameter<int> skin_color;
    };
    KSYS_CHECK_SIZE_NX150(Shape, 0xf0);

    struct Hair : agl::utl::ParameterObj {
        enum Type {
            Type_Invalid = 0x21,
        };

        agl::utl::Parameter<int> type;
        agl::utl::Parameter<int> color;
        agl::utl::Parameter<bool> flip;
    };
    KSYS_CHECK_SIZE_NX150(Hair, 0x90);

    struct Eye : agl::utl::ParameterObj {
        agl::utl::Parameter<int> type;
        agl::utl::Parameter<int> color;
        agl::utl::Parameter<float> trans_u;
        agl::utl::Parameter<float> trans_v;
        agl::utl::Parameter<float> rotate;
        agl::utl::Parameter<float> scale;
        agl::utl::Parameter<float> aspect;
        agl::utl::Parameter<float> eyeball_trans_u;
        agl::utl::Parameter<float> eyeball_trans_v;
        agl::utl::Parameter<float> eyeball_scale;
        agl::utl::Parameter<int> highlight_bright;
        float highlight_value;
    };
    KSYS_CHECK_SIZE_NX150(Eye, 0x198);

    struct EyeCtrl : agl::utl::ParameterObj {
        agl::utl::Parameter<sead::Vector3f> base_offset;
        agl::utl::Parameter<float> translim_out;
        agl::utl::Parameter<float> translim_in;
        agl::utl::Parameter<float> translim_d;
        agl::utl::Parameter<float> translim_u;
        agl::utl::Parameter<float> neck_offset_ud;
    };
    KSYS_CHECK_SIZE_NX150(EyeCtrl, 0xf8);

    struct Eyebrow : agl::utl::ParameterObj {
        agl::utl::Parameter<int> type;
        agl::utl::Parameter<int> color;
        agl::utl::Parameter<float> trans_u;
        agl::utl::Parameter<float> trans_v;
        agl::utl::Parameter<float> rotate;
        agl::utl::Parameter<float> scale;
        agl::utl::Parameter<float> aspect;
    };
    KSYS_CHECK_SIZE_NX150(Eyebrow, 0x110);

    struct Nose : agl::utl::ParameterObj {
        agl::utl::Parameter<int> type;
        agl::utl::Parameter<float> trans_v;
        agl::utl::Parameter<float> scale;
    };
    KSYS_CHECK_SIZE_NX150(Nose, 0x90);

    struct Mouth : agl::utl::ParameterObj {
        agl::utl::Parameter<int> type;
        agl::utl::Parameter<int> color;
        agl::utl::Parameter<float> trans_v;
        agl::utl::Parameter<float> scale;
        agl::utl::Parameter<float> aspect;
    };
    KSYS_CHECK_SIZE_NX150(Mouth, 0xd0);

    struct Beard : agl::utl::ParameterObj {
        agl::utl::Parameter<int> mustache;
        agl::utl::Parameter<float> scale;
        agl::utl::Parameter<int> type;
        agl::utl::Parameter<int> color;
    };
    KSYS_CHECK_SIZE_NX150(Beard, 0xb0);

    struct Glass : agl::utl::ParameterObj {
        agl::utl::Parameter<int> type;
        agl::utl::Parameter<int> color;
    };
    KSYS_CHECK_SIZE_NX150(Glass, 0x70);

    struct Korok : agl::utl::ParameterObj {
        enum Mask {
            Mask_Random = 9,
        };

        enum SkinColor {
            SkinColor_Random = 5,
        };

        enum LeftPlant {
            LeftPlant_Random = 3,
        };

        enum RightPlant {
            RightPlant_Random = 3,
        };

        agl::utl::Parameter<int> mask;
        agl::utl::Parameter<int> skin_color;
        agl::utl::Parameter<int> left_plant;
        agl::utl::Parameter<int> right_plant;
    };
    KSYS_CHECK_SIZE_NX150(Korok, 0xb0);

    struct Goron : agl::utl::ParameterObj {
        agl::utl::Parameter<int> skin_color;
    };
    KSYS_CHECK_SIZE_NX150(Goron, 0x50);

    struct Gerudo : agl::utl::ParameterObj {
        agl::utl::Parameter<int> hair;
        agl::utl::Parameter<int> hair_color;
        agl::utl::Parameter<int> glass;
        agl::utl::Parameter<int> glass_color;
        agl::utl::Parameter<int> skin_color;
        agl::utl::Parameter<int> lip_color;
    };
    KSYS_CHECK_SIZE_NX150(Gerudo, 0xf0);

    struct Rito : agl::utl::ParameterObj {
        agl::utl::Parameter<int> body_color;
        agl::utl::Parameter<int> hair_color;
    };
    KSYS_CHECK_SIZE_NX150(Rito, 0x70);

    struct Zora : agl::utl::ParameterObj {
        agl::utl::Parameter<int> body_color;
    };
    KSYS_CHECK_SIZE_NX150(Zora, 0x50);

    struct Face {
        Shape shape;
        Hair hair;
        Eye eye;
        EyeCtrl eye_ctrl;
        Eyebrow eyebrow;
        Nose nose;
        Mouth mouth;
        Beard beard;
        Glass glass;
    };
    KSYS_CHECK_SIZE_NX150(Face, 0x7a0);

    UMii();
    ~UMii() override;

    const sead::SafeString& getUser() const { return mUser; }
    const FFSD& getFFSD() const { return ffsd; }
    const Body& getBody() const { return body; }
    const Personal& getPersonal() const { return personal; }
    const Common& getCommon() const { return common; }
    const Face& getFace() const { return face; }
    const Korok& getKorok() const { return korok; }
    const Goron& getGoron() const { return goron; }
    const Gerudo& getGerudo() const { return gerudo; }
    const Rito& getRito() const { return rito; }
    const Zora& getZora() const { return zora; }

    void load(agl::utl::ResParameterArchive archive, const sead::SafeString& user,
              const u32& load_req_c);

    bool isFemale() const;
    int getHeightWeightIndex() const;
    Personal::SexAge getSexAge() const { return Personal::SexAge(*personal.sex_age); }
    Personal::Age getAge() const;
    void setKorokValues(const Korok& info);
    int sub_7100F4BE94() const;
    int sub_7100F4BF0C() const;

private:
    void reset();
    void doLoad(const u32& load_req_c);

    /// Name of the UMii config file ("user" in ActorLink).
    sead::FixedSafeString<64> mUser;

    FFSD ffsd;
    Body body;
    Personal personal;
    Common common;
    Face face;
    Korok korok;
    Goron goron;
    Gerudo gerudo;
    Rito rito;
    Zora zora;

    act::Actor* mActor = nullptr;
    act::ActorParam* mActorParam = nullptr;
    res::Handle mResHandle;
    sead::SafeString mActorName = sead::SafeString::cEmptyString;
};
KSYS_CHECK_SIZE_NX150(UMii, 0x10e0);

}  // namespace ksys::mii
