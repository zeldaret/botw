#include "KingSystem/ActorSystem/actAiParam.h"

namespace ksys::act::ai {

ParamPack::ParamPack() = default;

ParamPack::~ParamPack() {
    auto* param = mParams;
    while (param) {
        if (param->data) {
            switch (param->type) {
            case AIDefParamType::String:
                delete static_cast<sead::SafeString*>(param->data);
                break;
            case AIDefParamType::Int:
                delete static_cast<int*>(param->data);
                break;
            case AIDefParamType::Float:
                delete static_cast<float*>(param->data);
                break;
            case AIDefParamType::Vec3:
                delete static_cast<sead::Vector3f*>(param->data);
                break;
            case AIDefParamType::Bool:
                delete static_cast<bool*>(param->data);
                break;
            case AIDefParamType::AITreeVariablePointer:
                delete static_cast<void**>(param->data);
                break;
            case AIDefParamType::UInt:
                delete static_cast<u32*>(param->data);
                break;
            case AIDefParamType::MesTransceiverId:
                delete static_cast<mes::TransceiverId*>(param->data);
                break;
            case AIDefParamType::BaseProcHandle:
                delete static_cast<BaseProcHandle**>(param->data);
                break;
            case AIDefParamType::Rail:
                delete static_cast<Rail**>(param->data);
                break;
            case AIDefParamType::BaseProcLink:
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
        case AIDefParamType::String: {
            const sead::SafeString src = param->cstr;
            const sead::SafeString key = param->key;
            auto* dst = pack.getVariable<sead::BufferedSafeString>(key, AIDefParamType::String);
            if (dst)
                dst->copy(src);
            break;
        }
        case AIDefParamType::Int:
            pack.setVariable(param->key, AIDefParamType::Int, param->i);
            break;
        case AIDefParamType::Float:
            pack.setVariable(param->key, AIDefParamType::Float, param->f);
            break;
        case AIDefParamType::Vec3:
            if (auto* dst = pack.getVariable<sead::Vector3f>(param->key, AIDefParamType::Vec3)) {
                dst->x = param->vec3.x;
                dst->y = param->vec3.y;
                dst->z = param->vec3.z;
            }
            break;
        case AIDefParamType::Bool:
            pack.setVariable(param->key, AIDefParamType::Bool, param->b);
            break;
        case AIDefParamType::UInt:
            pack.setVariable(param->key, AIDefParamType::UInt, param->u);
            break;
        case AIDefParamType::BaseProcLink:
            pack.setVariable(param->key, AIDefParamType::BaseProcLink, param->baseProcLink);
            break;
        case AIDefParamType::MesTransceiverId:
            pack.setVariable(param->key, AIDefParamType::MesTransceiverId, param->mesTransceiverId);
            break;
        case AIDefParamType::BaseProcHandle: {
            auto* baseProcHandle = static_cast<BaseProcHandle*>(param->ptr);
            pack.setVariable(param->key, AIDefParamType::BaseProcHandle, baseProcHandle);
            break;
        }
        case AIDefParamType::Rail: {
            auto* rail = static_cast<Rail*>(param->ptr);
            pack.setVariable(param->key, AIDefParamType::Rail, rail);
            break;
        }
        default:
            break;
        }
    }
}

}  // namespace ksys::act::ai
