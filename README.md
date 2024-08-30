<h1>SOLVING VSBPPC</h1>

## Abstract

Application of heuristics to solve the variable-size bin packing problem with conflicts.

## Introduction

The Bin Packing Problem (BPP) is a combinatorial optimization problem that involves packing a set of items of varying sizes into a finite number of bins, each with a fixed capacity. The objective is to minimize the number of bins used while ensuring that the total size of the items in each bin does not exceed its capacity. This problem has the following variants:

1. **Bin Packing Problem with Conflicts** (BPPC): in this variant certain items cannot be packed together due to conflicts, the objective remains to minimize the number of bins used while respecting these conflicts.
2. **Variable Sized Bin Packing Problem** (VSBBP): this variant involves bins of different capacities, the goal is to minimize the total cost associated with the bins used taking into account their varying sizes.

In this work, we will focus on the **Variable Sized Bin Packing Problem with Conflicts** (VSBPPC), which generalizes the BPP, BPPC and VSBBP. This problem involves packing items into bins of varying sizes while considering conflicts between certain items. The VSBPPC presents additional challenges, including selecting appropriate bin sizes, minimizing total costs, and ensuring that conflicting items are not packed together, as a result it is a more complex and comprehensive problem than its predecessors.

The VSBPPC has practical applications in various industries where efficient space utilization is critical, and there are restrictions on how items can be grouped. It is applicable in cloud computing for virtual machine allocation, where conflicts between tasks or services may exist, and different server capacities must be considered.

The mathematical model for the VSBPPC can be formulated as an integer linear programming problem. The objective function minimizes the total cost of the bins used, considering both the size of the bins and the conflicts between items. Constraints include ensuring that the sum of item sizes within each bin does not exceed its capacity, that conflicting items are not placed in the same bin, and that each item is packed exactly once. The decision variables typically include binary indicators representing whether an item is placed in a particular bin and whether a bin of a certain size is used.

## References

Cabral, Lucídio dos Anjos Formiga. **Introdução à Pesquisa Operacional**. UFPB/CCEN/DE, Julho 1996.

Ekici, A. **A Large Neighborhood Search Algorithm and Lower Bounds for the Variable-Sized Bin Packing Problem with Conflicts**. European Journal of Operational Research, vol. 308, pp. 1007-1020, 2023.

Souza, M. J. F. **Inteligência Computacional para Otimização: meta-heurísticas**. Departamento de Computação, Universidade Federal de Ouro Preto, Ouro Preto, Minas Gerais, 2024.
