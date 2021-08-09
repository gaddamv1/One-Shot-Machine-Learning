#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
int total=0;
int *countTotal=&total;
bool one=false;
bool two=false;
bool three=false;
int** allocate_matrix(int rows,int cols){
  int** val=malloc(rows*sizeof(int*));
for(int i=0; i<rows; i++){
 val[i]=malloc(cols*sizeof(int));
  }
  return val;
}
void initialize_matrix(int**matrix,int rows,int cols,int num,int rowsPosistion,int colsPosistion){
  bool inserted=false;
  for(int i=0; i<rows; i++){
    for(int j=0; j<cols; j++){
      if(i==rowsPosistion){
	if(j==colsPosistion){
	  matrix[i][j]=num;
	  inserted=true;
	  break;
	}
      }
    }
    if(inserted==true){
      break;
    }
  }
}

int numOfRowOccurences(int**matrix,int value,int row,int numOfOccurences){
  for(int b=0; b<16; b++){
    if(matrix[row][b]==value){
      numOfOccurences++;
    }
  }
  return numOfOccurences;
}
int numOfColOccurences(int**matrix,int value,int col,int numOfOccurences){
  for(int b=0; b<16; b++){
    if(matrix[b][col]==value){
      numOfOccurences++;
    }
  }
  return numOfOccurences;
}
int findCol(int**matrix,int row,int cols,int value){
  int number=0;
  for(int k=0; k<cols; k++){
    if(matrix[row][k]==value){
      number=k;
      break;
   }
  }
  return number;
}
int findRow(int**matrix,int rows,int col,int value){
  int number=0;
  for(int k=0; k<rows; k++){
    if(matrix[k][col]==value){
      number=k;
    }
  }
  return number;
}
bool checkRow(int**matrix,int row,int value){
  bool inRow=false;
for(int a=0; a<16; a++){
  if(matrix[row][a]!=value){
    inRow=false;
  }
  else{
    inRow=true;
    a=0;
    break;
  }
  }
 return inRow;
}
bool checkCol(int**matrix,int col,int value){
  bool inCol=false;
for(int b=0; b<16; b++){
  if(matrix[b][col]!=value){
    inCol=false;
  }
  else{
    inCol=true;
    b=0;
    break;
  }
  }
 return inCol;
}
bool accessSubGrid1(int**matrix,int row,int col){ 
  bool good=true;
  for(int p=row; p<(row+4); p++){
    for(int a=col; a<(col+4); a++){
      if(matrix[p][a]==-1){
	continue;
      }
      else{
	int j=matrix[p][a];
	int count=0;
	for(int c=row; c<(row+4); c++){
	  for(int d=col; d<(col+4); d++){
	    if(matrix[c][d]==j){
	      count++;
	    }
	  }
	}
	if(count>1){
	  good=false;
	  break;
	}
      }
    }
    if(good==false){
      break;
    }
  }
  return good;
}
int accessSubGrid(int**matrix,int row,int col,int*countTotal){
 int count1=0;
  for(int p=row; p<(row+4); p++){
    for(int a=col; a<(col+4); a++){
      if(matrix[p][a]==-1){
	count1++;
      }
    }
  }  
  if(count1==1){
for(int i=row; i<(row+4); i++){
    for(int j=col; j<(col+4); j++){
      if(matrix[i][j]!=-1){
	continue;
      }
      else{
	int count=0;
      for(int b=0; b<16; b++){
	for(int q=row; q<(row+4); q++){
	  for(int r=col; r<(col+4); r++){
	    if(matrix[q][r]==b){
	      count++;
	    }
	  }
	}
	if(count==0){
	  *(*(matrix+i)+j)=b;
	   *countTotal-=1;
	  break;
	}
	count=0;
      }
      }
    }
 }
  }
  return *countTotal;
}
bool checkSubGrid(int**matrix,int row,int col,int value){
  bool y=true;  
  int rowBegin=(row/4)*4;
  int colBegin=(col/4)*4;
  for(int i=rowBegin; i<(rowBegin+4); i++){
    for(int j=colBegin; j<(colBegin+4); j++){
      if (matrix[i][j]==value){
      y=false;
	}
    }
  }
  return y;
}

int check(int**matrix,int row,int cols){
  int number=0;
  for(int b=0; b<cols; b++){
    if(matrix[row][b]==-1){
      number++;
    }
  }
  return number;
}
int check1(int**matrix,int rows,int col){
  int number=0;
  for(int b=0; b<rows; b++){
    if(matrix[b][col]==-1){
      number++;
    }
  }
  return number;
}

char* convert(char x){
  char *b =malloc(2*sizeof(char));
  b[0]=x;
  b[1]='\0';
  return b;
}

int main(int argc, char** argv){
FILE* fp=fopen(argv[1],"r");
 if(fp==NULL){
   exit(0);
   }
 else{
 int**matrix;
 int rows=16;
 int cols=16;
 char ch;
 matrix=allocate_matrix(rows,cols);
 int rowsRemain=0;
 int colsRemain=0;
 int j=0;
 bool number2=true;
 while(rowsRemain<rows){
   while(colsRemain<cols){
     if(colsRemain==cols-1){
       fscanf(fp, "%c\n",&ch);       
     }
     else{
       fscanf(fp, "%c\t",&ch);
     }
       if(ch=='-'){
	 j=-1;
       }
    else if(ch=='A'||ch=='B'||ch=='C'||ch=='D'||ch=='E'||ch=='F'){
      j=ch-55;
     }
     else{
       j=ch-48;
     }
       initialize_matrix(matrix,rows,cols,j,rowsRemain,colsRemain);
       colsRemain++;
 }
   colsRemain=0;
   rowsRemain++;
 }
  for(int i=0; i<rows; i++){
   for(int j=0; j<cols; j++){
     if(matrix[i][j]!=-1){
       int occurences=numOfRowOccurences(matrix,matrix[i][j],i,0);
       int occurences2=numOfColOccurences(matrix,matrix[i][j],j,0);
        if(occurences>1||occurences2>1){
	 printf("no-solution\n");
	 number2=false;
	 break;
	}
     }
   }
   if(number2==false){
     break;
   }
  }
 bool possible=true;
  if(number2==true){
  for(int i=0; i<15; i=i+4){
    for(int j=0; j<15; j=j+4){
      bool check=accessSubGrid1(matrix,i,j);
      if(check==false){
	possible =false;
	printf("no-solution\n");
	break;
      }
      else{
	continue;
      }
    }
    if(possible==false){
      break;
    }
  }
  }
  if(number2==true&&possible==true){
  for(int i=0; i<rows; i++){
    for(int j=0; j<cols; j++){
      if (matrix[i][j]==-1){
	*countTotal+=1;
      }
    }
  }
  bool v=false;
  bool w=false;
  while(*(countTotal)!=0){
  for(int i=0; i<rows; i++){
   int countExit=16;
   int q=check(matrix,i,16);
    if(q==1){
      for(int b=0; b<16; b++){
	int x=numOfRowOccurences(matrix,b,i,0);
	if(x==0){
	 int z=findCol(matrix,i,cols,-1);
	 w=checkCol(matrix,z,b);
	 v=checkSubGrid(matrix,i,z,b);
	 if(v==true&&w==false){
	 *(*(matrix+i)+z)=b;
	 *countTotal-=1;
	  one=true;
	 }
	 else{
	   v=false;
	   countExit=0;
	   printf("no-solution\n");
	   one=false;
	   break;
	 }
	}
      }
    }
    if(v==false&&countExit==0){
      break;
    }
  }
  if(v==false){
    break;
  }
for(int p=0; p<cols; p++){
   int countExit1=cols;
   int q=check1(matrix,rows,p);
    if(q==1){
      for(int b=0; b<16; b++){
	int x=numOfColOccurences(matrix,b,p,0);
	if(x==0){
	 int z=findRow(matrix,rows,p,-1);
	 w=checkRow(matrix,z,b);
	 v=checkSubGrid(matrix,z,p,b);
	 if(v==true&&w==false){
	 *(*(matrix+z)+p)=b;
	 *countTotal-=1;
	  two=true;
	 }
	 else{
	   v=false;
	   printf("no-solution\n");
	   two=false;
	   countExit1=0;
	   break;
	 }
	}
      }
    }
    if(v==false&&countExit1==0){
      break;
    }
 }
 if(v==false){
   break;
 }
 for(int b=0; b<15; b=b+4){
   for(int c=0; c<15; c=c+4){
     const int e=*countTotal;
     int d=accessSubGrid(matrix,b,c,countTotal);
     if(d<e){
      three=true;
    }
   }
 }
 if(one==false&&two==false&&three==false){
  for(int i=0; i<rows; i++){
    for(int j=0; j<cols; j++){
      if(matrix[i][j]!=-1){
	continue;
      }
      else{
	for(int b=0; b<16; b++){
	  bool check1=checkRow(matrix,i,b);
	  if(check1==false){
	     bool check2=checkCol(matrix,j,b);
	  if(check2==false){
	   bool check3=checkSubGrid(matrix,i,j,b);
	   if(check3==true){
	   *(*(matrix+i)+j)=b;
	   *countTotal-=1;
	   break;
	   }
	  }
	  }
	}
      }
    }
  }
 }
 one=false;
 two=false;
 three=false;
  }
  if(*countTotal==0){
    countTotal=NULL;
for(int n=0; n<rows; n++){
	 for(int k=0; k<cols; k++){
	   char*result1=malloc(200*sizeof(char));
	   if(k==cols-1){
	     if(matrix[n][k]<10){
	       if(matrix[n][k]==0){
		 strcat(result1,convert('0'));
	       }
	       else{
	       strcat(result1,convert(matrix[n][k]+'0'));
	       }
	     }
	     else{
	       if(matrix[n][k]==10){
		 strcat(result1,convert('A'));
	       }
	       else if(matrix[n][k]==11){
		 strcat(result1,convert('B'));
	       }
	       else if(matrix[n][k]==12){
		 strcat(result1,convert('C'));
	       }
	       else if(matrix[n][k]==13){
		 strcat(result1,convert('D'));
	       }
	       else if(matrix[n][k]==14){
		 strcat(result1,convert('E'));
	       }
	       else if(matrix[n][k]==15){
		 strcat(result1,convert('F'));
	       }
	     }
	     printf("%s\n",result1);
	     free(result1);
	   }
	   else{
	     if(matrix[n][k]<10){
	       if(matrix[n][k]==0){
	       strcat(result1,convert('0'));
	       }
	       else{
	       strcat(result1,convert(matrix[n][k]+'0'));
	       }
	     }
	     else{
	      if(matrix[n][k]==10){
		strcat(result1,convert('A'));
	       }
	       else if(matrix[n][k]==11){
		 strcat(result1,convert('B'));
	       }
	       else if(matrix[n][k]==12){
		 strcat(result1,convert('C'));
	       }
	       else if(matrix[n][k]==13){
		 strcat(result1,convert('D'));
	       }
	       else if(matrix[n][k]==14){
		 strcat(result1,convert('E'));
	       }
	       else if(matrix[n][k]==15){
		 strcat(result1,convert('F'));
	       }
	     }
	     printf("%s\t",result1);
	     free(result1);
	   }
	 }
       }
  }
  for(int i=0; i<rows; i++) {
      free(matrix[i]);
      matrix[i]=NULL;
    }
  free(matrix);
  matrix=NULL;
  }
 }
 return 0;
}









