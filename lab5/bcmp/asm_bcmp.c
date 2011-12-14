//#include <stdio.h>

/* 
 * fuction to implement:
 * fopen
 * fread
 * fclose
 * printf
 */

unsigned int myopen(char*);
int myreadSingleChar(unsigned int, char[]);
void printFirstChar(char*);
void myclose(unsigned int);
void sys_puts();

int asm_bcmp(int argc, char *argv[]){
	if (argc != 3){
		//printf("USAGE: %s [filename1] [filname2]\n",argv[0]);
		return 1;
	}

	char *nl = "\n";	

	char buf2[1];
	char buf1[1];
		
	char *filename1 = argv[1];
	char *filename2 = argv[2];	
	unsigned int fileHandler1 = myopen(filename1);
	unsigned int fileHandler2 = myopen(filename2);


	// contiue reading the file until a diffrence is found or end of file reached
	int diff, endOfFile1, endOfFile2;
	char f1=0;
	char f2=0;
	int byteNum;

	int diff_abc;
	char temp1 = '1';
	char temp2 = 1;
	diff_abc = temp1-temp2;

	byteNum = 1;
	diff = 0;
	endOfFile1 = 1;
	endOfFile2 = 1;


	// read the files until a diffrence is found 
	while ((endOfFile1 == 1) & (endOfFile2 == 1)){
		endOfFile1 = myreadSingleChar(fileHandler1, buf1);
		endOfFile2 = myreadSingleChar(fileHandler2, buf2);

		if ((endOfFile2 == 0) | (endOfFile1 == 0)){
			//printf("debug: end of file\n");
			break;
		}
		if ((char)*buf1 != (char)*buf2){
			char* msg = "byte ";
			sys_puts(msg);
			//*(msg+4) = byteNum + diff_abc;
			//sys_puts(msg+4);
			msg = " -";
			sys_puts(msg);
			sys_puts(buf1);
			msg = " +";	
			sys_puts(msg);
			sys_puts(buf2);
			sys_puts(nl);
			//printf("byte %d -%u +%u\n",byteNum, f1, f2);
			diff = 1;
		}
		//printf("debug: byte %d in file1 is %d & in file2 is %d\n",byteNum, f1, f2);
		byteNum ++;
	}
	
	myclose(fileHandler1);
	myclose(fileHandler2);

	return 0;
}
