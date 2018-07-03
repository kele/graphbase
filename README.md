# graphbase

## Hypothesis: Menger Theorem for mixed edge and vertex connectivity

Source: Beineke, Lowell W., and Frank Harary. "The connectivity function of a graph." Mathematika 14.2 (1967): 197-202.

If _(k, l)_ is a connectivity pair for vertices _s_ and _t_ in graph _G_, then 
there are _k + l_ edge-disjoint paths joining _s_ and _t_, of which _k_ are 
mutually non-vertex-intersecting.

## Main goal

Test the hypothesis for all small graphs (n <= 10).

## Goal

Create a system where queries like the above can be executed in a distributed fashion.
