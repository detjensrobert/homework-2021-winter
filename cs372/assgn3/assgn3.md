# CS 372 Assignment 3

## Robert Detjens

---

### 1. Consider a datagram network using 32-bit host addresses. Suppose a router has four links, numbered 0 through 3, and packets are to be forwarded to the link interfaces as follows:

| Destination Address Range                                                      | Interface |
|--------------------------------------------------------------------------------|-----------|
| `11100000 00000000 00000000 00000000` to `11100000 00111111 11111111 11111111` | 0         |
| `11100000 01000000 00000000 00000000` to `11100000 01000000 11111111 11111111` | 1         |
| `11100000 01000001 00000000 00000000` to `11100001 01111111 11111111 11111111` | 2         |
| otherwise                                                                      | 3         |

#### a. Provide a forwarding table that has five entries, uses longest prefix matching, and forwards packets to the correct link interfaces.

| Prefix Match                          | Interface |
|---------------------------------------|-----------|
| `11100000 00****** ******** ********` | 0         |
| `11100000 01000000 ******** ********` | 1         |
| `11100000 ******** ******** ********` | 2         |
| `11100001 0******* ******** ********` | 2         |
| `******** ******** ******** ********` | 3         |

#### b. Describe how your forwarding table determines the appropriate link interface for datagrams with destination addresses:

- 11001000 10010001 01010001 01010101

  None of the prefixes fully match, so the packet is sent to the link with no prefix (Link 3).

- 11100001 01000000 11000011 00111100

  This matches only the 4th entry, so the packet is sent to link 2.

- 11100001 10000000 00010001 01110111

  None of the prefixes fully match, so the packet is sent to the link with no prefix (Link 3).

$\pagebreak$

### 2. Consider a datagram network using 8-bit host addresses. Suppose a router uses longest prefix matching and has the following forwarding table. For each of the four interfaces, give the associated range of destination host addresses and the number of addresses in the range.

| Prefix Match | Interface |
|--------------|-----------|
| `00******`   | 0         |
| `010*****`   | 1         |
| `011*****`   | 2         |
| `10******`   | 2         |
| `11******`   | 3         |


| Destination Address Range | Interface |
|---------------------------|-----------|
| `00000000` to `00111111`  | 0         |
| `01000000` to `01011111`  | 1         |
| `01100000` to `10111111`  | 2         |
| `11000000` to `11111111`  | 3         |


### 3. Consider a datagram network using 8-bit host addresses. Suppose a router uses longest prefix matching and has the following forwarding table. For each of the four interfaces, give the associated range of destination host addresses and the number of addresses in the range.

| Prefix Match | Interface |
|--------------|-----------|
| `1*******`   | 0         |
| `10******`   | 1         |
| `111*****`   | 2         |
| otherwise    | 3         |

| Destination Address Range | Interface |
|---------------------------|-----------|
| `00000000` to `01111111`  | 3         |
| `10000000` to `10111111`  | 1         |
| `11000000` to `11011111`  | 0         |
| `11100000` to `11111111`  | 2         |

$\pagebreak$

### 4. Consider a router that interconnects three subnets: Subnet 1, Subnet 2, and Subnet 3. Suppose all of the interfaces in each of these three subnets are required to have the prefix `223.1.17/24`. Also suppose that Subnet 1 is required to support at least 60 interfaces, Subnet 2 is to support at least 90 interfaces, and Subnet 3 is to support at least 12 interfaces. Provide three network addresses (of the form `a.b.c.d/x`) that satisfy these constraints.

| Name | Minimum Subnet Size | Example Subnet    |
|------|---------------------|-------------------|
| 1    | `/26`               | `223.1.17.0/26`   |
| 2    | `/25`               | `223.1.17.128/25` |
| 3    | `/28`               | `223.1.17.64/28`  |

### 5 Consider a subnet with prefix `128.119.40.128/26`.

#### 5.a Give an example of one IP address (of form `xxx.xxx.xxx.xxx`) that can be assigned to this network.

`128.119.40.133` *(any IP between `128.119.40.128` to `128.119.40.191` is valid)*

### 5.b Suppose an ISP owns the block of addresses of the form `128.119.40.64/26`. Suppose it wants to create four subnets from this block, with each block having the same number of IP addresses. What are the prefixes (of form `a.b.c.d/x`) for the four subnets?

- `128.119.40.64/28`
- `128.119.40.80/28`
- `128.119.40.96/28`
- `128.119.40.112/28`

$\pagebreak$

### 6. Consider the following network. With the indicated link costs, use Dijkstras shortest-path algorithm to compute the shortest path from $X$ to all network nodes. Show how the algorithm works by computing a table.

![Network for Q6](https://i.imgur.com/0MJrz6q.png){ height=200px }

| Step | Visited Nodes ($N'$) | $Dist_{x}(T)$ | $Dist_{x}(U)$ | $Dist_{x}(V)$ | $Dist_{x}(W)$ | $Dist_{x}(Y)$ | $Dist_{x}(Z)$ |
|:----:|---------------------:|---------------|---------------|---------------|---------------|---------------|---------------|
|  0   |                    x | $\infty$      | $\infty$      | 3, xv         | 6, xw         | 6, xy         | 8, xz         |
|  1   |                   xv | 7, xvt        | 6, xvu        |               | 6, xw         | 6, xy         | 8, xz         |
|  2   |                  xvw | 7, xvt        | 6, xvu        |               |               | 6, xy         | 8, xz         |
|  3   |                 xvwy | 7, xvt        | 6, xvu        |               |               |               | 8, xz         |
|  4   |                xvwyu | 7, xvt        |               |               |               |               | 8, xz         |
|  5   |               xvwyut |               |               |               |               |               | 8, xz         |
|  6   |              xvwyutz |               |               |               |               |               |               |
|      |       *Final costs:* | 7             | 6             | 3             | 6             | 6             | 8             |

$\pagebreak$

### 7. Consider the network shown below, and assume that each node initially knows the costs to each of its neighbors. Consider the distance-vector algorithm and show the distance table entries at node $Z$.

![Network for Q7](https://i.imgur.com/e2ll2yC.png){ height=200px }

|  From z to: | u        | v     | x     | y        | z     |
|------------:|----------|-------|-------|----------|-------|
| time $t=0$: | $\infty$ | **6** | **2** | $\infty$ | **0** |
|      $t=1$: | **7**    | **5** | 2     | **5**    | 0     |
|      $t=2$: | **6**    | 5     | 2     | 5        | 0     |
|      $t=3$: | 6        | 5     | 2     | 5        | 0     |
|  $t \ge 4$: | 6        | 5     | 2     | 5        | 0     |

At time $t=0$, Z only knows the cost of itself and its immediate neighbors V and X. At $t=1$, information about U (via V), Y (via X), V (via X), and X (via V) arrives, and a new minimum cost to U, V, and Y is calculated. At $t=2$, a new lowest cost to U is received from X and the vector is updated again. At $t=3$, new information is received but does not cause a new minimum path and the vector is not updated. From $t=4$ onwards, all paths have propagated and no further updates are made.
