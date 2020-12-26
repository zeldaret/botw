from collections import defaultdict

_Visiting = 0
_Visited = 1


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

        def dfs(start):
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

        for u in nodes.keys():
            if u in visited:
                continue
            cc.append(dfs(u))
        return cc

    def topological_sort(self) -> list:
        result = []
        statuses = dict()

        def dfs(node):
            if statuses.get(node) == _Visiting:
                raise RuntimeError("Graph is not acyclic")
            if statuses.get(node) == _Visited:
                return

            statuses[node] = _Visiting
            for y in self.nodes.get(node, set()):
                dfs(y)

            statuses[node] = _Visited
            result.insert(0, node)

        for x in self.nodes:
            dfs(x)

        return result
