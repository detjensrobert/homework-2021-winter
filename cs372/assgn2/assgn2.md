# CS 372 Assignment 2

## Robert Detjens

---

### 1.(P22, Page 294) Consider the GBN protocol with a sender window size of $4$ and a sequence number range of $1024$. Suppose that at time $t$, the next in-order packet that the receiver is expecting has a sequence number of $k$. Assume that the medium does not reorder messages. Answer the following questions:

a. What are the possible sets of sequence numbers inside the senders window at time $t$? Justify your answer.

   $(k-4) \ldots k$. There are always 4 segments in the window at any time, so assuming all segments are delivered and ACKd successfully, the soonest the receiver can expect $k$ is if it has just received ACKd $k-4$, and the sender has just advanced the window. The worst case is if all packets before $k$ have been ACKd successfully, but $k$ has not. The sender's window will not advance past $k$ until it receives an ACK.

b. What are all possible values of the ACK field in all possible messages currently propagating back to the sender at time $t$? Justify your answer.

   $(k-4) \ldots (k-1)$. The receiver could have just received the preceding 4 packets and sent ACKs for each, or the receiver could have only just sent an ACK for $k-1$.

### 2.(P27, Page 294) Host $A$ and $B$ are communicating over a TCP connection, and Host $B$ has already received from $A$ all bytes up through byte $126$. Suppose Host $A$ then sends two segments to Host $B$ back-to-back. The first and second segments contain $80$ and $40$ bytes of data, respectively. In the first segment, the sequence number is $127$, the source port number is `302`, and the destination port number is `80`. Host $B$ sends an acknowledgment whenever it receives a segment from Host $A$.

a. In the second segment sent from Host $A$ to $B$, what are the sequence number, source port number, and destination port number?

   Sequence number: `207`, source port: `302`, dest port: `80`

b. If the first segment arrives before the second segment, in the acknowledgment of the first arriving segment, what is the acknowledgment number, the source port number, and the destination port number?

   Ack number: `127`, source port: `80`, dest port: `302`

c. If the second segment arrives before the first segment, in the acknowledgment of the first arriving segment, what is the acknowledgment number?

   Ack number: `167`, source port: `80`, dest port: `302`

d. Suppose the two segments sent by $A$ arrive in order at $B$. The first acknowledgment is lost and the second acknowledgment arrives after the first timeout interval. Draw a timing diagram, showing these segments and all other segments and acknowledgments sent. (Assume there is no additional packet loss.) For each segment in your figure, provide the sequence number and the number of bytes of data; for each acknowledgment that you add, provide the acknowledgment number.

   ![2D. timing diagram](https://i.imgur.com/SryL4ov.png){ height=300px }

### 3.(P32, Page 296) Consider the TCP procedure for estimating RTT. Suppose that $\alpha = 0.1$.  Let $SampleRTT_1$ be the most recent sample RTT, let $SampleRTT_2$ be the next most recent sample RTT, and so on.

a. For a given TCP connection, suppose four acknowledgments have been returned with corresponding `sampleRTT`s: $SampleRTT_4$, $SampleRTT_3$, $SampleRTT_2$, and $SampleRTT_1$. Express `EstimatedRTT` in terms of the four sample RTTs.

$$
\begin{split}
   EstimatedRTT &= (1-\alpha)*EstimatedRTT + \alpha*SampleRTT \\
      &= 0.9*EstimatedRTT + 0.1*SampleRTT\\
      &= 0.9*(  0.9*(  0.9*( SampleRTT_4 ) + 0.1*SampleRTT_3 ) + 0.1*SampleRTT_2 ) + 0.1*SampleRTT_1
\end{split}
$$

b. Generalize your formula for $n$ sample RTTs.

$$
EstimatedRTT_x =
\begin{cases}
   SampleRTT_n & if\ x = n \\
   0.9*( EstimatedRTT_{x+1} ) + 0.1*SampleRTT_x & if\ x < n
\end{cases}
$$

c. For the formula in part b. let $n$ approach infinity. Comment on why this averaging procedure is called an exponential moving average.

   This is an exponential moving average as a large datapoint in the past has an exponentially decreasing weight as $n$ increases, but will never reach a zero weight. A weighted moving average, in contrast, has a linear decrease in the weight of previous datapoints, so eventually old datapoints will no longer affect the new average.

$\pagebreak$

### 4.(P40, Page 297) Consider the following figure. Assuming TCP Reno is the protocol experiencing the behavior shown in the figure, answer the following questions. In all cases, you should provide a short discussion justifying your answer.

![TCP Reno Congestion](https://i.imgur.com/RyQ98at.png){ height=250px }

a. Identify the intervals of time when TCP slow start is operating.

   Time $t=1$ to $t=6$, $t=23$ to $t=26$. Slow start is the period of exponential growth.

b. Identify the intervals of time when TCP congestion avoidance is operating.

   Time $t=6$ to $t=15$, $t=16$ to $t=24$. Congestion avoidance is the period of linear increases.

c. After the 16th transmission round, is segment loss detected by a triple duplicate ACK or by a timeout?

   Yes, triple duplicate ACK. TCP Reno performs fast recovery on triple ACK instead of resetting to slow start.

d. After the 22nd transmission round, is segment loss detected by a triple duplicate ACK or by a timeout?

   Yes, timeout. If a packet times out, Reno resets back to slow start with a congestion window of 1.

e. What is the initial value of `ssthresh` at the first transmission round?

   `ssthresh` = 32. This is the point at which TCP stops the slow start and transitions to linear congestion avoidance.

f. What is the value of `ssthresh` at the 18th transmission round?

   `ssthresh` = 21. The congestion window before the triplicate ACK was 44, and fast recovery halves this to 22.

g. What is the value of `ssthresh` at the 24th transmission round?

   `ssthresh` = 21. A packet timeout does not change the threshold value, only a triplicate ACK does.

h. During what transmission round is the 70th segment sent?

   $t=7$. During the initial slow start from $t=1$ to $t=6$, $\Sigma_{n=1}^6 2^{n-1}$ (63) segments are sent. The next batch at time $t=7$ (33 segment) includes the 70th segment.

$\pagebreak$

i. Assuming a packet loss is detected after the 26th round by the receipt of a triple duplicate ACK, what will be the values of the congestion window size and of `ssthresh`?

   Congestion window = 4, `ssthresh` = 4. TCP Reno saves half of the previous congestion window as both the new congestion window and the new `sshtresh`.

j. Suppose TCP Tahoe is used (instead of TCP Reno), and assume that triple duplicate ACKs are received at the 16th round. What are the `ssthresh` and the congestion window size at the 19th round?

   Congestion window = 4, `ssthresh` = 21. TCP Tahoe sets `ssthresh` as half the previous congestion window and resets the new congestion window to 1 and performs slow start, growing exponentially until the 19th round.

k. Again suppose TCP Tahoe is used, and there is a timeout event at the 22nd round. How many packets have been sent out from 17th round till 22nd round, inclusive?

   141 packets. Assuming Tahoe is started at time $t=17$, Tahoe also performs linear congestion avoidance. The timeout occurs after the packets from round 22 are sent.

   | Time $t$:           | 17 | 18 | 19 | 20 | 21  | 22  |
   |---------------------|----|----|----|----|-----|-----|
   | Window size:        | 21 | 22 | 23 | 24 | 25  | 26  |
   | Cum. segments sent: | 21 | 43 | 66 | 90 | 115 | 141 |

### 5.(P44, Page 298) (BONUS) *did not do bonus*

### 6.(P45, Page 299) (BONUS) *did not do bonus*

### 7.(P46, Page 299) Consider that only a single TCP (Reno) connection uses one $10$ Mbps link which does not buffer any data. Suppose that this link is the only congested link between the sending and receiving hosts. Assume that the TCP sender has a huge file to send to the receiver, and the receiver's receive buffer is much larger than the congestion window. We also make the following assumptions: each TCP segment size is $1500$ bytes; the two-way propagation delay of this connection is $150$ msec; and this TCP connection is always in congestion avoidance phase, that is, ignore slow start.

a. What is the maximum window size (in segments) that this TCP connection can achieve?

$$
\frac{10 Mb}{1 sec} * \frac{1 segment}{12000 Kb} * 0.15 sec = \bold{125\ segments}
$$

b. What is the average window size (in segments) and average throughput (in bps) of this TCP connection?

$$
\begin{split}
   Window\ size &= 0.75 W = 0.75 * 125 = \bold{93.75\ segments}\\
   Average\ throughput &= 0.75 W * \frac{MSS}{RTT} = 93.75 * \frac{1500 * 8\ b}{0.15\ s} = 7500000\ b/s = \bold{7.5\ Mb/s}
\end{split}
$$

c. How long would it take for this TCP connection to reach its maximum window again after recovering from a packet loss?

$$\frac{W}{2} * RTT = \frac{125}{2} * 015 = \bold{9.375\ sec}$$
