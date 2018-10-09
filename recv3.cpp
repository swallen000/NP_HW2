#include "UDP.h"

using namespace std;


int main(int argc , char *argv[]){
	if(argc!=2){
		cout<<"Usage : ./receiver <port>\n";
		exit(1);
	}
    int round=1;
    while(true){
        //sleep(5);
    	int sockfd;
    	sockfd=socket(AF_INET,SOCK_DGRAM,0);
    	if(sockfd<0){
    		cout<<"create socket failed";
    		exit(1);
    	}
    	struct sockaddr_in receiver,sender;
    	receiver.sin_family=AF_INET;
    	receiver.sin_addr.s_addr=INADDR_ANY;
    	receiver.sin_port=htons(atoi(argv[1]));	
        if ( bind(sockfd, (struct sockaddr *) &receiver, sizeof(receiver)) < 0 ) {
            perror ("bind failed\n");
            exit(1);
        }

    //while(true){
        string filename;
        FILE *file;
        
        char buf[BUFSIZE];
        UDP r,*temp;             //change when finished
        bool setup=false;
        int count=0;


        while(1){
        	int rec=0;
        	socklen_t length=sizeof(sender);
        	rec=recvfrom( sockfd , &r , sizeof(type) , 0 , (struct sockaddr*) &sender , &length );
        	if( rec<=0 ){
        		cout<<"fail to recvfrom\n";
        		exit(1);
        	}
            if(!setup){
                filename=r.file;
                file=fopen(filename.c_str(),"wb+");
                temp=new UDP[r.size];
                for(int i=0;i<r.size;i++){
                    temp[i].send=false;
                    temp[i].done=false;
                }
                setup=true;
            }
        	/*cout<<"receive "<<rec<<" bytes successfully\n";
            cout<<"now is receive "<<r.now<<endl;*/
            
            /*for(int i=0;i<10;i++){
                cout<<"here buf["<<r.byte-i-1<<"] is "<<r.buf[r.byte-i-1]<<endl;
            }*/
            if(r.byte<BUFSIZE)
                r.buf[r.byte]='\0';
            
            cout<<"now="<<r.now<<"    count="<<count<<endl;
        	if(temp[r.now].send==false){
               //fwrite(r.buf, sizeof(char) , r.byte ,file);
               /*cout<<r.buf<<endl<<"-------------------------"<<endl;*/
        	   //cout<<"write to file "<<count<<" successfully\n";
               cout<<"receive "<<r.now<<"successfully\n";
               temp[r.now].send=true;
               memcpy(temp[r.now].buf,r.buf,r.byte);
               temp[r.now].byte=r.byte;
               //cout<<r.now<<"'s content is:\n"<<temp[r.now].buf<<endl<<"#########################"<<endl;
               /*if(count>480){
                    for(int j=0;j<r.size;j++){
                        if(temp[j].send==false){
                            cout<<j<<" is not sent!!!   ";
                        }
                    }    
                    cout<<endl;
               }*/
               count++;
               cout<<"now finish "<<count<<endl;
               cout<<"now = "<<r.now<<endl;
            }      
            cout<<"before send  now is"<<r.now<<endl;
        	rec=sendto( sockfd, &r , sizeof(type) , 0 , (struct sockaddr*) &sender , length );
        	if(rec<=0){
        		cout<<"failt to send\n";
        		exit(1);
        	}
            if(count == r.size){
                for(int i=0;i<r.size;i++){
                    temp[i].done=true;
                    sendto( sockfd, &temp[i] , sizeof(type) , 0 , (struct sockaddr*) &sender , length );
                }
                for(int i=0;i<r.size;i++){
                    fwrite(temp[i].buf , sizeof(char) , temp[i].byte , file);
                    cout<<"now write to file :"<<i<<endl;
                    //cout<<temp[i].buf<<endl<<"-------------------"<<endl;
                }
                break;
            }
        }
        close(sockfd);
        fclose(file);
        delete [] temp;
        round++;
        cout<<"send "<<filename<<" finished!\n";
        cout<<"                 uuuuuuu"<<endl;
        cout<<"             uu$$$$$$$$$$$uu"<<endl;
        cout<<"          uu$$$$$$$$$$$$$$$$$uu"<<endl;
        cout<<"         u$$$$$$$$$$$$$$$$$$$$$u"<<endl;
        cout<<"        u$$$$$$$$$$$$$$$$$$$$$$$u"<<endl;
        cout<<"       u$$$$$$$$$$$$$$$$$$$$$$$$$u"<<endl;
        cout<<"       u$$$$$$$$$$$$$$$$$$$$$$$$$u"<<endl;
        cout<<"       u$$$$$$'   '$$$''   '$$$$$$u"<<endl;
        cout<<"       \"$$$$\"      u$u       $$$$\""<<endl;
        cout<<"        $$$u       u$u       u$$$"<<endl;
        cout<<"        $$$u      u$$$u      u$$$"<<endl;
        cout<<"         \"$$$$uu$$$   $$$uu$$$$\""<<endl;
        cout<<"          \"$$$$$$$\"   \"$$$$$$$\""<<endl;
        cout<<"            u$$$$$$$u$$$$$$$u"<<endl;
        cout<<"             u$\"$\"$\"$\"$\"$\"$u"<<endl;
        cout<<"  uuu        $$u$ $ $ $ $u$$       uuu"<<endl;
        cout<<" u$$$$        $$$$$u$u$u$$$       u$$$$"<<endl;
        cout<<"  $$$$$uu      \"$$$$$$$$$\"     uu$$$$$$"<<endl;
        cout<<"u$$$$$$$$$$$uu    \"\"\"\"\"    uuuu$$$$$$$$$$"<<endl;
        cout<<"$$$$\"\"\"$$$$$$$$$$uuu   uu$$$$$$$$$\"\"\"$$$\""<<endl;
        cout<<" \"\"\"      \"\"$$$$$$$$$$$uu \"\"$\"\"\""<<endl;
        cout<<"           uuuu \"\"$$$$$$$$$$uuu"<<endl;
        cout<<"  u$$$uuu$$$$$$$$$uu \"\"$$$$$$$$$$$uuu$$$"<<endl;
        cout<<"  $$$$$$$$$$\"\"\"\"           \"\"$$$$$$$$$$$\""<<endl;
        cout<<"   \"$$$$$\"                      \"\"$$$$\"\""<<endl;
        cout<<"     $$$\"                         $$$$\""<<endl;
                        
                                                               
        sleep(5);
    }

    return 0;
}