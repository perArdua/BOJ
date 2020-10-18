#include <iostream>
#include <string>
#include <vector>
#include <queue>
#define endl "\n"
#define water 0
#define ice 1
#define swan 2
using namespace std;

const int dy[] = {-1, 1 ,0 ,0};
const int dx[] = {0, 0, -1, 1};

struct Point{
    int y, x;
    Point(int y, int x) : y{y}, x{x} {}
};

int row, col;
int map[1500][1500];
bool check[1500][1500];

vector<Point> swanPos;
queue<Point> waterQ;
queue<Point> g;
inline bool inRange(int y, int x){
    return ((y >= 0 && y < row) && (x >= 0 && x < col));
}

void input(){
    for(int i = 0; i < row; ++i){
        string tmp;
        cin >> tmp;
        for(int j = 0; j < tmp.size(); ++j){
            switch (tmp[j]){
                case '.':
                    map[i][j] = water;
                    break;
                case 'X':
                    map[i][j] = ice;
                    break;
                case 'L':
                    map[i][j] = swan;
                    swanPos.push_back(Point(i, j));
                    break;
                default:
                    cout << "wrong input" << endl;
                    exit(0);
                    break;
            }
        }
    }
}

void output(){
    for(int i = 0; i < row; ++i){
        for(int j = 0; j < col; ++j){
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
}

void findFirstAdjacent(){
    for(int i = 0; i < row; ++i){
        for(int j = 0; j < col; ++j){
            if(map[i][j] != ice){
                for(int dir = 0; dir < 4; ++dir){
                    const int ny = i + dy[dir];
                    const int nx = j + dx[dir];
                    if(map[ny][nx] == ice){
                        waterQ.push(Point(i, j));
                        break;
                    }
                }
            }
        }
    }
}

void melting(){
    queue<Point> tmp;
    while(!waterQ.empty()){
        Point po = waterQ.front(); waterQ.pop();
        int y = po.y, x = po.x;
        for(int dir = 0; dir < 4; ++dir){
            const int ny = y + dy[dir];
            const int nx = x + dx[dir];
            if(!inRange(ny, nx)) continue;
            if(map[ny][nx] == ice){
                map[ny][nx] = water;
                tmp.push(Point(ny, nx));
            }
        }
    }
    waterQ = move(tmp);
}

bool isSameSection(){
    queue<Point> nextStep;
    
    while(!g.empty()){
        Point tmp = g.front(); g.pop();
        int y = tmp.y, x = tmp.x;
        for(int dir = 0; dir < 4; ++dir){
            const int ny = y + dir[dy];
            const int nx = x + dir[dx];
            if(!inRange(ny, nx)) continue;
            if(map[ny][nx] == ice){
                nextStep.push(Point(ny, nx));
                continue;
            }
            if(check[ny][nx]) continue;
            /* inRange and isWater and isVisited  */
            if(ny == swanPos[1].y && nx == swanPos[1].x){
                return true;
            }else{
                g.push(Point(ny, nx));
                check[ny][nx] = true;
            }
        }
    }
    g = move(nextStep);

    return false;
}

int dfsSolve(){
    int retDays = 0;
    findFirstAdjacent();
    while(true){
        if(isSameSection()) {break;}
        else{
            melting();
            ++retDays;
        }
    }
    return retDays;
}

void initStart(){
    g.push(swanPos[0]);
    check[swanPos[0].y][swanPos[0].x] = true;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> row >> col;
    input();
    initStart();
    cout << dfsSolve() << endl;
    return 0;
}