## LOW_LEVEL: Networking 
This is a repository where I try to explore lower level networking 
functionality. Starting with basic client server, I want to then 
get into building headers from scratch, and eventually packets too.

I've compiled this through a set of different online articles and 
random code examples. I'm listing those sources at the bottom to
be clear that I am not trying to take credit for any work I do not
own. This repository is purely for educational purposes.
-----------------------------------------------------------------

### Networking 
Three protocols to look at first. Internet Protocol (IP) is how 
machines communicate with eachother. On top of this protocol other 
protocols are used to build up the bulk of our internet traffic. 

The Transmission Control Protocol (TCP) is the first I want to 
look at. It's a *connection oriented* protocol, so it is somewhat
elaborate in that it's assumed machines are working together to
communicate, starting off with a handshake.

User Datagram Protocol (UDP) is a protocol not assumed to have 
such strict state maintained between hosts, and assurance of zero
data loss or data being scrambled in transmission ([ABCD]->[ACDB]). 
For this reason though, many packets can be sent in much quicker 
succession and recieved as well making it better for certain cases.

#### **IP Header**
```
0                   1                   2                   3
0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|Version|  IHL  |Type of Service|          Total Length         |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|         Identification        |Flags|      Fragment Offset    |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|  Time to Live |    Protocol   |         Header Checksum       |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                       Source Address                          |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                    Destination Address                        |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                    Options                    |    Padding    |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```
 IP Header as descibed by [RFC 791](https://tools.ietf.org/html/rfc791)
-----------------------------------------------------------------

#### **TCP Header**
The structure of a TCP header as given by RFC 793
```
0                   1                   2                   3
0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|          Source Port          |       Destination Port        |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                        Sequence Number                        |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                    Acknowledgment Number                      |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|  Data |           |U|A|P|R|S|F|                               |
| Offset| Reserved  |R|C|S|S|Y|I|            Window             |
|       |           |G|K|H|T|N|N|                               |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|           Checksum            |         Urgent Pointer        |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                    Options                    |    Padding    |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|                             data                              |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
```
-----------------------------------------------------------------

#### Packets 
Data on the wire has an additional layer before the data, called ethernet. A 
packet consists of the following:
```Packet = Ethernet header + Ip header + TCP header + Data```

Four layers of the TCP/IP Protocol Suite:
```
		----------------------------------------------------------
        | 4. Application        | telnet, ftp, dns etc.          |
        ----------------------------------------------------------
        | 3. Transport          | TCP UDP                        |
        ----------------------------------------------------------
        | 2. Network            | IP ICMP IGMP                   |
        ----------------------------------------------------------
        | 1. Link               | device driver, network adapter |
```

When your application sends some data using a socket descriptor, the data is delivered to the transport (TCP/UDP) layer. Transport layer determines a local source port, if there needs to be a connection establishment procedure beforehand, opens the connection. Transport layer specific header is created and appended to the data, then the packet is delivered to the Network Layer (Layer II). Layer-II (e.g. IP) header is created, and appended to the packet. Source and destination address information is written onto the related fields in the IP header. The last station is the Link layer, where the packet is injected onto the wire.

Likewise, an incoming packet is demultiplexed as it goes upwards within the stack hierarchy, and is finaly delivered to the userspace application. [2]

#### TCP Handshake[3]

A TCP connection usually undergoes the following phases: connection setup (handshaking), data transfer and closing of the connection. The following diagrams depicts the usual handshaking routine of TCP:
```
          TCP A                                                TCP B
    	  
    1.  CLOSED                                               LISTEN
    	
    2.  SYN-SENT    --> <SEQ=100><CTL=SYN>               --> SYN-RECEIVED
    	  
    3.  ESTABLISHED <-- <SEQ=300><ACK=101><CTL=SYN,ACK>  <-- SYN-RECEIVED
    			
    4.  ESTABLISHED --> <SEQ=101><ACK=301><CTL=ACK>       --> ESTABLISHED
    			  
    5.  ESTABLISHED --> <SEQ=101><ACK=301><CTL=ACK><DATA> --> ESTABLISHED
```

#### TCP Options[3] 
The last field of the TCP header before the data, the options field is used for possible types of TCP options to signal:
	- The Maximum Segment Size (MSS) option informs the maximum TCP segment size the TCP implementation is willing to receive. The typical value for this is 1460 bytes in IPv4.
	- The Selective Acknowledgment (SACK) option optimizes the scenario when many packets are lost in transmit and the receiver’s window of data is filled with “holes”. 
	- The Window Scale option increases the limited 16-bit window size. Namely, if both sides include this option in their handshake segments, the window size is multiplied with this scale.
	- The Timestamps option allows the sender to place a timestamp into the TCP segment, which then can be used to calculate the RTT for each ACK segment. This information can then be used to calculate the TCP retransmission timeout.


--- Sources ----
[1] https://www.binarytides.com/raw-sockets-c-code-linux/
[2] http://www.enderunix.org/docs/en/rawipspoof/
[3] https://www.saminiir.com/lets-code-tcp-ip-stack-3-tcp-handshake/