# CS 372 Lab 2

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

- Given the difference between when each TCP segment was sent, and when its acknowledgement was received, what is the RTT value for each of the six segments?

- What is the Estimated RTT value after the receipt of each ACK?

### 8.

![](){}

### 9.

![](){}

### 10.

![](){}

### 11.

![](){}

### 12.

![](){}

### 13.

![](){}

### 14.
