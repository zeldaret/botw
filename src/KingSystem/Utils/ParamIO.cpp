#include "KingSystem/Utils/ParamIO.h"
#include <agl/Utils/aglParameter.h>
#include <cstring>
#include "KingSystem/ActorSystem/actActorParamMgr.h"

namespace ksys {

void ParamIO::applyParameter(char* data, char* data1, agl::utl::ParameterBase* param,
                             const sead::SafeString& parent_name, bool* applied) {
    sead::FixedSafeString<128> name;
    name.format("%s/%s", parent_name.cstr(), param->getName().cstr());
    if (name != data)
        return;

    if (param->getParameterType() == agl::utl::ParameterBase::ParameterType::StringRef) {
        auto* heap = act::ActorParamMgr::instance()->getDebugHeap();
        const auto len = sead::SafeString(data1).calcLength();
        auto* copy = new (heap) char[len + 1];
        std::memcpy(copy, data1, len);
        data1 = copy;
        data1[len] = '\0';
    }

    param->applyString(data1, false);
    *applied = true;
}

void ParamIO::applyParameterObj(char* data, char* data1, agl::utl::IParameterObj* obj,
                                const sead::SafeString& parent_name, bool* applied) {
    sead::FixedSafeString<128> name;
    name.format("%s/%s", parent_name.cstr(), obj->getName().cstr());

    if (obj->getNext())
        applyParameterObj(data, data1, obj->getNext(), parent_name, applied);

    for (auto param = obj->getParamListHead(); param; param = param->getNext()) {
        applyParameter(data, data1, param, name, applied);
        if (param == obj->getParamListTail())
            break;
    }
}

void ParamIO::applyParameterList(char* data, char* data1, agl::utl::IParameterList* list,
                                 const sead::SafeString& parent_name, bool* applied) {
    sead::FixedSafeString<128> name;
    name.format("%s/%s", parent_name.cstr(), list->getName().cstr());

    if (auto* obj = list->getChildObjHead())
        applyParameterObj(data, data1, obj, name, applied);

    if (auto* next = list->getNext())
        applyParameterList(data, data1, next, parent_name, applied);

    if (auto* child = list->getChildListHead())
        applyParameterList(data, data1, child, name, applied);
}

bool ParamIO::applyResourceUpdate(char* data, char* data1) {
    bool applied = false;
    applyParameterList(data, data1, this, "", &applied);
    return applied;
}

const char* ParamIO::getString(const agl::utl::ResParameterObj& obj, const char* key,
                               const char* default_value, void*) const {
    const auto param = agl::utl::getResParameter(obj, key);
    if (!param.ptr())
        return default_value;
    return param.getData<const char>();
}

// NON_MATCHING: how the default_value Vec3f is stored on the stack
sead::Vector3f ParamIO::getVec3(const agl::utl::ResParameterObj& obj, const char* key,
                                sead::Vector3f default_value, void*) const {
    const auto param = agl::utl::getResParameter(obj, key);
    return param.ptr() ? *param.getData<sead::Vector3f>() : default_value;
}

}  // namespace ksys
