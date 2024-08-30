<h1>SOLVING VSBPPC</h1>

## Abstract

Application of heuristics to solve the variable-size bin packing problem with conflicts...

## Introduction

The **Bin Packing Problem** (BPP) is a combinatorial optimization problem that involves packing a set of items of varying sizes into a finite number of bins, each with a fixed capacity. The objective is to minimize the number of bins used while ensuring that the total size of the items in each bin does not exceed its capacity, this problem has the following variants:

1. **Bin Packing Problem with Conflicts** (BPPC): in this variant certain items cannot be packed together due to conflicts, the objective remains to minimize the number of bins used while respecting these conflicts.
2. **Variable Sized Bin Packing Problem** (VSBBP): this variant involves bins of different capacities, the goal is to minimize the total cost associated with the bins used taking into account their varying sizes.

In this work, we will focus on the **Variable Sized Bin Packing Problem with Conflicts** (VSBPPC, which generalizes the BPP, BPPC and VSBBP), this problem involves packing items into bins of varying sizes while considering conflicts between certain items. The VSBPPC presents additional challenges, including selecting appropriate bin sizes, minimizing total costs and ensuring that conflicting items are not packed together, as a result it is a more complex and comprehensive problem than its predecessors.

Exemplifying its application, this problem models a scenario where multiple files must be stored across a heterogeneous network of computers, each with different storage capacities, processors and other specifications, with the objective of minimizing the number of machines used while implementing a fault tolerance mechanism that involves duplicating critical files and ensuring that these duplicates, which create conflicts, are assigned to separate machines:

<p align="center"> 
    <img src="https://github.com/filipemedeiross/solving_vsbppc/blob/main/examples/vsbppc_application.png?raw=true" width="500" height="350">
</p>

The mathematical model for the VSBPPC minimizes the total cost of the bins used, considering both the size of the bins and the conflicts between items. We present the integer programming model found in Ekici (2023):

**Decision Variables**:

If item $i$ is packed into bin $t$:

$$
x_{it},   i \in V, t \in N
$$

If bin $t$ is a type $k$ bin:

$$
y_{tk},   t \in N, k \in B
$$

**Objective Function**:

$$
Min \sum\limits_{t \in N} \sum\limits_{k \in B} C_{k}y_{tk}
$$

**Subject to**:

$$
\sum\limits_{i \in V}v_{i}x_{it} \leq \sum\limits_{k \in B}W_{k}y_{tk},   \forall t \in N
$$

$$
\sum\limits_{t \in N}x_{it} = 1,   \forall i \in V
$$

$$
\sum\limits_{k \in B}y_{tk} \leq 1,   \forall t \in N
$$

$$
x_{it} + x_{jt} \leq \sum\limits_{k \in B}y_{tk},   \forall (i, j) \in E, \forall t \in N
$$

$$
\sum\limits_{i \in V}v_{i}x_{i,t-1} \geq \sum\limits_{i \in V}v_{i}x_{it},   \forall t \in N\setminus\set{1}
$$

$$
x_{it} \in \set{0, 1}, \forall i \in V, \forall t \in N
$$

$$
y_{tk} \in \set{0, 1}, \forall t \in N, \forall k \in B
$$

## References

Cabral, Lucídio dos Anjos Formiga. **Introdução à Pesquisa Operacional**. UFPB/CCEN/DE, Julho 1996.

Ekici, A. **A Large Neighborhood Search Algorithm and Lower Bounds for the Variable-Sized Bin Packing Problem with Conflicts**. European Journal of Operational Research, vol. 308, pp. 1007-1020, 2023.

Souza, M. J. F. **Inteligência Computacional para Otimização: meta-heurísticas**. Departamento de Computação, Universidade Federal de Ouro Preto, Ouro Preto, Minas Gerais, 2024.
