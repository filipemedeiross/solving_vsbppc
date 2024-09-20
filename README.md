<h1>SOLVING VSBPPC</h1>

## Introduction

The **Bin Packing Problem** (BPP) is a combinatorial optimization problem that involves packing a set of items of varying sizes into a finite number of bins, each with a fixed capacity. The objective is to minimize the number of bins used while ensuring that the total size of the items in each bin does not exceed its capacity.

This problem has the following variants:

1. **Bin Packing Problem with Conflicts** (BPPC): in this variant certain items cannot be packed together due to conflicts, the objective remains to minimize the number of bins used while respecting these conflicts.
2. **Variable Sized Bin Packing Problem** (VSBPP): this variant involves bins of different capacities, the goal is to minimize the total cost associated with the bins used taking into account their varying sizes.

In this work, we will focus on the **Variable Sized Bin Packing Problem with Conflicts** (VSBPPC, which generalizes the BPP, BPPC and VSBPP), this problem involves packing items into bins of varying sizes while considering conflicts between certain items. The VSBPPC presents additional challenges, including selecting appropriate bin sizes, minimizing total costs and ensuring that conflicting items are not packed together, as a result it is a more complex and comprehensive problem.

Exemplifying its application, this problem models a scenario where multiple files must be stored across a heterogeneous network of computers, each with different storage capacities and other specifications. The goal is to minimize the overall cost of the machines used while implementing a fault tolerance mechanism that involves duplicating critical files and ensuring that these duplicates, which create conflicts, are assigned to separate machines:

<p align="center">
    <img src="https://github.com/filipemedeiross/solving_vsbppc/blob/main/examples/vsbppc_application.png?raw=true" width="550" height="350">
</p>

## Modeling as Integer Programming

The mathematical model for the VSBPPC minimizes the total cost of the bins used, considering both the size of the bins and the conflicts between items. We present the integer programming model found in Ekici (2023):

**Decision Variables**

If item $i$ is packed into bin $t$,

$$
x_{it}, \quad i \in V, t \in N
$$

If bin $t$ is a type $k$ bin,

$$
y_{tk}, \quad t \in N, k \in B
$$

**Objective Function**

$$
Min \sum\limits_{t \in N} \sum\limits_{k \in B} C_{k}y_{tk}
$$

**Subject to**

$$
\sum\limits_{i \in V}v_{i}x_{it} \leq \sum\limits_{k \in B}W_{k}y_{tk}, \quad t \in N
$$

$$
\sum\limits_{t \in N}x_{it} = 1, \quad i \in V
$$

$$
\sum\limits_{k \in B}y_{tk} \leq 1, \quad t \in N
$$

$$
x_{it} + x_{jt} \leq \sum\limits_{k \in B}y_{tk}, \quad (i, j) \in E, t \in N
$$

$$
\sum\limits_{i \in V}v_{i}x_{i,t-1} \geq \sum\limits_{i \in V}v_{i}x_{it}, \quad t \in N\setminus\set{1}
$$

$$
x_{it} \in \set{0, 1}, \quad i \in V, t \in N
$$

$$
y_{tk} \in \set{0, 1}, \quad t \in N, k \in B
$$

## Instances

In general, a problem instance must first specify the number of items to be packed and, for each item, it then details its size and the indices of other items that conflict with it. The test instances follow the specifications below:

1. **x** specifies the number of items in the instance:
   - $1 \rightarrow 100$
   - $2 \rightarrow 200$
2. **y** specifies the interval from which the item sizes are generated:
   - $1 \rightarrow [ 1, 100]$
   - $2 \rightarrow [20, 100]$
   - $3 \rightarrow [50, 100]$
3. **z** specifies the average conflict graph density:
    - $0 \rightarrow  0.0$
    - $1 \rightarrow  0.1$
    - $2 \rightarrow  0.2$
    - $3 \rightarrow  0.3$
    - $4 \rightarrow  0.4$
    - $5 \rightarrow  0.5$
    - $6 \rightarrow  0.6$
    - $7 \rightarrow  0.7$
    - $8 \rightarrow  0.8$
    - $9 \rightarrow  0.9$
    - $10 \rightarrow 0.95$
    - $11 \rightarrow 0.99$
4. **t** specifies the instance number.

> **Note 1**.: The instances are in the format "Correia_Random_x_y_z_t.txt".

> **Note 2**.: The size and cost of the available bins are separate from the problem instance and should be specified independently.

To represent problem instances on the computer, the `Instance` class was designed to encapsulate key problem attributes, including item weights and their conflict graph. Additionally, the total number of items is stored as an attribute, this design choice enhances efficiency with minimal memory overhead by eliminating the need to traverse data structures to determine the number of elements during each iteration:

```cpp
class Instance {
    public:
        int   n;  // number of items
        int*  v;  // size of items
        int** G;  // conflict graph
        int   s;  // minimum item size
        float d;  // conflict graph density

        (...)
```

The extended conflict graph was employed to enhance efficiency in the later stages of optimization. When the sum of the sizes of two items exceeds the capacity of the largest bin, a conflict exists between them, as they cannot be allocated together. This approach improves efficiency by removing the need to repeatedly check item weights:

```cpp
(...)

// Extended conflict graph
for (v1 = 0; v1 < n-1; v1++)
    for (v2 = v1+1; v2 < n; v2++)
        if (v[v1] + v[v2] > MAX_COST)
            G[v1][v2] = G[v2][v1] = 1;

(...)
```

## Solution

In the solution, each bin is represented by an instance of the `Bin` class, which maintains key attributes: the bin type $k$ and the items it contains. To minimize recalculations, the attribute $s$ records the current used capacity, while the attribute $n$ keeps track of the number of items in the bin.

A list of items was chosen because constant-time insertion and removal operations are crucial during the optimization phase. Conversely, scanning operations are more frequently used, whereas retrieval operations are not employed.

```cpp
class Bin {
    public:
        int k;  // bin type
        int s;  // capacity used
        int n;  // number of items in the bin
        std::list <int> items;

        (...)
```

A solution is represented by an instance of the `Solution` class, which manages a collection of bins. To improve efficiency, it tracks the number of bins and the current value of the objective function.

```cpp
class Solution {
    public:
        int   n;  // number of bins
        int obj;  // objective value
        Bin** S;  // bins reference

        (...)
```

The bins are organized using a pointer-to-pointer structure of `Bin`, allocated with a maximum capacity corresponding to the number of items, which serves as an upper bound for the number of bins. This design avoids the need for dynamic memory allocation associated with the `Vector` container, while still allowing constant-time retrieval of each bin, though it requires a small amount of extra memory for pointers.

<p align="center">
    <img src="https://github.com/filipemedeiross/solving_vsbppc/blob/main/examples/solution.png?raw=true" width="400" height="200">
</p>

Another advantage of the `Bin** S` data structure is the flexibility it provides for implementing the deletion operation. The `Vector` container assumes that the order of elements is important, so removing an element from the middle of the vector involves shifting the subsequent elements to maintain order.

<p align="center">
    <img src="https://github.com/filipemedeiross/solving_vsbppc/blob/main/examples/vector_erase.png?raw=true" width="400" height="30">
</p>

However, for the problem at hand, the order of the bins is not important; we only need to know the type of each bin and the items it contains. Therefore, we can remove an element from the middle of the vector, replacing its pointer with the last element's pointer and then using a null pointer to eliminate redundancy at the end. By adopting this method, we decrease the complexity of the bin removal operation from linear to constant time.

<p align="center">
    <img src="https://github.com/filipemedeiross/solving_vsbppc/blob/main/examples/erase_bin.png?raw=true" width="400" height="150">
</p>

## Large Neighborhood Search Algorithm

## Intelligence-Guided Constructive Heuristics

## Local Search

## Destroying a Solution

## References

Cabral, Lucídio dos Anjos Formiga. **Introdução à Pesquisa Operacional**. UFPB/CCEN/DE, Julho 1996.

Ekici, A. **A Large Neighborhood Search Algorithm and Lower Bounds for the Variable-Sized Bin Packing Problem with Conflicts**. European Journal of Operational Research, vol. 308, pp. 1007-1020, 2023.

Souza, M. J. F. **Inteligência Computacional para Otimização: meta-heurísticas**. Departamento de Computação, Universidade Federal de Ouro Preto, Ouro Preto, Minas Gerais, 2024.
