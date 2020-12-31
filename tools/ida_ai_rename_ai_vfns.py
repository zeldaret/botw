import struct
from typing import Dict

from util import utils, ai_common
import idaapi

from util.ai_common import BaseClasses

_vtable_fn_names = [
    "_ZNK5uking2ai{}27checkDerivedRuntimeTypeInfoEPKN4sead15RuntimeTypeInfo9InterfaceE",
    "_ZNK5uking2ai{}18getRuntimeTypeInfoEv",
    "_ZN5uking2ai{}D2Ev",
    "_ZN5uking2ai{}D0Ev",
    "_ZNK5uking2ai{}8isFailedEv",
    "_ZNK5uking2ai{}10isFinishedEv",
    "_ZNK5uking2ai{}10isFlag4SetEv",
    "_ZN5uking2ai{}14hasPreDeleteCbEv",
    "_ZN5uking2ai{}23hasUpdateForPreDeleteCbEv",
    "_ZN5uking2ai{}2m9Ev",
    "_ZN5uking2ai{}8oneShot_Ev",
    "_ZN5uking2ai{}5init_EPN4sead4HeapE",
    "_ZN5uking2ai{}6enter_EPN4ksys3act2ai15InlineParamPackE",
    "_ZN5uking2ai{}8reenter_EPS2_b",
    "_ZN5uking2ai{}6leave_Ev",
    "_ZN5uking2ai{}11loadParams_Ev",
    "_ZN5uking2ai{}14handleMessage_EPN4ksys3mes7MessageE",
    "_ZN5uking2ai{}15handleMessage2_EPN4ksys3mes7MessageE",
    "_ZN5uking2ai{}18updateForPreDeleteEv",
    "_ZN5uking2ai{}11onPreDeleteEv",
    "_ZN5uking2ai{}4calcEv",
    "_ZNK5uking2ai{}14getCurrentNameEPN4sead22BufferedSafeStringBaseIcEEPS2_",
    "_ZN5uking2ai{}11changeChildERKN4sead14SafeStringBaseIcEE",
    "_ZNK5uking2ai{}9getParamsEPN4ksys3act2ai18ParamNameTypePairsEb",
    "_ZNK5uking2ai{}14getNumChildrenEv",
    "_ZN5uking2ai{}12initChildrenERKN4ksys8AIDefSetEPN4sead4HeapE",
    "_ZNK5uking2ai{}15getCurrentChildEv",
    "_ZNK5uking2ai{}7getTypeEv",
    "_ZN5uking2ai{}7reenterEPS2_RKN4sead14SafeStringBaseIcEE",
    "_ZN5uking2ai{}9postLeaveEv",
    "_ZNK5uking2ai{}8getChildEi",
    "_ZNK5uking2ai{}8getNamesEPN4sead22BufferedSafeStringBaseIcEE",
    "_ZN5uking2ai{}5calc_Ev",
    "_ZN5uking2ai{}25handlePendingChildChange_Ev",
]


def format_fn_name(name: str, class_name: str):
    return name.format(f"{len(class_name)}{class_name}")


def iterate_vtable(vtable_addr):
    ea = vtable_addr
    while True:
        fn_ea = struct.unpack('<Q', idaapi.get_bytes(ea, 8))[0]
        if idaapi.get_name(fn_ea) != "__cxa_pure_virtual" and not idaapi.is_func(idaapi.get_flags(fn_ea)):
            return
        yield fn_ea
        ea += 8


_ida_base = 0x7100000000


def main() -> None:
    all_vtables = ai_common.get_vtables()
    names = ai_common.get_ai_vtable_names()
    not_decompiled = {func.addr for func in utils.get_functions() if func.status == utils.FunctionStatus.NotDecompiled}

    new_names: Dict[int, str] = dict()

    order = ai_common.topologically_sort_vtables(all_vtables, "AI")
    for vtable_addr in order:
        if vtable_addr in BaseClasses:
            continue

        class_name = names.get(vtable_addr)
        for i, fn_ea in enumerate(iterate_vtable(vtable_addr)):
            if idaapi.get_name(fn_ea) == "__cxa_pure_virtual":
                continue

            real_fn_ea = fn_ea & ~_ida_base
            if real_fn_ea not in new_names:
                if i < len(_vtable_fn_names):
                    new_names[real_fn_ea] = format_fn_name(_vtable_fn_names[i], class_name)
                else:
                    # Unknown member function.
                    new_names[real_fn_ea] = f"uking::ai::{class_name}::m{i}"

                if real_fn_ea in not_decompiled:
                    idaapi.set_name(fn_ea, new_names[real_fn_ea])

    utils.add_decompiled_functions(dict(), new_names)


if __name__ == '__main__':
    main()
