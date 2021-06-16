# Break a Node

Alice and Bob are playing a game. They are given a connected undirected graph containing n nodes and m edges . Each node has a sweetness value determined by an array w.

Alice moves first,

1. In the first move Alice may break a node. Each edge connected to this node will vanish.

2. In the second move Bob will pick any connected component containing some(or all) nodes.

3. In the third move Alice will pick any remaining connected components if there are any.

the game ends in three steps. Both of them want to maximize their score by collecting the maximum possible sweetness value. they are not trying to minimize each other score.

Write a code for this.
