# CS 372 Assignment 1

## Robert Detjens

---

### 1. Consider two hosts, A and B, connected by a single link of rate R bps.

a. $d_{prop} = m/s$

b. $d_{trans} = L/R$

c. $d_{end} = d_{prop} + d_{trans} = m/s + L/R$

d. Just leaving A.

e. In transit along the link from A to B.

f. Recieved by B.

g. $d_{prop} = d_{trans} \rightarrow m/s = L/R \rightarrow m = \frac{L}{R}*s \rightarrow m = \frac{120b}{56000b/s} * 2.5*10^8m/s = 535714.3m = \bold{535.7km}$

### 2. How much time elapses from the time a bit is created at Host A until the bit is decoded at Host B?

$d_{chunk}$ = 448 bits per packet / 64000 bits per second = 0.007 seconds per packet

$d_{trans}$ = 448 bpp / 2*10^6 bps = 0.000224 spp

$d_{prop}$ = 10msec = .01 seconds (per 1 packet)

$d_{total} = d_{chunk} + d_{prop} + d_{trans} = 0.007 + 0.000224 + .01 =$ **0.017224 seconds** per packet

### 3. Suppose users share a 3 Mbps link. Each user requires 150 kbps when transmitting but only transmits only 10 percent of the time.

a. 3000 kbps / 150 kbps = 20 users

b. $P = 0.1$

c. $P_{120}^n = \frac{120!}{n!(120-n)!} * 0.1^n(0.9)^{120-n}$

d. $\Sigma_{n=21}^{120} P_{120}^{n} = \Sigma_{n=21}^{120} (\frac{120!}{n!(120-n)!} * 0.1^{n}(0.9)^{120-n}) = 0.00794$

### 4. Consider a packet of length L that begins at end system A and travels over three links to a destination end system. What is the end-to-end delay?

$$d_{end} = 2d_{proc} + \sum_{i=1}^{3} (\frac{L}{R_i} + \frac{d_i}{s_i})$$

$$d_{end} = 2(0.003) + 3\frac{1500*8}{2*10^6} + \frac{5000*10^3 + 4000*10^3 + 1000*10^3}{2.5*10^8} = \bold{0.064s}$$

### 5. In the above problem, suppose $R_1=R_2=R_3=R$, $d_{proc}=0$, and bits are transmitted as soon as they are recieved. What is the end-to-end delay?

$$d_{end} = \frac{L}{R} + \sum_{i=1}^{3} \frac{d_i}{s_i}$$

$$d_{end} = \frac{1500*8}{2*10^6} + \frac{5000*10^3 + 4000*10^3 + 1000*10^3}{2.5*10^8} = \bold{0.046s}$$

### 6. What is the queuing delay for the packet?  More generally, what is the queuing delay when all packets have length L, the transmission rate is R, x bits of the currently-being-transmitted packethave been transmitted, and n packets are already in the queue?

$$d_{queue} = 4.5\frac{1500*8}{2*10^6} = 0.027s$$

$$d_{queue} = (n + \frac{L - x}{L})\frac{L}{R}$$

### 7.

a. What is the average queuing delay for the N packets?

$$\frac{\sum_{n=1}^{N} \frac{(n-1)L}{R} }{N}$$

b. N packets arrive to the link every LN/R seconds. What is the average queuing delay of a packet?

$$\frac{\sum_{n=1}^{N} \frac{(n-1)L}{R} }{N}$$

### 8. Consider the queuing delay in a router buffer. Let I denote traffic intensity: $I = La/R$. Suppose that the queuing delay takes the form $IL/R(1-I)$ for $I<1$.

a. Provide a formula for the total delay, that is, the queuing delay plus the transmission delay.

$$d_{total} = d_{queue} + d_{trans} = \frac{IL}{R(1-I)} + \frac{L}{R} = \frac{aL^2}{R^2(1-aL/R)} + \frac{L}{R}$$

b. Plot the total delay as a function of $L/R$.

![$f(x) = x(\frac{ax}{1-ax} + 1), a = 10$](https://i.imgur.com/B04JJFf.png){ height=300px }

$\pagebreak$

### 9. Based on the formula for the total delay, derive a formula for the total delay in terms of a and $\mu$.

$$d_{total} = \frac{a}{\mu^2(1-a/\mu)} + \frac{1}{\mu}$$

### 10. Assume that we know the bottleneck link along the path from the server to the client is the first link with rate $R_s$ bits/sec.

a. What is the packet inter-arrival time at the destination? How much time elapses from when the last bit of the first packet arrives until the last bit of the second packet arrives?

   $L/R_s$

b. Now assume that the second link is the bottleneck link. Is it possible that the second packet queues at the input queue of the second link?

   Yes. Since the second link is smaller, the router will not be finished sending the first packet before the second packet arrives; i.e. $2(L/R_s) + d_{prop} < L/R_s + d_{prop} + L/R_c$

   How long must the server wait to ensure no queuing occurs before the second link?

   $T = L/R_c - L/R_s$

### 11. Suppose two hosts A and B are separated by 20,000 kilometers and are connected by a direct link of R=2 Mbps. Suppose the propagation speed over the link is $2.5*10^8$ meters/sec

a. $R*d_{prop} = 2*10^6 * \frac{20,000*10^3}{2.5*10^8} = 160,000$ bits

b. 160,000 bits

c. The bandwidth-delay product is the maximum number of bits in transit in a link at any given time.

d. $\frac{20,000*10^3}{160,000} = 125\ m/b$. This is greater than a football field at 91.44m (or 100m for soccer).

e. $\frac{m}{R*\frac{m}{s}} = \frac{s}{R}$

### 12. Suppose there is a 10 Mbps microwave link between a geostationary satellite and its base station on Earth. Everyminute the satellite takes a digital photo and sends it to the base station. Assume a propagation speed of $2.4*10^8$ meters/sec. Note that geostationary satellite is d = 36,000 kilometers away from earth surface.

a. $d_{prop} = d/s = \frac{36*10^6}{2.4*10^8} = 0.15s$

b. $R*d_{prop} = 10*10^6 * 0.15 = 1,500,000$ bits

c. $10*10^6 * 60s$ = 600,000,000b = 600Mb

$\pagebreak$

### 15. Hands-on Activity

a. google.com (216.58.217.46): avg 19.166

   Others:

   - codewalr.us (104.21.9.233): avg 14.243
   - gamersnexus.net (192.124.249.12): avg 34.745
   - lttstore.com (23.227.38.36): avg15.922

   `ping n #` (or `ping -c #` on Linux) is the number of times to ping the host before exiting.

b. 9 hops observed. The route:

| Hop No | Source          | Dest            | RTT  |
|--------|-----------------|-----------------|------|
| 1      | 192.168.0.102   | 192.168.0.1     | 0.2  |
| 2      | 192.168.0.1     | 10.4.0.1        | 0.4  |
| 3      | 10.4.0.1        | 63.146.160.113  | 7.3  |
| 4      | 63.146.160.13   | 64.14.41.154    | 12.2 |
| 5      | 64.14.41.154    | 64.14.41.162    | 14.0 |
| 6      | 64.14.41.162    | 72.14.221.110   | 12.0 |
| 7      | 72.14.221.110   | 108.170.245.113 | 12.8 |
| 8      | 108.170.245.113 | 74.125.253.67   | 14.6 |
| 9      | 74.125.253.67   | 216.58.217.46   | 14.7 |

c. The first packet is from the local gateway `192.168.0.1` -- the first hop. Second machine is `10.4.0.1` -- the second hop.

   ![](https://i.imgur.com/rCs9pgH.png)
