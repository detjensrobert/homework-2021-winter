# CS 372 Lab 1

## Robert Detjens

---

### 1. What is the IP address and TCP port number used by the client computer (source) that is transferring the file to gaia.cs.umass.edu?

`192.168.1.102:1161`

![](https://i.imgur.com/K1KC5wv.png)

### 2. What is the IP address of gaia.cs.umass.edu? On what port number is it sending and receiving TCP segments for this connection?

`128.119.245.12:80`

![](https://i.imgur.com/4ENBQMV.png)

### 3. What is the IP address and TCP port number used by *your* client computer (source) to transfer the file to gaia.cs.umass.edu?

`192.168.0.102:44842`

![](https://i.imgur.com/7pEEtrW.png)

$\pagebreak$

### 4. What is the sequence number of the TCP SYN segment that is used to initiate the TCP connection between the client computer and gaia.cs.umass.edu? What is it in the segment that identifies the segment as a SYN segment?

Sequence number 0; the SYN flag is set.

![](https://i.imgur.com/GRKKjzW.png){ height=300px }

### 5. What is the sequence number of the SYNACK segment sent by gaia.cs.umass.edu to the client computer in reply to the SYN? What is the value of the Acknowledgement field in the SYNACK segment? How did gaia.cs.umass.edu determine that value? What is it in the segment that identifies the segment as a SYNACK segment?

Sequence number 0; ACK number 1; the server has recieved 1 SYN packet, thus ACK number of 1; both SYN and ACK flags are set.

![](https://i.imgur.com/63xqFiB.png){ height=300px }

### 6. What is the sequence number of the TCP segment containing the HTTP POST command?

Sequence number 1.

![](https://i.imgur.com/NkICnlk.png){ height=200px }

### 7. Consider the TCP segment containing the HTTP POST as the first segment in the TCP connection.

- What are the sequence numbers of the first six segments in the TCP connection (including the segment containing the HTTP POST)? At what time was each segment sent?

  ![](https://i.imgur.com/IvHwOlc.png)

- When was the ACK for each segment received?

  ![](https://i.imgur.com/jmFiMzG.png)

  $\pagebreak$

- Given the difference between when each TCP segment was sent, and when its acknowledgement was received, what is the RTT value for each of the six segments?

  | sent     | ack      | RTT      |
  |----------|----------|----------|
  | 0.041737 | 0.026477 | 0.015260 |
  | 0.053937 | 0.041737 | 0.012200 |
  | 0.077294 | 0.054026 | 0.023268 |
  | 0.124085 | 0.054690 | 0.069395 |
  | 0.169118 | 0.077405 | 0.091713 |
  | 0.217299 | 0.078157 | 0.139142 |

- What is the Estimated RTT value after the receipt of each ACK?

  | RTT estimate |
  |--------------|
  | 0.015260     |
  | 0.014878     |
  | 0.015926     |
  | 0.022610     |
  | 0.031248     |
  | 0.044735     |

### 8. What is the length of each of the first six TCP segments?

565 for the initial segment, 1460 for the following ones.

![](https://i.imgur.com/L3IAjhg.png)

### 9. What is the minimum amount of available buffer space advertised at the received for the entire trace? Does the lack of receiver buffer space ever throttle the sender?

1750; no, it does not throttle.

![](https://i.imgur.com/k1h10eS.png)

$\pagebreak$

### 10. Are there any retransmitted segments in the trace file? What did you check for (in the trace) in order to answer this question?

No retransmitted segments.

![](https://i.imgur.com/Of3grey.png)

### 11. How much data does the receiver typically acknowledge in an ACK? Can you identify cases where the receiver is ACKing every other received segment?

Typical data length is 1460B; some data packets are shorter but most are 1460.

![](https://i.imgur.com/PO4juG2.png)

### 12. What is the throughput (bytes transferred per unit time) for the TCP connection? Explain how you calculated this value.

Average throughput is 249 Kbps.

![](https://i.imgur.com/aW9ZswJ.png)

### 13. Can you identify where TCP’s slowstart phase begins and ends, and where congestion avoidance takes over?

Slow start is in the highlighted area, congestion avoidance is active for the rest of the connection.

![](https://i.imgur.com/vttwPM3.png){ height=250px }

### 14. Answer each of two questions above for the trace that you have gathered when you transferred a file from your computer to `gaia.cs.umass.edu`.

Average throughput is 3.21 Mbps.

![](https://i.imgur.com/b5YV9mv.png)

There does not appear to be a slow-start with this connection.

![](https://i.imgur.com/aKmsHQA.png){ height=250px }
