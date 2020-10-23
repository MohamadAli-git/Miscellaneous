#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <thread>

#pragma comment (lib, "ws2_32.lib")

using namespace std;
char *fields[2];
char buffer [33];
int split(char* str, char *splitter);
int Sum(int a , int b);
void Threads(int n,int Nums[],char Tags[]);
int  Factorization(int num ,char tag, int TH );
int Count=0;
int m=0;
string str2[200];
int threadnumber;

int main (int argc, char *argv[])
{
    string p=argv[1],p1,p2;
    p1=p.erase(0,1);
    p2=argv[2];
    if(p1.compare("t")==0){
        threadnumber=stoi(p2);
    }
    //threadnumber=2;
    p=argv[3];
    p1=p.erase(0,1);
    p2=argv[4];
    if(p1.compare("m")==0){
        m=stoi(p2);
    }
    //m=2;
    WSADATA wsData;
    WORD ver = MAKEWORD(2,2);

    int wsOk = WSAStartup(ver,&wsData);
    if (wsOk != 0)
    {
        cerr <<	"Can't initialize winsock ! Quitting" << endl;
        return 0;
    }

    SOCKET listening = socket (AF_INET,SOCK_STREAM,0);
    if ( listening == INVALID_SOCKET)
    {
        cerr << "Can't create a socket ! Quitting" << endl;
        return 0;
    }

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(44044);
    hint.sin_addr.S_un.S_addr = INADDR_ANY ; // Could also use inet_pton

    bind(listening,(sockaddr*) &hint,sizeof(hint));

    cout<< "Server is listening................"<<endl;
    listen(listening,SOMAXCONN);

    fd_set master;
    FD_ZERO (&master);

    FD_SET (listening, &master);

    while (true)
    {
        fd_set copy = master ;
        int socketCount = select (0 , &copy , nullptr ,nullptr,nullptr);
        for (int i = 0 ; i < socketCount ; i ++ )
        {
            SOCKET sock = copy.fd_array[i];
            if(sock == listening)
            {
                SOCKET client = accept(listening ,nullptr , nullptr);
                cout<< "  client" <<"  is connected"<<endl;

                FD_SET (client, &master);

                string welcomeMsg = " Wellcome to the factorize server! ";
                send(client,welcomeMsg.c_str(),welcomeMsg.size() + 1, 0);
            }
            else
            {
                char buf[4096];
                ZeroMemory(buf, 4096);

                int bytesIn = recv(sock, buf, 4096, 0);

                if(bytesIn <= 0)
                {
                    closesocket(sock);
                    FD_CLR(sock, &master);

                }
                else
                {

                    try
                        {

                            int Nums[200];
                            char Tags[200];
                            string Temp, Temp2;
                            string ComIn=buf;
                            Temp=ComIn.at(0);
                            if(int(Temp.at(0))<97 | int(Temp.at(0))>122 & int(Temp.at(0))!=160)
                                break;
                            int idd=0;
                            for (int i=0;i<ComIn.length();i++){
                                Temp=ComIn.at(i);
                                if (Temp.compare(" ")==0)
                                    ComIn.erase(i,1);
                            }

                            while(ComIn.length()>=1){
                                Temp=ComIn.at(0);
                                if (int(Temp.at(0))>65 & int(Temp.at(0))<122){
                                    Tags[idd] = Temp.at(0);
                                    ComIn.erase(0,2);
                                    Nums[idd]=stoi(ComIn.substr(0,ComIn.find_first_of(";",0)));
                                    idd+=1;
                                    Count=idd;
                                    ComIn.erase(0,ComIn.find_first_of(";",0)+1);
                                }
                                else if(Temp.compare("-")==0){
                                    ComIn.erase(0,2);
                                    threadnumber=stoi(ComIn);
                                    ComIn="";
                                }else{
                                    ComIn="";
                                }
                            }
                            //int res = Sum(stoi(fields[0]), stoi(fields[1]));
                            Threads(threadnumber,Nums,Tags);
                            string resMessage="";
                            for (int i=0;i<idd;i++){
                                resMessage+=str2[i];
                                resMessage+="\n";
                            }

                            //string resMessage = " ======> Fact = " + str2 + "\n"; //itoa(res,buffer,10)
                            send(sock,resMessage.c_str(), resMessage.size() + 1, 0);
                        }
                    catch(...)
                    {
                    }
                }

            }
        }
    }
    return 0;
}

int split(char* str, char *splitter)
{
    if(NULL == str)
    {
        return 0;
    }

    int cnt;
    fields[0] = str;
    for(cnt = 1; (fields[cnt] = strstr(fields[cnt - 1], splitter)) != NULL &&
            cnt < 5; cnt++)
    {
        *fields[cnt] = '\0';
        ++fields[cnt];
    }
    return cnt;
}

int  Factorization(int num ,char tag, int TH )
{
    //string str2[200];
    int index=1;
    str2[TH]="";
    str2[TH]=(tag);
    str2[TH]+="=";
    int Or=num;
    while (num % 2 == 0)
        {
            if (index>=m){
                break;
            }
            str2[TH]+=to_string(2);
            str2[TH]+=" ";
            num = num/2;
            index+=1;
        }

    // one element (Note i = i +2)
    for (int i = 3; i <= (Or/2); i = i + 2)
    {
        // While i divides n, print i and divide n
        while (num % i == 0)
        {
            if (index>=m){
                        break;
                    }
            str2[TH]+=to_string(i);
            str2[TH]+=" ";
            num = num/i;
            index+=1;
        }
    }
    if (num > 2){
        str2[TH]+=to_string(num);
        str2[TH]+=" ";
    }
  return 0;
}


void Threads(int n,int Nums[],char Tags[])
{
    if(n>=Count)
        n=Count;
    thread threads[n];
    int C2=0;
    if(Count%n==0)
        C2=(Count/n)-1;
    else
        C2=Count/n;
    for(int C1=0; C1<=C2; C1++){
        for (int i = 0; i < n; i++)
        {
          //thread (Factorization(Nums[i],Tags[i]), i + 1);
            if((C1*n+i)<=Count)
                threads[i] = thread(Factorization,Nums[i+(C1*n)],Tags[i+(C1*n)],i+(C1*n));
        }

        for (auto& th : threads) {
            th.join();
        }
    }
}
