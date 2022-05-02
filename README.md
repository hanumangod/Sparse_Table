# Sparse_Table
ADS assignment - Implementation of Sparse Table using C++

What is a Sparse Table?

A sparse table is a data structure that is used to answer range or interval
queries for a given set of numbers.
It is similar to a segment tree or fenwick tree specifically. We can say that a
sparse table is a subset of a segment tree but some of the features are
more powerful than a segment tree or fenwick tree like it resolves queries
in O(1) time only.

It is used to handle operations that have idempotent (x op x = x) properties
like we can resolve minimum or maximum or gcd queries because these
are all idempotent functions.
Operations :
● Create / Build
● Minimum Query
● Maximum Query

Construction of Sparse Table :

The main idea behind Sparse Tables is to precompute all answers for
range queries with a power of two lengths. After that, a different range
query can be answered by splitting the range into ranges with the power of
two lengths, looking up the precomputed answers, and combining them to
receive a complete answer.
To implement a sparse table, we use a 2-dimensional array where st[i][j] is
the F(i,i+1,...,i+2^(j-1)) and can be calculated using previous information as
below,
st[i][j] = F(st[i][j-1], st[i-1][i+(1<<(j-1)][j-1])

Queries On Sparse Table :

Queries are the most crucial part of a sparse table because it resolves
queries in O(1). We know that even if the interval overlaps result of the
idempotent function doesn’t affect so to answer the query we find two
segments whose length is the power of two in which the given range is fully
contained so using a sparse table we can answer that query as,
k = log2(r - l + 1)
F(st[l][k],st[r - (1 << k) + 1][k])
  
Applications :
  
1. In the database systems, many times we want to find some records in a
particular interval whose values are maximum or minimum in that range,
for example, we are given a mark sheet of students and we want to find
the minimum or maximum in some specific range for analysis purposes.
  
2. In a system or architecture where we want our query to be solved very
fast and the system itself doesn’t allow update operation at that place
instead of segment tree, sparse table perform very well.

