#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAX_SIZE = 10;
const int MAX_OBSTACLES = 10;

int SIZE, NUM_OBSTACLES, START, END;     //�� ũ��, ��ֹ� ����, ������, �������� �Է¹��� ����
int map[MAX_SIZE][MAX_SIZE];             //���� ������ 2���� �迭
int dist[MAX_SIZE * MAX_SIZE];           //���������������� �Ÿ��� �ֱ� ���� ����
bool visited[MAX_SIZE * MAX_SIZE];       //�湮�ߴ� ���� üũ�ϱ� ���� ����
int parent[MAX_SIZE * MAX_SIZE];         //Ʈ�� �θ� ���
vector<int> graph[MAX_SIZE * MAX_SIZE];

// �����ϰ� ��ֹ� ����
void generateObstacles() {
    srand(time(NULL));

    for (int i = 0; i < NUM_OBSTACLES; i++) {
        int x = rand() % SIZE;                  //�Է��� ��ֹ��� ������ŭ x,y���� �������� �����ְ� ��ֹ� ����
        int y = rand() % SIZE;

        // �̹� ��ֹ��� �ִ� ��� �ٽ� ����
        while (map[x][y] == 1) {
            x = rand() % SIZE;
            y = rand() % SIZE;
        }

        map[x][y] = 1;         //1���� �ƴ����� ���ؼ� �� ������ ��ֹ��� �ִ��� ������ Ȯ��
    }
}

// �׷��� ����
void generateGraph() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int cur = i * SIZE + j;

            if (i > 0 && map[i - 1][j] != 1) {
                int next = (i - 1) * SIZE + j;
                graph[cur].push_back(next);
            }

            if (i < SIZE - 1 && map[i + 1][j] != 1) {
                int next = (i + 1) * SIZE + j;
                graph[cur].push_back(next);
            }

            if (j > 0 && map[i][j - 1] != 1) {
                int next = i * SIZE + (j - 1);
                graph[cur].push_back(next);
            }
            
            if (j < SIZE - 1 && map[i][j + 1] != 1) {
                int next = i * SIZE + (j + 1);
                graph[cur].push_back(next);
            }
        }
    }
}
// �� ��忡 ���� ��尡 �ִٸ� ���Ϳ� ��带 �߰����ְ� ������ �����ֵ��ٸ� �������� �ʰ� �ٽ� Ž���ϸ鼭 �׷��� ����

// ���ͽ�Ʈ�� �˰��� ����
void dijkstra() {
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;

    for (int i = 0; i < SIZE * SIZE; i++) {
        dist[i] = 987654321;
        visited[i] = false;
        parent[i] = -1;
    }

    dist[START] = 0;               //���������� �Ÿ� 0 ����
    pq.push(make_pair(0, START));

    while (!pq.empty()) {
        int cur = pq.top().second;       //����� ��ȣ ����
        pq.pop();

        if (visited[cur]) {
            continue;
        }

        visited[cur] = true;             //�湮�ߴٸ� Ʈ��� ����

        for (int i = 0; i < graph[cur].size(); i++) {
            int next = graph[cur][i];

            if (!visited[next]) {
                int weight = 1;                           //�Ÿ��� 1 �÷���
                if (map[next / SIZE][next % SIZE] == 1) { //��ֹ��� ���
                    weight = 987654321;                   //�Ÿ��� �������� ���ϰ�
                }


                if (dist[next] > dist[cur] + weight) {
                    dist[next] = dist[cur] + weight;          //�ִܰŸ��� �������ش�
                    pq.push(make_pair(dist[next], next));
                    parent[next] = cur;                       //�θ��忡 ������� ����
                }
                for (int i = 1; i <= SIZE; i++) {
                    if (next == SIZE * i) {              //���� size * size�� ����� ���� Ư�� ������ �Ÿ� ������ ����
                        weight = 987654321;
                    }
                }
            }
        }
    }
}

// �ִܰ�� ���
void printPath() {
    int cur = END;

    while (cur != START) {
        int row = cur / SIZE;
        int col = cur % SIZE;
        map[row][col] = 2; // ��� ǥ��
        cur = parent[cur];
    }

    map[START / SIZE][START % SIZE] = 3; // ������ ǥ��
    map[END / SIZE][END % SIZE] = 4; // ������ ǥ��

    cout << endl << "�ִܰŸ�: " << dist[END] << endl;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (map[i][j] == 0) {         //�׳� ���϶�
                cout << "�� ";
            }
            else if (map[i][j] == 1) {    //��ֹ�
                cout << "�� ";
            }
            else if (map[i][j] == 2) {    //�ִܰ��
                cout << "�� ";
            }
            else if (map[i][j] == 3) {    //������
                cout << "S ";
            }
            else if (map[i][j] == 4) {    //������
                cout << "E ";
            }
        }
        cout << endl;
    }
}

int main() {
    cout << "���� ũ�⸦ �Է��ϼ���(1 �̻� 10 ����): ";
    cin >> SIZE;
    cout << "��ֹ��� ������ �Է��ϼ���(0 �̻� 20����): ";
    cin >> NUM_OBSTACLES;
    cout << "�������� �Է��ϼ���(0 �̻� " << SIZE * SIZE - 1 << " ����): ";
    cin >> START;
    cout << "�������� �Է��ϼ���(0 �̻� " << SIZE * SIZE - 1 << " ����): ";
    cin >> END;

    generateObstacles();
    generateGraph();
    dijkstra();
    printPath();

    cout << endl << "S : ������" << endl;
    cout << "E : ������" << endl;
    cout << "�� : ��" << endl;
    cout << "�� : ��ֹ�" << endl;
    cout << "�� : �ִܰ��" << endl;
    return 0;
}
