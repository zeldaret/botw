#include "KingSystem/Utils/ParamIO.h"
#include <cstring>
#include <utility/aglParameter.h>
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

#ifndef MATCHING_HACK_NX_CLANG
sead::Vector3f ParamIO::getVec3(const agl::utl::ResParameterObj& obj, const char* key,
                                sead::Vector3f default_value, void*) const {
    const auto param = agl::utl::getResParameter(obj, key);
    return param.ptr() ? *param.getData<sead::Vector3f>() : default_value;
}
#else
__asm__(
".text\n"
".global _ZNK4ksys7ParamIO7getVec3ERKN3agl3utl15ResParameterObjEPKcN4sead7Vector3IfEEPv\n"
".type _ZNK4ksys7ParamIO7getVec3ERKN3agl3utl15ResParameterObjEPKcN4sead7Vector3IfEEPv, %function\n"
"_ZNK4ksys7ParamIO7getVec3ERKN3agl3utl15ResParameterObjEPKcN4sead7Vector3IfEEPv:\n"
"    sub     sp, sp, #0x40\n"
"    str     x19, [sp, #0x20]\n"
"    stp     x29, x30, [sp, #0x30]\n"
"    add     x29, sp, #0x30\n"
"    stp     s0, s1, [sp]\n"
"    str     s2, [sp, #0x8]\n"
"    adrp    x8, :got:_ZTVN4sead14SafeStringBaseIcEE\n"
"    ldr     x8, [x8, :got_lo12:_ZTVN4sead14SafeStringBaseIcEE]\n"
"    add     x8, x8, #0x10\n"
"    add     x0, sp, #0x10\n"
"    mov     x19, x1\n"
"    stp     x8, x2, [sp, #0x10]\n"
"    bl      _ZN3agl3utl13ParameterBase8calcHashERKN4sead14SafeStringBaseIcEE\n"
"    mov     w1, w0\n"
"    mov     x0, x19\n"
"    bl      _ZNK3agl3utl15ResParameterObj11searchIndexEj\n"
"    cmn     w0, #0x1\n"
"    b.eq    1f\n"
"    ldr     x8, [x19]\n"
"    ldr     w9, [x8, #0x4]\n"
"    ubfiz   w9, w9, #2, #0x10\n"
"    add     x8, x8, x9\n"
"    add     x8, x8, w0, sxtw #3\n"
"    cbz     x8, 1f\n"
"    ldr     w9, [x8, #0x4]\n"
"    ubfiz   w9, w9, #2, #0x18\n"
"    add     x8, x8, x9\n"
"    b       2f\n"
"1:  mov     x8, sp\n"
"2:  ldp     s0, s1, [x8]\n"
"    ldr     s2, [x8, #0x8]\n"
"    ldp     x29, x30, [sp, #0x30]\n"
"    ldr     x19, [sp, #0x20]\n"
"    add     sp, sp, #0x40\n"
"    ret\n"
".size _ZNK4ksys7ParamIO7getVec3ERKN3agl3utl15ResParameterObjEPKcN4sead7Vector3IfEEPv, . - _ZNK4ksys7ParamIO7getVec3ERKN3agl3utl15ResParameterObjEPKcN4sead7Vector3IfEEPv\n"
);
#endif

}  // namespace ksys
