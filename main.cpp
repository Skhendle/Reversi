#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdlib>
#include <sstream>
#include <ctime>
#include <vector>
using namespace std;


void RandomAlgorithm(char myBoard[][16],int rowsize, int colsize,char C,std::ofstream &OutputFile){
    /*
    Random algorithm, checks the surround areas before adding an element and places in an empty cell which is close to a none empty cell
    */
    char opp = 'B';
    if( C=='B'){
        opp = 'W';
    }
    bool conditions = true;
    for(int i =0;i< rowsize && conditions;i++){
        for(int j =0; j < rowsize && conditions; j++){
            if(myBoard[i][j] == '#' ){
                if( i-1 <0 && myBoard[i+1][j]==opp){
                    myBoard[i][j] = C;
                    conditions = false;
                    OutputFile <<"r"<<i<<"c"<<j<<" ";
                }else if( i+1 > colsize && myBoard[i-1][j]==opp ){
                    myBoard[i][j] = C;
                    conditions = false;
                    OutputFile <<"r"<<i<<"c"<<j<<" ";
                }else if( j-1 < 0 && myBoard[i][j+1]==opp ){
                    myBoard[i][j] = C;
                    conditions = false;
                    OutputFile <<"r"<<i<<"c"<<j<<" ";
                }else if(j+1 > colsize && myBoard[i][j-1]==opp){
                    myBoard[i][j] = C;
                    conditions = false;
                    OutputFile <<"r"<<i<<"c"<<j<<" ";
                }else if(myBoard[i-1][j] == opp || myBoard[i+1][j] ==opp || myBoard[i][j-1] ==opp || myBoard[i][j+1] ==opp){
                    myBoard[i][j] = C;
                    conditions = false;
                    OutputFile <<"r"<<i<<"c"<<j<<" ";
                }
            }
        }
    }
}


void  SmartAlgorithm(char myBoard[][16],int rowsize, int colsize,std::ofstream &OutputFile){
    /*
    This works row-wise by checking the element in the next/previous column
    but in the same row. If there is an element in those checked positions and our current
    position is empty, it will insert the playing value of this random algorithm. It it cannot work row wise it will choose
    a random position. Uses the help of the smart algorithm in all the inner parts are filled.
    */
    bool condition = true;
    for(int i=1;i < rowsize-1 && condition;i++){
        for(int j=1; j < rowsize-1 && condition ;j++){
            if(myBoard[i][j] == '#'){
                if( (myBoard[i-1][j] == 'W' || myBoard[i+1][j] =='W' || myBoard[i][j-1] =='W' || myBoard[i][j+1] =='W')){
                         myBoard[i][j]='B';
                        condition = false;
                        OutputFile <<"r"<<i<<"c"<<j<<" ";
                }
            }
        }
    }
    if(condition){
            RandomAlgorithm(myBoard,rowsize,colsize,'B',OutputFile);
            condition = false;
    }

}


// This functon must be removed at the end of the project
void printBoardState(char myBoard[][16],int rowsize, int colsize,std::ofstream &OutputFile){

    OutputFile << '\n'<< endl;

    for(int row=0; row<rowsize; row++){
        for(int col=0; col<colsize;col++){
            OutputFile<<myBoard[row][col];
        }
        OutputFile<<endl;
    }
  //  system("pause");
   // system("cls");


}
// This function checks who the winner is
void Winning(char myBoard[][16], int rowsize,std::ofstream &OutputFile )
{
    int a=0,b=0;
    for(int i = 0;i < rowsize;i++){
        for(int j = 0;j < rowsize;j++){
            if(myBoard[i][j]=='B' ){
                a=a+1;
            }else if(myBoard[i][j] == 'W'){
                b=b+1;
            }
        }
    }
    OutputFile << "alg1 = " <<a<<endl;
    OutputFile << "alg2 = " << b<<endl;

    if(a>b){
        OutputFile <<"win = "<<"alg1" <<'\n'<<endl;
    }else if(a<b) {
       OutputFile<<"win = "<<"alg2"<<'\n'<<endl;
    }else if(a==b){
        OutputFile<<"tie"<<'\n'<<endl;
    }


}

void flip_horizontal(char myBoard[][16],int rowsize,int i,int j,char C,char opp,std::ofstream &OutputFile){

        int righ_check = 0;
        bool righ_check_con = false;
        for( int c = j+1; c < rowsize && myBoard[i][c] != '#'; c++ ){
                if(myBoard[i][c] == opp){
                        righ_check =righ_check + 1 ;
                }

                if( righ_check>0 && myBoard[i][c] == C){
                    righ_check_con = true;
                    break;
                }

        }
        if(righ_check_con ){
                int counter = 0;
        while(counter < righ_check){
            counter=counter +1;
            myBoard[i][j+counter]=C;
            OutputFile << " "<<"r" <<i<<"c"<<j+counter;
        }
    }
}

void flip_vetical(char myBoard[][16],int rowsize,int i,int j,char C,char opp,std::ofstream &OutputFile){

        int righ_check = 0;
        bool righ_check_con = false;
        for( int c = i+1; c < rowsize && myBoard[c][j] != '#'; c++ ){
                if(myBoard[c][j] == opp){
                        righ_check =righ_check + 1 ;
                }
                if( righ_check>0 && myBoard[c][j] == C){
                    righ_check_con = true;
                    break;
                }
        }
        if(righ_check_con ){
                int counter = 0;
        while(counter < righ_check){
            counter=counter +1;
            myBoard[i+counter][j]=C;
            OutputFile<<" " <<"r" <<i+counter<<"c"<<j;
        }
    }
}

void flippBoard(char myBoard[][16],int rowsize, char C,std::ofstream &OutputFile){

    char opp;
    if( C=='W'){
            opp ='B';
    }else{
        opp ='W';
    }
    for(int i=0;i < rowsize;i++){
        for(int j=0;j < rowsize;j++){
            if(myBoard[i][j] == C){
                    //Do flips to the right and left side of our board if any flips are available
                    flip_horizontal(myBoard,rowsize,i,j,C,opp,OutputFile);
                    flip_vetical(myBoard,rowsize,i,j,C,opp,OutputFile);
                    //Do flips vertical in our board
        }
    }
}
}


//Creates default game board
void createGameBoard(char myBoard[][16],int rowsize, int colsize, std::ofstream &OutputFile){

        for (int row=0; row<rowsize; row++ )  {
            for(int col=0; col<colsize;col++){
                int n = (rowsize/2) - 1;
                myBoard[row][col]='#';
                myBoard[n][n]='W';
                myBoard [n][n+1]='B';
                myBoard[n+1][n]='B';
                myBoard[n+1][n+1]='W';
            }
      }
}




int main()
{
    ifstream infile("input.txt");
    ofstream outfile("result.txt");
    ofstream output("output.txt");


    int x,y;
    string line;
    vector<int> numbers;
       while(getline(infile,line)){
        std::stringstream   linestream(line);
        std::string   value;
        stringstream geek(value);
        while(getline(linestream,value,',')){
            stringstream geek(value);
            geek >> x;
            y=x;
            if((x%2==0)&& (y==x)&&(x>=4&&y<=16)){

                outfile<<"size = " <<y<<endl;
                char playBoard[x][16];

                createGameBoard(playBoard,x,y,outfile);
                //printBoardState(playBoard,x,y);
                 //printBoardState(playBoard,x,y);
                //Calculates the number of moves available in the game and control them using a counter
                int m = x*x-4;
                int counter =0;
                while(counter < m){

                        if(counter % 2 == 0){
                            // Our first algorithm plays black
                            SmartAlgorithm(playBoard,x,y,outfile);
                            outfile<< "alg1,";
                            flippBoard(playBoard,x, 'B',outfile);
                            outfile<<endl;
                        }else{
                            // Our second algorithm plays white
                            RandomAlgorithm(playBoard,x,y,'W',outfile);
                            outfile<< "alg2,";
                            flippBoard(playBoard,x, 'W',outfile);
                            outfile<<endl;
                        }
                        counter = counter + 1;
                        printBoardState(playBoard,x,y,output);
                }
                Winning(playBoard,x,outfile);
            }

        }
    }
    outfile.close();
    return 0;
}
