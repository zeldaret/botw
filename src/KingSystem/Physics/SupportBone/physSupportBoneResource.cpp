#include "KingSystem/Physics/SupportBone/physSupportBoneResource.h"

namespace ksys::phys {

SupportBoneResource::Bone::~Bone() = default;

SupportBoneResource::BaseBone::BaseBone()
    : bone(-1, "bone", "bone", this), aim(sead::Vector3f::ez, "aim", "aim", this),
      up(sead::Vector3f::ey, "up", "up", this), space(-1, "space", "space", this),
      base_rotate(sead::Quatf::unit, "base_rotate", "base_rotate", this),
      base_translate(sead::Vector3f::zero, "base_translate", "base_translate", this) {}

SupportBoneResource::SupportBone::SupportBone()
    : bendH(-1, "bendH", "bendH", this), bendV(-1, "bendV", "bendV", this),
      roll(-1, "roll", "roll", this), translateX(-1, "translateX", "translateX", this),
      translateY(-1, "translateY", "translateY", this),
      translateZ(-1, "translateZ", "translateZ", this) {}

SupportBoneResource::SupportBoneResource()
    : IParameterIO("physsb", 0), boneNum(0, "bone_num", "bone_num", &supportBoneHeader),
      connectionLinearNum(0, "connection_linear_num", "connection_linear_num", &supportBoneHeader),
      connectionCurveNum(0, "connection_curve_num", "connection_curve_num", &supportBoneHeader),
      outputSingleNum(0, "output_single_num", "output_single_num", &supportBoneHeader),
      outputDoubleNum(0, "output_double_num", "output_double_num", &supportBoneHeader),
      mainBoneNum(0, "main_bone_num", "main_bone__num", &supportBoneHeader),
      supportBoneNum(0, "support_bone_num", "support_bone__num", &supportBoneHeader) {
    addObj(&supportBoneHeader, "support_bone_header");
    addList(&supportBoneData, "support_bone_data");
}

SupportBoneResource::~SupportBoneResource() {
    freeBuffers();
}

void SupportBoneResource::freeBuffers() {
    boneBuffer.freeBuffer();
    connectionLinearBuffer.freeBuffer();
    connectionCurveBuffer.freeBuffer();
    outputSingleBuffer.freeBuffer();
    outputDoubleBuffer.freeBuffer();
    mainBoneBuffer.freeBuffer();
    supportBoneBuffer.freeBuffer();
}

bool uninlineAllocDoubleBuffer(sead::Buffer<ksys::phys::SupportBoneResource::OutputDouble>* buffer,
                               int size, sead::Heap* heap, s32 alignment = sizeof(void*)) {
    return buffer->allocBufferAssert(size, heap, alignment);
}

void SupportBoneResource::doCreate_(u8* data, u32 actualFileSize, sead::Heap* heap) {
    init(agl::utl::ResParameterArchive(data), heap);
}

float SupportBoneResource::somethingGetLinearConnection(u32 a2, float a3){
    sead::Vector2f slope_intercept = connectionLinearBuffer[a2].slope_intercept.ref();
    float result = slope_intercept.x * a3 + slope_intercept.y;
    return iscustomnan(result) ? 0.0f : result;
}

int SupportBoneResource::getSupportBoneIndexByName(const sead::SafeString& name){
    s32 support_bone_num = supportBoneNum.ref();
    for(s32 i=0;i<support_bone_num;i++){
        int bone_index = supportBoneBuffer[i].bone.ref();
        sead::SafeString bone_name = boneBuffer[bone_index].name.ref().cstr();
        if(name == bone_name)
            return i;
    }
    return -1;
}

//NON_MATCHING: Mismatches in the creation part of `connectionCurveList`
bool SupportBoneResource::init(agl::utl::ResParameterArchive archive, sead::Heap* heap) {
    agl::utl::ResParameterList param_list = archive.getRootList();
    const auto support_bone_list = param_list.getResParameterList(0);
    supportBoneHeader.applyResParameterObj(param_list.getResParameterObj(0));

    int bone_num = boneNum.ref();
    if (bone_num < 1)
        return false;
    supportBoneData.addList(&boneList, "bone_list");
    boneBuffer.allocBufferAssert(bone_num, heap);
    for (int i = 0; i < bone_num; i++) {
        auto bone_name = sead::FormatFixedSafeString<32>("bone_%d", i);
        boneList.addObj(&boneBuffer[i], bone_name);
        boneBuffer[i].name.init(sead::FixedSafeString<64>::cEmptyString, "name", "name",
                                &boneBuffer[i]);
    }

    int connection_linear_num = connectionLinearNum.ref();
    if (connection_linear_num > 0) {
        supportBoneData.addList(&connectionLinearList, "connection_linear_list");
        connectionLinearBuffer.allocBufferAssert(connection_linear_num, heap);

        for (int i = 0; i < connection_linear_num; i++) {
            auto connection_name = sead::FormatFixedSafeString<32>("connection_linear_%d", i);
            connectionLinearList.addObj(&connectionLinearBuffer[i], connection_name);
            connectionLinearBuffer[i].bone_attribute.init(
                0, "bone_attribute", "bone_attribute",
                &connectionLinearBuffer[i]);  // initiated with 0 instead of -1
            connectionLinearBuffer[i].slope_intercept.init(
                {1, -1}, "slope_intercept", "slope_intercept", &connectionLinearBuffer[i]);
        }
    }

    int connection_curve_num = connectionCurveNum.ref();
    if (connection_curve_num > 0) {
        supportBoneData.addList(&connectionCurveList, "connection_curve_list");
        connectionCurveBuffer.allocBufferAssert(connection_curve_num, heap);

        for (int i = 0; i < connection_curve_num; i++) {
            auto connection_name = sead::FormatFixedSafeString<32>("connection_curve_%d", i);
            auto& obj = connectionCurveBuffer[i];
            connectionCurveList.addObj(&obj, connection_name);
            obj.bone_attribute.init(-1, "bone_attribute", "bone_attribute", &obj);
            obj.constant_in.init(true, "constant_in", "constant_in", &obj);
            obj.constant_out.init(true, "constant_out", "constant_out", &obj);
            obj.key0.init({0, 0, 1, 1}, "key_0", "key_0", &obj);
            obj.key1.init({0.5, 0.5, 1, 1}, "key_1", "key_1", &obj);
            obj.key2.init({1, 1, 1, 1}, "key_2", "key_2", &obj);
        }
    }

    int output_single_num = outputSingleNum.ref();
    if (output_single_num > 0) {
        supportBoneData.addList(&outputSingleList, "output_single_list");
        outputSingleBuffer.allocBufferAssert(output_single_num, heap);

        for (int i = 0; i < output_single_num; i++) {
            auto output_name = sead::FormatFixedSafeString<32>("output_single_%d", i);
            outputSingleList.addObj(&outputSingleBuffer[i], output_name);
            outputSingleBuffer[i].connection.init(0, "connection", "connection",
                                                  &outputSingleBuffer[i]);
            outputSingleBuffer[i].weight.init(0, "weight", "weight", &outputSingleBuffer[i]);
        }
    }

    int output_double_num = outputDoubleNum.ref();
    if (output_double_num > 0) {
        supportBoneData.addList(&outputDoubleList, "output_double_list");
        // outputDoubleBuffer.allocBufferAssert(output_double_num, heap);
        uninlineAllocDoubleBuffer(&outputDoubleBuffer, output_double_num, heap);

        for (int i = 0; i < output_double_num; i++) {
            auto output_name = sead::FormatFixedSafeString<32>("output_double_%d", i);
            outputDoubleList.addObj(&outputDoubleBuffer[i], output_name);
            outputDoubleBuffer[i].connection_0.init(0, "connection_0", "connection_0",
                                                    &outputDoubleBuffer[i]);
            outputDoubleBuffer[i].weight_0.init(0, "weight_0", "weight_0", &outputDoubleBuffer[i]);
            outputDoubleBuffer[i].connection_1.init(0, "connection_1", "connection_1",
                                                    &outputDoubleBuffer[i]);
            outputDoubleBuffer[i].weight_1.init(0, "weight_1", "weight_1", &outputDoubleBuffer[i]);
        }
    }

    int main_bone_num = mainBoneNum.ref();
    if (main_bone_num < 1)
        return false;
    supportBoneData.addList(&mainBoneList, "main_bone_list");
    mainBoneBuffer.allocBufferAssert(main_bone_num, heap);
    for (int i = 0; i < main_bone_num; i++) {
        auto name = sead::FormatFixedSafeString<32>("main_bone_%d", i);
        mainBoneList.addObj(&mainBoneBuffer[i], name);
    }

    int support_bone_num = supportBoneNum.ref();
    if (support_bone_num < 1)
        return false;
    supportBoneData.addList(&supportBoneList, "support_bone_list");
    supportBoneBuffer.allocBufferAssert(support_bone_num, heap);
    for (int i = 0; i < support_bone_num; i++) {
        auto name = sead::FormatFixedSafeString<32>("support_bone_%d", i);
        supportBoneList.addObj(&supportBoneBuffer[i], name);
    }

    supportBoneData.applyResParameterList(support_bone_list);
    return true;
}

float inline someHelperInterpolationForConnectionCurvesSomething(const sead::Vector4f& key1,
                                                                 const sead::Vector4f& key2,
                                                                 float lookup) {
    float result = key2.y;
    if (key1.x != key2.x) {
        float v9 = key2.x - key1.x;
        float v10 = (lookup - key1.x) / v9;
        float v11 = 2.0f * v10 * v10;
        float v12 = 3.0f * v10 * v10;
        //float v13 = v10 * v12 - v12 + 1.0f;
        float v13 = v10 * v11 - v12 + 1.0f;
        float v14 = (-2.0f * v10 * v10 * v10) + v12;
        float v17 = (v10 * v10 * v10 - v11 + v10) * v9;
        float v18 = v9 * ((v10 * v10 * v10) - (v10 * v10));
        float v19 = ((v14 * result) + (v13 * key1.y)) + (v17 * key1.w);
        result = v19 + (v18 * key2.z);
    }
    return result;
}

//NON_MATCHING: Float operations being picky about the order of commands
float SupportBoneResource::doSomethingAboutConnectionCurves(u32 index, float lookup) {
    auto& connectionCurve = connectionCurveBuffer[index];
    float result;
    float x0 = connectionCurve.key0->x;  // lowest (always minus pi?)
    float x1 = connectionCurve.key1->x;  // middle (0 in most cases)
    float x2 = connectionCurve.key2->x;  // highest
    if (x0 == lookup)
        result = connectionCurve.key0->y;
    else if (x1 == lookup)
        result = connectionCurve.key1->y;
    else if (x2 == lookup)
        result = connectionCurve.key2->y;
    else if (x0 > lookup) {
        result = connectionCurve.key0->y;
        if (!connectionCurve.constant_in.ref())
            result -= (x0 - lookup) * connectionCurve.key0->z;
    } else if (x1 > lookup) {
        result = someHelperInterpolationForConnectionCurvesSomething(connectionCurve.key0.ref(), connectionCurve.key1.ref(), lookup);
    } else if (x2 > lookup) {
        result = someHelperInterpolationForConnectionCurvesSomething(connectionCurve.key1.ref(), connectionCurve.key2.ref(), lookup);
    } else {
        if (!connectionCurve.constant_out.ref())
            result = connectionCurve.key2->y + ((lookup - x2) * connectionCurve.key2->z);
        else
            result = connectionCurve.key2->y;
    }

    return isnan(result) ? 0.0f : result;
}

//NON_MATCHING: Due to seadQuat::normalize() mismatch, this function does not match.
void SupportBoneResource::BaseBone::postRead_(){
    sead::Vector3f aim_local = aim.ref();
    sead::Vector3f up_local = up.ref();
    aim_local.normalize();
    
    side = sead::cross(aim_local, up_local);
    side.normalize();
    
    up_local = sead::cross(side, aim_local);
    up_local.normalize();
    aim = aim_local;
    up = up_local;
    
    base_rotate->normalize();
    reverse_rotate = base_rotate->inverse();
}

}  // namespace ksys::phys