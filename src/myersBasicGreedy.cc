/*Authors: Jack Mavorah, Logan Smith
I pledge my honor that I have abided by the Stevens Honor System
Sources:
https://blog.jcoglan.com/2017/02/12/the-myers-diff-algorithm-part-1/
https://www.codeproject.com/Articles/42280/Investigating-Myers-Diff-Algorithm-Part-2-of-2
https://github.com/psionic12/Myers-Diff-in-c-
https://gist.github.com/Quasar-Kim/cafb5415ed111e47716c403de2490007 */
#include <iostream> 
#include <string.h>
#include <list>
#include <vector>
using namespace std;

class Point{
    public:
        int x,y;
        Point(): x(0),y(0){}
        Point(int x, int y): x(x),y(y){}

        friend ostream& operator <<(ostream& s, const Point& a){
        s << a.x << ',' << a.y;
        return s;
    }
};

class Snake{
    public:
        Point start;
        Point mid;
        Point end;
        Snake(Point start, Point mid, Point end): start(start),mid(mid),end(end){}

        friend ostream& operator <<(ostream& s, const Snake& a){
        s << "(" << a.start << "), (" << a.mid << "), (" << a.end << ")";
        return s;
        }
};


vector<int> testV;
//vector<int>::iterator it;
vector<vector<int>> Vs;

vector<vector<int>> myers(string A, string B) {

    vector<int> testV;
    //vector<int>::iterator it;
    vector<vector<int>> Vs;

    int N = A.length();
    int M = B.length();
    int * V = new int [2*(N+M)];
    V[1] = 0;

    int xStartPoint, yStartPoint, xMidPoint, yMidPoint, xEndPoint, yEndPoint, snakeLength, previousK;
    bool moveDown;


    for (int d = 0; d <= N + M; d++) {        //find furthest paths for incrementing d values
        for (int k = -d; k <= d; k += 2) {   //find furthest path for incrementing k lines

            moveDown = (k == -d || (k != d && V[k - 1] < V[k + 1])); //determine if next move is down or right
            previousK = moveDown ? k + 1 : k - 1; //set previous K line depending on move direction

            xStartPoint = V[previousK];
            yStartPoint = xStartPoint - previousK; //set x and y values of start point

            xMidPoint = moveDown ? xStartPoint : xStartPoint + 1;
            yMidPoint = xMidPoint - k; //set x and y values of mid point

            xEndPoint = xMidPoint;
            yEndPoint = yMidPoint; //initialize x and y values of end point to mid point

            snakeLength = 0; //start snake at 0
            while (xEndPoint < N && yEndPoint < M && A[xEndPoint] == B[yEndPoint]) { //while A and B match (following diagonal)
                xEndPoint++; 
                yEndPoint++; 
                snakeLength++;
            }

            V[k] = xEndPoint; //save x value of end point in V
            //testV.insert(it,k,xEndPoint);
            testV.push_back(xEndPoint);

            if (xEndPoint >= N && yEndPoint >= M) { //solution has been found when this coord is reached
                cout << "solution found\nd = " << d << "\n\n";
                // for (int i = 0; i < d; i++)
                //     cout << V[i] << " ";
                // cout << endl;
                // cout << "\nd: " << d << "\n";

                // for (int i = 0; i < Vs.size(); i++) {
                //     for (int j = 0; j < Vs[i].size(); j++)
                //         cout << Vs[i][j] << " ";
                //     cout << endl;
                // }
                return Vs;
            }
        }
        Vs.push_back(testV);
        testV.clear();
    }
}

void reverseDiff(string A, string B, vector<vector<int>> Vs, int D) {
    
    int N = A.length();
    int M = B.length();
    int d = Vs.size();
    //int * V[];

    int k,x,y,prevK,prevX,prevY;
    string patch = "";

    x = N; 
    y = M;
    //for (int i = 1; i <= d; i++)
    int fullSize = ((d * (d + 1)) / 2);
    int *V = new int[fullSize];

    for (int d = D; d >= 0; d--){
        for (int j = 0; j < Vs[d].size(); j++)
            V[j] = Vs[d][j];
    }

     for (int d = D; x > 0 || y > 0; d--){
        //y = x - k ==> k = x - y
        k = x - y;

        // if (k == -d || (k !=d && V[k-1] < V[k+1])){
        //     prevK = k + 1;
        // }
        // else{
        //     prevK = k - 1;
        // }
    
    //init prev k, x, y
        prevK = (k == -d || (k != d && V[k-1] < V[k+1])) ? k + 1 : k - 1;
        prevX = V[prevK];
        prevY = prevX - prevK;

    //follow diagonals
        while (x > prevX && y > prevY){
            x--;
            y--;
        }

    //construct patch:
        if(x == prevX) { //down move - insertion
        cout << "down move\n";
        patch = to_string(prevX) + "I" + B[prevX] + " " + patch;
        }
        else { // right move - deletion
        cout << "right move\n";
        patch = to_string(prevX) + "D " + patch;
        }
        x = prevX;
        y = prevY;
        //delete V;
    }
    cout << patch << endl;

//------------------------------------------
    // for (int i = 0; i < Vs.size(); i++) {
    // for (int j = 0; j < Vs[i].size(); j++)
    //     cout << Vs[i][j] << " ";
    // cout << endl;
    // }
}


int main() {
    string A = "ABCABBA";
    string B = "CBABAC";
    //char A[] = "ABCABBA";
    //char B[] = "CBABAC";

    // cout << "\n---------------\n";
    // myers(A,B);
    // cout << "---------------\n";

    //vector<vector<int>> test = myers(A,B);
    reverseDiff(A,B,myers(A,B),5);

}