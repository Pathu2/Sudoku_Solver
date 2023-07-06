#include<bits/stdc++.h>
using namespace std;

/*What optimisation we did in this code?
It is that initially we were checking that the particular cell value which we are
taking is present in row, in col and in the grid, but now, with the help of the bit masking
we know that this this elements are present in each row, each col and each grid
and we are bit masking it, and each time when we are taking a number, we dont need to 
take the O(n) time complexity to find whether can we take it or not we can simply
use one if statement and can check.*/

const int Boardsize = 9;
const int Cellsize = 3;
int ans = 0;
int board[Boardsize][Boardsize];

int takenrow[Boardsize];
int takencol[Boardsize];
int takengrid[Cellsize][Cellsize];
/*We are storing the data of each row in each col..as 01011...as this row is 
prefilled with 3, 1 and 0....in each index in the takenrow array, we can store data
for each row*/
/*Same in case of column*/
/*In case of the takengrid, all the information about grid is stored in the first cell*/

int makemove(int ch, int row, int col)
{
    board[row][col]=ch;
    takenrow[row]^=(1<<ch);
    takencol[col]^=(1<<ch);
    takengrid[row/Cellsize][col/Cellsize]^=(1<<ch);
    /*In the making move we are storing 1 according to ch value
    */
}

int revertmove(int ch, int row, int col)
{
    board[row][col]=0;
    takenrow[row]^=(1<<ch);
    takencol[col]^=(1<<ch);
    takengrid[row/Cellsize][col/Cellsize]^=(1<<ch);
    /*In this we are making it again zero, as we are reverting*/
}

int getchoices(int row, int col)
{
    int taken = (takenrow[row]|takencol[col]|takengrid[row/Cellsize][col/Cellsize]);
    /*The values which are present, their bits are set to one*/
    int nottaken = ((1<<(Boardsize+1))-1)^taken;
    /*The values which are not present, their bits are set to one*/
    if (nottaken&1)
    {
        nottaken = nottaken^1;
    }
    /*the bit for zero..last one is flipped to one...as zero doesnt matter much*/
    return nottaken;  
}

void rec(int row, int col)
{
    if (col==Boardsize)
    {
        rec(row+1, 0);
        return;
    }
    
    if (row==Boardsize)
    {
        ans++;
        for (int i = 0; i < Boardsize; i++)
        {
            for (int j = 0; j < Boardsize; j++)
            {
                cout<<board[i][j]<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
        return;
    }
    if (board[row][col]==0)
    {
        int chmask = getchoices(row, col);
        for (int i = 1; i <=Boardsize; i++)
        {
            if (chmask&(1<<i))
            {
                makemove(i, row, col);
                rec(row, col+1);
                revertmove(i, row, col);
            }
            
        }
        
    }
    else
    {
        rec(row, col+1);
    }
}

void solve(){
    for (int i = 0; i < Boardsize; i++)
    {
        for (int j = 0; j < Boardsize; j++)
        {
            int ch;
            cin>>ch;
            makemove(ch, i, j);
        }
    }
    cout<<endl<<"Solution is: "<<endl;
    rec(0,0);
    /*Our level is cell, so we will pass the column number and row number to the fucntion*/
    cout<<ans<<endl;
    /*Number of solutions*/
}
signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    solve();
    return 0;
}