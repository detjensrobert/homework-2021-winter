# CS 372 Lab 0

## Robert Detjens

---

### 1. List 3 different protocols that appear in the protocol column in the unfiltered packet-listing window.

- `DNS`
- `TCP`
- `TLSv1.3`

### 2.How long did it take from when the HTTP GET message was sent until the HTTP OK reply was received?

Ping was 0.08305s.

### 3.What is the IP of `gaia.cs.umass.edu`?  What is the IP of your computer?

`gaia.cs.umass.edu`: `128.119.245.12`

Local computer: `192.168.0.102`

### 4.Print the two HTTP messages (GET and OK) referred to in question 2.

```http
Frame 64: 478 bytes on wire (3824 bits), 478 bytes captured (3824 bits) on interface eno1, id 0
Ethernet II, Src: Giga-Byt_a7:49:3b (b4:2e:99:a7:49:3b), Dst: Tp-LinkT_7b:f5:41 (98:da:c4:7b:f5:41)
Internet Protocol Version 4, Src: 192.168.0.102, Dst: 128.119.245.12
Transmission Control Protocol, Src Port: 56650, Dst Port: 80, Seq: 1, Ack: 1, Len: 412
Hypertext Transfer Protocol
    GET /wireshark-labs/INTRO-wireshark-file1.html HTTP/1.1\r\n
    Host: gaia.cs.umass.edu\r\n
    User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:84.0) Gecko/20100101 Firefox/84.0\r\n
    Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n
    Accept-Language: en-US,en;q=0.5\r\n
    Accept-Encoding: gzip, deflate\r\n
    Connection: keep-alive\r\n
    Upgrade-Insecure-Requests: 1\r\n
    Pragma: no-cache\r\n
    Cache-Control: no-cache\r\n
    \r\n
    [Full request URI: http://gaia.cs.umass.edu/wireshark-labs/INTRO-wireshark-file1.html]
    [HTTP request 1/2]
    [Response in frame: 66]
    [Next request in frame: 68]
```

$\pagebreak$

```http
Frame 66: 504 bytes on wire (4032 bits), 504 bytes captured (4032 bits) on interface eno1, id 0
Ethernet II, Src: Tp-LinkT_7b:f5:41 (98:da:c4:7b:f5:41), Dst: Giga-Byt_a7:49:3b (b4:2e:99:a7:49:3b)
Internet Protocol Version 4, Src: 128.119.245.12, Dst: 192.168.0.102
Transmission Control Protocol, Src Port: 80, Dst Port: 56650, Seq: 1, Ack: 413, Len: 438
Hypertext Transfer Protocol
    HTTP/1.1 200 OK\r\n
    Date: Wed, 06 Jan 2021 00:01:48 GMT\r\n
    Server: Apache/2.4.6 (CentOS) OpenSSL/1.0.2k-fips PHP/7.4.13 mod_perl/2.0.11 Perl/v5.16.3\r\n
    Last-Modified: Tue, 05 Jan 2021 06:59:01 GMT\r\n
    ETag: "51-5b821bdcffcaa"\r\n
    Accept-Ranges: bytes\r\n
    Content-Length: 81\r\n
    Keep-Alive: timeout=5, max=100\r\n
    Connection: Keep-Alive\r\n
    Content-Type: text/html; charset=UTF-8\r\n
    \r\n
    [HTTP response 1/2]
    [Time since request: 0.083059701 seconds]
    [Request in frame: 64]
    [Next request in frame: 68]
    [Next response in frame: 69]
    [Request URI: http://gaia.cs.umass.edu/wireshark-labs/INTRO-wireshark-file1.html]
    File Data: 81 bytes
    Line-based text data: text/html (3 lines)
```
