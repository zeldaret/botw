#include "KingSystem/Map/mapPlacementData.h"

#include "KingSystem/Map/mapMubinIter.h"
#include "KingSystem/Map/mapLazyTraverseList.h"

#include <math/seadMatrix.h>

namespace ksys::map {

s32 PlacementData::Unknown2::_298_idx = 0;
sead::TypedBitFlag<PlacementData::UnkFlag> PlacementData::unkFlag;

PlacementData::PlacementData() {
    _8.reset();
    playerPos = sead::Vector3f::zero;
    _29c54 = 0;

    if (objects && !objects->empty()) {
        unkFlag.set(UnkFlag::_80);
    }

    mJudgeArea.reset();
    _2a468.reset();
    _2a4ec.reset();
    _2d5c4 = 0.0f;
    _2acf0.reset();
    _2adc0_count = 0;
    _2adb8 = nullptr;
    mFlags.set(Flag::_10);
}

//#ifdef NON_MATCHING
bool PlacementData::parseObj(const sead::SafeString& unitConfigName, const MubinIter& objIter) {
    if (unitConfigName == "AreaCulling_InnerHide") {
        auto& area = _8.create();
        SRT srt;
        objIter.getSRT(&srt);

        bool hide = true;
        objIter.tryGetParamBoolByKey(&hide, "HideOutSide");
        area.params.hideOutSide = hide;

        s32 culling = 0;
        objIter.tryGetIntByKey(&culling, "CullingOption");
        switch (static_cast<Unknown1::Culling>(culling)) {
            case Unknown1::Culling::_0:
                area.params.culling = Unknown1::CullingType::None;
                break;
            case Unknown1::Culling::_1:
                area.params.culling = Unknown1::CullingType::Culling_1;
                break;
            case Unknown1::Culling::_2:
                area.params.culling = Unknown1::CullingType::Culling_3;
                break;
            case Unknown1::Culling::_3:
                area.params.culling = Unknown1::CullingType::Culling_F;
                break;
            case Unknown1::Culling::_4:
                area.params.culling = Unknown1::CullingType::Culling_1F;
                break;
            case Unknown1::Culling::_5:
                area.params.culling = Unknown1::CullingType::Culling_33;
                break;
            case Unknown1::Culling::_6:
                area.params.culling = Unknown1::CullingType::Culling_3B;
                break;
            case Unknown1::Culling::_7:
                area.params.culling = Unknown1::CullingType::Culling_1B;
                break;
            case Unknown1::Culling::_8:
                area.params.culling = Unknown1::CullingType::Culling_18;
                break;
            case Unknown1::Culling::_9:
                area.params.culling = Unknown1::CullingType::Culling_10;
                break;
            case Unknown1::Culling::_A:
                area.params.culling = Unknown1::CullingType::Culling_13;
                break;
            case Unknown1::Culling::_B:
                area.params.culling = Unknown1::CullingType::Culling_43;
                break;
            case Unknown1::Culling::_C:
                area.params.culling = Unknown1::CullingType::Culling_9B;
                break;
            
            default: break;
        }

        bool connect;
        objIter.tryGetBoolByKey(&connect, "IsConnectNeighborArea");
        area.params.isConnectNeighborArea = connect;

        area.hideRoomNum = 0xFF;
        objIter.tryGetParamUInt8ByKey(&area.hideRoomNum, "HideRoomNum");

        bool weirdCheck = false;
        // is this some sort of hack?
        if (srt.translate.x > -440.0f && srt.translate.x < -436.0f && srt.translate.z > -1036.0f && srt.translate.z < -1032.0f) {
            srt.scale.x = 27.863f;
            srt.translate.x = -439.24f;
            weirdCheck = true;
            srt.translate.z = -1033.4f;
            srt.scale.z = 40.908f;
        }
        
        area.translate = srt.translate;
        
        float scale = sead::Mathf::max3(srt.scale.x, srt.scale.y, srt.scale.z); // same logic
        
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
        area.base = Axis{ srt.scale };
        area.calc = Axis{ srt.scale + sead::Vector3f{ calcXPlus, calcYPlus, calcZPlus }, srt.scale + sead::Vector3f{ calcXMinus, calcYMinus, calcZMinus }};
        area.load = Axis{ srt.scale + sead::Vector3f{ loadXPlus, loadYPlus, loadZPlus }, srt.scale + sead::Vector3f{ loadXMinus, loadYMinus, loadZMinus }};
        area._d8 = Axis{ -sead::Vector3f::ones };

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
        if (_2980c._298_idx > 25) {  // this if statement has ++ but this structure makes more sense
            return true;
        }

        auto& area = _2980c._298[_2980c._298_idx++];
        SRT srt;

        objIter.getSRT(&srt);
        area.translate = srt.translate;
        area.scale = srt.scale.x;
        return true;
    } else if (unitConfigName.include("AreaCulling_TwinsHide")) {
        Unknown1* area;
        if (unitConfigName.include("Alpha")) {
            area = &_2980c.alpha; // 2980C
        } else if (unitConfigName.include("Omega")) {
            area = &_2980c.omega; // 29958
        } else {
            return true;
        }

        SRT srt;
        objIter.getSRT(&srt);
        area->translate = srt.translate;
        
        area->base = Axis{ srt.scale };
        area->calc = Axis{ srt.scale };
        area->load = Axis{ -sead::Vector3f::ones };
        area->_d8 = Axis{ -sead::Vector3f::ones };

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
    } else if (unitConfigName == "AreaCulling_JudgeArea") {
        SRT srt;
        auto& area = mJudgeArea.create();

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
                    area.parentIds.create() = _id;
                }
            }
        }

        return true;
    } else if (unitConfigName.include("AreaCulling_")) {  // only InnerOn?
        auto& area = _2a4ec.create();
        SRT srt;

        area.bb.set(srt.translate - srt.scale, srt.translate + srt.scale);
        objIter.tryGetParamUIntByKey(&area.id, "HashId");

        const char* param;
        if (objIter.tryGetParamStringByKey(&param, "UniqueName")) {
            if (sead::SafeString(param) == "LoadOpt") {
                area.type = GeneralArea::Type::LoadOpt;

                auto& subArea = _2acf0.create();
                subArea.parentArea = &area;
                subArea.id = "Demo102_0";
            } else {
                area.type = GeneralArea::Type::None;

                auto& subArea = mJudgeArea.create();
                sead::Vector3f offset { 20.0f, 0.0f, 20.0f };
                subArea.bb.set(srt.translate - srt.scale - offset, srt.translate + srt.scale + offset);
                subArea.parentIds.create() = 0;
                subArea.parentAreas[0] = &area;
            }
        }

        return true;
    } else if (unitConfigName == "FarModelCullingArea") {
        auto& area = _2adc0[_2adc0_count++];
        SRT srt;

        objIter.getSRT(&srt);
        area.translate = srt.translate;
        area.rotate = srt.rotate;
        area.scale = srt.scale;
        area.id.format("Area_%04d", _2adc0.size() - 1);

        return true;
    }

    return false;
}
//#endif

/*
void _d24400() {
    FarModelCullMgr* v1 = Graphics::sInstance->farModelCullMgr;
    if (v1 && *(v1 + 0x130) <= 0 && !_2adc0.empty()) {
        for (size_t i = 0; i < _2adc0.size(); ++i) {
            sub_7100EFDCF8(v1, _2adc0.data[i]); 
        }
    }
}
*/

}  // namespace ksys::map