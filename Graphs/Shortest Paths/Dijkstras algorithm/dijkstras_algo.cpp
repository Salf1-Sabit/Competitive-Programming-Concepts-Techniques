/* Facts about dijkstras algo: 
		 - Time complexity O(V + ElogN) [where V = number of nodes and
		                                       E = number of edges]
 		 - Dijkstra only works on "non-negative edge weights".
 		 - Finds the shortest path from a SOURCE vertex to ALL 
 		 	 OTHER vertices in a graph.
 		 - It works on both directed and undirected graphs.
		 - Whichever distance for the TARGET node this algorithm finds 
		   first is the shortest path.
		 - Dijkstra moves forward greedily. As this the least 
		   path it moves ahead and that's guaranteed that that's
			 the shortest path till now.
			 
	 Implementation tricks:  
		 - Minimum Priority Queue can be created in 2 ways: 
				 - priority_queue<int, vector<int>, greater<int>> minPriorityQueue;
				 	   common operations: 
						 	 - push()
						 	 - pop() 
						 	 - top()
			 	 - multiset<int> minPriorityQueue;
			 	 		 common operations: 
			 	 		 	 - insert()
			 	 		 	 - erase()
			 	 		 	 - find()
			 	 		 	 - begin() | rbegin()
			 	 		 	 - end() | rend() */

vector<int> dijkstra (int n, int source, vector<pair<int, int>> G[]) {
  const int INF = (int) 1e9;
  vector<int> D(n, INF);
  D[source] = 0;
  multiset<array<int, 2>> Q;
  Q.insert({0,source});
  while(!Q.empty())   {
    auto [old_len, from] = *Q.begin();
    Q.erase(Q.begin());
    for(auto [to, new_len] : G[from]) {
      if(old_len + new_len < D[to]) {
        D[to] = old_len + new_len;
        Q.insert({D[to], to});
      }
    }
  }
  return D;
}
