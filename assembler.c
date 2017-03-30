#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
	struct instruc      //defines structure instruction to store
	{
		char s[5][10];  //instruction name and its arguments
		int type;       //type of instruction (3 reg/2 reg/1 reg/no reg)
		int k;          //stores number of arguments scanned
		
	}
    inst[100];  
	
	 struct symbol   //defines structure symbol to store symbol table
	 {
		 char s[4];  //stores label name
		 int line;   //stores line number at which the label is found
		 
	 }sym[6];
	 int a[100];
	 
 int instruc,symbols;//number of instructions and symbols 
 
 int integer(char p[])   /*checks whether given string is an integer*/
 {
	 int i;
	 for(i=1;p[i]!='\0';i++)
	 {
		if(p[i]-'0'>=0 && p[i]-'0'<=9)  //if the character is between 0-9 ,
		  continue;                    //its a digit
	
		else
		  return 0;               //if not, return 0 
	 }
	 
	 return 1;
 }
 
    int three_reg_instr(char p1[]) /*checks whether instruction is 3-register inst*/
	{
		if(strcmp(p1,"ADD")==0 || strcmp(p1,"SUB")==0 ||strcmp(p1,"MUL")==0 || strcmp(p1,"DIV")==0 )
			return 1;
		else
			return 0;
	}
	
	int two_reg_instr(char p1[]) /*checks whether instruction is 2-register inst*/
	{
		if(strcmp(p1,"CMP")==0 || strcmp(p1,"NOT")==0 ||strcmp(p1,"LSHIFT")==0 || strcmp(p1,"RSHIFT")==0 || strcmp(p1,"STR")==0 || strcmp(p1,"MOV")==0 ||strcmp(p1,"LOAD")==0 || strcmp(p1,"IN")==0 || strcmp(p1,"OUT")==0)
			return 1;
		else
		    return 0;		

	}
	
	int one_reg_instr(char p1[]) /*checks whether instruction is 1-register inst*/
	{
		if(strcmp(p1,"INC")==0 || strcmp(p1,"DEC")==0 ||strcmp(p1,"PUSH")==0 || strcmp(p1,"POP")==0 || strcmp(p1,"SP")==0 || strcmp(p1,"JME")==0 ||strcmp(p1,"JNZ")==0 || strcmp(p1,"JNE")==0 || strcmp(p1,"JMP")==0)
			return 1;
		
		else
			return 0;
			
	}
	
	int instruct(FILE *fp,char p1[]) /*checks whether given instruction is valid instruction*/
	{
			fp=fopen("Opcode.txt","r"); //open opcode file in read mode
			char l1[17],l2[17];
			
			while(!feof(fp))
			{
				fscanf(fp,"%s %s",l1,l2); //scan instruction name and address
				
				if(strcmp(p1,l1)==0) //if instruc name matches with p1
					return 1;		//instruc found! return 1
			}
			return 0;	
	} 
	int regis(char p1[]) /*checks whether given register is valid register or not*/
	{
			if(p1[0]=='R') //if 1st character is R
			{
				int i;
				for(i=0;i<strlen(p1);i++)
				  {
					  if(p1[i]-'0'>=0 && p1[i]-'0'<=9) //if all other digits are numbers
						  continue; //continue till you find a non-digit char
					  else
						  return 0; //if non-digit, returns 0
				  }
					return 1; // valid register, return 1
			}
			return 0;		
	}
	int label(char p1[]) /*checks whether p1 is valid label or not*/
	{
		if(p1[0]=='L' && p1[2]==':') //if 1st character is L
		{
			switch(p1[1]-'0')
			{
				case 1:         //If next char is b/w 1-6, return 1
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
				return 1;
				default:
				return 0; //if not,return 0
				
			}
			
		}
		return 0; //if 1st char is not L,invalid label
		
	}
	
	void fcheck(FILE *fp,char p1[],FILE *fout) /*finds & prints in output file if character p1 is in file fp*/
	{
			rewind(fp);
			char p2[17],p3[17];
			
			while(!feof(fp))
				{   
					fscanf(fp,"%s %s\n",p2,p3); //scan name and address
					
					if(strcmp(p1,p2)==0)     //if found
						{
							fprintf(fout,"%s",p3); //print the corresponding adress              
							break;				 // in output file
						}
					
				}
				
			
	}
	int freg_chk(char s[]) /*checks whether the register used is b/w R0-R13*/
	{   
		if(strlen(s)>3) 
			return 0;
		
		if(s[0]!='R')
			return 0;
		
		if(strlen(s)==3)
		{
			if(s[2]-'0'>3 || s[1]-'0'>1)
				return 0;
			else
			{
				if(isdigit(s[1]) && isdigit(s[2]))
					return 1;
				else
					return 0;
				
			}
			
		}
		if(strlen(s)==2)
		{
			if(isdigit(s[1]))
				return 1;
			else
				return 0;
		}
		return 0;
		
		
	}
	void enter_input(FILE *f_in) /*takes input from user and write in input file*/
	{
			char m[17];
			printf("Enter Assembly Instructions: \n");
			
			while(1)
			{
				fscanf(stdin,"%s",m);
				fprintf(f_in,"%s\n",m);
				if(strcmp(m,"HLT")==0) //loop continues till user enters HLT
					break;
				
			}
			
	
	}
	
	int overflow(char pl[]) /*checks whether user has entered a value more than 2^15*/
	{   
	    int j,i;
		j=strlen(pl);
		char s[j];
		
		for(i=1;pl[i]!='\0';i++)
		{
			s[i-1]=pl[i];
		}
		s[i]='\0';
		int k=atoi(s);
		if(k>32768)
			return 1;
		else
			return 0;
	
	}
	
	 void fconvert_to_hex(FILE* f_out,char pl[]) /*converts integer to 16-bit binary num*/
	 {
		 int k=atoi(pl),t=15;
		 //printf("%s \n",pl);
		 char m[17];
		 
		 while(k)
		 {
			m[t--]=(k%2)+'0';
			k=k/2;		
		 }
		 
		 while(t>=0)
			 m[t--]='0';
		 
		 m[16]='\0';
		 //printf("%s\n",m);
		 fprintf(f_out,"1110\n");
		 fprintf(f_out,"%s",m);//write the binary code in output file
		 
	 }
	 int r;
	 void store(FILE *f_in,FILE *f_op,FILE *f_reg,FILE *f_lab,FILE *f_sym)
	 {
		 char m[17];
			
			char p1[17],p2[17],p3[17],p4[17],p5[17],prev[17];
			int i=-1,instr=0,flag,n,end=0,q,s,t,k=0,j=0;
			r=0;
			for(i=0;i<100;i++)
				inst[i].k=0;
			i=-1;
			instruc=0;
			
			while(!feof(f_in))
			{   
					flag=0;
					rewind(f_op);
					rewind(f_reg);
					rewind(f_lab);
					
					fscanf(f_in,"%s\n",p1);
					//printf("%d : %s\n",instr,p1);
					if(strcmp(p1,"HLT")==0) //if encountered a HLT, assign 1 to end
						end=1;
					
					if(instruct(f_op,p1)) //if scanned string is instruction
					{   k=0;      
						i++;     //increment num of instructions
						strcpy(inst[i].s[k],p1);
						//printf("%s ",inst[i].s[k]);
						
						inst[i].k=k; 
						k++;
						
						if(three_reg_instr(p1)) //3-reg inst
							inst[i].type=3;     
						else if(two_reg_instr(p1)) //2-reg inst
							inst[i].type=2;
						else if(one_reg_instr(p1)) //1-reg inst
							inst[i].type=1;
						else                     //no arg inst
							inst[i].type=0;
						
					}
					else if(label(p1)) //if scanned string is a label
					{   
						if(strcmp(prev,"JMP")==0 || strcmp(prev,"JNE")==0 ||strcmp(prev,"JNZ")==0 ||strcmp(prev,"JME")==0) //if its encountered after loop instructions
						{
							strcpy(inst[i].s[k],p1); //store it in instruction row i
							inst[i].k=k;
							k++;
						}
						else
						{ 
					      i++; //increment num of inst and store it in separate instruction row
						  k=0;
						  strcpy(inst[i].s[k],p1);
						  strcpy(sym[j].s,inst[i].s[k]);
						   fprintf(f_sym,"%s",sym[j].s); //since its a label,store it in symbol table
						  sym[j++].line=i+1;    //line num is line at which label is found
						  inst[i].type=0; 
						   //j-->num of symbols
						  
						}
					}
					else if(regis(p1) || integer(p1)) //if scanned string is a register or integer
					{
						strcpy(inst[i].s[k],p1); //store it in the same instruction row
						inst[i].k=k;
						k++;
						
					}
					else
					{
				     k=0;      
						i++;     //increment num of instructions
						strcpy(inst[i].s[k],p1);
						//printf("%s ",inst[i].s[k]);
						a[r++]=i;
						inst[i].k=k; 
						k++;
					}
					
					instr++; //increment number of lines
					strcpy(prev,p1);// store the current string in prev string 
			}
			symbols=j; //j->num of symbols =>store in symbols
		
			instruc=i; //i-->num of instructions
		 
		 
		 
	 }
	 int error=1;
	int compile(FILE *f_in,FILE *f_op,FILE *f_reg,FILE *f_lab) /*checks the error in instruction format entered by user*/
	{
		
				int p,y,u=0,j,end=0;
				error=0;
			

			for(p=0;p<=instruc;p++)	 //start scanning the stored instruction table
			{       
				if(p==0 && strcmp(inst[p].s[0],"START")!=0) //if start is not in line1
				{printf("Line 1:START not found!!\n");
			     error=1;}
				 if(p!=0 && strcmp(inst[p].s[0],"START")==0 )
				 {
					 printf("Line %d: START at wrong line!!\n",p+1);
					 error=1;
				 }
				//print error
			if(strcmp(inst[p].s[0],"HLT")==0)
				end=1;
				u=0; //change
					
				if(inst[p].k>inst[p].type) //if num of arguments user has entered is more than actual arg of instr
				{		
					printf("Line %d: Error too many arguments in instruction %s\n",p+1,inst[p].s[0]);
					error=1;
				}
				else if(inst[p].k<inst[p].type) //if num of args is less
				{
					printf("Line %d: Error too few arguments in instruction %s\n",p+1,inst[p].s[0]);
					error=1;
				}
				for(j=1;j<=inst[p].k;j++)
				   {
					   if(strcmp(inst[p].s[0],"JMP")==0 || strcmp(inst[p].s[0],"JNE")==0 ||strcmp(inst[p].s[0],"JNZ")==0 ||strcmp(inst[p].s[0],"JME")==0) //if encountered a loop instruction
					   { 
					       if(strcmp(inst[p-1].s[0],"CMP")!=0 )
						   { printf("Line %d: Error Condition not found to Jump \n",p);
					   error=1;}
						   if(label(inst[p].s[j])) // if it has label field after it
						   { 
							 for(y=0;y<symbols;y++) //check if that label is defined already in symbol table
							 {
								 if(strcmp(sym[y].s,inst[p].s[j])==0)
									 break;
							 }
							 if(y==symbols) //if not found in symbol table, print error
							    {
								 printf("Line %d: Error expected label %s not found!\n",p+1,inst[p].s[j]);
						         error=1;
						        }
						   }
					   }
					  else if((strcmp(inst[p].s[0],"MOV")==0 || strcmp(inst[p].s[0],"STR")==0 || strcmp(inst[p].s[0],"LOAD")==0 || strcmp(inst[p].s[0],"PUSH")==0) ) //if encountered a mov instruction with integer argument
					   { 
						   if(integer(inst[p].s[j]) && inst[p].s[j][0]!='R')
						   {	if(inst[p].s[j][0]!='#') // if the integer don't have '#' before it, print error
								{
								 printf("Line %d: Error expected '#' before integer in instr MOV\n",p+1);
							     error=1;
								}
								if(overflow(inst[p].s[j])) //if integer is more than 2^15,print error
								{printf("Line %d: Integer Overflow!! Only 0-2^15 allowed!\n",p+1); error=1;}
								
								  
								//denotes than 1st arg is an integer
								u=1;
								
						   }
						 else if(u==1) // if both arg are integer, print error
						   {
							printf("Line %d: Wrong Instruction format %s instruc\n",p+1,inst[p].s[0]);
						    error=1;
						   }
						   
					   
				  }					   
				  else if(!freg_chk(inst[p].s[j])) // if invalid register is entered
						{ 
						   printf("Line %d: Invalid register! Only R0-R13 allowed!!\n",p+1);
					       error=1;
					    }
					   
				   
				
				}
				for(j=0;j<r;j++)
				{
					if(a[j]==p)
					{printf("Line %d: Invalid instruction.See ISA HELP\n",p+1);
				error=1;}
				}
			}
			if(end!=1)
			{
				printf("HLT not found!!\n"); //if end is not 1, HLT is not found
				error=1;
			}
		
		
		if(error!=1) // if code has no errors, compilation successful!
		printf("Successfully compiled! Generated binary code!\n");
	
	}
	
	
	void display_symbol_table(FILE *f_lab) /*displays symbol table*/
	{  	
		int y;
		char m1[17],m2[17];
		printf("Symbol   ILC(Line Num)   Label Address\n");

		
		for(y=0;y<symbols;y++)
		{  
			while(!feof(f_lab))
			{
				fscanf(f_lab,"%s %s",m1,m2);
				if(strcmp(sym[y].s,m1)==0)

					break;
			}
			printf("%s     %d       %s\n",sym[y].s,sym[y].line,m2); // print symbol name,line num and label address
		rewind(f_lab);
		}
	
	}
	void display_binary(FILE *f_out) /*displays our binary machine code output file*/
	{
		
		char p1[17],por[17],c;
		int k=0;
		
			while( (c = getc(f_out))!=EOF )
			{    
				putchar(c);
				
			}
	
	}
    

	void display_help(FILE *f_help) /*displays ISA help file*/
	{
			char p1[17],c;
			f_help=fopen("Help.txt","r");
			
			while( (c = getc(f_help))!= EOF )
				{    
					putchar(c);
				}
				fclose(f_help);
		
		
	}
	void show() /*Shows the instructions user has entered*/
	{
		int p,i,j;
			for(p=0;p<=instruc;p++)

			{       
					   for(j=0;j<=inst[p].k;j++)
					   {   
						   printf("%s ",inst[p].s[j]);
					   }
				printf("\n");
				
			}
			
	}
	
	void generate(FILE *f_op,FILE *f_out,FILE *f_reg,FILE *f_lab) /*generates binary machine code file*/
	{
		
		int p,i,j=1,b,t=0;
		char sp[4];
		for(p=0;p<=instruc;p++)
		{     
			if(strcmp(inst[p].s[0],"JME")==0 ||strcmp(inst[p].s[0],"JMP")==0 ||strcmp(inst[p].s[0],"JNZ")==0 ||strcmp(inst[p].s[0],"JNE")==0) //if loop instruction
   					    {     
					           fcheck(f_op,inst[p].s[0],f_out);
							   
							   if(label(inst[p].s[1]))
							   {  
						   
							   fprintf(f_out,"1111\n");
							   fcheck(f_lab,inst[p].s[1],f_out);
							   fprintf(f_out,"\n");
							   
							   }
							   continue;
						} 
			
			if(instruct(f_op,inst[p].s[0])) // checks if instr,and outputs its binary address to file
				 fcheck(f_op,inst[p].s[0],f_out);
			 
			else if(label(inst[p].s[0])) //check if label and output its binary address to file
				 fcheck(f_lab,inst[p].s[0],f_out);
				 
			for(j=1;j<=inst[p].k;j++)
				{   
					if(inst[p].s[j][0]=='#') //if integer is found
						   {   
					           for(b=1;inst[p].s[j][b]!='\0';b++)
							   sp[t++]=inst[p].s[j][b];
						       sp[t]='\0';
						   
							   fconvert_to_hex(f_out,sp); //convert to 16-bit binary equivalent
						   }
						   
						   else
						   fcheck(f_reg,inst[p].s[j],f_out); //if register, output its binary add to file
				}
			fprintf(f_out,"\n");
				
		}
			
		
	}
	
int main()
{
			FILE *f_in;  // input file
			FILE *f_op; // opcode file
			FILE *f_reg;  // register adress file
			FILE *f_out;  //output file
			FILE *f_lab;  //label adress file
			FILE *f_help;
			FILE *f_sym;  //ISA help file
			
			f_in=fopen("Input.txt","w"); 
			f_op=fopen("Opcode.txt","r");
			f_reg=fopen("Reg.txt","r");
			f_lab=fopen("Labels.txt","r");
			f_out=fopen("Output.txt","w");
			f_help=fopen("Help.txt","r");
			f_sym = fopen("Symbol.txt","w");
			
			int choice=-1;
			
			printf("\n\n\tAssembler to Our ISA::\n");
			
		printf("\tThe menu is:\n");
		printf("\t1.Enter Assembly Language Code\n");
		printf("\t2.Display Assembly Language Code.\n"); 
		printf("\t3.Compile the Code.(First Pass)\n");
		printf("\t4.Display Symbol Table\n"); 
		printf("\t5.Generate & Display Machine Code.(Second Pass)\n");  
		printf("\t6.ISA Help.\n"); 
		printf("\t7.Exit.\n"); 
		printf("\n\nEnter your choice?\n");
		
	while(choice!=7)
	{  printf("Enter choice: ");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
			f_in=fopen("Input.txt","w");
			enter_input(f_in);
			fclose(f_in);
			f_in=fopen("Input.txt","r");
			f_op=fopen("Opcode.txt","r");
			f_reg=fopen("Reg.txt","r");
			f_lab=fopen("Labels.txt","r");
			
			store(f_in,f_op,f_reg,f_lab,f_sym);
			fclose(f_in);
			break;

			case 2:
			show();
			break;

			case 3:
			f_in=fopen("Input.txt","r");
			f_op=fopen("Opcode.txt","r");
			f_reg=fopen("Reg.txt","r");
			f_lab=fopen("Labels.txt","r");
			
			compile(f_in,f_op,f_reg,f_lab);
			
			fclose(f_op);
		    fclose(f_reg);
		    fclose(f_lab);
		    fclose(f_in);
			break;
			
			case 4:
			f_lab=fopen("Labels.txt","r");
			display_symbol_table(f_lab);
			break;
			
			case 5:
			if(error==1)
			{
				printf("Can't generate binary code,compilation errors\n");
				break;
			}
			f_op=fopen("Opcode.txt","r");
			f_reg=fopen("Reg.txt","r");
			f_lab=fopen("Labels.txt","r");
			f_out=fopen("Output.txt","w");
			
			generate(f_op,f_out,f_reg,f_lab);
			
		    fclose(f_op);
		    fclose(f_reg);
		   	fclose(f_lab);
		    fclose(f_out);
			
			f_out=fopen("Output.txt","r");
			display_binary(f_out); 
			fclose(f_out);
			break;

			case 6:
			display_help(f_help); 
			break;
	
		}
			
	}
return 0;	
}
	
