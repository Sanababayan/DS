import sys
sys.setrecursionlimit(10 ** 9)
read = sys.stdin.readline
write = sys.stdout.write
zaman = 1
def dfs(u, aList, pre, post, vis):
    global zaman
    pre[u] = zaman
    zaman += 1
    vis[u] = 1
    for v in aList[u]:
        if (vis[v] == 0):
            dfs(v, aList, pre, post, vis)
    post[u] = zaman
    zaman += 1

if __name__ == '__main__':
    the_string = read()
    N, q = the_string.split()
    N, q = int(N), int(q)
    adj = [[] for i in range(N + 1)]
    for i in range(N - 1):
        the_string = read()
        ui, vi = the_string.split()
        ui, vi = int(ui), int(vi)
        adj[vi].append(ui)
        adj[ui].append(vi)
    pre = [0 for i in range(N + 1)]
    post = [0 for i in range(N + 1)]
    vis = [0 for i in range(N + 1)]
    dfs(1, adj, pre, post, vis)
    for j in range(q):
        the_string = read()
        ai, bi = the_string.split()
        ai, bi = int(ai), int(bi)
        if pre[bi] >= pre[ai] and post[bi] <= post[ai]:
            write("YES\n")
        else:
            write("NO\n")
