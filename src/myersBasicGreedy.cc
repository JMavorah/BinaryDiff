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
/*
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
*/

vector<vector<int>> myers(string A, string B) {

    vector<int> testV;
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
            testV.push_back(xEndPoint);

            if (xEndPoint >= N && yEndPoint >= M) { //solution has been found when this coord is reached
                cout << "solution found\nd = " << d << "\n\n";
                return Vs;
            }
        }
        Vs.push_back(testV);
        testV.clear();
    }
    //return Vs;
}

void reverseDiff(string A, string B, vector<vector<int>> Vs) {
    
    int N = A.length();
    int M = B.length();
    int D = Vs.size();
    int k,x,y,prevK,prevX,prevY;
    string patch = "";
    x = N; 
    y = M;

    int fullSize = ((D * (D + 1)) / 2);
    int *V = new int[fullSize];

    int j = 0;
    int index = 0;
  
    //load Vs into one array V
    for (int d = D-1; d >= 0; d--){ // 5...0
        while(index < Vs[d].size())
            V[j++] = Vs[d][index++];
        index = 0;
    }

    //V = [7,7,5,4,3,5,5,4,3,3,2,2,1,0,0];
    //V[0]=7;  V[1]=7; V[2]=5; V[3]=4; V[4]=3; V[5]=5; V[6]=5; V[7]=4; V[8]=3; V[9]=3; V[10]=2; V[11]=2; V[12]=1; V[13]=0;  V[14]=0;

    //print V
    for (int i = 0; i < fullSize; i++)
        cout << V[i] << " ";
    cout << "\n";
    

    for (int d = D; d > 0;/*x > 0 || y > 0;*/ d--){
        //y = x - k ==> k = x - y
        k = x - y;
        // cout << "Before prev init: k, x, y, = " << k << ", " << x << ", " << y << "\n";
        // cout << "After init: prevK, prevX, prevY, = " << prevK << ", " << prevX << ", " << prevY << "\n\n";

        //init prev k, x, y
        prevK = (k == -d || (k != d && V[k-1] < V[k+1])) ? k + 1 : k - 1;
        prevX = V[prevK];
        prevY = prevX - prevK;
        // cout << "After prev init: k, x, y, = " << k << ", " << x << ", " << y << "\n";
        // cout << "After init: prevK, prevX, prevY, = " << prevK << ", " << prevX << ", " << prevY << "\n\n";

        //follow diagonals
        while (x > prevX && y > prevY){
            x--;
            y--;
        }
        // cout << "After while: k, x, y, = " << k << ", " << x << ", " << y << "\n";
        // cout << "After init: prevK, prevX, prevY, = " << prevK << ", " << prevX << ", " << prevY << "\n\n";

        //construct patch:
        if(x == prevX) { //down move - insertion
        cout << "down move - insertion\n";
        patch = to_string(prevX) + "I" + B[prevX] + " " + patch;
        }
        else { // right move - deletion
        cout << "right move - deletion\n";
        patch = to_string(prevX) + "D " + patch;
        }
        x = prevX;
        y = prevY;
    }
    cout << patch << endl;
}


int main() {
    string A = "ABCABBA";
    string B = "CBABAC";

    reverseDiff(A,B,myers(A,B));
}
