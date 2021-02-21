# CS 372 Lab 2

## Robert Detjens

---

*Note: the given trace was used my capture was more cluttered and did not fragment*

### 1. Select the first ICMP Echo Request message sent by your computer, and expand the Internet Protocol part of the packet in the packet details window. What is the IP of your computer?

Source IP is 192.168.1.102.

![](https://i.imgur.com/KcD3sYw.png){ height=200px }

### 2. Within the IP packet header, what is the value in the upper layer protocol field?

Protocol field is 1 (ICMP)

![](https://i.imgur.com/2zkOEUE.png){ height=200px }

$\pagebreak$

### 3. How many bytes are in the IP header? How many bytes are in the payload *of the IP datagram*? Explain how you determined the number of payload bytes.

- Header size: 5 * 32-bit words = 20 bytes
- Payload size: 84 bytes total - 20 bytes for header = 64 bytes for payload

![](https://i.imgur.com/2ayhjHm.png){ height=200px }

### 4. Has this IP datagram been fragmented? Explain how you determined whether or not the datagram has been fragmented.

Not fragmented: the `More fragments` has not been set and the fragment offset is zero.

![](https://i.imgur.com/Pl4heZY.png){ height=200px }

### 5. Which fields in the IP datagram always change from one datagram to the next within this series of ICMP messages sent by your computer?

The TTL, identification, and checksum vary between packets.

![](https://i.imgur.com/oLkuOzC.png){ height=200px }

### 6. Which fields stay constant? Which of the fields must stay constant? Which fields must change? Why?

Fields that identify the packet *must* stay the same -- protocol and source. The others *can* change but may not provide consistent results e.g. if sent to a different dest.

![](https://i.imgur.com/jQNGxcs.png){ height=200px }

### 7. Describe the pattern you see in the values in the Identification field of the IP datagram.

The Ident field increments by 1 for each ICMP packet sent.

![](https://i.imgur.com/9mK4xIi.png){ height=200px }

### 8. What is the value in the Identification field and the TTL field?

Identification: 40316, TTL 255.

![](https://i.imgur.com/JfSWTvp.png){ height=200px }

### 9. Do these values remain unchanged for all of the ICMP TTL-exceeded replies sent to your computer by the nearest (first hop) router? Why?

The TTL for the first hop is always 255, as packets always start at 255 TTL by default and are decremented *after* the first hop. The Identification field changes across different packets. All the other fields stay the same.

![](https://i.imgur.com/ecj4dom.png){ height=200px }

### 10. Find the first ICMP Echo Request message that was sent by your computer after you changed the Packet Size in pingplotter to be 2000. Has that message been fragmented across more than one IP datagram?

Yes. Packets 92 and 93 in the given trace are fragments of the larger 2000B packet.

![](https://i.imgur.com/CbCFBXe.png){ height=200px }

### 11. Print out the first fragment of the fragmented IP datagram. What information in the IP header indicates that the datagram been fragmented? What information in the IP header indicates whether this is the first fragment versus a latter fragment? How long is this IP datagram?

- The `More fragments` flag is set, indicating that this datagram is one in a series of fragments of a larger packet.
- The `Fragment offset` indicates where this fragment goes in the reassembled packet. The offset here is `0`, marking that this fragment is the first.
- The size of this fragment is `1500`, the maximum allowed by the current MTU of the Ethernet interface.

![](https://i.imgur.com/pgvciAO.png){ height=200px }

### 12. Print out the second fragment of the fragmented IP datagram. What information in the IP header indicates that this is not the first datagram fragment? Are the more fragments? How can you tell?

- This fragment is not the first, as the `Fragment offset` is not zero.
- The `More fragments` flag is not set, indicating that this is the last fragment and there are no more coming.

![](https://i.imgur.com/1tL77h0.png){ height=200px }

### 13. What fields change in the IP header between the first and second fragment?

Length, `More fragments` flag, `Fragment offset`, and checksum.

![](https://i.imgur.com/8KtGlI5.png){ height=200px }

### 14. How many fragments were created from the original datagram?

3 fragments.

![](https://i.imgur.com/EqJuRJa.png){ height=200px }

### 15. What fields change in the IP header among the fragments?

Length, `More fragments` flag, `Fragment offset`, and checksum.

![](https://i.imgur.com/QfQgN77.png){ height=200px }
