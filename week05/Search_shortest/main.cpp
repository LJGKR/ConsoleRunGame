#include <iostream>
#include <vector>
#include <queue>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MAX_SIZE = 10;
const int MAX_OBSTACLES = 10;

int SIZE, NUM_OBSTACLES, START, END;     //맵 크기, 장애물 개수, 시작점, 목적지를 입력받을 변수
int map[MAX_SIZE][MAX_SIZE];             //맵을 저장할 2차원 배열
int dist[MAX_SIZE * MAX_SIZE];           //시작점에서부터의 거리를 넣기 위한 변수
bool visited[MAX_SIZE * MAX_SIZE];       //방문했던 곳을 체크하기 위한 변수
int parent[MAX_SIZE * MAX_SIZE];         //트리 부모 노드
vector<int> graph[MAX_SIZE * MAX_SIZE];

// 랜덤하게 장애물 생성
void generateObstacles() {
    srand(time(NULL));

    for (int i = 0; i < NUM_OBSTACLES; i++) {
        int x = rand() % SIZE;                  //입력한 장애물의 개수만큼 x,y값을 랜덤으로 정해주고 장애물 생성
        int y = rand() % SIZE;

        // 이미 장애물이 있는 경우 다시 생성
        while (map[x][y] == 1) {
            x = rand() % SIZE;
            y = rand() % SIZE;
        }

        map[x][y] = 1;         //1인지 아닌지를 통해서 그 공간에 장애물이 있는지 없는지 확인
    }
}

// 그래프 생성
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
// 각 노드에 인접 노드가 있다면 벡터에 노드를 추가해주고 벽으로 막혀있따다면 생성하지 않고 다시 탐색하면서 그래프 생성

// 다익스트라 알고리즘 수행
void dijkstra() {
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;

    for (int i = 0; i < SIZE * SIZE; i++) {
        dist[i] = 987654321;
        visited[i] = false;
        parent[i] = -1;
    }

    dist[START] = 0;               //시작점에서 거리 0 시작
    pq.push(make_pair(0, START));

    while (!pq.empty()) {
        int cur = pq.top().second;       //노드의 번호 저장
        pq.pop();

        if (visited[cur]) {
            continue;
        }

        visited[cur] = true;             //방문했다면 트루로 변경

        for (int i = 0; i < graph[cur].size(); i++) {
            int next = graph[cur][i];

            if (!visited[next]) {
                int weight = 1;                           //거리를 1 늘려줌
                if (map[next / SIZE][next % SIZE] == 1) { //장애물인 경우
                    weight = 987654321;                   //거리를 갱신하지 못하게
                }


                if (dist[next] > dist[cur] + weight) {
                    dist[next] = dist[cur] + weight;          //최단거리를 갱신해준다
                    pq.push(make_pair(dist[next], next));
                    parent[next] = cur;                       //부모노드에 인접노드 전달
                }
                for (int i = 1; i <= SIZE; i++) {
                    if (next == SIZE * i) {              //맵을 size * size로 만들기 위해 특정 수에서 거리 갱신을 막음
                        weight = 987654321;
                    }
                }
            }
        }
    }
}

// 최단경로 출력
void printPath() {
    int cur = END;

    while (cur != START) {
        int row = cur / SIZE;
        int col = cur % SIZE;
        map[row][col] = 2; // 경로 표시
        cur = parent[cur];
    }

    map[START / SIZE][START % SIZE] = 3; // 시작점 표시
    map[END / SIZE][END % SIZE] = 4; // 목적지 표시

    cout << endl << "최단거리: " << dist[END] << endl;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (map[i][j] == 0) {         //그냥 길일때
                cout << "□ ";
            }
            else if (map[i][j] == 1) {    //장애물
                cout << "▣ ";
            }
            else if (map[i][j] == 2) {    //최단경로
                cout << "◆ ";
            }
            else if (map[i][j] == 3) {    //시작점
                cout << "S ";
            }
            else if (map[i][j] == 4) {    //목적지
                cout << "E ";
            }
        }
        cout << endl;
    }
}

int main() {
    cout << "맵의 크기를 입력하세요(1 이상 10 이하): ";
    cin >> SIZE;
    cout << "장애물의 개수를 입력하세요(0 이상 20이하): ";
    cin >> NUM_OBSTACLES;
    cout << "시작점을 입력하세요(0 이상 " << SIZE * SIZE - 1 << " 이하): ";
    cin >> START;
    cout << "목적지를 입력하세요(0 이상 " << SIZE * SIZE - 1 << " 이하): ";
    cin >> END;

    generateObstacles();
    generateGraph();
    dijkstra();
    printPath();

    cout << endl << "S : 시작점" << endl;
    cout << "E : 목적지" << endl;
    cout << "□ : 길" << endl;
    cout << "▣ : 장애물" << endl;
    cout << "◆ : 최단경로" << endl;
    return 0;
}
