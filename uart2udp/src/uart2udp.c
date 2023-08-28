# include <stdio.h> 
# include <stdlib.h> 
# include <termio.h> 
# include <unistd.h> 
# include <fcntl.h> 
# include <getopt.h> 
# include <time.h> 
# include <errno.h> 
# include <string.h> 
//---
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <arpa/inet.h>



//# include <linux/delay.h>
//# include <asm/delay.h>

//check uart_ctrl pin status
//return 0 pass, 1 fail

int hUart1; 
int ret1;
//---
fd_set rfds;
struct timeval tv;
char buff[1024];
char st1[1024];
int nread;
//---
struct termios TtyAttr; 
int DeviceSpeed = B115200; 
int ByteBits = CS8; 
//const char *DeviceName = "/dev/ttySAC2"; 
char DeviceName[256];
int wait_usec;
//---
int sockfd,n;
struct sockaddr_in servaddr,cliaddr;
char sendline[1000];
char recvline[1000];




int main(int argc, char **argv) 
{ 



	//int i1;	
	//char st1[256];
	//int status1;	

	printf("UART to UDP 1.00 Greatcat 2023Aug28\n");
	if (argc != 5)
	{	
		printf("Err, need parameter.\n");
		printf("\tExample\n");
		printf("\t\t./uart2udp.out <uart_node> <udp_server_addr> <port> <wait_usec>\n");
		printf("\t\t./uart2udp.out /dev/ttyUSB0 127.0.0.1 8888 1001\n");
		printf("\t\twait_usec=1001 is for more debug message\n");

		return 1;
	}

	wait_usec=atoi(argv[4]);

	//---udp init

	sockfd=socket(AF_INET,SOCK_DGRAM,0);

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr=inet_addr(argv[2]);
	//servaddr.sin_port=htons(32000);
	servaddr.sin_port=htons(atoi(argv[3]));


	//---
	strcpy(DeviceName,argv[1]);

	hUart1 = open(DeviceName, O_RDWR, 0); 
	if (hUart1 < 0)
	{	
		printf("Unable to open device\n"); 	
		return 1;
	}		
	if (fcntl(hUart1, F_SETFL, O_NONBLOCK) < 0) 
	{
		printf("Err, Unable to open device\n"); 	
		return 1; 
	}

	memset(&TtyAttr, 0, sizeof(struct termios)); 
	TtyAttr.c_iflag = IGNPAR; 
	TtyAttr.c_cflag = DeviceSpeed | HUPCL | ByteBits | CREAD | CLOCAL; 
	TtyAttr.c_cc[VMIN] = 1; 		

	if (tcsetattr(hUart1, TCSANOW, &TtyAttr) < 0) 
	{  
		printf("Err, Unable to set comm port\n"); 
		return 1;	
	}			

	//pin23 test
	tcflush(hUart1, TCIOFLUSH);
	//strcpy(st1,"ABCDEF");

	//for (i1=0;i1<5;i1++)
	//{
	//	write(hUart1,st1,strlen(st1));
	//}
	//usleep(50*1000);




	st1[0]='\0';
	while (1) {

		//tv.tv_sec=1;
		//tv.tv_usec=0;

		tv.tv_sec=0;
		tv.tv_usec=wait_usec*1000;


		FD_ZERO(&rfds);
		FD_SET(hUart1,&rfds);
		ret1=select(hUart1+1,&rfds,NULL,NULL,&tv);
		//printf("%d\n",ret1);

		if (ret1 < 0)
		{  
			printf("Err,error handled.\n"); 
			FD_CLR(hUart1,&rfds);
			close(hUart1);			
			return 1;	
		}

		if (ret1 > 0)
		{
			if (FD_ISSET(hUart1,&rfds))
			{
				nread=read(hUart1,buff,sizeof(buff)-1);
				//printf("rx1=%d\n",nread);
				buff[nread]='\0';
				strcat(st1,buff);
			}

			tv.tv_sec=0;
			tv.tv_usec=wait_usec*1000;
			FD_ZERO(&rfds);
			FD_SET(hUart1,&rfds);
			ret1=select(hUart1+1,&rfds,NULL,NULL,&tv);
			while ( ret1 > 0 ){
				if (FD_ISSET(hUart1,&rfds))
				{
					nread=read(hUart1,buff,sizeof(buff)-1);
					//printf("rx2=%d\n",nread);
					buff[nread]='\0';
					strcat(st1,buff);


				}
				tv.tv_sec=0;
				tv.tv_usec=500*1000;
				FD_ZERO(&rfds);
				FD_SET(hUart1,&rfds);
				ret1=select(hUart1+1,&rfds,NULL,NULL,&tv);
			}
			if ( wait_usec==1001 )
				printf("%s\n",st1);
			sendto(sockfd,st1,strlen(st1),0,
				(struct sockaddr *)&servaddr,sizeof(servaddr));
			st1[0]='\0';

		} else {
			//ret1 == 0
			if ( wait_usec==1001 )
				printf("timeout .\n"); 
		}

	}

	FD_CLR(hUart1,&rfds);
	return 0;
}	
