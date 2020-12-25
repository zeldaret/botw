#!/usr/bin/env python3
import argparse
from collections import defaultdict
from pathlib import Path
from typing import Union

import yaml

_base_classes = {
    0x71024d8d68,
    0x71025129f0,
    0x7102513278,
    0x71024d8ef0,
    0x710243c9b8,
}

_known_vtables = {
    0x71024d8d68: "ActionBase",
    0x71025129f0: "Action",
    0x7102513278: "Ai",
    0x71024d8ef0: "Behavior",
    0x710243c9b8: "Query",
}


def get_name_for_vtable(vtable: Union[str, int]):
    if isinstance(vtable, str):
        return vtable

    known_name = _known_vtables.get(vtable, None)
    if known_name is not None:
        return f"[V] {known_name}"

    return f"[V] {vtable:#x}"


def dfs(nodes: dict, start, visited: set):
    result = []
    to_visit = [start]
    while to_visit:
        x = to_visit.pop()
        result.append(x)
        visited.add(x)

        for y in nodes[x]:
            if y not in visited:
                to_visit.append(y)

    return result


class Graph:
    def __init__(self):
        self.nodes = defaultdict(set)

    def add_edge(self, a, b):
        self.nodes[a].add(b)

    def find_connected_components(self):
        nodes = defaultdict(list)
        for u in self.nodes:
            for v in self.nodes[u]:
                nodes[u].append(v)
                nodes[v].append(u)
        cc = []
        visited = set()
        for u in nodes.keys():
            if u in visited:
                continue
            cc.append(dfs(nodes, u, visited))
        return cc


def guess_vtable_names(reverse_graph: Graph):
    for u in reverse_graph.nodes:
        targets = list(reverse_graph.nodes[u])
        known_targets = list(filter(lambda x: isinstance(x, str), targets))
        if len(known_targets) == 1:
            # Leaves can be named pretty easily.
            _known_vtables[u] = known_targets[0]


def build_graph(all_vtables: dict, type_: str, graph: Graph, reverse_graph: Graph):
    for name, vtables in all_vtables[type_].items():
        classes = [name] + list(reversed(vtables))
        # Each class has at least one parent, so the -1 is fine.
        for i in range(len(classes) - 1):
            from_ = classes[i]
            to_ = classes[i + 1]
            # Skip base classes to reduce noise.
            if to_ in _base_classes:
                break
            reverse_graph.add_edge(to_, from_)

    guess_vtable_names(reverse_graph)

    for name, vtables in all_vtables[type_].items():
        classes = [name] + list(reversed(vtables))
        for i in range(len(classes) - 1):
            if classes[i + 1] in _base_classes:
                break
            from_ = get_name_for_vtable(classes[i])
            to_ = get_name_for_vtable(classes[i + 1])
            graph.add_edge(from_, to_)


def main() -> None:
    parser = argparse.ArgumentParser(description="Shows AI classes with non-trivial class hierarchies.")
    parser.add_argument("aidef_vtables", help="Path to aidef_vtables.yml")
    parser.add_argument("--type", help="AI class type to visualise", choices=["Action", "AI", "Behavior", "Query"],
                        required=True)
    parser.add_argument("--out-names", help="Path to which a vtable -> name map will be written", required=True)
    args = parser.parse_args()

    with Path(args.aidef_vtables).open() as f:
        all_vtables: dict = yaml.load(f, Loader=yaml.CSafeLoader)

    graph = Graph()
    reverse_graph = Graph()
    build_graph(all_vtables, args.type, graph, reverse_graph)

    interesting_nodes = set()
    node_colors = dict()

    colors = ["#c7dcff", "#ffc7c7", "#ceffc7", "#dcc7ff", "#fffdc9", "#c9fff3", "#ffe0cc", "#ffcffe", "#96a8ff"]
    components = graph.find_connected_components()
    num_nontrivial_cc = 0
    for i, comp in enumerate(components):
        if len(comp) == 2:
            continue
        for node in comp:
            node_colors[node] = colors[i % len(colors)]
        num_nontrivial_cc += 1
        interesting_nodes |= set(comp)

    print("digraph {")
    print("node [shape=rectangle]")
    for u in graph.nodes:
        if u not in interesting_nodes:
            continue
        for v in graph.nodes[u]:
            shape_u = "shape=component," if "[V]" not in u else ""
            shape_v = "shape=component," if "[V]" not in v else ""
            print(f'"{u}" [{shape_u}style=filled, fillcolor="{node_colors[u]}"]')
            print(f'"{v}" [{shape_v}style=filled, fillcolor="{node_colors[v]}"]')
            print(f'"{u}" -> "{v}"')
    print("}")
    print(f"# {len(components)} connected components")
    print(f"# {num_nontrivial_cc} non-trivial connected components")

    yaml.add_representer(int, lambda dumper, data: yaml.ScalarNode('tag:yaml.org,2002:int', f"{data:#x}"),
                         Dumper=yaml.CSafeDumper)
    with Path(args.out_names).open("w") as f:
        yaml.dump(_known_vtables, f, Dumper=yaml.CSafeDumper)


if __name__ == '__main__':
    main()
