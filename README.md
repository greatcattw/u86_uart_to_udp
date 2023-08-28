# uart_to_udp
Rx in uart message and Tx out UDP message

# Test#1 Local, UDP message Tx and Rx itself.
![pic](pic/test1a.png)<br>
![pic](pic/test1b.png)<br><br><br>
Run with X86 Ubuntu  
bin_u86\udp.svr.out  8888
bin_u86\udp.cli.out 127.0.0.1 8888
<br>
type something then press [Enter] with udp.cli.out  
udp.svr.out show the message.  
<br>

# Test#2 minicom uart Tx and UDP Rx
![pic](pic/test2.png)<br><br><br>


# Test#3 arduino uart Tx, mt7688 uart Rx and UDP Tx, PC Rx UDP
![pic](pic/test3.png)<br><br><br>
