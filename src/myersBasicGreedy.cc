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
vector<int>::iterator it;
vector<vector<int>> Vs;
int myers(string A, string B) {

    int N = A.length();
    int M = B.length();
    int * V = new int [2*(N+M)];
    V[1] = 0;

    int xStartPoint, yStartPoint, xMidPoint, yMidPoint, xEndPoint, yEndPoint, snakeLength, previousK;
    bool moveDown;

    for (int d = 0; d <= N + M; d++) {   //find furthest paths for incrementing d values
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
            while (xEndPoint < N && yEndPoint < M && A[xEndPoint] == B[yEndPoint]) { //while A and B match (follwing )
                xEndPoint++; 
                yEndPoint++; 
                snakeLength++;
            }

            V[k] = xEndPoint; //save x value of end point in V
            //testV.insert(it,k,xEndPoint);
            //testV[k] = xEndPoint;
            //testV.push_back(xEndPoint);

            if (xEndPoint >= N && yEndPoint >= M) { //solution has been found when this coord is reached
                cout << "solution found" << endl;
                for (int i = 0; i < d; i++)
                    cout << V[i] << " ";
                cout << endl;
                for (int i = 0; i < d; i++)
                    cout << testV[i] << " ";
                cout << "\nd: " << d << "\n";
                return d;
            }
        }
        //Vs.push_back(testV);
        //Vs.insert(Vs.end(), &V[0], &V[sizeof(V)/sizeof(int)]);
    }
    return -1;
}

void reverseDiff(string A, string B) {

    int N = A.length();
    int M = B.length();
    //list<V> Vs;
    //list<Snake> snakes;
    Point p(N,M);
    Point q(1,2);
    Point r(3,4);
    Snake test(p,q,r);
    int x,y;

    //for ()
    cout << "N,M = " << p.x << "," << p.y << endl;
    cout << "N,M = " << p << endl;
    cout << "Snake test = " << test << endl;

    for (int i = 0; i < Vs.size(); i++) {
        for (int j = 0; j < Vs[i].size(); j++)
            cout << Vs[i][j] << " ";
        cout << endl;
    }
}


int main() {
    string A = "ABCABBA";
    string B = "CBABAC";
    //char A[] = "ABCABBA";
    //char B[] = "CBABAC";

    string C = "Hamlet: Do you see yonder cloud that's almost in shape of a camel? \
Polonius: By the mass, and 'tis like a camel, indeed. \
Hamlet: Methinks it is like a weasel. \
Polonius: It is backed like a weasel. \
Hamlet: Or like a whale? \
Polonius: Very like a whale. \
-- Shakespeare";
    string D = "Hamlet: Do you see the cloud over there that's almost the shape of a camel? \
Polonius: By golly, it is like a camel, indeed. \
Hamlet: I think it looks like a weasel. \
Polonius: It is shaped like a weasel. \
Hamlet: Or like a whale?  \
Polonius: It's totally like a whale. \
-- Shakespeare";

    cout << "\n---------------\n";
    myers(A,B);
    cout << "---------------\n";
    reverseDiff(A,B);
    return 0;
}