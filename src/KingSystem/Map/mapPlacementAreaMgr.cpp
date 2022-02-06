#include "KingSystem/Map/mapPlacementAreaMgr.h"

#include "KingSystem/Map/mapLazyTraverseList.h"
#include "KingSystem/Map/mapMubinIter.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"

#include <math/seadMatrix.h>

namespace ksys::map {

static s32 mNpc_count = 0;

enum class UnkFlag : u8 {
    _1 = 1 << 0,
    _2 = 1 << 1,
    _4 = 1 << 2,
    _20 = 1 << 5,
    _40 = 1 << 6,
    _80 = 1 << 7
};
static sead::TypedBitFlag<UnkFlag> unkFlag;

static sead::SafeArray<float, 26> mNpcScales = {
    {0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.85f, 0.6f, 0.75f, 0.6f, 0.6f,  0.6f, 0.6f,
     0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f,  0.6f, 0.6f,  0.6f, 0.75f, 0.6f, 0.6f}};

// NON_MATCHING: weird memsets, hard to replicate
PlacementAreaMgr::PlacementAreaMgr() {
    mInnerHide_count = 0;
    playerPos = sead::Vector3f::zero;
    mActiveNpc = 0;

    if (objects && !objects->empty()) {
        unkFlag.set(UnkFlag::_80);
    }

    mJudgeArea_count = 0;
    _2a468_count = 0;
    mGeneralAreas_count = 0;
    _2d5c4 = 0.0f;
    mOptAreas_count = 0;
    mFarModels_count = 0;
    mIntroArea = nullptr;
    mFlags.set(Flag::_10);
}

PlacementAreaMgr::~PlacementAreaMgr() {
    mNpc_count = 0;
}

// NON_MATCHING: I'm just bad but should be a template to try and fix
bool PlacementAreaMgr::parseAreas(const sead::SafeString& unitConfigName,
                                  const MubinIter& objIter) {
    if (unitConfigName == "AreaCulling_InnerHide") {
        auto& area = mInnerHide[mInnerHide_count++];
        SRT srt;
        objIter.getSRT(&srt);

        bool hide = true;
        objIter.tryGetParamBoolByKey(&hide, "HideOutSide");
        area.params.hideOutSide = hide;

        s32 culling = 0;
        objIter.tryGetIntByKey(&culling, "CullingOption");
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
        objIter.tryGetBoolByKey(&connect, "IsConnectNeighborArea");
        area.params.isConnectNeighborArea = connect;

        area.hideRoomNum = 0xFF;
        objIter.tryGetParamUInt8ByKey(&area.hideRoomNum, "HideRoomNum");

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
        objIter.tryGetParamFloatByKey(&calcXPlus, "CalcMarginXPlus");
        float calcXMinus = -1.0f;
        objIter.tryGetParamFloatByKey(&calcXMinus, "CalcMarginXMinus");
        float calcYPlus = -1.0f;
        objIter.tryGetParamFloatByKey(&calcYPlus, "CalcMarginYPlus");
        float calcYMinus = -1.0f;
        objIter.tryGetParamFloatByKey(&calcYMinus, "CalcMarginYMinus");
        float calcZPlus = -1.0f;
        objIter.tryGetParamFloatByKey(&calcZPlus, "CalcMarginZPlus");
        float calcZMinus = -1.0f;
        objIter.tryGetParamFloatByKey(&calcZMinus, "CalcMarginZMinus");

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
        objIter.tryGetParamFloatByKey(&loadXPlus, "LoadMarginXPlus");
        float loadXMinus = -1.0f;
        objIter.tryGetParamFloatByKey(&loadXMinus, "LoadMarginXMinus");
        float loadYPlus = -1.0f;
        objIter.tryGetParamFloatByKey(&loadYPlus, "LoadMarginYPlus");
        float loadYMinus = -1.0f;
        objIter.tryGetParamFloatByKey(&loadYMinus, "LoadMarginYMinus");
        float loadZPlus = -1.0f;
        objIter.tryGetParamFloatByKey(&loadZPlus, "LoadMarginZPlus");
        float loadZMinus = -1.0f;
        objIter.tryGetParamFloatByKey(&loadZMinus, "LoadMarginZMinus");

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
    } else if (unitConfigName == "AreaCulling_OuterNPCMementary") {
        if (mNpc_count > 25) {  // this if statement has ++ but this structure makes more sense
            return true;
        }

        auto& area = mNpc[mNpc_count++];
        SRT srt;

        objIter.getSRT(&srt);
        area.mTranslate = srt.translate;
        area.mScale = srt.scale.x;
        return true;
    } else if (unitConfigName.include("AreaCulling_TwinsHide")) {  // no objects
        Unknown1* area;
        if (unitConfigName.include("Alpha")) {
            area = &alpha;  // 2980C
        } else if (unitConfigName.include("Omega")) {
            area = &omega;  // 29958
        } else {
            return true;
        }

        SRT srt;
        objIter.getSRT(&srt);
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

        unkFlag.set(UnkFlag::_40);
        return true;
    } else if (unitConfigName == "AreaCulling_JudgeArea") {  // no objects
        SRT srt;
        auto& area = mJudgeArea[mJudgeArea_count++];

        objIter.getSRT(&srt);
        area.bb.set(srt.translate - srt.scale, srt.translate + srt.scale);

        MubinIter links;
        if (!objIter.tryGetParamIterByKey(&links, "LinksToObj")) {
            return true;
        }

        for (int i = 0; i < links.getSize(); ++i) {
            MubinIter iter;
            if (links.tryGetIterByIndex(&iter, i)) {
                u32 _id = 0;
                if (iter.tryGetParamUIntByKey(&_id, "DestUnitHashId")) {
                    area.parentIds[area.parentCount++] = _id;
                }
            }
        }

        return true;
    } else if (unitConfigName.include("AreaCulling_")) {  // only InnerOn?
        auto& area = mGeneralAreas[mGeneralAreas_count++];
        SRT srt;

        objIter.getSRT(&srt);
        area.bb.set(srt.translate - srt.scale, srt.translate + srt.scale);
        objIter.tryGetParamUIntByKey(&area.id, "HashId");

        area.type = GeneralArea::Type::None;

        const char* param = nullptr;
        if (objIter.tryGetParamStringByKey(&param, "UniqueName")) {
            if (sead::SafeString(param) == "LoadOpt") {
                area.type = GeneralArea::Type::LoadOpt;
            }
        }

        if (area.type == GeneralArea::Type::LoadOpt) {
            auto& subArea = mOptAreas[mOptAreas_count++];
            subArea.parentArea = &area;
            subArea.id = "Demo102_0";
        } else {
            auto& subArea = mJudgeArea[mJudgeArea_count++];
            sead::Vector3f offset{20.0f, 0.0f, 20.0f};
            subArea.bb.set(srt.translate - srt.scale - offset, srt.translate + srt.scale + offset);
            subArea.parentIds[subArea.parentCount++] = 0;
            subArea.parentAreas[0] = &area;
        }

        return true;
    } else if (unitConfigName == "FarModelCullingArea") {
        auto& area = mFarModels[mFarModels_count++];
        SRT srt;

        objIter.getSRT(&srt);
        area.translate = srt.translate;
        area.rotate = srt.rotate;
        area.scale = srt.scale;
        area.id.format("Area_%04d", mFarModels.size() - 1);

        return true;
    }

    return false;
}

PlacementAreaMgr::GeneralArea* PlacementAreaMgr::findGeneralArea(const u32& id) {
    for (int i = 0; i < mGeneralAreas_count; i++) {
        if (mGeneralAreas[i].id == id) {
            return &mGeneralAreas[i];
        }
    }

    return nullptr;
}

// NON_MATCHING: stack doesn't match, not sure if that's due to the first loop
void PlacementAreaMgr::x() {
    unkFlag.set(UnkFlag::_20);
    unkFlag.set(UnkFlag::_4);
    unkFlag.set(UnkFlag::_2);
    unkFlag.set(UnkFlag::_1);

    for (int i = 0; i < mInnerHide_count; i++) {
        auto& area = mInnerHide[i];

        area._12c = isInsideNpcIdx(area.translate);
        area._130_count = 0;
    }

    for (int i = 0; i < mInnerHide_count; i++) {
        auto& area = mInnerHide[i];

        if (area.hideRoomNum == 0xFF) {
            continue;
        }

        for (int j = 0; j < mInnerHide_count; j++) {
            auto& subarea = mInnerHide[j];

            if (i != j) {
                if (subarea.hideRoomNum != 0xFF && area._12c == subarea._12c &&
                    area.hideRoomNum == subarea.hideRoomNum) {
                    area._130[area._130_count++] = j;
                    break;
                }
            }
        }
    }

    for (int i = 0; i < mInnerHide_count; i++) {
        auto& area = mInnerHide[i];

        if (area.params.isConnectNeighborArea) {
            for (int j = 0; j < mInnerHide_count; j++) {
                auto& subarea = mInnerHide[j];

                if (subarea.params.isConnectNeighborArea && i != j) {
                    if (area._12c == subarea._12c && (x_0(i, j) || x_0(j, i))) {
                        addLinkPair(i, j);
                    }
                }
            }
        }
    }

    alpha._12c = -1;
    omega._12c = -1;
    for (int i = 0; i < mJudgeArea_count; i++) {
        auto& judgeArea = mJudgeArea[i];
        for (int j = 0; j < judgeArea.parentCount; j++) {
            auto& id = judgeArea.parentIds[j];

            if (id == 0) {
                continue;
            }

            // doesn't necessarily exist, done to try and match
            judgeArea.parentAreas[j] = findGeneralArea(id);
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

// too specific for sead
float sqXZDistance(const sead::Vector3f& a, const sead::Vector3f& b) {
    return sead::Mathf::square(a.x - b.x) + sead::Mathf::square(a.z - b.z);
}

bool PlacementAreaMgr::insideInnerHideTrans(const int& idx) {
    if (mActiveNpc == mInnerHide[idx]._12c) {
        if (mActiveNpc == 5) {
            return true;
        }

        if (mActiveNpc != 6) {
            if (mFlags.isOn(Flag::FinalTrial) || mFlags.isOn(Flag::_4000)) {
                return true;
            }

            if (mFlags.isOff(Flag::Remains)) {
                if (mFlags.isOn(Flag::AocField)) {
                    return true;
                }

                if (mActiveNpc != 21 && mActiveNpc != 16 && mActiveNpc != 14 && mActiveNpc != 7 &&
                    mActiveNpc != 2 && mActiveNpc != 0) {
                    return sqXZDistance(playerPos, mInnerHide[idx].translate) <
                           sead::Mathf::square(200.0f);
                }
            }
        }
        return sqXZDistance(playerPos, mInnerHide[idx].translate) < sead::Mathf::square(500.0f);
    }
    return sqXZDistance(playerPos, mInnerHide[idx].translate) < sead::Mathf::square(1000.0f);
}

bool PlacementAreaMgr::insideInnerHideBase(const int& idx) {
    for (int i = 0; i < 6; i++) {
        if ((playerPos - mInnerHide[idx].base[i]).dot(mInnerHide[idx]._d8[i]) < 0.0f) {
            return false;
        }
    }

    return true;
}

bool PlacementAreaMgr::insideInnerHideCalc(const int& idx) {
    for (int i = 0; i < 6; i++) {
        if ((playerPos - mInnerHide[idx].calc[i]).dot(mInnerHide[idx]._d8[i]) < 0.0f) {
            return false;
        }
    }

    return true;
}

bool PlacementAreaMgr::insideInnerHideLoad(const int& idx) {
    for (int i = 0; i < 6; i++) {
        if ((playerPos - mInnerHide[idx].load[i]).dot(mInnerHide[idx]._d8[i]) < 0.0f) {
            return false;
        }
    }

    return true;
}

bool PlacementAreaMgr::insideInnerHideBase(const sead::Vector3f& pos, const float& distFromFace,
                                           const int& idx) {
    for (int i = 0; i < 6; i++) {
        if ((pos - mInnerHide[idx].base[i]).dot(mInnerHide[idx]._d8[i]) <= distFromFace) {
            return false;
        }
    }

    return true;
}

bool PlacementAreaMgr::insideInnerHideCalc(const sead::Vector3f& pos, const float& distFromFace,
                                           const int& idx) {
    for (int i = 0; i < 6; i++) {
        if ((pos - mInnerHide[idx].calc[i]).dot(mInnerHide[idx]._d8[i]) <= distFromFace) {
            return false;
        }
    }

    return true;
}

bool PlacementAreaMgr::insideAlphaBase() {
    for (int i = 0; i < 6; i++) {
        if ((playerPos - alpha.base[i]).dot(alpha._d8[i]) < 0.0f) {
            return false;
        }
    }

    return true;
}

bool PlacementAreaMgr::insideAlphaBase(const sead::Vector3f& pos, const float& distFromFace) {
    for (int i = 0; i < 6; i++) {
        if ((pos - alpha.base[i]).dot(alpha._d8[i]) < distFromFace) {
            return false;
        }
    }

    return true;
}

bool PlacementAreaMgr::insideOmegaBase() {
    for (int i = 0; i < 6; i++) {
        if ((playerPos - omega.base[i]).dot(omega._d8[i]) < 0.0f) {
            return false;
        }
    }

    return true;
}

bool PlacementAreaMgr::insideOmegaBase(const sead::Vector3f& pos, const float& distFromFace) {
    for (int i = 0; i < 6; i++) {
        if ((pos - omega.base[i]).dot(omega._d8[i]) < distFromFace) {
            return false;
        }
    }

    return true;
}

bool PlacementAreaMgr::isPlayerInsideNpc(const sead::Vector3f& pos) {
    // matches with 2 && but this looks cleaner
    if (mActiveNpc >= 0 && !isInsideNpc(pos)) {
        if (sqXZDistance(playerPos, mNpc[mActiveNpc].mTranslate) <
            (mNpc[mActiveNpc].mScale * mNpcScales[mActiveNpc])) {
            return true;
        }
    }

    return false;
}

// maybe doesn't exist?
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
    if (unkFlag.isOff(UnkFlag::_4)) {
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

void PlacementAreaMgr::loadDemoCulling(const sead::SafeString& demoName) {
    mIntroArea = nullptr;

    for (int i = 0; i < mOptAreas_count; ++i) {
        auto& area = mOptAreas[i];

        bool loaded = false;
        if (area.id == demoName) {
            loaded = true;
            mIntroArea = &area;
        }
        area.parentArea->loaded = loaded;
    }
}

void PlacementAreaMgr::unloadDemoCulling() {
    mIntroArea = nullptr;

    for (int i = 0; i < mOptAreas_count; ++i) {
        mOptAreas[i].parentArea->loaded = false;
    }
}

}  // namespace ksys::map