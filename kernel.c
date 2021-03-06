/* Loading and Executing Files
Reem Alhumaidan
*/

void StrPrinter(char* str);
//void CharacterPrinter(char);
void StrReader(char* str);
void SecReader(char* buffer, int sector);
int CalculateMod(int i, int j);
int CalculateDiv(int x, int y);
void handleInterrupt21(int ax, int bx, int cx, int dx);
int readFile(char* fileName, char* buffer);
void executeProg(char* name, int seg);
void terminate();
int getFileSec(char* s,char* n,char* r);
void setFileSec(char* x,char* y);
void clear(char*,int);


//_____________________Main Function___________________________
int main(){
        char buffer[13312]; //maximum size of the file
         makeInterrupt21();
         interrupt(0x21,3,"messag",buffer,0);
         interrupt(0x21,0,buffer,0,0);
         interrupt(0x21,4,"shell",0x2000,0);
        while(1){
                //todo
        }
        return 0; }

//_____________________Calculate Div Function___________________
int CalculateDiv(int x, int y){
        int f;
        int n;
        for(f=0;f*y<x;f++);
            /* Subtract 1 because you can go over and get
            remainder*/
        return f-1; }

//_____________________Calculate Mod Function___________________
int CalculateMod(int i, int j){
        while(i>j)i=i-j;
        return i; }


//_____________________Print to Screen Function_________________
void StrPrinter(char* str){
        int i;
        for(i=0;str[i]!=0;i++){
                interrupt(0x10,0xE*256+str[i],0,0,0);        } }

//_____________________Read From Keyboard Function______________
void StrReader(char* str){
    /* Read until str receives 0xd.*/
        int i=0;
        char temp;
        temp=interrupt(0x16,0,0,0,0);
        while(temp!=0xd){
                interrupt(0x10,0xE*256+temp,0,0,0);
                if(temp!=0x8){ str[i]=temp;
                        temp=interrupt(0x16,0,0,0,0);
                        i++;  }
                        else temp=interrupt(0x16,0,0,0,0); }
        str[i]=0xa;
        str[i+1]=0xd;
        str[i+2]=0x0;
        interrupt(0x10,0xE*256+0xa,0,0,0);
        interrupt(0x10,0xE*256+0xd,0,0,0); }
        

//_____________ ___Read Sector From Disk Function______________
// This function will take a predefined character array of 512
// bytes+, plus a sector number
void SecReader(char* buffer, int sector){
        int AnotherSector,head,track;
        /* Another Sector - CL*/
        AnotherSector=CalculateMod(sector,18)+1;
        /* Head - DH*/
        head=CalculateMod(CalculateDiv(sector,18),2);
        /* Track - CH*/
        track=CalculateDiv(sector,36);
        interrupt(0x13,2*256+1,buffer,track*256+AnotherSector,head*256); }

//_______________Load a Program and Execute Function___________
void executeProg(char* name, int seg){
        char temp2[13312];
        int i;
        StrPrinter("start the program...\r\n");
        if(readFile(name,temp2)==1){
                        putInMemory(seg,i,temp2[i]); }
                        launchProgram(seg); }


//_________________Read File Function__________________________
int readFile(char* fileName, char* buffer){
        int i,j,k;
        char temp1[512]; /* Mapping the directory sector to temp1*/
        SecReader(temp1,2);
        for(i=0;i<16;i++){
                for(j=0;j<6;j++){
                        if(temp1[j+32*i]!=fileName[j])break; }
                        if(j==6)break; }
                        if(j==6){
                while(j<32){ //that means start load sector
                        if(temp1[j+32*i]!=0x00)SecReader(buffer+512*(j-6),temp1[j+32*i]);
                        j++; }}
                        if(i==16){
                StrPrinter("File not found!\r\n");
                        return 0; }
                        else return 1; }
                        

//_________________Handle Interrupt Function___________________
void handleInterrupt21(int ax, int bx, int cx, int dx){
        if(ax==0){
            // bx = String
                printString(bx); }
                else if(ax==1){
            // bx = buffer to hold read string
                readString(bx); }
                else if(ax==2){
            // bx = buffer to hold read string
            // cx = sector number
                readSector(bx,cx); }
                else if(ax==3){
            // bx = char array holding file name
            // cx = address of a buffer to hold the file
                /* For reading in files.
                bx is the array
                cx is to hold the file.*/
                readFile(bx,cx); }
                else if(ax==6){
                executeProg(bx,cx);  }
                else if(ax==7){
                terminate(); }
                else{
                printString("error:invalid interrupt\r\n"); }}
                

//__________Terminate Program System Call Function_____________
void terminate(){

                interrupt(0x21,4,"shell",0x2000,0); }

           
//________________Function to Get File Sector_________________  
int SIZE_OF_NAME;
int SEC_SIZE;
int getFileSec(char fName[SIZE_OF_NAME], char buf[SEC_SIZE], char fileSec[26])
{
        int e = 0;
        int a = 0;
        int q = 0;

  while (e < SEC_SIZE)
 {
        while (buf[e + a] == fName[a])
        {
                if (a == 5){
                        a++;
                        while (buf[e+a+q] != 0x00)
                        { fileSec[q] = buf[e + a + q];
                        q++;
                         }

        return q; }

                q++; }

                q++; }
                return q;
}

//_______________Function to Set the File Sector________________
int SIZE_OF_FILE;
void setFileSec(char buf[SIZE_OF_FILE], char fileSec[26]) {
        char BufSec[SEC_SIZE];
        int a = 0;
        int e = 0;
        int i=0;
                   while (fileSec[i] != 0x00 && i < 26) {
                   e = 0;
                   SecReader(buf, fileSec[a]);
        while (e < SEC_SIZE) {
                buf[a * SEC_SIZE + e] = buf[e];
                e++; }
                e++; }}

//___________________Clear Function____________________________

void clear(char* buf, int i){
          int j;
              for(j=0;j<i;j++){
              buf[j]=0x0; } }














