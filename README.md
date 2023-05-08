# Lab 2
[Fork](https://docs.github.com/en/get-started/quickstart/fork-a-repo) this repo and clone it to your machine to get started!

## Team Members
- Dylan Gatua

## Lab Question Answers
1. When 50% packet loss is added to the local environment, the reliability of UDP will decrease significantly. This is because UDP is a connectionless protocol that does not guarantee the delivery of packets. With 50% packet loss, half of the packets are lost, which may cause delays or even failure in the communication process. UDP does not have any mechanism for retransmission, error recovery, or flow control, so the lost packets will not be recovered, and the data transmission may be incomplete or incorrect.

2. The reliability of TCP is generally more robust than UDP since TCP is a reliable protocol that provides mechanisms for error detection, recovery, and flow control. When 50% packet loss is introduced, TCP's reliability may decrease somewhat, but the impact will be less severe than UDP. TCP uses a sequence number to track packets, and if a packet is lost, TCP will detect the loss and retransmit the packet. This mechanism ensures that all packets are delivered correctly and in order, which results in better reliability.

3. The speed of the TCP response may decrease when 50% packet loss is added to the local environment. This may happen because TCP uses flow control mechanisms to ensure that the receiver can handle the data at the same rate as the sender is transmitting it. When packets are lost, TCP detects the loss and reduces the transmission rate, causing the sender to slow down. As a result, the speed of the TCP response may be slower due to the additional retransmissions and reduced transmission rate. Additionally, the network congestion caused by the lost packets may also contribute to slower response times.
