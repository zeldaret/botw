#include "KingSystem/ActorSystem/actAiParam.h"

namespace ksys::act::ai {

ParamPack::ParamPack() = default;

ParamPack::~ParamPack() {
    auto* param = mParams;
    while (param) {
        if (param->data) {
            switch (Param::Type(param->type)) {
            case Param::Type::String:
                delete static_cast<sead::SafeString*>(param->data);
                break;
            case Param::Type::Int:
                delete static_cast<int*>(param->data);
                break;
            case Param::Type::Float:
                delete static_cast<float*>(param->data);
                break;
            case Param::Type::Vec3:
                delete static_cast<sead::Vector3f*>(param->data);
                break;
            case Param::Type::Bool:
                delete static_cast<bool*>(param->data);
                break;
            case Param::Type::AITreeVariablePointer:
                delete static_cast<void**>(param->data);
                break;
            case Param::Type::UInt:
                delete static_cast<u32*>(param->data);
                break;
            case Param::Type::MesTransceiverId:
                delete static_cast<mes::TransceiverId*>(param->data);
                break;
            case Param::Type::BaseProcHandle:
                delete static_cast<BaseProcHandle**>(param->data);
                break;
            case Param::Type::Rail:
                delete static_cast<Rail**>(param->data);
                break;
            case Param::Type::BaseProcLink:
                delete static_cast<BaseProcLink*>(param->data);
                break;
            default:
                break;
            }
        }
        param = mParams->next;
        if (mParams)
            delete mParams;
        mParams = param;
    }
}

void InlineParamPack::copyToParamPack(ParamPack& pack) const {
    const u32 n = count >= 0x1F ? 0x1F : count;
    const InlineParam* param = params;
    for (u32 i = 0; i < n; ++i, ++param) {
        switch (param->type) {
        case Param::Type::String: {
            const sead::SafeString src = param->cstr;
            const sead::SafeString key = param->key;
            auto* dst = pack.getVariable<sead::BufferedSafeString>(key, Param::Type::String);
            if (dst)
                dst->copy(src);
            break;
        }
        case Param::Type::Int:
            pack.setVariable(param->key, Param::Type::Int, param->i);
            break;
        case Param::Type::Float:
            pack.setVariable(param->key, Param::Type::Float, param->f);
            break;
        case Param::Type::Vec3:
            if (auto* dst = pack.getVariable<sead::Vector3f>(param->key, Param::Type::Vec3)) {
                dst->x = param->vec3.x;
                dst->y = param->vec3.y;
                dst->z = param->vec3.z;
            }
            break;
        case Param::Type::Bool:
            pack.setVariable(param->key, Param::Type::Bool, param->b);
            break;
        case Param::Type::UInt:
            pack.setVariable(param->key, Param::Type::UInt, param->u);
            break;
        case Param::Type::BaseProcLink:
            pack.setVariable(param->key, Param::Type::BaseProcLink, param->baseProcLink);
            break;
        case Param::Type::MesTransceiverId:
            pack.setVariable(param->key, Param::Type::MesTransceiverId, param->mesTransceiverId);
            break;
        case Param::Type::BaseProcHandle: {
            auto* baseProcHandle = static_cast<BaseProcHandle*>(param->ptr);
            pack.setVariable(param->key, Param::Type::BaseProcHandle, baseProcHandle);
            break;
        }
        case Param::Type::Rail: {
            auto* rail = static_cast<Rail*>(param->ptr);
            pack.setVariable(param->key, Param::Type::Rail, rail);
            break;
        }
        default:
            break;
        }
    }
}

}  // namespace ksys::act::ai
