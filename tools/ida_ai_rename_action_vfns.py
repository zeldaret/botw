import struct
from collections import defaultdict
from pathlib import Path
from typing import Dict

from ai_show_nontrivial_hierarchies import _base_classes
from util import utils
import yaml
import idaapi


class Graph:
    def __init__(self):
        self.nodes = defaultdict(set)

    def add_edge(self, a, b):
        self.nodes[a].add(b)

    def topological_sort(self) -> list:
        result = []
        visited = set()

        def dfs(node):
            if node in visited:
                return
            # Our graph is guaranteed to be acyclic since it's a graph of vtables...
            visited.add(node)
            for y in self.nodes.get(node, set()):
                dfs(y)
            result.insert(0, node)

        for x in self.nodes:
            dfs(x)

        return result


def build_graph(all_vtables: dict, graph: Graph):
    for name, vtables in all_vtables["Action"].items():
        classes = list(dict.fromkeys(reversed(vtables)))
        for i in range(len(classes) - 1):
            graph.add_edge(classes[i + 1], classes[i])


_vtable_fn_names = [
    "_ZNK5uking6action{}27checkDerivedRuntimeTypeInfoEPKN4sead15RuntimeTypeInfo9InterfaceE",
    "_ZNK5uking6action{}18getRuntimeTypeInfoEv",
    "_ZN5uking6action{}D2Ev",
    "_ZN5uking6action{}D0Ev",
    "_ZNK5uking6action{}8isFailedEv",
    "_ZNK5uking6action{}10isFinishedEv",
    "_ZNK5uking6action{}10isFlag4SetEv",
    "_ZN5uking6action{}14hasPreDeleteCbEv",
    "_ZN5uking6action{}23hasUpdateForPreDeleteCbEv",
    "_ZN5uking6action{}2m9Ev",
    "_ZN5uking6action{}8oneShot_Ev",
    "_ZN5uking6action{}5init_EPN4sead4HeapE",
    "_ZN5uking6action{}6enter_EPN4ksys3act2ai15InlineParamPackE",
    "_ZN5uking6action{}8reenter_EPS2_b",
    "_ZN5uking6action{}6leave_Ev",
    "_ZN5uking6action{}11loadParams_Ev",
    "_ZN5uking6action{}14handleMessage_EPN4ksys3mes7MessageE",
    "_ZN5uking6action{}15handleMessage2_EPN4ksys3mes7MessageE",
    "_ZN5uking6action{}18updateForPreDeleteEv",
    "_ZN5uking6action{}11onPreDeleteEv",
    "_ZN5uking6action{}4calcEv",
    "_ZNK5uking6action{}14getCurrentNameEPN4sead22BufferedSafeStringBaseIcEEPS2_",
    "_ZN5uking6action{}11changeChildERKN4sead14SafeStringBaseIcEE",
    "_ZNK5uking6action{}9getParamsEPN4ksys3act2ai18ParamNameTypePairsEb",
    "_ZNK5uking6action{}14getNumChildrenEv",
    "_ZN5uking6action{}12initChildrenERKN4ksys8AIDefSetEPN4sead4HeapE",
    "_ZNK5uking6action{}15getCurrentChildEv",
    "_ZNK5uking6action{}7getTypeEv",
    "_ZN5uking6action{}7reenterEPS2_RKN4sead14SafeStringBaseIcEE",
    "_ZN5uking6action{}9postLeaveEv",
    "_ZNK5uking6action{}8getChildEi",
    "_ZN5uking6action{}5calc_Ev",
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
    data_dir = utils.get_repo_root() / "data"
    with Path(data_dir / "aidef_vtables.yml").open() as f:
        all_vtables: dict = yaml.load(f, Loader=yaml.CSafeLoader)
    with Path(data_dir / "aidef_action_vtables.yml").open() as f:
        names: Dict[int, str] = yaml.load(f, Loader=yaml.CSafeLoader)

    new_names: Dict[int, str] = dict()

    not_decompiled = {func.addr for func in utils.get_functions() if func.status == utils.FunctionStatus.NotDecompiled}

    graph = Graph()
    build_graph(all_vtables, graph)
    order = graph.topological_sort()
    for vtable_addr in order:
        if vtable_addr in _base_classes:
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
                    new_names[real_fn_ea] = f"uking::action::{class_name}::m{i}"

                if real_fn_ea in not_decompiled:
                    idaapi.set_name(fn_ea, new_names[real_fn_ea])

    utils.add_decompiled_functions(dict(), new_names)


if __name__ == '__main__':
    main()
