Prim’s algorithm for finding the Minimum Spanning Tree

Problem: Given an undirected graph, G = <N, E>, the task is find
a minimum spanning tree of G, using the Prim’s algorithm.

I.	Input: an undirected graph, represented by a list of edges with costs, <ni, nj, c>, (an edge from ni to nj and the edge cost is c.)
  
/**The name of the input file should be given in argv[1].

The first text line is the number of nodes, N, in G, follows by a list of triplets, <ni, nj, cost>

	For example:
		5	// there are 5 nodes in the graph 
		1  5 10 // an edge <1, 5, 10>
    		2  3  5 // an edge <2, 3, 5>
     		1  2  20 // an edge <1, 2, 20>
		3  5  2 // an edge <3, 5, 2>
    		:	
		:
II.	Output-1 : 
A minimum spanning tree, MST of G, represented by a list of edges with cost

// The name of output-1 file should be given in argv[2].

The first text line is the number nodes, N, follows by the list of edges with costs in MST of G and the total cost of the MST.

For example:
     A MST of the input graph

		5	 
		3  5  2 
     		2  3  5 
    		:	
		:
		Total Cost is: 

III.	Output-2: For all debugging outputs. // The name of output-2 file should be given in argv[3].

IV.	Data structure:
1)	A graphNode class 
-	nodeID (integer)
-	Next (a graphNode pointer to the next node)
-	isEmpty (a graphNode point)
-	A constructor to create a new graphNode of a given nodeID and next should be null.
-	A distractor to free a graphNode
-	Insert method
-	Delete method

2) An edgeNode class 
- Ni (integer) // an integer 1 to N
- Nj (integer) // an integer 1 to N
- edgeCost (integer) // a positive integer > 0
- Next (an edgeNode pointer to the next edgeNode)
- a printEdgeNode method to print the info of a given edgeNode
- a constructor to create a new edgeNode of given data and next should be null.
- a distractor to free an edgeNode
- Insert method
- Delete method

	3) A PrimMST class
	
	- N (integer)//number of nodes in G
	- totalCost (integer) // initially set to zero
	- graphNodeIDarray (a 1-D array of integer, size N, dynamically allocated) 
// to mark node ID in the graph G,   initialize to 0
	- edgeList(the head of a linked list of edgeNode, should point to a dummy node)
- setA (the head of a linked list of graphNode should point to a dummy node)
	- setB (the head of a linked list of graphNode should point to a dummy node)
	- MSTofG (the head of a linked list of edgeNode, should point to a dummy node) 	
	- PrimsMST method // the Prim’s algorithm

V.	 Prim’s Algorithm

step 0:  N  get from input file
	   initialize all objects in PrimMST class accordingly

step 1: 1.1: newEdgeNode  read each <Ni, Nj, cost> from input file
  to create an edgeNode
        1.2: insert newEdgeNode into edgeList 
(in ascending order by the cost) using insertion sort as in project 1.		  
	   1.3: graphNodeIDarray[Ni]++
   graphNodeIDarray[Nj]++

step 2: repeat step 1 until the input file is empty

step 3: print graphNodeIDarry to output-2 file (with property heading)
        print edgeList (only the first 10 edges) to output-2 file (with property heading)
        
step 4: k  find the first none zero graphNodeIDarray[k],
	   newGraphNode  create a new graphNode for k
   insert newGraphNode into SetA 

step 5: k  get the next none zero graphNodeIDarray[k]
newGraphNode  create a new graphNode for k
insert newGraphNode in the front of setB

step 6: repeat step 5 until reach the end of graphNodeIDarray

step 7: newEdge  remove the front edge, say <Ni, Nj,cost>, from the edgeList
   if Ni and Nj are in the same set, discards newEdge
	  repeat step 7 until Ni and Nj are one in setA and the other in setB

step 8: - inset newEdge in the front of MSTofG
	  - add the cost in the newEdge to totalCost
- move the graphNode (Ni or Nj whoever in setB) from setB to setA 
(i.e., make a deletion in setB and make an insertion in setA)

Step 9: print setA to output-2 file (with property heading)
	  Print setB to output-2 file (with property heading)
	  Print MSTofG to output-2 file (with property heading)

step 10: repeat step 7 – step 9 until setB is empty

step 11: output MSTofG and the totalCost to output-1 file with proper heading,  one edge with cost per text line.
