from typing import Dict, List
import yaml

from util import utils
from util.graph import Graph

BaseClasses = {
    0x71024d8d68,
    0x71025129f0,
    0x7102513278,
    0x71024d8ef0,
    0x710243c9b8,
}


def check_vtable_name_dict(names: Dict[int, str]):
    seen = set()
    for k, v in names.items():
        if v in seen:
            raise ValueError(f"invalid vtable names: {v} appears twice")
        seen.add(k)
        seen.add(v)


def get_vtables() -> Dict[str, Dict[str, List[int]]]:
    with (utils.get_repo_root() / "data" / "aidef_vtables.yml").open(encoding="utf-8") as f:
        return yaml.load(f, Loader=yaml.CSafeLoader)


def get_action_params() -> Dict[str, List[dict]]:
    with (utils.get_repo_root() / "data" / "aidef_action_params.yml").open(encoding="utf-8") as f:
        return yaml.load(f, Loader=yaml.CSafeLoader)


def get_action_vtable_names() -> Dict[int, str]:
    with (utils.get_repo_root() / "data" / "aidef_action_vtables.yml").open(encoding="utf-8") as f:
        names = yaml.load(f, Loader=yaml.CSafeLoader)

    check_vtable_name_dict(names)
    return names


def get_ai_params() -> Dict[str, List[dict]]:
    with (utils.get_repo_root() / "data" / "aidef_ai_params.yml").open(encoding="utf-8") as f:
        return yaml.load(f, Loader=yaml.CSafeLoader)


def get_ai_vtable_names() -> Dict[int, str]:
    with (utils.get_repo_root() / "data" / "aidef_ai_vtables.yml").open(encoding="utf-8") as f:
        names = yaml.load(f, Loader=yaml.CSafeLoader)

    check_vtable_name_dict(names)
    return names


def topologically_sort_vtables(all_vtables: dict, type_: str) -> List[int]:
    graph = Graph()
    for name, vtables in all_vtables[type_].items():
        classes = list(dict.fromkeys(reversed(vtables)))
        for i in range(len(classes) - 1):
            graph.add_edge(classes[i + 1], classes[i])
    return graph.topological_sort()
