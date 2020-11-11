#!/usr/bin/env python3
import argparse
from pathlib import Path
import typing as tp

import oead


class FlagTypeInfo(tp.NamedTuple):
    def get_getter_fn_name(self) -> str:
        return self.getter_fn_name

    def get_handle_getter_fn_name(self) -> str:
        s = self.getter_fn_name
        if self.is_value_array():
            s += "Array"
        s += "Handle"
        return s

    def get_setter_fn_name(self) -> str:
        return "s" + self.getter_fn_name[1:]

    def is_value_inline(self) -> bool:
        return self.arg_type in ("bool", "s32", "f32")

    def is_value_array(self) -> bool:
        return self.is_array

    def get_setter_arg_type(self) -> str:
        return self.setter_arg_type if self.setter_arg_type else self.arg_type

    getter_fn_name: str
    arg_type: str
    setter_arg_type: str = ""
    is_array: bool = False


flag_type_info = {
    "bool_data": FlagTypeInfo("getBool", "bool"),
    "s32_data": FlagTypeInfo("getS32", "s32"),
    "f32_data": FlagTypeInfo("getF32", "f32"),
    "string_data": FlagTypeInfo("getStr", "char const*", "const sead::SafeString&"),
    "string64_data": FlagTypeInfo("getStr64", "char const*", "const sead::SafeString&"),
    "string256_data": FlagTypeInfo("getStr256", "char const*", "const sead::SafeString&"),
    "vector2f_data": FlagTypeInfo("getVec2f", "sead::Vector2f", "const sead::Vector2f&"),
    "vector3f_data": FlagTypeInfo("getVec3f", "sead::Vector3f", "const sead::Vector3f&"),
    "vector4f_data": FlagTypeInfo("getVec4f", "sead::Vector4f", "const sead::Vector4f&"),

    "bool_array_data": FlagTypeInfo("getBool", "bool", is_array=True),
    "s32_array_data": FlagTypeInfo("getS32", "s32", is_array=True),
    "f32_array_data": FlagTypeInfo("getF32", "f32", is_array=True),
    "string_array_data": FlagTypeInfo("getStr", "char const*", "const sead::SafeString&", is_array=True),
    "string64_array_data": FlagTypeInfo("getStr64", "char const*", "const sead::SafeString&", is_array=True),
    "string256_array_data": FlagTypeInfo("getStr256", "char const*", "const sead::SafeString&", is_array=True),
    "vector2f_array_data": FlagTypeInfo("getVec2f", "sead::Vector2f", "const sead::Vector2f&", is_array=True),
    "vector3f_array_data": FlagTypeInfo("getVec3f", "sead::Vector3f", "const sead::Vector3f&", is_array=True),
    "vector4f_array_data": FlagTypeInfo("getVec4f", "sead::Vector4f", "const sead::Vector4f&", is_array=True),
}


def add_development_remnant_flags(flags: tp.Dict[str, str]):
    _flags = {
        "AoC_DragonFireChallengeRing_Advent": "bool_data",
        "AoC_RandomSpawnTreasure_Contents": "string64_array_data",
        "AoC_RandomSpawnTreasure_IsRandomized": "bool_data",
        "AoC_TestProg_Imoto_Flag_00": "bool_data",
        "AoC_TestProg_Imoto_TagCount_00": "s32_data",
        "AocTestEx_Omosako_IsPastWorld": "bool_data",
        "AocTestEx_Omosako_ReturnToMainField_Position": "vector3f_data",
        "AocTestEx_Omosako_ReturnToMainField_Rotation": "f32_data",
        "AocTestEx_Omosako_SandOfTime_Num": "s32_data",
        "AocTestEx_Omosako_SandOfTime_Rate": "f32_data",
        "Location_DarkDungeon01": "s32_data",
        "Location_DarkDungeon02": "s32_data",
        "Location_DarkDungeon03": "s32_data",
        "Location_DarkDungeon04": "s32_data",
        "SpurGear_revolve_01": "bool_data",
        "SpurGear_revolve_02": "bool_data",
    }
    flags.update(_flags)


def load_flag_types(root: Path) -> tp.Dict[str, str]:
    flag_types: tp.Dict[str, str] = dict()
    add_development_remnant_flags(flag_types)

    gdt_dir = root / "GameData"
    for path in gdt_dir.glob("Flag/*.yml"):
        flag_list = oead.byml.from_text(path.read_text(encoding="utf-8"))
        keys = list(flag_list.keys())
        assert len(keys) == 1
        flag_type = keys[0]
        for flag in flag_list[flag_type]:
            flag_types[flag["DataName"]] = flag_type

    return flag_types


def write_struct_chunk(f: tp.TextIO, flags: tp.Collection[str], i: int) -> None:
    f.write(f"""\
struct CommonFlags{i} {{
""")
    for name in flags:
        f.write(f"    FlagHandle flag_{name} = InvalidHandle;\n")
    f.write(f"""\
    u32 _pad = 0;
}};

[[gnu::visibility("hidden")]] extern CommonFlags{i} sCommonFlags{i};
""")


FLAGS_PER_CHUNK = 1023


def chunk_flag_iterator(flags: tp.Iterator[str]):
    while True:
        chunk = []
        for i in range(FLAGS_PER_CHUNK):
            try:
                chunk.append(next(flags))
            except StopIteration:
                break

        if not chunk:
            return

        yield chunk


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("root", help="Path to the root of the GameROM source")
    parser.add_argument("exe_flag_list", help="Path to a file containing a list of flags")
    args = parser.parse_args()

    src_root = Path(__file__).parent.parent
    src_gdt = src_root / "src" / "KingSystem" / "GameData"
    root = Path(args.root)
    exe_flag_list = Path(args.exe_flag_list).read_text().splitlines()
    flag_types = load_flag_types(root)

    with (src_gdt / "gdtCommonFlags.h").open("w") as f:
        f.write("""\
#pragma once

// DO NOT EDIT. This file is automatically generated.

#include "KingSystem/GameData/gdtManager.h"

namespace ksys::gdt {

// clang-format off

namespace detail {

""")
        for i, chunk in enumerate(chunk_flag_iterator(iter(exe_flag_list))):
            write_struct_chunk(f, chunk, i)
            f.write("\n")
        f.write("""\
}  // namespace detail

void initCommonFlags();

""")

        for i, name in enumerate(exe_flag_list):
            chunk_idx: int = i // FLAGS_PER_CHUNK
            f.write(f"inline FlagHandle& flag_{name}() {{ return detail::sCommonFlags{chunk_idx}.flag_{name}; }}\n")

        f.write("""\

// clang-format on

}  // namespace ksys::gdt
""")

    # Generate the implementation.
    with (src_gdt / "gdtCommonFlags.cpp").open("w") as f:
        f.write("""\
// DO NOT EDIT. This file is automatically generated.

#include "KingSystem/GameData/gdtCommonFlags.h"

namespace ksys::gdt {

namespace detail {

""")
        for i in range(len(exe_flag_list) // FLAGS_PER_CHUNK + 1):
            f.write(f"CommonFlags{i} sCommonFlags{i};\n")
        f.write("""
}  // namespace detail

void initCommonFlags_();

void initCommonFlags() {
    initCommonFlags_();
}

void initCommonFlags_() {
    auto* mgr = Manager::instance();
    if (!mgr)
        return;

    // clang-format off

""")
        for flag_name in exe_flag_list:
            info = flag_type_info[flag_types[flag_name]]
            f.write(f"    flag_{flag_name}() = mgr->{info.get_handle_getter_fn_name()}(\"{flag_name}\");\n")

        f.write("""\

    // clang-format on
}

}  // namespace ksys::gdt
""")

    # Generate gdtCommonFlagsUtils.h
    with (src_gdt / "gdtCommonFlagsUtils.h").open("w") as f:
        f.write("""\
#pragma once

// DO NOT EDIT. This file is automatically generated.

#include "KingSystem/GameData/gdtCommonFlags.h"
#include "KingSystem/GameData/gdtFlagUtils.h"

namespace ksys::gdt {

// clang-format off

bool getFlagGenericBool(FlagHandle handle, bool debug = false);
s32 getFlagGenericS32(FlagHandle handle, bool debug = false);

""")
        for i, name in enumerate(exe_flag_list):
            info = flag_type_info[flag_types[name]]
            if info.is_value_array():
                # Getter
                if info.is_value_inline():
                    f.write(
                        f"{info.arg_type} getFlag_{name}(s32 idx, bool debug = false);\n")
                else:
                    f.write(
                        f"void getFlag_{name}({info.arg_type}* value, s32 idx, bool debug = false);\n")
                # Increase function
                if info.arg_type == "s32":
                    f.write(f"void increaseFlag_{name}(s32 value, s32 idx, bool debug = false);\n")
                # Setter
                f.write(f"void setFlag_{name}({info.get_setter_arg_type()} value, s32 idx, bool debug = false);\n")
                # Resetter
                f.write(f"void resetFlag_{name}(s32 idx, bool debug = false);\n")
            else:
                # Getter
                if info.is_value_inline():
                    f.write(
                        f"{info.arg_type} getFlag_{name}(bool debug = false);\n")
                else:
                    f.write(
                        f"void getFlag_{name}({info.arg_type}* value, bool debug = false);\n")
                # Increase function
                if info.arg_type == "s32":
                    f.write(f"void increaseFlag_{name}(s32 value, bool debug = false);\n")
                # Setter
                f.write(f"void setFlag_{name}({info.get_setter_arg_type()} value, bool debug = false);\n")
                # Resetter
                f.write(f"void resetFlag_{name}(bool debug = false);\n")

        f.write("""\

// clang-format on

}  // namespace ksys::gdt
""")

    # Generate gdtCommonFlagsUtils.cpp
    with (src_gdt / "gdtCommonFlagsUtils.cpp").open("w") as f:
        f.write("""\
// DO NOT EDIT. This file is automatically generated.

#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace ksys::gdt {

// clang-format off

bool getFlagGenericBool(FlagHandle handle, bool debug) { return getBool(handle, debug); }
s32 getFlagGenericS32(FlagHandle handle, bool debug) { return getS32(handle, debug); }

""")
        for i, name in enumerate(exe_flag_list):
            info = flag_type_info[flag_types[name]]
            if info.is_value_array():
                # Getter
                if info.is_value_inline():
                    f.write(
                        f"{info.arg_type} getFlag_{name}(s32 idx, bool debug) {{ return {info.get_getter_fn_name()}(flag_{name}(), idx, debug); }}\n")
                else:
                    f.write(
                        f"void getFlag_{name}({info.arg_type}* value, s32 idx, bool debug) {{ {info.get_getter_fn_name()}(flag_{name}(), value, idx, debug); }}\n")
                # Increase function
                if info.arg_type == "s32":
                    f.write(f"void increaseFlag_{name}(s32 value, s32 idx, bool debug) {{ "
                            f"increaseS32CommonFlag(value, \"{name}\", idx, debug); }}\n")
                # Setter
                f.write(
                    f"void setFlag_{name}({info.get_setter_arg_type()} value, s32 idx, bool debug) {{ "
                    f"{info.get_setter_fn_name()}(value, flag_{name}(), idx, debug); }}\n")
                # Resetter
                f.write(
                    f"void resetFlag_{name}(s32 idx, bool debug) {{ "
                    f"re{info.get_setter_fn_name()}(flag_{name}(), idx, debug); }}\n")
            else:
                # Getter
                if info.is_value_inline():
                    f.write(
                        f"{info.arg_type} getFlag_{name}(bool debug) {{ return {info.get_getter_fn_name()}(flag_{name}(), debug); }}\n")
                else:
                    f.write(
                        f"void getFlag_{name}({info.arg_type}* value, bool debug) {{ {info.get_getter_fn_name()}(flag_{name}(), value, debug); }}\n")
                # Increase function
                if info.arg_type == "s32":
                    f.write(f"void increaseFlag_{name}(s32 value, bool debug) {{ "
                            f"increaseS32CommonFlag(value, \"{name}\", -1, debug); }}\n")
                # Setter
                f.write(
                    f"void setFlag_{name}({info.get_setter_arg_type()} value, bool debug) {{ "
                    f"{info.get_setter_fn_name()}(value, flag_{name}(), debug); }}\n")
                # Resetter
                f.write(
                    f"void resetFlag_{name}(bool debug) {{ re{info.get_setter_fn_name()}(flag_{name}(), debug); }}\n")

        f.write("""\

// clang-format on

}  // namespace ksys::gdt
""")


if __name__ == "__main__":
    main()
