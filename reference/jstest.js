function cloneObject(obj) {
    return Object.assign({}, obj);
}

// find shortest edit path required to transform a to b
// downward - deletion, rightward - insertion
function findShortedEditPath(a, b) {
    const n = a.length;
    const m = b.length;
    // trace of each v for each d 
    const trace = [];

    /* x values for each d, indexed by k(actually k + m)
    since k has range of d to -d, in order to use negative numbers as index
    we use an object rather than an array */
    const v = {};

    /* set v at 1 so that iteration for d = 0 picks x = 0
    which is equivalent to moving downward from (0, -1) */
    v[1] = 0;

    // max value of d is when their's no diagonals to follow in entire matrix
    for (let d = 0; d <= n + m; d++) {
        for (let k = -d; k <= d; k += 2) {

            /* in order to reach the lowest k, we should move downward
            if k !== d and moving downward from k + 1 maximizes x, select it
            otherwise, select moving rightward from k - 1 */
            let x;
            if (k === -d) {
                x = v[k + 1];
            } else if (k !== d && v[k - 1] < v[k + 1]) {
                x = v[k + 1];
            } else {
                x = v[k - 1] + 1;
            }

            let y = x - k;

            // follow available diagonals
            while (a[x] === b[y] && x < n && y < m) {
                x++;
                y++;
            }

            v[k] = x;

            // TODO: find other implementations:
            // is it possible for x or y to go beyond n or m?
            if (x >= n && y >= m) {
                console.log(d);
                return {
                    trace,
                    n,
                    m,
                };
            }
        }
        trace.push(cloneObject(v));
    }
}

function backtrack({ trace, n, m }) {
    let x = n;
    let y = m;

    return trace.reduceRight((moves, v, d) => {
        let k = x - y;

        let prevK;
        if (k === -d) {
            prevK = k + 1;
        } else if (k !== d && v[k - 1] < v[k + 1]) {
            prevK = k + 1;
        } else {
            prevK = k - 1;
        }

        let prevX = v[prevK];
        let prevY = prevX - prevK;

        // follow diagonals
        while (x > prevX && y > prevY) {
            x--;
            y--;
        }

        if (x === prevX) {
            // downward move: insert
            moves.unshift({
                operation: 'insert',
                at: prevX,
                itemIndex: prevY,
            });
        } else {
            // rightward move: delete
            moves.unshift({
                operation: 'delete',
                at: prevX,
            });
        }

        x = prevX;
        y = prevY;

        return moves;
    }, []);
}

function diff(a, b) {
    return backtrack(findShortedEditPath(a, b));
}
console.log(test('abcabba', 'cbabac'));
console.log("\n\n");
//console.log(findShortedEditPath('abcabba', 'cbabac'));
const result = diff('abcabba', 'cbabac');
console.log(result);
/* [
    { operation: 'delete', at: 0 },
    { operation: 'delete', at: 1 },
    { operation: 'insert', at: 3, itemIndex: 1 },
    { operation: 'delete', at: 5 },
    { operation: 'insert', at: 7, itemIndex: 5 }
] */