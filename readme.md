# FastVC

This is a solver for the minimum vertex cover problem.

## Usage
Compile with `$ make` and execute with
`$ ./fastvc [DIMACS] DATASET SEED CUTOFF`, where:
* the keyword DIMACS allows to select this format (see below). Default format is edgelist.
* dataset is the txt file containing the dataset in corresponding format.
* SEED sets random seed (default: 0).
* CUTOFF sets cutoff time in seconds (default: 0).


## Input format

### Edgelist (default)
Each line contains 2 integers separated by a space and describes one undirected edge.
Nodes may start from index 0.
For instance, here is a dataset with 4 nodes and 5 edges:
```
1 2
3 1
2 4
1 4
4 3
```

### DIMACS
The input graph is asked to be in DIMACS ascii format for undirected graphs.

A small exmple is given as follow:

```
c nodes: 4, edges: 3
c the lines begin with a 'c' are comment lines and are not considered by the solvers.
c the graph data begin with a 'p' line that in the format as:
c 'p edge <number of nodes> <number of edges>',
c followed by all 'e' lines.
p edge 4 3
e 1 2
e 1 3
e 2 4
```
