from pulp import *
import numpy as np
import numpy.random as rd
import queue

n = 10
s,t = rd.choice(n,2,replace=False)

def rand_graph():
    G = [[rd.binomial(1,0.5) for _ in range(n)] for _ in range(n)]
    for i in range(n):
        for j in range(i, n):
            if i==j:
                G[i][j] = 0
            else:
                G[i][j] = G[j][i]
    return G

def is_connected(G):
    visited = [False]*n
    q = queue.Queue()
    q.put(0)
    while(not q.empty()):
        v = q.get()
        if (not visited[v]):
            visited[v]=True
            for j in range(n):
                if G[v][j] == 1 and not visited[j]:
                    q.put(j)
    for b in visited:
        if b == 0:
            return False
    return True

def rand_connected_graph():
    G = rand_graph()
    while(not is_connected(G)):
        G = rand_graph()
    return G

def make_sets():
    edges = set()
    flow_v = set()
    flow_t = set()
    for i in range(n):
        for j in range(i):
            if (G[i][j]==1):
                edges.add((i,j))
                flow_t.add((i,j))
                flow_t.add((j,i))
                for v in range(n):
                    if v != s and v != t:
                        flow_v.add((v,i,j))
                        flow_v.add((v,j,i))
    return edges, flow_v, flow_t

def delta_plus(v):
    res = set()
    for a in range(n):
        if G[a][v] == 1:
            res.add((a,v))
    return res

def delta_minus(v):
    res = set()
    for a in range(n):
        if G[v][a] == 1:
            res.add((v,a))
    return res

G = rand_connected_graph()

print("G= ", G)
print("s,t = ", s,t)
print("")

edges, flow_v, flow_t = make_sets()

prob = LpProblem("Path-TSP", LpMinimize)

x = pulp.LpVariable.dicts('x', edges)
f_t = pulp.LpVariable.dicts('f_t', flow_t)
f_v = pulp.LpVariable.dicts('f_v', flow_v)

prob += lpSum(x)

for (v,i,j) in flow_v:
    prob += f_v[(v,i,j)] >= 0
    if j < i:
        prob += f_v[(v,i,j)] <= x[(i,j)]
    else:
        prob += f_v[(v,i,j)] <= x[(j,i)]

for (i,j) in edges:
    prob += f_t[(i,j)] >= 0
    prob += f_t[(j,i)] >= 0
    prob += f_t[(i,j)] <= x[(i,j)]
    prob += f_t[(j,i)] <= x[(i,j)]

for v in range(n):
    if v != s and v != t:
        for u in range(n):
            if u != v and u != s and u != t:
                sortant = lpSum([f_v[(v,i,j)] for (i,j) in delta_plus(u)])
                entrant = lpSum([f_v[(v,i,j)] for (i,j) in delta_minus(u)])
                prob += sortant == entrant

for v in range(n):
    if v != s and v != t:
        sortant = lpSum([f_v[(v,i,j)] for (i,j) in delta_plus(v)])
        entrant = lpSum([f_v[(v,i,j)] for (i,j) in delta_minus(v)])
        prob += sortant == entrant + 2

        sortant = lpSum([f_v[(v,i,j)] for (i,j) in delta_plus(s).union(delta_plus(t))])
        entrant = lpSum([f_v[(v,i,j)] for (i,j) in delta_minus(s).union(delta_minus(t))])
        prob += sortant == entrant - 2

        sortant = lpSum([f_t[a] for a in delta_plus(v)])
        entrant = lpSum([f_t[a] for a in delta_minus(v)])
        prob += sortant == entrant


sortant = lpSum([f_t[a] for a in delta_plus(t)])
entrant = lpSum([f_t[a] for a in delta_minus(t)])
prob += sortant == entrant + 1

entrant = lpSum([f_t[a] for a in delta_plus(s)])
sortant = lpSum([f_t[a] for a in delta_minus(s)])
prob += sortant == entrant + 1

#print(prob)

prob.solve()
print("Status:", LpStatus[prob.status])
for v in prob.variables():
    if v.name[0] == "x":
        print(v.name, "=", v.varValue)
