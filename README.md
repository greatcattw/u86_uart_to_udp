# uart_to_udp
Rx in uart message and Tx out UDP message

## Test#1 Local, UDP message Tx and Rx itself.
![pic](pic/test1a.png)<br>
![pic](pic/test1b.png)<br><br><br>
Run with X86 Ubuntu  
bin_u86\udp.svr.out  8888
bin_u86\udp.cli.out 127.0.0.1 8888
<br>
type something then press [Enter] with udp.cli.out  
udp.svr.out show the message.  
<br>

## Test#2 minicom uart Tx and UDP Rx
![pic](pic/test2d.png)<br><br><br>
Run UDP server to Rx UDP message  
bin_u86\udp.svr.out  8888  
<br>
Run minicom with ttyUSB1, 115200, to Tx uart message from ttyUSB1.
<br>
Run bin_u18\uart2udp.out to Rx uart message from ttyUSB0, and send message out over UDP  
wait_usec=1001 is a magic number for showing more debug message.  
type something quickly with minicom.  
![pic](pic/test2a.png)<br>
udp.svr.out show the message.  
![pic](pic/test2b.png)<br><br><br>
<br>
## Test#3 arduino uart Tx, mt7688 uart Rx and UDP Tx, PC Rx UDP
Tested, this program is able to receive short string ( > 20 char) from arduino uart (115200) every 200ms.  
![pic](pic/test3b.png)<br><br><br>
<br>
## Test#4 Log data with long distance
arduino uart Tx, mt7688 uart Rx and UDP Tx over WiFi, PC Rx UDP from WiFi.  
![pic](pic/lk7688duo.jpg)<br>
Method#1  
![pic](pic/test6.png)<br><br><br>
<br>
Method#1  
![pic](pic/test5.png)<br><br><br>


arduino uart Tx, mt7688 uart Rx and UDP Tx over LTE, PC Rx UDP from LTE.    
![pic](pic/test4c.png)<br>
![pic](pic/lk7688_ec20.jpg)<br>

![pic](pic/duo_ardu2.png)<br>
![pic](pic/duo_ardu5.png)<br>
![pic](pic/duo1.png)<br>
![pic](pic/duo2.png)<br>
