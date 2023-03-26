#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int MAX = 100; // �ִ� ���� ��
vector<int>* graph; // ���� ����Ʈ
bool* visited; // �湮 ���� üũ

void dfs(int v) {
    visited[v] = true; // ���� ���� �湮 üũ
    cout << v << " "; // ���� ���� ���

    for (int i = 0; i < graph[v].size(); i++) {
        int next = graph[v][i];
        if (!visited[next]) { // ���� ������ �湮���� �ʾҴٸ�
            dfs(next); // ���� �������� �̵�
        }
    }
}

void bfs(int start) {
    queue<int> q;
    visited[start] = true; // ���� ���� �湮 üũ
    q.push(start); // ���� ���� ť�� ����

    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        cout << cur << " "; // ���� ���� ���

        for (int i = 0; i < graph[cur].size(); i++) {
            int next = graph[cur][i];
            if (!visited[next]) { // ���� ������ �湮���� �ʾҴٸ�
                visited[next] = true; // ���� ���� �湮 üũ
                q.push(next); // ���� ���� ť�� ����
            }
        }
    }
}

int main() {
    int n, m; // n�� ���� ��, m�� ���� ��
    cin >> n >> m;

    graph = new vector<int>[n + 1]; // ���� ����Ʈ ���� �Ҵ�
    visited = new bool[n + 1]; // �湮 ���� �迭 ���� �Ҵ�

    for (int i = 0; i < m; i++) {
        int u, v; // ���� ���� (u���� v�� ���� ����)
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u); // ������ �׷����̹Ƿ� �������� �߰�
    }

    for (int i = 1; i <= n; i++) {
        sort(graph[i].begin(), graph[i].end()); // ���� ����Ʈ ����
    }

    // DFS Ž��
    fill(visited, visited + n + 1, false);
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) { // ���� i�� �湮���� �ʾҴٸ�
            dfs(i); // i���� DFS Ž�� ����
        }
    }
    cout << endl;

    // BFS Ž��
    fill(visited, visited + n + 1, false);
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) { // ���� i�� �湮���� �ʾҴٸ�
            bfs(i); // i���� BFS Ž�� ����
        }
    }
    cout << endl;

    delete[] graph; // ���� ����Ʈ �޸� ����
    delete[] visited; // �湮 ���� �迭 �޸� ����

    return 0;
}
