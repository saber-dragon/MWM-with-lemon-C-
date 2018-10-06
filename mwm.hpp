//
// Created by saber on 10/4/18.
//

#ifndef MWM_WITH_LEMON_C_MWM_HPP
#define MWM_WITH_LEMON_C_MWM_HPP
#include <iostream>
#include <vector>
#include <cassert>
#include <limits>
#include <lemon/list_graph.h>
#include <lemon/matching.h>

using lemon::INVALID;
using namespace std;

namespace lemonwrap {
const int NO_MATE = -1;

class MWM {
  typedef lemon::ListGraph Graph;
  typedef Graph::Node Node;
  typedef Graph::Edge Edge;
  typedef Graph::EdgeMap<int> WeightMap; // map each edge to a double number
  typedef lemon::MaxWeightedMatching<Graph, WeightMap> MaxWeightedMatching;
 private:
  size_t _m; // size of U
  size_t _n; // size of V
  vector<Node> _U; // vertex set U
  vector<Node> _V; // vertex set V
  Graph _g;
  WeightMap _weights;
 public:
  MWM() = delete;
  MWM(size_t m, size_t n) : _m(m), _n(n), _weights(_g) {
    for (size_t i = 0; i < m; ++i) _U.push_back(_g.addNode());
    for (size_t i = 0; i < n; ++i) _V.push_back(_g.addNode());
    Edge e;
    for (size_t i = 0; i < m; ++i) {
      for (size_t j = 0; j < n; ++j) {
        e = _g.addEdge(_U[i], _V[j]);
        _weights[e] = 0;
        assert (_g.id(e) == i * n + j);
      }
    }

  }
  void set(size_t u, size_t v, int weight) {
    assert(u < _m);
    assert(v < _n);
    Edge e = _g.edgeFromId(static_cast<int>(u * _n + v));
    _weights[e] = weight;
  }
  int get(size_t u, size_t v) const {
    assert(u < _m);
    assert(v < _n);
    Edge e = _g.edgeFromId(static_cast<int>(u * _n + v));
    return _weights[e];
  }
  std::pair<std::vector<int>, int> run() {
    /* Step 2. Run MWM on the graph */
    MaxWeightedMatching mwm(_g, _weights); /* Initialize an instance of mwm */
    mwm.run(); /* run mwm */

    /* Create a vector to store the result matching
       matching[i] = j if the edge from _U[i] to R[j] belongs to the matching.
       If no one matches with i, then matching[i] = NO_MATE.
    */
    vector<int> matching(_m);
    std::fill(matching.begin(), matching.end(), NO_MATE); // initialization

    Node u, v;
    
    /* read results */
    int weight = mwm.matchingWeight();
    for (int i = 0; i < _m; ++i) {
      u = _U[i];
      v = mwm.mate(u);
      if (v == INVALID) matching[i] = NO_MATE; /* make sure every i is setting */
      else {
        assert(_g.id(v) >= _m);
        auto o = static_cast<int>(_g.id(v) - _m);
        matching[i] = o;
      }
    }
    

    return {matching, weight};
  }
  void self_decrease(const std::vector<int> &matching, int nm) {
    Edge e;
    for (int i = 0; i < matching.size(); ++i) {
      auto j = matching[i];
      if (j == nm) continue;
      e = _g.edgeFromId(static_cast<int>(i * _n + j));
      if (_weights[e] > 0) --_weights[e];
    }
  }
  void self_increase(const std::vector<int> &matching, int nm) {
    Edge e;
    for (int i = 0; i < matching.size(); ++i) {
      auto j = matching[i];
      if (j == nm) continue;
      e = _g.edgeFromId(static_cast<int>(i * _n + j));
      ++_weights[e];
    }
  }
};
}
#endif //MWM_WITH_LEMON_C_MWM_HPP
