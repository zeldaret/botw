#include "KingSystem/Map/mapPlacementAreaMgr.h"

#include "KingSystem/Map/mapLazyTraverseList.h"
#include "KingSystem/Map/mapMubinIter.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"
#include "KingSystem/Utils/MathUtil.h"

#include <math/seadMatrix.h>

namespace ksys::map {

static s32 s_npc_count = 0;

enum class UnkFlag : u8 {
    _1 = 1 << 0,
    _2 = 1 << 1,
    _4 = 1 << 2,
    _20 = 1 << 5,
    _40 = 1 << 6,
    _80 = 1 << 7
};
static sead::TypedBitFlag<UnkFlag> s_unk_flag;

static sead::SafeArray<float, 26> s_npc_scales = {
    {0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.85f, 0.6f, 0.75f, 0.6f, 0.6f,  0.6f, 0.6f,
     0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f,  0.6f, 0.6f,  0.6f, 0.75f, 0.6f, 0.6f}};

// NON_MATCHING: weird memsets, hard to replicate
PlacementAreaMgr::PlacementAreaMgr() {
    mInnerHideCount = 0;
    mPlayerPos = sead::Vector3f::zero;
    mActiveNpc = 0;

    if (mObjects && !mObjects->empty()) {
        s_unk_flag.set(UnkFlag::_80);
    }

    mJudgeAreaCount = 0;
    _2a468Count = 0;
    mGeneralAreasCount = 0;
    _2d5c4 = 0.0f;
    mOptAreasCount = 0;
    mFarModelsCount = 0;
    mIntroArea = nullptr;
    mFlags.set(Flag::_10);
}

PlacementAreaMgr::~PlacementAreaMgr() {
    s_npc_count = 0;
}

// NON_MATCHING: many various parts don't match but should be a template
bool PlacementAreaMgr::parseAreas(const sead::SafeString& unit_config_name,
                                  const MubinIter& obj_iter) {
    if (unit_config_name == "AreaCulling_InnerHide") {
        auto& area = mInnerHide[mInnerHideCount++];
        SRT srt;
        obj_iter.getSRT(&srt);

        bool hide = true;
        obj_iter.tryGetParamBoolByKey(&hide, "HideOutSide");
        area.params.hide_out_side = hide;

        s32 culling = 0;
        obj_iter.tryGetIntByKey(&culling, "CullingOption");
        switch (static_cast<Unknown1::CullingOption>(culling)) {
        case Unknown1::CullingOption::_0:
            area.params.culling = Unknown1::CullingType::None;
            break;
        case Unknown1::CullingOption::_1:
            area.params.culling = Unknown1::CullingType::Culling_1;
            break;
        case Unknown1::CullingOption::_2:
            area.params.culling = Unknown1::CullingType::Culling_3;
            break;
        case Unknown1::CullingOption::_3:
            area.params.culling = Unknown1::CullingType::Culling_F;
            break;
        case Unknown1::CullingOption::_4:
            area.params.culling = Unknown1::CullingType::Culling_1F;
            break;
        case Unknown1::CullingOption::_5:
            area.params.culling = Unknown1::CullingType::Culling_33;
            break;
        case Unknown1::CullingOption::_6:
            area.params.culling = Unknown1::CullingType::Culling_3B;
            break;
        case Unknown1::CullingOption::_7:
            area.params.culling = Unknown1::CullingType::Culling_1B;
            break;
        case Unknown1::CullingOption::_8:
            area.params.culling = Unknown1::CullingType::Culling_18;
            break;
        case Unknown1::CullingOption::_9:
            area.params.culling = Unknown1::CullingType::Culling_10;
            break;
        case Unknown1::CullingOption::_A:
            area.params.culling = Unknown1::CullingType::Culling_13;
            break;
        case Unknown1::CullingOption::_B:
            area.params.culling = Unknown1::CullingType::Culling_43;
            break;
        case Unknown1::CullingOption::_C:
            area.params.culling = Unknown1::CullingType::Culling_9B;
            break;

        default:
            break;
        }

        bool connect;
        obj_iter.tryGetBoolByKey(&connect, "IsConnectNeighborArea");
        area.params.is_connect_neighbor_area = connect;

        area.hide_room_num = 0xFF;
        obj_iter.tryGetParamUInt8ByKey(&area.hide_room_num, "HideRoomNum");

        bool weirdCheck = false;
        // is this some sort of hack?
        if (srt.translate.x > -440.0f && srt.translate.x < -436.0f && srt.translate.z > -1036.0f &&
            srt.translate.z < -1032.0f) {
            srt.scale.x = 27.863f;
            srt.translate.x = -439.24f;
            weirdCheck = true;
            srt.translate.z = -1033.4f;
            srt.scale.z = 40.908f;
        }

        area.translate = srt.translate;

        float scale = sead::Mathf::max3(srt.scale.x, srt.scale.y, srt.scale.z);  // same logic

        float calcMaxSize = sead::Mathf::max(scale * 0.5f, 4.0f);
        float calcXPlus = -1.0f;
        obj_iter.tryGetParamFloatByKey(&calcXPlus, "CalcMarginXPlus");
        float calcXMinus = -1.0f;
        obj_iter.tryGetParamFloatByKey(&calcXMinus, "CalcMarginXMinus");
        float calcYPlus = -1.0f;
        obj_iter.tryGetParamFloatByKey(&calcYPlus, "CalcMarginYPlus");
        float calcYMinus = -1.0f;
        obj_iter.tryGetParamFloatByKey(&calcYMinus, "CalcMarginYMinus");
        float calcZPlus = -1.0f;
        obj_iter.tryGetParamFloatByKey(&calcZPlus, "CalcMarginZPlus");
        float calcZMinus = -1.0f;
        obj_iter.tryGetParamFloatByKey(&calcZMinus, "CalcMarginZMinus");

        if (weirdCheck) {
            calcXMinus = 3.0f;
        }

        if (calcXPlus < 0.0f) {
            calcXPlus = calcMaxSize;
        }
        if (calcXMinus < 0.0f) {
            calcXMinus = calcMaxSize;
        }
        if (calcYPlus < 0.0f) {
            calcYPlus = calcMaxSize;
        }
        if (calcYMinus < 0.0f) {
            calcYMinus = calcMaxSize;
        }
        if (calcZPlus < 0.0f) {
            calcZPlus = calcMaxSize;
        }
        if (calcZMinus < 0.0f) {
            calcZMinus = calcMaxSize;
        }

        float loadMaxSize = calcMaxSize * 1.75f;
        float loadXPlus = -1.0f;
        obj_iter.tryGetParamFloatByKey(&loadXPlus, "LoadMarginXPlus");
        float loadXMinus = -1.0f;
        obj_iter.tryGetParamFloatByKey(&loadXMinus, "LoadMarginXMinus");
        float loadYPlus = -1.0f;
        obj_iter.tryGetParamFloatByKey(&loadYPlus, "LoadMarginYPlus");
        float loadYMinus = -1.0f;
        obj_iter.tryGetParamFloatByKey(&loadYMinus, "LoadMarginYMinus");
        float loadZPlus = -1.0f;
        obj_iter.tryGetParamFloatByKey(&loadZPlus, "LoadMarginZPlus");
        float loadZMinus = -1.0f;
        obj_iter.tryGetParamFloatByKey(&loadZMinus, "LoadMarginZMinus");

        if (loadXPlus < 0.0f) {
            loadXPlus = loadMaxSize;
        }
        if (loadXMinus < 0.0f) {
            loadXMinus = loadMaxSize;
        }
        if (loadYPlus < 0.0f) {
            loadYPlus = loadMaxSize;
        }
        if (loadYMinus < 0.0f) {
            loadYMinus = loadMaxSize;
        }
        if (loadZPlus < 0.0f) {
            loadZPlus = loadMaxSize;
        }
        if (loadZMinus < 0.0f) {
            loadZMinus = loadMaxSize;
        }

        // same code in AreaCulling_TwinsHide
        area.base = Axis{srt.scale};
        area.calc = Axis{srt.scale + sead::Vector3f{calcXPlus, calcYPlus, calcZPlus},
                         srt.scale + sead::Vector3f{calcXMinus, calcYMinus, calcZMinus}};
        area.load = Axis{srt.scale + sead::Vector3f{loadXPlus, loadYPlus, loadZPlus},
                         srt.scale + sead::Vector3f{loadXMinus, loadYMinus, loadZMinus}};
        area._d8 = Axis{-sead::Vector3f::ones};

        sead::Matrix33f m;
        m.makeR(srt.rotate);

        for (size_t i = 0; i < 6; ++i) {
            area.base[i] = srt.translate + (m * area.base[i]);
            area.calc[i] = srt.translate + (m * area.calc[i]);
            area.load[i] = srt.translate + (m * area.load[i]);
            area._d8[i] = m * area._d8[i];
        }

        return true;
    } else if (unit_config_name == "AreaCulling_OuterNPCMementary") {
        if (s_npc_count > 25) {  // this if statement has ++ but this structure makes more sense
            return true;
        }

        auto& area = mNpc[s_npc_count++];
        SRT srt;

        obj_iter.getSRT(&srt);
        area.translate = srt.translate;
        area.scale = srt.scale.x;
        return true;
    } else if (unit_config_name.include("AreaCulling_TwinsHide")) {  // no objects
        Unknown1* area;
        if (unit_config_name.include("Alpha")) {
            area = &mAlpha;  // 2980C
        } else if (unit_config_name.include("Omega")) {
            area = &mOmega;  // 29958
        } else {
            return true;
        }

        SRT srt;
        obj_iter.getSRT(&srt);
        area->translate = srt.translate;

        area->base = Axis{srt.scale};
        area->calc = Axis{srt.scale};
        area->load = Axis{-sead::Vector3f::ones};
        area->_d8 = Axis{-sead::Vector3f::ones};

        sead::Matrix33f m;
        m.makeR(srt.rotate);

        for (size_t i = 0; i < 6; ++i) {
            area->base[i] = srt.translate + (m * area->base[i]);
            area->calc[i] = srt.translate + (m * area->calc[i]);
            area->load[i] = srt.translate + (m * area->load[i]);
            area->_d8[i] = m * area->_d8[i];
        }

        s_unk_flag.set(UnkFlag::_40);
        return true;
    } else if (unit_config_name == "AreaCulling_JudgeArea") {  // no objects
        SRT srt;
        auto& area = mJudgeArea[mJudgeAreaCount++];

        obj_iter.getSRT(&srt);
        area.bb.set(srt.translate - srt.scale, srt.translate + srt.scale);

        MubinIter links;
        if (!obj_iter.tryGetParamIterByKey(&links, "LinksToObj")) {
            return true;
        }

        for (int i = 0; i < links.getSize(); ++i) {
            MubinIter iter;
            if (links.tryGetIterByIndex(&iter, i)) {
                u32 _id = 0;
                if (iter.tryGetParamUIntByKey(&_id, "DestUnitHashId")) {
                    area.parent_ids[area.parent_count++] = _id;
                }
            }
        }

        return true;
    } else if (unit_config_name.include("AreaCulling_")) {  // only InnerOn?
        auto& area = mGeneralAreas[mGeneralAreasCount++];
        SRT srt;

        obj_iter.getSRT(&srt);
        area.bb.set(srt.translate - srt.scale, srt.translate + srt.scale);
        obj_iter.tryGetParamUIntByKey(&area.id, "HashId");

        area.type = GeneralArea::Type::None;

        const char* param = nullptr;
        if (obj_iter.tryGetParamStringByKey(&param, "UniqueName")) {
            if (sead::SafeString(param) == "LoadOpt") {
                area.type = GeneralArea::Type::LoadOpt;
            }
        }

        if (area.type == GeneralArea::Type::LoadOpt) {
            auto& subArea = mOptAreas[mOptAreasCount++];
            subArea.parent_area = &area;
            subArea.id = "Demo102_0";
        } else {
            auto& subArea = mJudgeArea[mJudgeAreaCount++];
            sead::Vector3f offset{20.0f, 0.0f, 20.0f};
            subArea.bb.set(srt.translate - srt.scale - offset, srt.translate + srt.scale + offset);
            subArea.parent_ids[subArea.parent_count++] = 0;
            subArea.parent_areas[0] = &area;
        }

        return true;
    } else if (unit_config_name == "FarModelCullingArea") {
        auto& area = mFarModels[mFarModelsCount++];
        SRT srt;

        obj_iter.getSRT(&srt);
        area.translate = srt.translate;
        area.rotate = srt.rotate;
        area.scale = srt.scale;
        area.id.format("Area_%04d", mFarModels.size() - 1);

        return true;
    }

    return false;
}

PlacementAreaMgr::GeneralArea* PlacementAreaMgr::findGeneralArea(const u32& id) {
    for (int i = 0; i < mGeneralAreasCount; i++) {
        if (mGeneralAreas[i].id == id) {
            return &mGeneralAreas[i];
        }
    }

    return nullptr;
}

// NON_MATCHING: stack doesn't match, not sure if that's due to the first loop
void PlacementAreaMgr::x() {
    s_unk_flag.set(UnkFlag::_20);
    s_unk_flag.set(UnkFlag::_4);
    s_unk_flag.set(UnkFlag::_2);
    s_unk_flag.set(UnkFlag::_1);

    for (int i = 0; i < mInnerHideCount; i++) {
        auto& area = mInnerHide[i];

        area._12c = isInsideNpcIdx(area.translate);
        area._130_count = 0;
    }

    for (int i = 0; i < mInnerHideCount; i++) {
        auto& area = mInnerHide[i];

        if (area.hide_room_num == 0xFF) {
            continue;
        }

        for (int j = 0; j < mInnerHideCount; j++) {
            auto& subarea = mInnerHide[j];

            if (i != j) {
                if (subarea.hide_room_num != 0xFF && area._12c == subarea._12c &&
                    area.hide_room_num == subarea.hide_room_num) {
                    area._130[area._130_count++] = j;
                    break;
                }
            }
        }
    }

    for (int i = 0; i < mInnerHideCount; i++) {
        auto& area = mInnerHide[i];

        if (area.params.is_connect_neighbor_area) {
            for (int j = 0; j < mInnerHideCount; j++) {
                auto& subarea = mInnerHide[j];

                if (subarea.params.is_connect_neighbor_area && i != j) {
                    if (area._12c == subarea._12c && (x_0(i, j) || x_0(j, i))) {
                        addLinkPair(i, j);
                    }
                }
            }
        }
    }

    mAlpha._12c = -1;
    mOmega._12c = -1;
    for (int i = 0; i < mJudgeAreaCount; i++) {
        auto& judgeArea = mJudgeArea[i];
        for (int j = 0; j < judgeArea.parent_count; j++) {
            auto& id = judgeArea.parent_ids[j];

            if (id == 0) {
                continue;
            }

            // doesn't necessarily exist, done to try and match
            judgeArea.parent_areas[j] = findGeneralArea(id);
        }
    }
}

void PlacementAreaMgr::Unknown1::addLink(const int& idx) {
    if (_130_count == 0) {
        _130[_130_count++] = idx;
    } else {
        // check to see if idx is in _130, add to end if not
        for (u8 i = 0; i < _130_count && _130[i] != idx; i++) {
            if (i == (_130_count - 1)) {
                _130[_130_count++] = idx;
                break;
            }
        }

        // weird logic because this would only trigger if _130_count was 6 in the loop
        if ((_130_count - 1) >= _130.size()) {
            --_130_count;
        }
    }
}

void PlacementAreaMgr::addLinkPair(const int& idx, const int& sub_idx) {
    mInnerHide[idx].addLink(sub_idx);
    mInnerHide[sub_idx].addLink(idx);
}

bool PlacementAreaMgr::insideInnerHideTrans(const int& idx) {
    if (mActiveNpc != mInnerHide[idx]._12c) {
        return util::sqXZDistance(mPlayerPos, mInnerHide[idx].translate) <
               sead::Mathf::square(1000.0f);
    }

    if (mActiveNpc == 5)
        return true;

    if (mActiveNpc == 6) {
        return util::sqXZDistance(mPlayerPos, mInnerHide[idx].translate) <
               sead::Mathf::square(500.0f);
    }

    if (mFlags.isOn(Flag::FinalTrial) || mFlags.isOn(Flag::_4000)) {
        return true;
    }

    if (mFlags.isOff(Flag::Remains)) {
        if (mFlags.isOn(Flag::AocField)) {
            return true;
        }

        if (mActiveNpc != 21 && mActiveNpc != 16 && mActiveNpc != 14 && mActiveNpc != 7 &&
            mActiveNpc != 2 && mActiveNpc != 0) {
            return util::sqXZDistance(mPlayerPos, mInnerHide[idx].translate) <
                   sead::Mathf::square(200.0f);
        }
    }

    return util::sqXZDistance(mPlayerPos, mInnerHide[idx].translate) < sead::Mathf::square(500.0f);
}

bool PlacementAreaMgr::insideInnerHideBase(const int& idx) {
    for (int i = 0; i < 6; i++) {
        if ((mPlayerPos - mInnerHide[idx].base[i]).dot(mInnerHide[idx]._d8[i]) < 0.0f) {
            return false;
        }
    }

    return true;
}

bool PlacementAreaMgr::insideInnerHideCalc(const int& idx) {
    for (int i = 0; i < 6; i++) {
        if ((mPlayerPos - mInnerHide[idx].calc[i]).dot(mInnerHide[idx]._d8[i]) < 0.0f) {
            return false;
        }
    }

    return true;
}

bool PlacementAreaMgr::insideInnerHideLoad(const int& idx) {
    for (int i = 0; i < 6; i++) {
        if ((mPlayerPos - mInnerHide[idx].load[i]).dot(mInnerHide[idx]._d8[i]) < 0.0f) {
            return false;
        }
    }

    return true;
}

bool PlacementAreaMgr::insideInnerHideBase(const sead::Vector3f& pos, const float& dist_from_face,
                                           const int& idx) {
    for (int i = 0; i < 6; i++) {
        if ((pos - mInnerHide[idx].base[i]).dot(mInnerHide[idx]._d8[i]) <= dist_from_face) {
            return false;
        }
    }

    return true;
}

bool PlacementAreaMgr::insideInnerHideCalc(const sead::Vector3f& pos, const float& dist_from_face,
                                           const int& idx) {
    for (int i = 0; i < 6; i++) {
        if ((pos - mInnerHide[idx].calc[i]).dot(mInnerHide[idx]._d8[i]) <= dist_from_face) {
            return false;
        }
    }

    return true;
}

bool PlacementAreaMgr::insideAlphaBase() {
    for (int i = 0; i < 6; i++) {
        if ((mPlayerPos - mAlpha.base[i]).dot(mAlpha._d8[i]) < 0.0f) {
            return false;
        }
    }

    return true;
}

bool PlacementAreaMgr::insideAlphaBase(const sead::Vector3f& pos, const float& dist_from_face) {
    for (int i = 0; i < 6; i++) {
        if ((pos - mAlpha.base[i]).dot(mAlpha._d8[i]) < dist_from_face) {
            return false;
        }
    }

    return true;
}

bool PlacementAreaMgr::insideOmegaBase() {
    for (int i = 0; i < 6; i++) {
        if ((mPlayerPos - mOmega.base[i]).dot(mOmega._d8[i]) < 0.0f) {
            return false;
        }
    }

    return true;
}

bool PlacementAreaMgr::insideOmegaBase(const sead::Vector3f& pos, const float& dist_from_face) {
    for (int i = 0; i < 6; i++) {
        if ((pos - mOmega.base[i]).dot(mOmega._d8[i]) < dist_from_face) {
            return false;
        }
    }

    return true;
}

bool PlacementAreaMgr::isPlayerInsideNpc(const sead::Vector3f& pos) {
    // matches with 2 && but this looks cleaner
    if (mActiveNpc >= 0 && !isInsideNpc(pos)) {
        if (util::sqXZDistance(mPlayerPos, mNpc[mActiveNpc].translate) <
            (mNpc[mActiveNpc].scale * s_npc_scales[mActiveNpc])) {
            return true;
        }
    }

    return false;
}

// used to try and simplify PlacementAreaMgr::x and PlacementAreaMgr::isInsideNpc logic
// doesn't seem to match so maybe remove after matching x?
s8 PlacementAreaMgr::isInsideNpcIdx(const sead::Vector3f& pos) {
    for (int i = 0; i < mNpc.size(); i++) {
        if (!mNpc[i].isInside(pos)) {
            continue;
        }

        if (i == 5) {
            if (mNpc[6].isInside(pos)) {
                continue;
            }
        }

        return i;
    }

    return -1;
}

bool PlacementAreaMgr::isInsideNpc(const sead::Vector3f& pos) {
    if (s_unk_flag.isOff(UnkFlag::_4)) {
        return false;
    }

    // XXX: what the heck Nintendo
    int i = 0;
    while (i < mNpc.size()) {
        if (i == 5) {
            if (mNpc[i].isInside(pos) && !mNpc[i + 1].isInside(pos)) {
                return true;
            }
        } else {
            if (mNpc[i].isInside(pos)) {
                return true;
            }
        }

        ++i;
    }

    return false;
}

void PlacementAreaMgr::loadDemoCulling(const sead::SafeString& demo_name) {
    mIntroArea = nullptr;

    for (int i = 0; i < mOptAreasCount; ++i) {
        auto& area = mOptAreas[i];

        bool loaded = false;
        if (area.id == demo_name) {
            loaded = true;
            mIntroArea = &area;
        }
        area.parent_area->loaded = loaded;
    }
}

void PlacementAreaMgr::unloadDemoCulling() {
    mIntroArea = nullptr;

    for (int i = 0; i < mOptAreasCount; ++i) {
        mOptAreas[i].parent_area->loaded = false;
    }
}

}  // namespace ksys::map