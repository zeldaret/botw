from pathlib import Path


def apply(config, args):
    config['arch'] = 'aarch64'
    config['baseimg'] = 'data/main.elf'
    config['myimg'] = 'build/uking'
    config['source_directories'] = ['src', 'lib']
    config['objdump_executable'] = 'tools/aarch64-none-elf-objdump'

    for dir in ('build', 'build/nx64-release'):
        if (Path(dir) / 'build.ninja').is_file():
            config['make_command'] = ['ninja', '-C', dir]


def map_build_target(make_target: str):
    if make_target == "build/uking":
        return "uking"

    # TODO: When support for directly diffing object files is added, this needs to strip
    # the build/ prefix from the object file targets.
    return make_target
