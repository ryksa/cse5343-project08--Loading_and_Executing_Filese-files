// Reem Alhumidan
// shell.c

#define SIZE_OF_NAME   7
#define SIZE_OF_FILE   13312
#define LEN    80

typedef enum { FALSE, TRUE } bool;
void do_print(char*);
void do_scan(char*);
void readFile(char*);
void executeFile(char*);
void command(char*);
void type(char*);
void exeProc(char*);
void split(char*, char*, char*);
bool str(char*, char*);
//void trunkFil(char*, char*);

int main() {
   char command1[LEN];
   char command2[LEN];
   char command3[LEN];

   do_print("shell:\n\r\0");
   while ( 1 )
   {
      do_print("SHELL>\0");
      do_scan(command2);
      print("\r");
      split_command(command1, command2, command3);
      command(command2, command3);
   }
}



//__________________Print Function________________________
void do_print(char line[LEN]) {
   interrupt(0x21, 0, line, 0, 0);
}

//__________________Scan Function________________________
void do_scan(char line[LEN]) {
   interrupt(0x21, 1, line, 0, 0);
}

//__________________Function to Read File________________
void readFile(char fName[SIZE_OF_NAME], char buffer[SIZE_OF_FILE]) {
   interrupt(0x21, 3, fName, buffer, 0);
}

//___________Function to Execute the File________________
void executeFile(char fName[SIZE_OF_NAME]) {
   interrupt(0x21, 6, fName, 0x2000, 0);
}

//______________Function to Process Command______________
void command(char newCom1[LEN], char newCom2[LEN]) {
   if ( str(newCom1, "type\0") )
   {
      command(newCom2);
   }
   else if ( command(newCom1, "execute\0") )
   {
      exeProc(newCom2);
   }
   else
   {
      do_print("Ops not a valid entry(\n\r\0");
   }
}

//______________Function to Process Type________________
void type(char fName[LEN]) {
   char buf[SIZE_OF_FILE];
   char fileTrunc[SIZE_OF_NAME];

   truncFileName(fName);
   readFile(fName, buf[SIZE_OF_FILE]);
   print(buf);
}


//_____________Function to Process Execute_____________
void processExecute(char fName[LEN]) {
   char fileNameTrunc[SIZE_OF_NAME];

   truncFil(fName, fileNameTrunc);
   executeFile(fileNameTrunc);
}


//________Function to Splite Between Commands__________
void split(char command1[LEN], char command2[LEN], char command3[LEN]) {
   int x = 0;
   int y = 0;

   while ( command1[x] != ' ' && command1[y] != 0x0A )
   {
      command2[x] = command1[x];
      x++;
   }
   command2[x] = '\0';
   x++;
   while ( command1[x] != ' ' && command1[x] != 0x0A )
   {
      command2[y] = command1[x];
      x++;
      y++;
   }
   command2[x] = '\0';
}


//_________Function to Compare Between Strings_________
bool str(char stringA[LEN], char stringB[LEN]) {
   int x = 0;
   bool result =FALSE;

   while (result)
   {
             if(stringA[x] == stringB[x])
             result =TRUE;
             if ( stringA[x] == '\0' && stringB[x] == '\0')
             result =TRUE;
      Switch(result);
   {
               case TRUE: return TRUE;
               case FALSE: return FALSE;
               default: return FALSE;
   }
               x++;
   }
               return(FALSE);
   }


//__________Function to Truncate File Name_____________
void truncFil(char lin1[LEN], char fName[SIZE_OF_NAME])
   {
	int sze=SIZE_OF_NAME-1;
	int x=0;
   for ( ;((lin1[x]!='\0')&&(x<sze));x++ )
   {
             fName[x] = lin1[x];
   }
             fName[x] = '\0';
   }
              
       
