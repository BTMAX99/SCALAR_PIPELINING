#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include<fstream>
using namespace std;
class pipe_line
{
    public:
        int memory[256];
        int reg[16];
        int regA;
        int regB;
        int reg_desti;
        string ins[128];
        int pc=0;
        int alu;
        int reg_lmd;
        int exit_now=0;
        string ir;
        int stall=0;
        int no_cycles=0;
        int no_control=0;
        int no_logic=0;
        int no_ins=0;
        int no_alu=0;
        int no_mem=0;
        int stall1=0;
        int jhg=0;
int temp100;
    vector<string> stalls;
        int dep[16];
        int test1=0;
        int test2=0;
   pipe_line()
   {
        for(int j=0;j<16;j++)
        {
            dep[j]=0;
        }
   }
    string IF(int b)
    {
        pc=b;
	//cout<<"pc"<<pc<<endl;
	if(pc == 127){jhg=1;}
        string a=ins[pc];
        ir = "";
     ir=ir+a[0];

    for (int i = 1; i < 4; i++) {
      if (a[i] == '0') {
        ir = ir + "0000";
      } else if (a[i] == '1') {
        ir = ir + "0001";
      } else if (a[i] == '2') {
        ir = ir + "0010";
      } else if (a[i] == '3') {
        ir = ir + "0011";
      } else if (a[i] == '4') {
        ir = ir + "0100";
      } else if (a[i] == '5') {
        ir = ir + "0101";
      } else if (a[i] == '6') {
        ir = ir + "0110";
      } else if (a[i] == '7') {
        ir = ir + "0111";
      } else if (a[i] == '8') {
        ir = ir + "1000";
      } else if (a[i] == '9') {
        ir = ir + "1001";
      } else if (a[i] == 'A') {
        ir = ir + "1010";
      } else if (a[i] == 'B') {
        ir = ir + "1011";
      } else if (a[i] == 'C') {
        ir = ir + "1100";
      } else if (a[i] == 'D') {
        ir = ir + "1101";
      } else if (a[i] == 'E') {
        ir = ir + "1110";
      } else if (a[i] == 'F') {
        ir = ir + "1111";
      }
    }
//cout<<"ir"<<ir<<endl;
        pc=b+1;
        return ir;
    }
    void ID(string binary)
    {
        int a=0;
         int b=0;
         int c=0;
         if(binary[4]=='1')
         {
             a=a+1;
         }
         if(binary[3]=='1')
         {
             a=a+2;
         }
         if(binary[2]=='1')
         {
             a=a+4;
         }
         if(binary[1]=='1')
         {
             a=a+8;
         }
         if(binary[8]=='1')
         {
             b=b+1;
         }
         if(binary[7]=='1')
         {
             b=b+2;
         }
         if(binary[6]=='1')
         {
             b=b+4;
         }
         if(binary[5]=='1')
         {
             b=b+8;
         }  
         if(binary[12]=='1')
         {
             c=c+1;
         }
         if(binary[11]=='1')
         {
             c=c+2;
         }
         if(binary[10]=='1')
         {
             c=c+4;
         }
         if(binary[9]=='1')
         {
             c=c+8;
         }
        test1=b;
        test2=c;
        reg[0]=0;
        regA=reg[b];
        regB=reg[c]; 
        reg_desti=a;
        
    }
   void EX(string binary)
    {   

     if(binary[0]=='0')
     {
         alu=regB+regA;
            int fg=0;
        if(binary[4]=='1')
         {
             fg=fg+1;
         }
         if(binary[3]=='1')
         {
             fg=fg+2;
         }
         if(binary[2]=='1')
         {
             fg=fg+4;
         }
         if(binary[1]=='1')
         {
             fg=fg+8;
         }
         if(fg!=0)
         {
         dep[fg]=1;
         }
     }
     if(binary[0]=='1')
     {

         alu=regA-regB;
//cout<<"alu"<<alu<<endl;
        int fg=0;

        if(binary[4]=='1')
         {
             fg=fg+1;
         }
         if(binary[3]=='1')
         {
             fg=fg+2;
         }
         if(binary[2]=='1')
         {
             fg=fg+4;
         }
         if(binary[1]=='1')
         {
             fg=fg+8;
         }
        if(fg!=0)
        {
        dep[fg]=1;
        }
     }
     if(binary[0]=='2')
     {
         alu=regA*regB;
        int fg=0;
        if(binary[4]=='1')
         {
             fg=fg+1;
         }
         if(binary[3]=='1')
         {
             fg=fg+2;
         }
         if(binary[2]=='1')
         {
             fg=fg+4;
         }
         if(binary[1]=='1')
         {
             fg=fg+8;
         }
        if(fg!=0)
        {
        dep[fg]=1;
        }
     }
     if(binary[0]=='3')
     {
         alu=reg_desti+1;
        int fg=0;
        if(binary[4]=='1')
         {
             fg=fg+1;
         }
         if(binary[3]=='1')
         {
             fg=fg+2;
         }
         if(binary[2]=='1')
         {
             fg=fg+4;
         }
         if(binary[1]=='1')
         {
             fg=fg+8;
         }
        if(fg!=0)
        {

        dep[fg]=1;
        }
     }
     if(binary[0]=='4')
     {
        alu=regA & regB;
        int fg=0;
        if(binary[4]=='1')
         {
             fg=fg+1;
         }
         if(binary[3]=='1')
         {
             fg=fg+2;
         }
         if(binary[2]=='1')
         {
             fg=fg+4;
         }
         if(binary[1]=='1')
         {
             fg=fg+8;
         }
        if(fg!=0)
        {

        dep[fg]=1;
        }
     }
     if(binary[0]=='5')
     {  
         
         alu=regA | regB;
        int fg=0;
        if(binary[4]=='1')
         {
             fg=fg+1;
         }
         if(binary[3]=='1')
         {
             fg=fg+2;
         }
         if(binary[2]=='1')
         {
             fg=fg+4;
         }
         if(binary[1]=='1')
         {
             fg=fg+8;
         }
        if(fg!=0)
        {

        dep[fg]=1;
        }

     }
     if(binary[0]=='6')
     {
         
         alu=~regA;
        int fg=0;
        if(binary[4]=='1')
         {
             fg=fg+1;
         }
         if(binary[3]=='1')
         {
             fg=fg+2;
         }
         if(binary[2]=='1')
         {
             fg=fg+4;
         }
         if(binary[1]=='1')
         {
             fg=fg+8;
         }
        if(fg!=0)
        {

        dep[fg]=1;
        }
     }
     if(binary[0]=='7')
     {
         
         alu=(regA & (~regB)) | (regB & (~regA));
int fg=0;
if(binary[4]=='1')
         {
             fg=fg+1;
         }
         if(binary[3]=='1')
         {
             fg=fg+2;
         }
         if(binary[2]=='1')
         {
             fg=fg+4;
         }
         if(binary[1]=='1')
         {
             fg=fg+8;
         }
if(fg!=0)
        {

        dep[fg]=1;
        }
     }
     if(binary[0]=='8')
     {
        int b=0;
        if(binary[4]=='1')
         {
             b=b+1;
         }
         if(binary[3]=='1')
         {
             b=b+2;
         }
         if(binary[2]=='1')
         {
             b=b+4;
         }
         if(binary[1]=='1')
         {
             b=b+8;
         }  
         int c=0;
         if(binary[12]=='1')
         {
             c=c+1;
         }
         if(binary[11]=='1')
         {
             c=c+2;
         }
         if(binary[10]=='1')
         {
             c=c+4;
         }
         if(binary[9]=='1')
         {
             c=c+8;
         }
         int k=regA+c;
       alu=k;
    if(b!=0)
        {
        dep[b]=1;
        }
     }
     if(binary[0]=='9')
     {
int b=0;if(binary[8]=='1')
         {
             b=b+1;
         }
         if(binary[7]=='1')
         {
             b=b+2;
         }
         if(binary[6]=='1')
         {
             b=b+4;
         }
         if(binary[5]=='1')
         {
             b=b+8;
         }  
         int c=0;
//cout<<"binary"<<binary<<endl;
         if(binary[12]=='1')
         {
             c=c+1;
         }
         if(binary[11]=='1')
         {
             c=c+2;
         }
         if(binary[10]=='1')
         {
             c=c+4;
         }
         if(binary[9]=='1')
         {
             c=c+8;
         }
//cout<<"regA"<<regA<<"C"<<c<<endl;
         int k=regA+c;
       alu=k;

     }
     if(binary[0]=='A')
     {
         int a=0;
         int b=0;
        if(binary[4]=='1')
            a=a+1;
         if(binary[3]=='1')
         {
             a=a+2;
         }
         if(binary[2]=='1')
         {
             a=a+4;
         }
         if(binary[8]=='1')
         {
             b=b+1;
         }
         if(binary[7]=='1')
         {
             b=b+2;
         }
         if(binary[6]=='1')
         {
             b=b+4;
         }
         if(binary[5]=='1')
         {
             b=b+8;
         }  
         stall1=stall1+2;
	stalls.push_back("Branch");
stalls.push_back("Branch");
int k;
if(binary[1]=='1')
k=a*16+b-128;
else
k=a*16+b;

       // cout<<"error"<<pc<<" "<<k<<" "<<binary<<endl;
         alu=pc+k-1;

         pc=alu;
     }
     if(binary[0]=='B')
     {
int a=0;
if(binary[4]=='1')
a=a+1;
if(binary[3]=='1')
a=a+2;
if(binary[2]=='1')
a=a+4;
if(binary[1]=='1')
a=a+8;
         int b=0;
         int c=0;
         if(binary[8]=='1')
         {
             b=b+1;
         }
         if(binary[7]=='1')
         {
             b=b+2;
         }
         if(binary[6]=='1')
         {
             b=b+4;
         }  
         if(binary[12]=='1')
         {
             c=c+1;
         }
         if(binary[11]=='1')
         {
             c=c+2;
         }
         if(binary[10]=='1')
         {
             c=c+4;
         }
         if(binary[9]=='1')
         {
             c=c+8;
         }
int k;
if(binary[5]=='1')
k=b*16+c-128;
else
k=b*16+c;
         stall1=stall1+2;
stalls.push_back("Branch");
stalls.push_back("Branch");
//cout<<"abbbbbbbbbbbbbb"<<a<<"rega"<<reg[a]<<endl;
         if(reg[a]==0)
         {
  //          cout<<"came"<<a<<reg[a]<<endl;
             alu=pc+k-1;

             pc=alu;
         }
     }
     if(binary[0]=='F')
     {
         exit_now=1;
     }


    }
    void MEM(string binary)
    {
int a=0;
 if(binary[4]=='1')
         {
             a=a+1;
         }
         if(binary[3]=='1')
         {
             a=a+2;
         }
         if(binary[2]=='1')
         {
             a=a+4;
         }
         if(binary[1]=='1')
         {
             a=a+8;
         }
if(binary[0]=='0'||binary[0]=='1'||binary[0]=='2'||binary[0]=='3'||binary[0]=='4'||binary[0]=='5'||binary[0]=='6'||binary[0]=='7')
        {
                temp100=alu;
        }
        if(binary[0]=='8')
        {
no_mem++;
            reg_lmd=memory[alu];
        }
        if(binary[0]=='9')
        {
no_mem++;

	//	cout<<"store"<<alu<<endl<<reg[a]<<endl;
if(alu<256)
{
//cout<<"alu"<<alu<<"a"<<a<<"reg"<<reg[a]<<endl;
            memory[alu]=reg[a];
}
        }
    }
   void WB(string binary)

    { 
no_cycles++;
//cout<<"hi"<<endl<<binary[0]<<endl;
if(binary!="0000000000000")
{
no_ins++;
}
if(binary[0]=='0'||binary[0]=='1'||binary[0]=='2'||binary[0]=='3')
{
if(binary!="0000000000000")
no_alu++;
}
if(binary[0]=='4'||binary[0]=='5'||binary[0]=='6'||binary[0]=='7')
{
no_logic++;
}
if(binary[0]=='A'||binary[0]=='B')
{
no_control++;
}
int a=0;
if(binary[4]=='1')
         {
             a=a+1;
         }
         if(binary[3]=='1')
         {
             a=a+2;
         }
         if(binary[2]=='1')
         {
             a=a+4;
         }
         if(binary[1]=='1')
         {
             a=a+8;
         }
int b=0;
         int c=0;
         if(binary[8]=='1')
         {
             b=b+1;
         }
         if(binary[7]=='1')
         {
             b=b+2;
         }
         if(binary[6]=='1')
         {
             b=b+4;
         }
         if(binary[5]=='1')
         {
             b=b+8;
         }  
         if(binary[12]=='1')
         {
             c=c+1;
         }
         if(binary[11]=='1')
         {
             c=c+2;
         }
         if(binary[10]=='1')
         {
             c=c+4;
         }
         if(binary[9]=='1')
         {
             c=c+8;
         }
  if(binary[0]=='0'||binary[0]=='1'||binary[0]=='2'||binary[0]=='3'||binary[0]=='4'||binary[0]=='5'||binary[0]=='6'||binary[0]=='7')
        {
 
            reg[a]=temp100;
            
if(a!=0)
     {
//cout<<"niyu"<<a<<endl;
dep[a]=-1;

    }

        }
//cout<<"check"<<binary;
        if(binary[0]=='8')
        {

//cout<<"bbbbb";
            reg[a]=reg_lmd;  
if(a!=0)
     {
//cout<<"niyu"<<a<<endl;
dep[a]=-1;
        }

    
    }
}
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    pipe_line P;

    ifstream abc("RF.txt");
    for(int i=0;i<16;i++)
    {
        abc>>P.reg[i];

    }
    ifstream pqr;
    pqr.open("ICache.txt");
    for(int i=0;i<128;i++)
    {
        pqr>>P.ins[i];
        
    }
    ifstream xyz;
    xyz.open("DCache.txt");
    for(int j=0;j<256;j++)
    {
         string a;
int ir=0;
        xyz>>a;
for (int i = 0; i < 2; i++) {
      if (a[i] == '0') {
        ir = ir + 0;
      } else if (a[i] == '1') {
        ir = ir + 1;
      } else if (a[i] == '2') {
        ir = ir + 2;
      } else if (a[i] == '3') {
        ir = ir + 3;
      } else if (a[i] == '4') {
        ir = ir + 4;
      } else if (a[i] == '5') {
        ir = ir + 5;
      } else if (a[i] == '6') {
        ir = ir + 6;
      } else if (a[i] == '7') {
        ir = ir + 7;
      } else if (a[i] == '8') {
        ir = ir + 8;
      } else if (a[i] == '9') {
        ir = ir + 9;
      } else if (a[i] == 'A') {
        ir = ir + 10;
      } else if (a[i] == 'B') {
        ir = ir + 11;
      } else if (a[i] == 'C') {
        ir = ir + 12;
      } else if (a[i] == 'D') {
        ir = ir + 13;
      } else if (a[i] == 'E') {
        ir = ir + 14;
      } else if (a[i] == 'F') {
        ir = ir + 15;
      }
    }
       P.memory[j]=ir;
        
    }
    
    int temp1=0;
    int temp2=0;
    int temp3=0;
string s1,s2,s3,s4;
    int cycle=0;
    s2="0000000000000"; 
        s3="0000000000000";
        s1="0000000000000";
    s4="0000000000000";
    while(P.jhg!=1)
    {
    //for(int i=0;i<1e9;i++);
        cycle++;
    
        for(int i=0;i<16;i++)
        {
            if(P.dep[i]==-1)
            {
                P.dep[i]=0;
            }
        }
//cout<<"poiu"<<endl;
//out<<"wb"<<endl;
//cout<<s1<<endl;
//cout<<"hjkl"<<endl;
        P.WB(s1);
//cout<<"mem"<<endl;
//cout<<s2<<endl;
        P.MEM(s2);
//cout<<"ex"<<endl;
//cout<<s3<<endl;
        P.EX(s3);
if(P.exit_now==1)
{
temp3++;
}
if(temp3==3)
{
break;
}
//cout<<"id"<<endl;
//cout<<s4<<endl;
int kl1=P.regA;
int kl2=P.regB;
int kl3=P.reg_desti;
        P.ID(s4);
//cout<<"here line"<<endl;
//cout<<"test "<<P.test1<<" "<<P.test2<<endl;
//cout<<"test "<<P.dep[P.test1]<<" "<<P.dep[P.test2]<<endl;
int stop=0;
if(s4[0]=='0'||s4[0]=='1'||s4[0]=='2'||s4[0]=='4'||s4[0]=='5'||s4[0]=='7')
{
if(P.dep[P.test1]==1||P.dep[P.test1]==-1||P.dep[P.test2]==1||P.dep[P.test2]==-1)
{
stop=1;
}
}
if(s4[0]=='3'||s4[0]=='6'||s4[0]=='B')
{
if(P.dep[P.reg_desti]==1||P.dep[P.reg_desti]==-1)
{
stop=1;
}
}
if(s4[0]=='8'||s4[0]=='9')
{
//cout<<"ghhg"<<P.dep[P.test1]<<P.test1<<endl;
if(P.dep[P.test1]==1||P.dep[P.test1]==-1)
{
stop=1;
}
}
//cout<<"stop"<<endl<<stop;
        if(stop==1)
        {

P.regA=kl1;
P.regB=kl2;
P.reg_desti=kl3;
for(int i=0;i<16;i++)
        {
            if(P.dep[i]==-1)
            {
                P.dep[i]=0;
            }
        }
            P.stall++;
P.stalls.push_back("RAW");
//cout<<"wb"<<endl;
//cout<<s2<<endl;
            P.WB(s2);
//cout<<"MEM"<<endl;
//cout<<s3<<endl;
            P.MEM(s3);
 kl1=P.regA;
kl2=P.regB;
 kl3=P.reg_desti;

        P.ID(s4);
//cout<<"ID"<<endl<<s4<<endl;

//cout<<"test "<<P.test1<<" "<<P.test2<<endl;
//cout<<"test "<<P.dep[P.test1]<<" "<<P.dep[P.test2]<<endl;
int stop1=0;
if(s4[0]=='0'||s4[0]=='1'||s4[0]=='2'||s4[0]=='4'||s4[0]=='5'||s4[0]=='7')
{
if(P.dep[P.test1]==1||P.dep[P.test1]==-1||P.dep[P.test2]==1||P.dep[P.test2]==-1)
{
stop1=1;
}
}
if(s4[0]=='3'||s4[0]=='6'||s4[0]=='B')
{
if(P.dep[P.reg_desti]==1||P.dep[P.reg_desti]==-1)
{
stop1=1;
}
}
if(s4[0]=='8'||s4[0]=='9')
{
if(P.dep[P.test1]==1||P.dep[P.test1]==-1)
{
stop1=1;
}
}
//cout<<"stop1"<<endl<<stop1;
            if(stop1==1)
            {
P.regA=kl1;
P.regB=kl2;
P.reg_desti=kl3;
for(int i=0;i<16;i++)
        {
            if(P.dep[i]==-1)
            {
                P.dep[i]=0;
            }
        }
                P.stall++;
P.stalls.push_back("RAW");
//cout<<"wb"<<endl;
//cout<<s3<<endl;
                P.WB(s3);
kl1=P.regA;
kl2=P.regB;
 kl3=P.reg_desti;
P.ID(s4);
//cout<<"test "<<P.test1<<" "<<P.test2<<endl;
// cout<<"test "<<P.dep[P.test1]<<" "<<P.dep[P.test2]<<endl;
int stop2=0;
if(s4[0]=='0'||s4[0]=='1'||s4[0]=='2'||s4[0]=='4'||s4[0]=='5'||s4[0]=='7')
{
if(P.dep[P.test1]==1||P.dep[P.test1]==-1||P.dep[P.test2]==1||P.dep[P.test2]==-1)
{
stop2=1;
}
}
if(s4[0]=='3'||s4[0]=='6'||s4[0]=='B')
{
if(P.dep[P.reg_desti]==1||P.dep[P.reg_desti]==-1)
{
stop2=1;
}
}
if(s4[0]=='8'||s4[0]=='9')
{
if(P.dep[P.test1]==1||P.dep[P.test1]==-1)
{
stop2=1;
}
}
//cout<<"stop"<<endl<<stop;

                if(stop2==1)
                {
P.regA=kl1;
P.regB=kl2;
P.reg_desti=0;

                    P.stall++;
P.stalls.push_back("RAW");
                    s1="0000000000000";
                     s2="0000000000000"; 
                     s3="0000000000000";
                    s4=s4;
                }
                else 
                {

                    P.regA=kl1;
P.regB=kl2;
P.reg_desti=0;
//cout<<"Id"<<endl<<s4<<endl;
P.ID(s4);
if(s4[0]=='B'||s4[0]=='A')
{
P.WB(s2);
P.MEM(s3);
//cout<<"ex"<<endl<<s4<<endl;
P.EX(s4);
s1=s3;
s2=s4;
s3="0000000000000";
s4="0000000000000";
P.reg_desti=0;
continue;
}
if(P.pc>127)
break;
string s5=P.IF(P.pc);
//cout<<"if"<<endl<<s5<<endl;
                    s2="0000000000000"; 
                     s3="0000000000000";
                    s1="0000000000000";
                }
            }
            else
            {
                P.regB=kl2;
//cout<<"Id"<<endl<<s4<<endl;
P.ID(s4);
if(s4[0]=='B'||s4[0]=='A')
{
P.WB(s2);
P.MEM(s3);
//cout<<"ex"<<endl<<s4<<endl;
P.EX(s4);
s1=s3;
s2=s4;
s3="0000000000000";
s4="0000000000000";
 
continue;
}
                    s1=s3;

                    s3=s4;
if(P.pc>127)
break;
                    string s5=P.IF(P.pc); 
//cout<<"if"<<endl<<s5<<endl;
                    s2="0000000000000"; 
                     s4="0000000000000";

            }
            
        }
        else
        {
P.regB=kl2;
//cout<<"Id"<<endl<<s4<<endl;
P.ID(s4);
if(s4[0]=='B'||s4[0]=='A')
{
//cout<<"wb"<<endl<<s2<<endl;
P.WB(s2);
//cout<<"mem"<<endl<<s3<<endl;
P.MEM(s3);
//cout<<"ex"<<endl<<s4<<endl;
P.EX(s4);
s1=s3;
s2=s4;
s3="0000000000000";
s4="0000000000000";
 
continue;
}

if(P.pc>127)
break;
        string s5=P.IF(P.pc);
  //cout<<"nithinP"<<endl<<s5<<endl;
    //    cout<<s1<<' '<<s2<<' '<<s5<<endl;
        s1=s2;
        s2=s3;
        s3=s4;
        s4=s5;
  //cout<<"s1 here"<<endl<<s1<<endl;
        }
        
    }
    abc.close();
    ofstream Abc;
    Abc.open("DCache.txt");
    for(int i=0;i<256;i++)
    {
	int poi=P.memory[i]/16;
	int ytr=P.memory[i]%16;
char tyu;
char ert;
if(poi==0)
tyu='0';
if(poi==1)
tyu='1';
if(poi==2)
tyu='2';
if(poi==3)
tyu='3';
if(poi==4)
tyu='4';
if(poi==5)
tyu='5';
if(poi==6)
tyu='6';
if(poi==7)
tyu='7';
if(poi==8)
tyu='8';
if(poi==9)
tyu='9';
if(poi==10)
tyu='A';
if(poi==11)
tyu='B';
if(poi==12)
tyu='C';
if(poi==13)
tyu='D';
if(poi==14)
tyu='E';
if(poi==15)
tyu='F';
if(ytr==0)
ert='0';
if(ytr==1)
ert='1';
if(ytr==2)
ert='2';
if(ytr==3)
ert='3';
if(ytr==4)
ert='4';
if(ytr==5)
ert='5';
if(ytr==6)
ert='6';
if(ytr==7)
ert='7';
if(ytr==8)
ert='8';
if(ytr==9)
ert='9';
if(ytr==10)
ert='A';
if(ytr==11)
ert='B';
if(poi==12)
ert='C';
if(ytr==13)
ert='D';
if(ytr==14)
ert='E';
if(ytr==15)
ert='F';


        Abc<<tyu<<ert<<endl;
    }
    xyz.close();
ofstream jkl;
jkl.open("Output.txt");
{
jkl<<P.no_ins<<endl;
jkl<<P.no_alu<<endl;
jkl<<P.no_logic<<endl;
jkl<<P.no_mem<<endl;
jkl<<P.no_control<<endl;
float cpi,pl,io;
io=P.no_cycles;
pl=P.no_ins;
cpi=io/pl;
jkl<<cpi<<endl;
jkl<<P.stall+P.stall1<<endl;
int xyz=P.stalls.size();
for(int h=1;h<=xyz;h++)
{
jkl<<"S"<<h<<" : "<<P.stalls[h-1]<<endl;
}
jkl<<"RAW: "<<P.stall<<endl;
jkl<<"Control: "<<P.stall1<<endl;
}
    return 0;
}


