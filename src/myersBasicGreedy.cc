/*Authors: Jack Mavorah, Logan Smith
I pledge my honor that I have abided by the Stevens Honor System
Sources:
https://blog.jcoglan.com/2017/02/12/the-myers-diff-algorithm-part-1/
https://www.codeproject.com/Articles/42280/Investigating-Myers-Diff-Algorithm-Part-2-of-2
https://github.com/psionic12/Myers-Diff-in-c-
https://gist.github.com/Quasar-Kim/cafb5415ed111e47716c403de2490007 */
#include <iostream> 
#include <string.h>
using namespace std;

int myers(string A, string B) {

    int N = A.length();
    int M = B.length();
    int V[N*M];
    //int V[100];
    V[1] = 0;
    cout << "\n size of V: " << M*N << "\n\n";
    int xStart, yStart, xMid, yMid, xEnd, yEnd, snake, previousK;
    bool down;

    for (int d = 0; d <= N + M; d++) {   //find furthest paths for incrementing d values
        for (int k = -d; k <= d; k += 2) {   //find furthest path for incrementing k lines

            down = (k == -d || (k != d && V[k - 1] < V[k + 1])); //determine if next move is down or right

            previousK = down ? k + 1 : k - 1; //set previous K line depending on move direction

            xStart = V[previousK];
            yStart = xStart - previousK; //set x and y values of start point

            xMid = down ? xStart : xStart + 1;
            yMid = xMid - k; //set x and y values of mid point

            xEnd = xMid;
            yEnd = yMid; //initialize x and y values of end point to mid point

            
            snake = 0; //start snake at 0
            while (xEnd < N && yEnd < M && A[xEnd] == B[yEnd]) { //while values from A and B match ==> while following diagonals
                xEnd++; 
                yEnd++; 
                snake++;
            }

            V[k] = xEnd; //save x value of end point in V

            // check for solution
            if (xEnd >= N && yEnd >= M) /* solution has been found */{
                cout << "solution found" << endl;
                for (int i = 0; i < d; i++)
                    cout << V[i] << " ";
                cout << "\nd: " << d << "\n";
                return d;
            }
        }
    }
    return -1;
}

int main() {
    string A = "ABCABBA";
    string B = "CBABAC";
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
    //int N = A.length();
    //int M = B.length();
    //cout << N << "   " << M << endl;
    myers(A,B);
    cout << "---------------\n";
    myers(C,D);
    return 0;
}

