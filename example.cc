#include <iostream>
#include <vector>
#include <cassert>
#include <limits>
#include <lemon/list_graph.h>
#include <lemon/matching.h>

using lemon::INVALID;
using namespace std;
const size_t NO_MATE = numeric_limits<size_t>::max();
/**
* This example demonstrates the usage of lemon::MaxWeightedMatching
* in lemon C++ for computing maximum weighted matching in bipartite 
* graphs.
* 
* Note that, lemon::MaxWeightedMatching is designed for general graphs,
* not just bipartite graphs. To the best of my knowledge, the algorithms
* only working for bipartite graphs (in lemon C++) is still under development.
*
* This example uses the weighted bipartite graph in 
* https://resources.mpi-inf.mpg.de/departments/d1/teaching/ss12/AdvancedGraphAlgorithms/Slides06.pdf
* (Page 12/77).
*/

int main(){
    typedef lemon::ListGraph Graph;
    typedef Graph::Node Node;
    typedef Graph::Edge Edge;
    typedef Graph::EdgeMap<double> WeightMap; // map each edge to a double number
    typedef lemon::MaxWeightedMatching<Graph, WeightMap> MaxWeightedMatching;

        /* Step 1. create the graph */
        Graph g;
        /* 1.1 Add nodes to the graph */
        vector<Node> L; // vertex set L
        vector<Node> R; // vertex set R
        size_t m = 3; // size of L
        size_t n = 3; // size of R
        for (size_t i = 0;i < m;++ i) L.push_back(g.addNode());
        for (size_t i = 0;i < n;++ i) R.push_back(g.addNode());
        /* Note that, internally the vertices in L will be labeled as 0, 1, ..., m - 1
           and those in R will be labeled as m, m + 1, ..., m + n - 1.
        */
        /* 1.2 Add edges */
        Edge e;
        WeightMap weights(g); // weight map
        e = g.addEdge(L[0], R[0]); 
        weights[e] = 2.0;
        e = g.addEdge(L[0], R[1]); 
        weights[e] = 6.0;
        e = g.addEdge(L[0], R[2]); 
        weights[e] = 4.0;
        e = g.addEdge(L[1], R[0]); 
        weights[e] = 3.0;
        e = g.addEdge(L[1], R[1]); 
        weights[e] = 1.0;
        e = g.addEdge(L[1], R[2]); 
        weights[e] = 2.0;
        e = g.addEdge(L[2], R[0]); 
        weights[e] = 5.0;
        e = g.addEdge(L[2], R[1]); 
        weights[e] = 4.0;
        e = g.addEdge(L[2], R[2]); 
        weights[e] = 3.0;
        /* Note that, in real applications, you do not need to
           add edges one by one like what we did above. */

    /* Step 2. Run MWM on the graph */
    MaxWeightedMatching mwm(g, weights); /* Initialize an instance of mwm */
    mwm.run(); /* run mwm */

    /* Create a vector to store the result matching 
       matching[i] = j if the edge from L[i] to R[j] belongs to the matching.
       If no one matches with i, then matching[i] = NO_MATE.
    */
    vector<size_t> matching(m);
    std::fill(matching.begin(), matching.end(), NO_MATE); // initialization

    Node u, v;
    /* read results */
    for (int i = 0;i < m;++ i) {
        u = L[i];
        v = mwm.mate(u);
        if (v == INVALID) matching[i] = NO_MATE; /* make sure every i is setting */
        else {assert(g.id(v) >= m); matching[i] = g.id(v) - m;}
    }

    /* print result */
    cout << "The maximum weighted matching is:\n";
    for (size_t i = 0;i < m;++ i) if (matching[i] != NO_MATE) cout << "\tL" << i << " -- R" << matching[i] << "\n";
    cout << "Its weight is: " << mwm.matchingWeight() << endl;


    return 0;
}