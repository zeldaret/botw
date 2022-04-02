#!/usr/bin/env python3
import argparse
import json
import oead
from pathlib import Path


def _parse_parameter_archive(path: Path) -> oead.aamp.ParameterIO:
    data = path.read_bytes()
    try:
        return oead.aamp.ParameterIO.from_binary(data)
    except:
        return oead.aamp.ParameterIO.from_text(data)


_AampTypeToAglUtlParameterType = {
    oead.aamp.Parameter.Type.Bool: "agl::utl::Parameter<bool>",
    oead.aamp.Parameter.Type.F32: "agl::utl::Parameter<f32>",
    oead.aamp.Parameter.Type.Int: "agl::utl::Parameter<s32>",
    oead.aamp.Parameter.Type.Vec2: "agl::utl::Parameter<sead::Vector2f>",
    oead.aamp.Parameter.Type.Vec3: "agl::utl::Parameter<sead::Vector3f>",
    oead.aamp.Parameter.Type.Vec4: "agl::utl::Parameter<sead::Vector4f>",
    oead.aamp.Parameter.Type.Color: "agl::utl::Parameter<sead::Color4f>",
    oead.aamp.Parameter.Type.String32: "agl::utl::Parameter<sead::SafeString>",
    oead.aamp.Parameter.Type.String64: "agl::utl::Parameter<sead::SafeString>",
    oead.aamp.Parameter.Type.Curve1: "agl::utl::ParameterCurve<1>",
    oead.aamp.Parameter.Type.Curve2: "agl::utl::ParameterCurve<2>",
    oead.aamp.Parameter.Type.Curve3: "agl::utl::ParameterCurve<3>",
    oead.aamp.Parameter.Type.Curve4: "agl::utl::ParameterCurve<4>",
    oead.aamp.Parameter.Type.BufferInt: "agl::utl::ParameterBuffer<s32>",
    oead.aamp.Parameter.Type.BufferF32: "agl::utl::ParameterBuffer<f32>",
    oead.aamp.Parameter.Type.String256: "agl::utl::Parameter<sead::SafeString>",
    oead.aamp.Parameter.Type.Quat: "agl::utl::Parameter<sead::Quatf>",
    oead.aamp.Parameter.Type.U32: "agl::utl::Parameter<u32>",
    oead.aamp.Parameter.Type.BufferU32: "agl::utl::ParameterBuffer<u32>",
    oead.aamp.Parameter.Type.BufferBinary: "agl::utl::ParameterBuffer<u8>",
    oead.aamp.Parameter.Type.StringRef: "agl::utl::Parameter<sead::SafeString>",
}


def _aamp_type_to_agl_utl_parameter_type(type_: oead.aamp.Parameter.Type) -> str:
    return _AampTypeToAglUtlParameterType[type_]


def _represent_float(value: float) -> str:
    s = f'{value:g}'
    if 'e' not in s and '.' not in s:
        s += '.0'
    return s


def _get_value_repr(value) -> str:
    v = value.v

    if isinstance(v, bool):
        return "true" if v else "false"

    if isinstance(v, oead.FixedSafeString32) or isinstance(v, oead.FixedSafeString64) or isinstance(v, oead.FixedSafeString256) or isinstance(v, str):
        return json.dumps(str(v))

    if isinstance(v, oead.Vector2f):
        return f"{{{_represent_float(v.x)}, {_represent_float(v.y)}}}"

    if isinstance(v, oead.Vector3f):
        return f"{{{_represent_float(v.x)}, {_represent_float(v.y)}, {_represent_float(v.z)}}}"

    if isinstance(v, oead.Vector4f):
        return f"{{{_represent_float(v.x)}, {_represent_float(v.y)}, {_represent_float(v.z)}, {_represent_float(v.t)}}}"

    if isinstance(v, float):
        return _represent_float(v)

    return repr(v)


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("bgparamlist_path", type=Path,
                        help="Path to Dummy.bgparamlist (text or binary)")
    parser.add_argument("--object", required=True)
    args = parser.parse_args()

    name_table = oead.aamp.get_default_name_table()

    pio = _parse_parameter_archive(args.bgparamlist_path)
    pobj = pio.objects[args.object]

    class_name = f"GParamListObject{args.object}"

    # Includes
    print("""\
#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {
""")

    # Generate the class definition.
    print(f"class {class_name} : public GParamListObject {{")
    print(f"public:")
    print(f"    {class_name}();")
    print(f'    const char* getName() const override {{ return "{args.object}"; }}')
    print()
    for key, value in pobj.params.items():
        name = name_table.get_name(key.hash, 0, 0)
        assert name
        type_str = _aamp_type_to_agl_utl_parameter_type(value.type())
        print(f"    {type_str} m{name};")
    print("};")
    print()

    # Generate the constructor now.
    print(f"inline {class_name}::{class_name}() {{")
    print("    auto* const obj = &mObj;")
    print()
    for key, value in pobj.params.items():
        name = name_table.get_name(key.hash, 0, 0)
        assert name
        default_value_repr = _get_value_repr(value)
        print(f'    m{name}.init({default_value_repr}, "{name}", "", obj);')
    print("}")

    print()
    print("}  // namespace ksys::res")


if __name__ == "__main__":
    main()
