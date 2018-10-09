#include "UDP.h"


typedef void (*Sigfunc)(int);

void sig_alrm(int signo){
    alarm(1);
    return ;
}

int main(int argc , char *argv[]){
	if(argc!=4){
		cout<<"Usage : ./sender <receiver IP> <receiver port> <file name>\n";
		exit(1);
	}
    struct timeval start;
    struct timeval end;
	struct sockaddr_in sender;
	int sockfd=0;


    gettimeofday(&start,NULL);
	if( (sockfd=socket(AF_INET , SOCK_DGRAM , 0) )<0 ){
		cout<<"fail to create socket";
		exit(1);
	}
	sender.sin_family = AF_INET;
    sender.sin_port = htons(atoi(argv[2]));
    sender.sin_addr.s_addr = inet_addr(argv[1]);
    if( connect(sockfd , (struct sockaddr *)&sender , sizeof(sender))<0 ){
    	cout<<"fail to connect";
    	exit(1);
    }

    timeval timeout,timeout2;
    timeout.tv_sec=0;
    timeout.tv_usec=100000;


    fd_set rfds,mas;
    FD_ZERO(&rfds);
    FD_ZERO(&mas);
    FD_SET(sockfd,&mas);


    FILE *file;
    file=fopen(argv[3],"rb");
    bool flag=false;
    int count=0;
    int size,total_byte=0;
    fseek(file,0,SEEK_END);
    size=ftell(file);
    fseek(file,0,SEEK_SET);
    cout<<"file size="<<size<<endl;
    int packet;
    if( (size%BUFSIZE)!=0 )
        packet=(size/BUFSIZE)+1;
    else
        packet=(size/BUFSIZE);
    UDP *s,r;
    s=new UDP[packet];
    cout<<"here\n";
    for(int i=0;i<packet;i++){
        s[i].send=false;
        s[i].now=i;
        s[i].size=packet;
        string temp;
        temp=argv[3];
        memcpy(s[i].file,temp.c_str(),temp.length());
    }
    cout<<s[packet-1].file<<endl;
    cout<<"start read\n";
    for(int i=0;i<packet;i++){
        int byte;
        byte=fread(s[i].buf ,sizeof(char), BUFSIZE , file);
        cout<<"byte="<<byte<<endl;
        s[i].byte=byte;
        /*for(int i=0;i<10;i++){
            cout<<"here buf["<<byte-i-1<<"] is "<<s.buf[byte-i-1]<<endl;
        }*/
        //total_byte+=byte;
        if(byte<BUFSIZE){
            s[i].buf[byte]='\0';      
        }
    }




    while(!flag){
    	while( count!=packet ){
    	
    			for(int i=0;i<packet;i++){
                    if(s[i].send == false){
                        if( write( sockfd, &s[i] , sizeof(type) )<0 ){
        					//cout<<"fail to write";
                        }
                    }
                    else{
                        /*  do nothing  */
                    }
                }

                rfds=mas;
                timeout2=timeout;
                int sel;
                sel=select(sockfd+1,&rfds,NULL,NULL,&timeout2);
        		
                if(sel<0){
                    cout<<"fail to select\n";
                    exit(1);
                }
                else if(sel==0){
                    cout<<"TIME OUT ! Resend the socket\n";
                    /*  do nothing  */
                }
                else{
                    int ack;
        		    ack=read( sockfd , &r , sizeof(type) );
                    if(ack<0){
                        cout<<"the connection is closed!\n";
                        break;
                    }
        			//r.buf[r.byte]='\0';
        			/*cout<<r.buf<<"-------------------------------------"<<endl;*/
        			if(r.done == true){
                        flag=true;
                        cout<<"terminated by done\n";
                        break;
                    }
                    cout<<"send "<<r.now<<" succeffully\n";
        			s[r.now].send=true;
                    count++;
        		}
                if(count==packet)
                    cout<<"terminated by count done\n";
                
    	}
    	flag=true;
    }

    close(sockfd);

    delete [] s;
    gettimeofday(&end,NULL);
    float time=0;
    time=1000000*(end.tv_sec-start.tv_sec)+end.tv_usec-start.tv_usec;
    cout<<"total sending time is : "<<time/1000000<<"s"<<endl;

    return 0;
}