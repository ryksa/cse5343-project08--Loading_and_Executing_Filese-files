// Reem Alhumaidan
// shell.c

void str(char* i);

int main(){
        int i;
        char command[128],buffer[13312],tst[128];
        while(1){
                interrupt(0x21,0,"shell> \0",0,0);
                interrupt(0x21,1,command,0,0);
                if(command[0]=='t'&&command[1]=='y'&&command[2]=='p'&&command[3]=='e'){
                        for(i=5;command[i]!=0;i++){
                                        tst[i-5]=command[i]; }
                        interrupt(0x21,3,tst,buffer,0); 
                        interrupt(0x21,0,buffer,0,0);
                        interrupt(0x21,5,0,0,0);//terminate() 
                } else 
                if(command[0]=='e'&&command[1]=='x'&&command[2]=='e'&&command[3]=='c'&&command[4]=='u'&&command[5]=='t'&&command[6]=='e'){
                        for(i=8;command[i]!=0;i++){
                                        tst[i-8]=command[i];  }
                        interrupt(0x21,4,tst,0x2000,0);
                        interrupt(0x21,5,0,0,0); }
                        else { interrupt(0x21,0,"Ops not a valid command! \r\n",0,0); }  }
        return 0; }

        void str(char* i){
                int n;
                while (i[n]!=0)
                { i[n]='\0';  }
        }