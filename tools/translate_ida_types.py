#!/usr/bin/env python3

from colorama import Back, Fore, Style
import sys

mapping = {
    "agl::utl::Parameter$uint$": "agl::utl::Parameter<u32>",
    "agl::utl::Parameter$int$": "agl::utl::Parameter<int>",
    "agl::utl::Parameter$s32$": "agl::utl::Parameter<int>",
    "agl::utl::Parameter$float$": "agl::utl::Parameter<float>",
    "agl::utl::Parameter$f32$": "agl::utl::Parameter<float>",
    "agl::utl::Parameter$bool$": "agl::utl::Parameter<bool>",
    "agl::utl::Parameter$sead::SafeString$": "agl::utl::Parameter<sead::SafeString>",
    "agl::utl::Parameter$sead::Vector3f$": "agl::utl::Parameter<sead::Vector3f>",
    "agl::utl::Parameter$sead::FixedSafeString20$": "agl::utl::Parameter<sead::FixedSafeString<32>>",
    "agl::utl::Parameter$sead::FixedSafeString40$": "agl::utl::Parameter<sead::FixedSafeString<64>>",
    "agl::utl::Parameter$sead::FixedSafeString100$": "agl::utl::Parameter<sead::FixedSafeString<256>>",
    "agl::utl::Parameter$sead::Color4f$": "agl::utl::Parameter<sead::Color4f>",
    "agl::utl::Parameter_String32": "agl::utl::Parameter<sead::FixedSafeString<32>>",
    "agl::utl::Parameter_String64": "agl::utl::Parameter<sead::FixedSafeString<64>>",
    "agl::utl::Parameter_String256": "agl::utl::Parameter<sead::FixedSafeString<256>>",
}

lines = list(sys.stdin)

sys.stderr.write(Back.BLUE + Fore.WHITE + Style.BRIGHT + "=" * 30 + " output " + "=" * 30 + Style.RESET_ALL + "\n")

for line in lines:
    for from_type, to_type in mapping.items():
        line = line.replace(from_type, to_type)
    sys.stdout.write(line)
