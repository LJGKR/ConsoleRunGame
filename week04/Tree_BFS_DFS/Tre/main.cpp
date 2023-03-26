#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int MAX = 100; // 최대 정점 수
vector<int>* graph; // 인접 리스트
bool* visited; // 방문 여부 체크

void dfs(int v) {
    visited[v] = true; // 현재 정점 방문 체크
    cout << v << " "; // 현재 정점 출력

    for (int i = 0; i < graph[v].size(); i++) {
        int next = graph[v][i];
        if (!visited[next]) { // 다음 정점이 방문되지 않았다면
            dfs(next); // 다음 정점으로 이동
        }
    }
}

void bfs(int start) {
    queue<int> q;
    visited[start] = true; // 시작 정점 방문 체크
    q.push(start); // 시작 정점 큐에 삽입

    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        cout << cur << " "; // 현재 정점 출력

        for (int i = 0; i < graph[cur].size(); i++) {
            int next = graph[cur][i];
            if (!visited[next]) { // 다음 정점이 방문되지 않았다면
                visited[next] = true; // 다음 정점 방문 체크
                q.push(next); // 다음 정점 큐에 삽입
            }
        }
    }
}

int main() {
    int n, m; // n은 정점 수, m은 간선 수
    cin >> n >> m;

    graph = new vector<int>[n + 1]; // 인접 리스트 동적 할당
    visited = new bool[n + 1]; // 방문 여부 배열 동적 할당

    for (int i = 0; i < m; i++) {
        int u, v; // 간선 정보 (u에서 v로 가는 간선)
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u); // 무방향 그래프이므로 양쪽으로 추가
    }

    for (int i = 1; i <= n; i++) {
        sort(graph[i].begin(), graph[i].end()); // 인접 리스트 정렬
    }

    // DFS 탐색
    fill(visited, visited + n + 1, false);
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) { // 정점 i가 방문되지 않았다면
            dfs(i); // i부터 DFS 탐색 시작
        }
    }
    cout << endl;

    // BFS 탐색
    fill(visited, visited + n + 1, false);
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) { // 정점 i가 방문되지 않았다면
            bfs(i); // i부터 BFS 탐색 시작
        }
    }
    cout << endl;

    delete[] graph; // 인접 리스트 메모리 해제
    delete[] visited; // 방문 여부 배열 메모리 해제

    return 0;
}
