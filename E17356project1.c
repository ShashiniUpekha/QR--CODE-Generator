/*******
CO222 PROGRAMMING METHODOLODY
PROJECT1 :  QR Code Generator -
E/17/356
H.P.S. UPEKHA

*****/
/*Including headers*/
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>


/*Define colors using Ansi escape codes */
#define B "\x1b[40m"   //BLACK
#define R "\x1b[41m"   //RED
#define G "\x1b[42m"   //GREEN
#define Y "\x1b[43m" //YELLOW
#define BB "\x1b[44m"  // BLUE
#define M "\x1b[45m"  //MAGENTA
#define CY "\x1b[46m"  //CYAN
#define W "\x1b[47m" // WHITE
#define RE "\x1b[0m"  //Reset color

/*Prototypes of functions*/

void CBin(int num, int C[9]);
int *BArray(int num);


static int BIN[9];     // static declaration

/*main function*/

int main(int argc,char *argv[]){
int Hashsize,i;
char Input[1000];        //url input array


char *COLOUR;      //To select the  color of the QR code

/*since the argument for color selecting is not case sensitive : convert the input argument for color into lowercase before  checking*/

if(argc==3){
    for (i=0;i<strlen(argv[2]);i++){
    argv[2][i]=tolower(argv[2][i]);         //to convert to the lower case
}
}




if (argc==1){    //when running the program without any flags
        COLOUR=B;        //QR Code in black (default)
}

/*When color selecting flag [ -c]  command is used*/
if ((argc==3) && (strcmp("-c",argv[1])==0)){
        /*Check the given argument color and assign that to the variable COLOUR*/

    if (strcmp("red",argv[2])==0) {
        COLOUR=R;                                                                        //Red
    }
    else  if (strcmp("green",argv[2])==0) {
            COLOUR=G;                                                                   //Green
    }

    else  if (strcmp("yellow",argv[2])==0) {
            COLOUR=Y;                                                                     //Yellow
    }
    else  if (strcmp("blue",argv[2])==0){
            COLOUR=BB;                                                                  //Blue
    }
    else  if (strcmp("magenta",argv[2])==0) {
            COLOUR=M;                                                                   //Magenta
    }
    else  if (strcmp("black",argv[2])==0){
            COLOUR=B;                                                                     //Black
    }
    else  if (strcmp("cyan",argv[2])==0) {
            COLOUR=CY;                                                                  //Cyan
    }
    else{               //For incorrect color argument
        printf("Invalid argument for color.\n");
        printf("usage :\n");
        printf("%s -c [black|red|green|yellow|blue|magenta|cyan]\n",argv[0]);
        printf("%s -h for the help about the program\n",argv[0]);

    }

}


/* When argument flag [-h] is used*/

if (argc==2 && (strcmp("-h",argv[1])==0)){            //Print the usage of the program
    printf("usage :\n");
    printf("%s -c [black|red|green|yellow|blue|magenta|cyan]\n",argv[0]);
    printf("%s -h for the help about the program\n",argv[0]);
}

/*Checking the conditions of the arguments to print the qr code*/
else if(argc==1 || (argc==3  && (strcmp("-c",argv[1])==0 ) &&((strcmp("red",argv[2])==0  )||  (strcmp("black",argv[2])==0  ) ||   (strcmp("green",argv[2])==0 )|| (strcmp("blue",argv[2])==0 )  || (strcmp("yellow",argv[2])==0 )||  (strcmp("magenta",argv[2])==0 )||  (strcmp("cyan",argv[2])==0 ) ))){



/*Getting the user input for the URL*/

printf("Enter the URL: ");
scanf("%[^\n]",Input);



int lenInput=strlen(Input);                 //Size of the input URL

//printf("%i\n",lenInput);


/*SELECTING PROPER INPUT RANGE*/
if (lenInput<=3){
    printf("String is too short. Not supported by available QR versions\n");          //Setting boundary conditions
}
else if(lenInput>120){
    printf("String is too long. Not supported by available QR versions\n");
}

/*If the input is within the given range*/
else{
    if(lenInput<=20){
        Hashsize=24;                    //Size for small QR Version
    }
    else{
        Hashsize=132;                       //Size for large QR Version
    }

    /*First part of the HashString >>> Assign it a array named Num1   */

    int  Num1[lenInput+1];
    Num1[0]=lenInput+50;     //First element of the array

    //printf("%i",HashArrayNum[0]);

    for(i=1;i<=lenInput;i++){                   //Assign values for the other elements in the array
        Num1[i]=(Input[i-1]);
    }
    //*****For printing the array Num1
    /*
    for (i=0;i<(lenInput+1);i++){
        printf("%i ",Num1[i]);

    }*/

//printf("\n");



    /* Error Detection Part  >>>> Assign it to a Array named Num2*/

int x=Hashsize-lenInput-1;  //Size of the Error detection  part
  int  k=1;
  int j=0;
  int Num2[x];            //New Array for the error detection part
   for (i=0;i<x;i++){
    Num2[i]=Input[j]+k;  //Incrementing the adding value by 1 in each turn
    j++;
    if (j==lenInput){       //To start the next turn
        j=0;
        k++;      //To increment the adding value
    }
   }


   //To print Num2
   /*
    for (i=0;i<x;i++){
        printf("%d ",Num2[i]);
    }
    printf("\n");
    */


    /*Reverse the Error Detection Part >>>> Assign it to a Array named RENum2*/

   int RENum2[x];   //Array to store reverse of the error detection part
   k=0;
   //Assign Values to the elements of of Array
    for(i=(x-1);i>=0;i--) {
        RENum2[k]=Num2[i];
        k++;
    }


    //For printing the Array
    /*
    for(i=0;i<x;i++){
        printf("%d ",RENum2[i]);
    }
    printf("\n");
*/


    /*Array for the Acsii Values of the input >>> Assigned by merging Array Num1 and RENum2*/

    int Ascii[Hashsize];   //Array to store the Ascii values  of the hashed string
    for(i=0;i<Hashsize;i++){
        if (i<(lenInput+1)){     //Adding elements from Num1 Array
            Ascii[i]=Num1[i];
        }
        else{
            Ascii[i]=RENum2[i-(lenInput+1)];     //Adding elements from RENEum2 Array
        }
    }

    //For printing the Array
    /*
    for(i=0;i<Hashsize;i++){
            printf("%i ",Ascii[i]);
    }
printf("\n");
*/

//Array for the Hashstring
/*
char HashString[Hashsize];


for(i=0;i<Hashsize;i++){
            HashString[i]=Ascii[i];

}
//For printing the values of the Array

for(i=0;i<Hashsize;i++){
    printf("%c ",HashString[i]);
}

*/


/*To clear the screen before printing the QR Code*/
printf("\e[2J\e[H");


/*To print the small version QR code*/
if (Hashsize==24){

int CC[24][9];  //multi dimensional array to store the binary values for  the QR code




for(int i=0;i<24;i++){
    CBin(Ascii[i],CC[i]);   //To get digits of  binary values as an array relevant  to the Ascii values of the characters
}

/*COLOR CODE for small version QR Code*/
int ColorPattern[20][20]={{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}  ,//ROW1

                                            {0,1,1,1,1,1,1,CC[16][0],CC[16][1],CC[16][2],CC[17][0],CC[17][1],CC[17][2],1,1,1,1,1,1,0} , //ROW 2
                                            {0,1,0,0,0,0,1,CC[16][3],CC[16][4],CC[16][5],CC[17][3],CC[17][4],CC[17][5],1,0,0,0,0,1,0}, //ROW3
                                            {0,1,0,1,1,0,1,CC[16][6],CC[16][7],CC[16][8],CC[17][6],CC[17][7],CC[17][8],1,0,1,1,0,1,0} , //ROW4
                                            {0,1,0,1,1,0,1,CC[18][0],CC[18][1],CC[18][2],CC[19][0],CC[19][1],CC[19][2],1,0,1,1,0,1,0} , //ROW5
                                             {0,1,0,0,0,0,1,CC[18][3],CC[18][4],CC[18][5],CC[19][3],CC[19][4],CC[19][5],1,0,0,0,0,1,0}, //ROW6
                                             {0,1,1,1,1,1,1,CC[18][6],CC[18][7],CC[18][8],CC[19][6],CC[19][7],CC[19][8],1,1,1,1,1,1,0} ,  // ROW7

                                             {0,CC[20][0],CC[20][1],CC[20][2],CC[21][0],CC[21][1],CC[21][2],CC[0][0],CC[0][1],CC[0][2],CC[1][0],CC[1][1],CC[1][2],CC[2][0],CC[2][1],CC[2][2],CC[3][0],CC[3][1],CC[3][2],0} ,//ROW8
                                            {0,CC[20][3],CC[20][4],CC[20][5],CC[21][3],CC[21][4],CC[21][5],CC[0][3],CC[0][4],CC[0][5],CC[1][3],CC[1][4],CC[1][5],CC[2][3],CC[2][4],CC[2][5],CC[3][3],CC[3][4],CC[3][5],0}, //ROW9
                                            {0,CC[20][6],CC[20][7],CC[20][8],CC[21][6],CC[21][7],CC[21][8],CC[0][6],CC[0][7],CC[0][8],CC[1][6],CC[1][7],CC[1][8],CC[2][6],CC[2][7],CC[2][8],CC[3][6],CC[3][7],CC[3][8],0},  //ROW10

                                            {0,CC[22][0],CC[22][1],CC[22][2],CC[23][0],CC[23][1],CC[23][2],CC[4][0],CC[4][1],CC[4][2],CC[5][0],CC[5][1],CC[5][2],CC[6][0],CC[6][1],CC[6][2],CC[7][0],CC[7][1],CC[7][2],0} ,//ROW11
                                            {0,CC[22][3],CC[22][4],CC[22][5],CC[23][3],CC[23][4],CC[23][5],CC[4][3],CC[4][4],CC[4][5],CC[5][3],CC[5][4],CC[5][5],CC[6][3],CC[6][4],CC[6][5],CC[7][3],CC[7][4],CC[7][5],0}, //ROW12
                                            {0,CC[22][6],CC[22][7],CC[22][8],CC[23][6],CC[23][7],CC[23][8],CC[4][6],CC[4][7],CC[4][8],CC[5][6],CC[5][7],CC[5][8],CC[6][6],CC[6][7],CC[6][8],CC[7][6],CC[7][7],CC[7][8],0},  //ROW13

                                             {0,1,1,1,1,1,1,CC[8][0],CC[8][1],CC[8][2],CC[9][0],CC[9][1],CC[9][2],CC[10][0],CC[10][1],CC[10][2],CC[11][0],CC[11][1],CC[11][2],0} , //ROW 14
                                            {0,1,0,0,0,0,1,CC[8][3],CC[8][4],CC[8][5],CC[9][3],CC[9][4],CC[9][5],CC[10][3],CC[10][4],CC[10][5],CC[11][3],CC[11][4],CC[11][5],0}, //ROW15
                                            {0,1,0,1,1,0,1,CC[8][6],CC[8][7],CC[8][8],CC[9][6],CC[9][7],CC[9][8],CC[10][6],CC[10][7],CC[10][8],CC[11][6],CC[11][7],CC[11][8],0}  ,//ROW16
                                            {0,1,0,1,1,0,1,CC[12][0],CC[12][1],CC[12][2],CC[13][0],CC[13][1],CC[13][2],CC[14][0],CC[14][1],CC[14][2],CC[15][0],CC[15][1],CC[15][2],0},  //ROW17
                                             {0,1,0,0,0,0,1,CC[12][3],CC[12][4],CC[12][5],CC[13][3],CC[13][4],CC[13][5],CC[14][3],CC[14][4],CC[14][5],CC[15][3],CC[15][4],CC[15][5],0}, //ROW18
                                             {0,1,1,1,1,1,1,CC[12][6],CC[12][7],CC[12][8],CC[13][6],CC[13][7],CC[13][8],CC[14][6],CC[14][7],CC[14][8],CC[15][6],CC[15][7],CC[15][8],0} ,  // ROW19

                                             {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}  //ROW20
};

//printf("\n");


/*Printing the QR CODE*/
for(i=0;i<20;i++){
    for(j=0;j<20;j++){
            if (ColorPattern[i][j]==1){                         //If binary value equals to 1 prints the color
                printf("%s  %s",COLOUR,RE);                 //(Use 2 spaces to print a box)
            }
            else{
                printf("%s  %s",W,RE);                      //else print it in white
            }
        }
    printf("\n");
}
printf("\n");
}

/*For Larger QR version*/

else if (Hashsize==132){
    int CD[132][9];              //multi dimensional array to store the binary values for  the QR code

    for(int i=0;i<132;i++){     //To get digits of  binary values as an array relevant  to the Ascii values of the character
    CBin(Ascii[i],CD[i]);
}

//COLOR CODE PATTERN
int ColorPattern2[38][38]={{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //ROW1
                                            {0,1,1,1,1,1,1,CD[100][0],CD[100][1],CD[100][2],CD[101][0],CD[101][1],CD[101][2],CD[102][0],CD[102][1],CD[102][2],CD[103][0],CD[103][1],CD[103][2],CD[104][0],CD[104][1],CD[104][2],CD[105][0],CD[105][1],CD[105][2],CD[106][0],CD[106][1],CD[106][2],CD[107][0],CD[107][1],CD[107][2],1,1,1,1,1,1,0},//ROW2
                                            {0,1,0,0,0,0,1,  CD[100][3],CD[100][4],CD[100][5],CD[101][3],CD[101][4],CD[101][5],CD[102][3],CD[102][4],CD[102][5],CD[103][3],CD[103][4],CD[103][5],CD[104][3],CD[104][4],CD[104][5],CD[105][3],CD[105][4],CD[105][5],CD[106][3],CD[106][4],CD[106][5],CD[107][3],CD[107][4],CD[107][5]  ,1,0,0,0,0,1,0} ,  //ROW3
                                            {0,1,0,1,1,0,1,CD[100][6],CD[100][7],CD[100][8],CD[101][6],CD[101][7],CD[101][8],CD[102][6],CD[102][7],CD[102][8],CD[103][6],CD[103][7],CD[103][8],CD[104][6],CD[104][7],CD[104][8],CD[105][6],CD[105][7],CD[105][8],CD[106][6],CD[106][7],CD[106][8],CD[107][6],CD[107][7],CD[107][8],1,0,1,1,0,1,0}, //ROW4

                                            {0,1,0,1,1,0,1, CD[108][0],CD[108][1],CD[108][2],CD[109][0],CD[109][1],CD[109][2],CD[110][0],CD[110][1],CD[110][2],CD[111][0],CD[111][1],CD[111][2],CD[112][0],CD[112][1],CD[112][2],CD[113][0],CD[113][1],CD[113][2],CD[114][0],CD[114][1],CD[114][2],CD[115][0],CD[115][1],CD[115][2] ,1,0,1,1,0,1,0}, //ROW5
                                            {0,1,0,0,0,0,1, CD[108][3],CD[108][4],CD[108][5],CD[109][3],CD[109][4],CD[109][5],CD[110][3],CD[110][4],CD[110][5],CD[111][3],CD[111][4],CD[111][5],CD[112][3],CD[112][4],CD[112][5],CD[113][3],CD[113][4],CD[113][5],CD[114][3],CD[114][4],CD[114][5],CD[115][3],CD[115][4],CD[115][5] ,1,0,0,0,0,1,0}, //ROW6
                                            {0,1,1,1,1,1,1,  CD[108][6],CD[108][7],CD[108][8],CD[109][6],CD[109][7],CD[109][8],CD[110][6],CD[110][7],CD[110][8],CD[111][6],CD[111][7],CD[111][8],CD[112][6],CD[112][7],CD[112][8],CD[113][6],CD[113][7],CD[113][8],CD[114][6],CD[114][7],CD[114][8],CD[115][6],CD[115][7],CD[115][8],1,1,1,1,1,1,0}, //ROW7

                                            {0,CD[116][0],CD[116][1],CD[116][2],CD[117][0],CD[117][1],CD[117][2],CD[0][0],CD[0][1],CD[0][2],CD[1][0],CD[1][1],CD[1][2],CD[2][0],CD[2][1],CD[2][2],CD[3][0],CD[3][1],CD[3][2],CD[4][0],CD[4][1],CD[4][2],CD[5][0],CD[5][1],CD[5][2],CD[6][0],CD[6][1],CD[6][2],CD[7][0],CD[7][1],CD[7][2],CD[8][0],CD[8][1],CD[8][2],CD[9][0],CD[9][1],CD[9][2],0},  //ROW8
                                            {0,CD[116][3],CD[116][4],CD[116][5],CD[117][3],CD[117][4],CD[117][5],CD[0][3],CD[0][4],CD[0][5],CD[1][3],CD[1][4],CD[1][5],CD[2][3],CD[2][4],CD[2][5],CD[3][3],CD[3][4],CD[3][5],CD[4][3],CD[4][4],CD[4][5],CD[5][3],CD[5][4],CD[5][5],CD[6][3],CD[6][4],CD[6][5],CD[7][3],CD[7][4],CD[7][5],CD[8][3],CD[8][4],CD[8][5],CD[9][3],CD[9][4],CD[9][5],0},  //ROW9
                                            {0,CD[116][6],CD[116][7],CD[116][8],CD[117][6],CD[117][7],CD[117][8],CD[0][6],CD[0][7],CD[0][8],CD[1][6],CD[1][7],CD[1][8],CD[2][6],CD[2][7],CD[2][8],CD[3][6],CD[3][7],CD[3][8],CD[4][6],CD[4][7],CD[4][8],CD[5][6],CD[5][7],CD[5][8],CD[6][6],CD[6][7],CD[6][8],CD[7][6],CD[7][7],CD[7][8],CD[8][6],CD[8][7],CD[8][8],CD[9][6],CD[9][7],CD[9][8],0} , //ROW10

                                            {0,CD[118][0],CD[118][1],CD[118][2],CD[119][0],CD[119][1],CD[119][2],CD[10][0],CD[10][1],CD[10][2],CD[11][0],CD[11][1],CD[11][2],CD[12][0],CD[12][1],CD[12][2],CD[13][0],CD[13][1],CD[13][2],CD[14][0],CD[14][1],CD[14][2],CD[15][0],CD[15][1],CD[15][2],CD[16][0],CD[16][1],CD[16][2],CD[17][0],CD[17][1],CD[17][2],CD[18][0],CD[18][1],CD[18][2],CD[19][0],CD[19][1],CD[19][2],0},  //ROW11
                                            {0,CD[118][3],CD[118][4],CD[118][5],CD[119][3],CD[119][4],CD[119][5],CD[10][3],CD[10][4],CD[10][5],CD[11][3],CD[11][4],CD[11][5],CD[12][3],CD[12][4],CD[12][5],CD[13][3],CD[13][4],CD[13][5],CD[14][3],CD[14][4],CD[14][5],CD[15][3],CD[15][4],CD[15][5],CD[16][3],CD[16][4],CD[16][5],CD[17][3],CD[17][4],CD[17][5],CD[18][3],CD[18][4],CD[18][5],CD[19][3],CD[19][4],CD[19][5],0} , //ROW12
                                            {0,CD[118][6],CD[118][7],CD[118][8],CD[119][6],CD[119][7],CD[119][8],CD[10][6],CD[10][7],CD[10][8],CD[11][6],CD[11][7],CD[11][8],CD[12][6],CD[12][7],CD[12][8],CD[13][6],CD[13][7],CD[13][8],CD[14][6],CD[14][7],CD[14][8],CD[15][6],CD[15][7],CD[15][8],CD[16][6],CD[16][7],CD[16][8],CD[17][6],CD[17][7],CD[17][8],CD[18][6],CD[18][7],CD[18][8],CD[19][6],CD[19][7],CD[19][8],0},  //ROW13

                                            {0,CD[120][0],CD[120][1],CD[120][2],CD[121][0],CD[121][1],CD[121][2],CD[20][0],CD[20][1],CD[20][2],CD[21][0],CD[21][1],CD[21][2],CD[22][0],CD[22][1],CD[22][2],CD[23][0],CD[23][1],CD[23][2],CD[24][0],CD[24][1],CD[24][2],CD[25][0],CD[25][1],CD[25][2],CD[26][0],CD[26][1],CD[26][2],CD[27][0],CD[27][1],CD[27][2],CD[28][0],CD[28][1],CD[28][2],CD[29][0],CD[29][1],CD[29][2],0},  //ROW14
                                            {0,CD[120][3],CD[120][4],CD[120][5],CD[121][3],CD[121][4],CD[121][5],CD[20][3],CD[20][4],CD[20][5],CD[21][3],CD[21][4],CD[21][5],CD[22][3],CD[22][4],CD[22][5],CD[23][3],CD[23][4],CD[23][5],CD[24][3],CD[24][4],CD[24][5],CD[25][3],CD[25][4],CD[25][5],CD[26][3],CD[26][4],CD[26][5],CD[27][3],CD[27][4],CD[27][5],CD[28][3],CD[28][4],CD[28][5],CD[29][3],CD[29][4],CD[29][5],0} , //ROW15
                                            {0,CD[120][6],CD[120][7],CD[120][8],CD[121][6],CD[121][7],CD[121][8],CD[20][6],CD[20][7],CD[20][8],CD[21][6],CD[21][7],CD[21][8],CD[22][6],CD[22][7],CD[22][8],CD[23][6],CD[23][7],CD[23][8],CD[24][6],CD[24][7],CD[24][8],CD[25][6],CD[25][7],CD[25][8],CD[26][6],CD[26][7],CD[26][8],CD[27][6],CD[27][7],CD[27][8],CD[28][6],CD[28][7],CD[28][8],CD[29][6],CD[29][7],CD[29][8],0},  //ROW16

                                            {0,CD[122][0],CD[122][1],CD[122][2],CD[123][0],CD[123][1],CD[123][2],CD[30][0],CD[30][1],CD[30][2],CD[31][0],CD[31][1],CD[31][2],CD[32][0],CD[32][1],CD[32][2],CD[33][0],CD[33][1],CD[33][2],CD[34][0],CD[34][1],CD[34][2],CD[35][0],CD[35][1],CD[35][2],CD[36][0],CD[36][1],CD[36][2],CD[37][0],CD[37][1],CD[37][2],CD[38][0],CD[38][1],CD[38][2],CD[39][0],CD[39][1],CD[39][2],0},  //ROW17
                                            {0,CD[122][3],CD[122][4],CD[122][5],CD[123][3],CD[123][4],CD[123][5],CD[30][3],CD[30][4],CD[30][5],CD[31][3],CD[31][4],CD[31][5],CD[32][3],CD[32][4],CD[32][5],CD[33][3],CD[33][4],CD[33][5],CD[34][3],CD[34][4],CD[34][5],CD[35][3],CD[35][4],CD[35][5],CD[36][3],CD[36][4],CD[36][5],CD[37][3],CD[37][4],CD[37][5],CD[38][3],CD[38][4],CD[38][5],CD[39][3],CD[39][4],CD[39][5],0} , //ROW18
                                            {0,CD[122][6],CD[122][7],CD[122][8],CD[123][6],CD[123][7],CD[123][8],CD[30][6],CD[30][7],CD[30][8],CD[31][6],CD[31][7],CD[31][8],CD[32][6],CD[32][7],CD[32][8],CD[33][6],CD[33][7],CD[33][8],CD[34][6],CD[34][7],CD[34][8],CD[35][6],CD[35][7],CD[35][8],CD[36][6],CD[36][7],CD[36][8],CD[37][6],CD[37][7],CD[37][8],CD[38][6],CD[38][7],CD[38][8],CD[39][6],CD[39][7],CD[39][8],0} , //ROW19

                                            {0,CD[124][0],CD[124][1],CD[124][2],CD[125][0],CD[125][1],CD[125][2],CD[40][0],CD[40][1],CD[40][2],CD[41][0],CD[41][1],CD[41][2],CD[42][0],CD[42][1],CD[42][2],CD[43][0],CD[43][1],CD[43][2],CD[44][0],CD[44][1],CD[44][2],CD[45][0],CD[45][1],CD[45][2],CD[46][0],CD[46][1],CD[46][2],CD[47][0],CD[47][1],CD[47][2],CD[48][0],CD[48][1],CD[48][2],CD[49][0],CD[49][1],CD[49][2],0} , //ROW20
                                            {0,CD[124][3],CD[124][4],CD[124][5],CD[125][3],CD[125][4],CD[125][5],CD[40][3],CD[40][4],CD[40][5],CD[41][3],CD[41][4],CD[41][5],CD[42][3],CD[42][4],CD[42][5],CD[43][3],CD[43][4],CD[43][5],CD[44][3],CD[44][4],CD[44][5],CD[45][3],CD[45][4],CD[45][5],CD[46][3],CD[46][4],CD[46][5],CD[47][3],CD[47][4],CD[47][5],CD[48][3],CD[48][4],CD[48][5],CD[49][3],CD[49][4],CD[49][5],0} , //ROW21
                                            {0,CD[124][6],CD[124][7],CD[124][8],CD[125][6],CD[125][7],CD[125][8],CD[40][6],CD[40][7],CD[40][8],CD[41][6],CD[41][7],CD[41][8],CD[42][6],CD[42][7],CD[42][8],CD[43][6],CD[43][7],CD[43][8],CD[44][6],CD[44][7],CD[44][8],CD[45][6],CD[45][7],CD[45][8],CD[46][6],CD[46][7],CD[46][8],CD[47][6],CD[47][7],CD[47][8],CD[48][6],CD[48][7],CD[48][8],CD[49][6],CD[49][7],CD[49][8],0} , //ROW22

                                            {0,CD[126][0],CD[126][1],CD[126][2],CD[127][0],CD[127][1],CD[127][2],CD[50][0],CD[50][1],CD[50][2],CD[51][0],CD[51][1],CD[51][2],CD[52][0],CD[52][1],CD[52][2],CD[53][0],CD[53][1],CD[53][2],CD[54][0],CD[54][1],CD[54][2],CD[55][0],CD[55][1],CD[55][2],CD[56][0],CD[56][1],CD[56][2],CD[57][0],CD[57][1],CD[57][2],CD[58][0],CD[58][1],CD[58][2],CD[59][0],CD[59][1],CD[59][2],0},  //ROW23
                                            {0,CD[126][3],CD[126][4],CD[126][5],CD[127][3],CD[127][4],CD[127][5],CD[50][3],CD[50][4],CD[50][5],CD[51][3],CD[51][4],CD[51][5],CD[52][3],CD[52][4],CD[52][5],CD[53][3],CD[53][4],CD[53][5],CD[54][3],CD[54][4],CD[54][5],CD[55][3],CD[55][4],CD[55][5],CD[56][3],CD[56][4],CD[56][5],CD[57][3],CD[57][4],CD[57][5],CD[58][3],CD[58][4],CD[58][5],CD[59][3],CD[59][4],CD[59][5],0} , //ROW24
                                            {0,CD[126][6],CD[126][7],CD[126][8],CD[127][6],CD[127][7],CD[127][8],CD[50][6],CD[50][7],CD[50][8],CD[51][6],CD[51][7],CD[51][8],CD[52][6],CD[52][7],CD[52][8],CD[53][6],CD[53][7],CD[53][8],CD[54][6],CD[54][7],CD[54][8],CD[55][6],CD[55][7],CD[55][8],CD[56][6],CD[56][7],CD[56][8],CD[57][6],CD[57][7],CD[57][8],CD[58][6],CD[58][7],CD[58][8],CD[59][6],CD[59][7],CD[59][8],0},  //ROW25

                                            {0,CD[128][0],CD[128][1],CD[128][2],CD[129][0],CD[129][1],CD[129][2],CD[60][0],CD[60][1],CD[60][2],CD[61][0],CD[61][1],CD[61][2],CD[62][0],CD[62][1],CD[62][2],CD[63][0],CD[63][1],CD[63][2],CD[64][0],CD[64][1],CD[64][2],CD[65][0],CD[65][1],CD[65][2],CD[66][0],CD[66][1],CD[66][2],CD[67][0],CD[67][1],CD[67][2],CD[68][0],CD[68][1],CD[68][2],CD[69][0],CD[69][1],CD[69][2],0}  ,//ROW26
                                            {0,CD[128][3],CD[128][4],CD[128][5],CD[129][3],CD[129][4],CD[129][5],CD[60][3],CD[60][4],CD[60][5],CD[61][3],CD[61][4],CD[61][5],CD[62][3],CD[62][4],CD[62][5],CD[63][3],CD[63][4],CD[63][5],CD[64][3],CD[64][4],CD[64][5],CD[65][3],CD[65][4],CD[65][5],CD[66][3],CD[66][4],CD[66][5],CD[67][3],CD[67][4],CD[67][5],CD[68][3],CD[68][4],CD[68][5],CD[69][3],CD[69][4],CD[69][5],0} , //ROW27
                                            {0,CD[128][6],CD[128][7],CD[128][8],CD[129][6],CD[129][7],CD[129][8],CD[60][6],CD[60][7],CD[60][8],CD[61][6],CD[61][7],CD[61][8],CD[62][6],CD[62][7],CD[62][8],CD[63][6],CD[63][7],CD[63][8],CD[64][6],CD[64][7],CD[64][8],CD[65][6],CD[65][7],CD[65][8],CD[66][6],CD[66][7],CD[66][8],CD[67][6],CD[67][7],CD[67][8],CD[68][6],CD[68][7],CD[68][8],CD[69][6],CD[69][7],CD[69][8],0},  //ROW28

                                            {0,CD[130][0],CD[130][1],CD[130][2],CD[131][0],CD[131][1],CD[131][2],CD[70][0],CD[70][1],CD[70][2],CD[71][0],CD[71][1],CD[71][2],CD[72][0],CD[72][1],CD[72][2],CD[73][0],CD[73][1],CD[73][2],CD[74][0],CD[74][1],CD[74][2],CD[75][0],CD[75][1],CD[75][2],CD[76][0],CD[76][1],CD[76][2],CD[77][0],CD[77][1],CD[77][2],CD[78][0],CD[78][1],CD[78][2],CD[79][0],CD[79][1],CD[79][2],0} , //ROW29
                                            {0,CD[130][3],CD[130][4],CD[130][5],CD[131][3],CD[131][4],CD[131][5],CD[70][3],CD[70][4],CD[70][5],CD[71][3],CD[71][4],CD[71][5],CD[72][3],CD[72][4],CD[72][5],CD[73][3],CD[73][4],CD[73][5],CD[74][3],CD[74][4],CD[74][5],CD[75][3],CD[75][4],CD[75][5],CD[76][3],CD[76][4],CD[76][5],CD[77][3],CD[77][4],CD[77][5],CD[78][3],CD[78][4],CD[78][5],CD[79][3],CD[79][4],CD[79][5],0},  //ROW30
                                            {0,CD[130][6],CD[130][7],CD[130][8],CD[131][6],CD[131][7],CD[131][8],CD[70][6],CD[70][7],CD[70][8],CD[71][6],CD[71][7],CD[71][8],CD[72][6],CD[72][7],CD[72][8],CD[73][6],CD[73][7],CD[73][8],CD[74][6],CD[74][7],CD[74][8],CD[75][6],CD[75][7],CD[75][8],CD[76][6],CD[76][7],CD[76][8],CD[77][6],CD[77][7],CD[77][8],CD[78][6],CD[78][7],CD[78][8],CD[79][6],CD[79][7],CD[79][8],0} , //ROW31


                                            {0,1,1,1,1,1,1,CD[80][0],CD[80][1],CD[80][2],CD[81][0],CD[81][1],CD[81][2],CD[82][0],CD[82][1],CD[82][2],CD[83][0],CD[83][1],CD[83][2],CD[84][0],CD[84][1],CD[84][2],CD[85][0],CD[85][1],CD[85][2],CD[86][0],CD[86][1],CD[86][2],CD[87][0],CD[87][1],CD[87][2],CD[88][0],CD[88][1],CD[88][2],CD[89][0],CD[89][1],CD[89][2],0} , //ROW32
                                            {0,1,0,0,0,0,1,CD[80][3],CD[80][4],CD[80][5],CD[81][3],CD[81][4],CD[81][5],CD[82][3],CD[82][4],CD[82][5],CD[83][3],CD[83][4],CD[83][5],CD[84][3],CD[84][4],CD[84][5],CD[85][3],CD[85][4],CD[85][5],CD[86][3],CD[86][4],CD[86][5],CD[87][3],CD[87][4],CD[87][5],CD[88][3],CD[88][4],CD[88][5],CD[89][3],CD[89][4],CD[89][5],0}, //ROW33
                                           {0,1,0,1,1,0,1,CD[80][6],CD[80][7],CD[80][8],CD[81][6],CD[81][7],CD[81][8],CD[82][6],CD[82][7],CD[82][8],CD[83][6],CD[83][7],CD[83][8],CD[84][6],CD[84][7],CD[84][8],CD[85][6],CD[85][7],CD[85][8],CD[86][6],CD[86][7],CD[86][8],CD[87][6],CD[87][7],CD[87][8],CD[88][6],CD[88][7],CD[88][8],CD[89][6],CD[89][7],CD[89][8],0},//ROW34
                                            {0,1,0,1,1,0,1,CD[90][0],CD[90][1],CD[90][2],CD[91][0],CD[91][1],CD[91][2],CD[92][0],CD[92][1],CD[92][2],CD[93][0],CD[93][1],CD[93][2],CD[94][0],CD[94][1],CD[94][2],CD[95][0],CD[95][1],CD[95][2],CD[96][0],CD[96][1],CD[96][2],CD[97][0],CD[97][1],CD[97][2],CD[98][0],CD[98][1],CD[98][2],CD[99][0],CD[99][1],CD[99][2],0}, //ROW35
                                            {0,1,0,0,0,0,1,CD[90][3],CD[90][4],CD[90][5],CD[91][3],CD[91][4],CD[91][5],CD[92][3],CD[92][4],CD[92][5],CD[93][3],CD[93][4],CD[93][5],CD[94][3],CD[94][4],CD[94][5],CD[95][3],CD[95][4],CD[95][5],CD[96][3],CD[96][4],CD[96][5],CD[97][3],CD[97][4],CD[97][5],CD[98][3],CD[98][4],CD[98][5],CD[99][3],CD[99][4],CD[99][5],0}, //ROW36
                                            {0,1,1,1,1,1,1,CD[90][6],CD[90][7],CD[90][8],CD[91][6],CD[91][7],CD[91][8],CD[92][6],CD[92][7],CD[92][8],CD[93][6],CD[93][7],CD[93][8],CD[94][6],CD[94][7],CD[94][8],CD[95][6],CD[95][7],CD[95][8],CD[96][6],CD[96][7],CD[96][8],CD[97][6],CD[97][7],CD[97][8],CD[98][6],CD[98][7],CD[98][8],CD[99][6],CD[99][7],CD[99][8],0}, //ROW37
                                            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} //ROW38
                                                };


//printf("\n");


/*Printing the QR Code*/

for(i=0;i<38;i++){
    for(j=0;j<38;j++){
            if (ColorPattern2[i][j]==1){
                printf("%s  %s",COLOUR,RE);     //If binary value equals to one prints the color
            }
            else{
                printf("%s  %s",W,RE);               //else print it in white
            }
        }
    printf("\n");
}
printf("\n");
}

}
}


/*Checking conditions for the incorrect usage of arguments*/

else if(argc>3 || ((strcmp("-c",argv[1])!=0 ) && (strcmp("-h",argv[1])!=0)) || (argc==2 && (strcmp("-h",argv[1])!=0)) || (argc==3 && (strcmp("-c",argv[1])!=0 ))){

    printf("Incorrect usage of arguments.\n");
    printf("usage :\n");
    printf("%s -c [black|red|green|yellow|blue|magenta|cyan]\n",argv[0]);
    printf("%s -h for the help about the program\n",argv[0]);
}

return 0;
}

/* Function to get the array of digits of the  binary value of  the given ascii value*/

int *BArray(int num){
    int Array[9];        //Array to store DIGITS of binary values without zeros at front
    int count=0;    //To count the number of digits
int i=0;

while(num!=0){

         int LSB=num%2;   //least significant values from modulus values
    num=num/2;

    Array[8-i]=LSB;    //Assign values from last position of the array
count++;
    i++;
}

/*
for(i=0;i<9;i++){
printf("%i  ",Array[i]);

}
//printf("\n%i",count);
*/

int AddZeros=9-count;            //No of zeros that should add at the beginning of the binary number
//printf("\n%i",AddZeros);

//printf("\n");

for (i=0;i<AddZeros;i++){      //Adding zeros to the array
    BIN[i]=0;
}
int j=0;
for(i=(AddZeros);i<9;i++){

    BIN[i]=Array[j+AddZeros];    //Adding digits of the binary value into the array
    j++;
}
return (BIN);
}
/*
//To print the array BIN
for(i=0;i<9;i++){
    printf("%i  ",BIN[i]);
}
printf("\n");
}
*/


/*Function to get an integer and return an array of  digits of its binary form*/
void CBin(int num, int C[9]){
BArray(num);
for(int i=0;i<9;i++){
    C[i]=BIN[i];
}
}



