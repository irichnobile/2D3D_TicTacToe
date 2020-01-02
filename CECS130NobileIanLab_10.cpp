//******************************************************************************
//  CECS130NobileIanLab_10.c        Author: Ian Nobile
//  
//  Program_description: this program, written in the C++ programming language, 
//  is capable of playing 2D or 3D Tic-Tac-Toe against the user. It uses OOP 
//  concepts in its design, a derived class from the Lab #9 2D Tic-Tac-Toe 
//  class and ASCII art to generate and display the 3x3x3 playing board. The 
//  program randomly decides who goes first, knows and will inform the user if 
//  an illegal move is made and keeps score, announcing when one of the players 
//  wins or if a draw is achieved.
//  
//  Lab section: 01
//  Due Date: 16 November 2018
//******************************************************************************

#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <iostream>
#include <cstdlib>

class Board2D 
{
    private:
        //there's nothing here!

    protected:
        std::vector< std::vector<bool> > vbAvailability;
        std::vector< std::vector<char> > vcSpace;

    public:
        //constructor; sets board values and marks spaces as "available":
        Board2D() {
            int iNumberer = 1;
            vbAvailability.resize(3);
            vcSpace.resize(3);
            for (int i = 0; i < 3; i++) 
            {
                vbAvailability[i].resize(3);
                vcSpace[i].resize(3);
            }
            for (int i = 0;i < 3;i++)
            {
                for (int j = 0;j < 3;j++)
                {
                    vbAvailability[i][j] = true;
                    vcSpace[i][j] = ('0' + (iNumberer++));//or static_cast<char>
                }
            }//end fors
        }//end 2D Board constructor

        //destructor:
        ~Board2D() {}

        //converts user selection to cell row index:
        int SpaceToRow(int PlayerMove)
        {
            return (PlayerMove <= 3) ? 0 
                    : (PlayerMove >= 4 && PlayerMove <= 6) ? 1 
                    : 2;
        }//end SpaceToRow

        //converts user selection to cell column index:
        int SpaceToColumn(int PlayerMove)
        {
            switch (PlayerMove) {
                case 1:
                case 4:
                case 7: return 0;
                case 2:
                case 5:
                case 8: return 1;
                case 3:
                case 6:
                case 9: return 2;
            }
        }//end SpaceToColumn

        //checks if player selected space is unavailable:
        bool IsTaken(int PlayerMove) 
        {
            int row = SpaceToRow(PlayerMove);
            int column = SpaceToColumn(PlayerMove);

            //catching bad input:
            if (PlayerMove < 1 || PlayerMove > 9)
            {
                return true;
            }
            else if (vbAvailability[row][column] == false)
            {
                return true;
            }
            else
            {
                return false;
            }
        }//end IsTaken

        //marks space with X or O and as unavailable:
        void MarkSpace(int PlayerMove, char PlayerPiece)
        {
            int row = SpaceToRow(PlayerMove);
            int column = SpaceToColumn(PlayerMove);
            vcSpace[row][column] = PlayerPiece;
            vbAvailability[row][column] = false;
        }//end MarkSpace

        //displays the game board:
        void ShowBoard()
        {
            std::cout << std::endl;
            std::cout << "\t" << vcSpace[0][0] << "\t|\t" << vcSpace[0][1] << "\t|\t" << vcSpace[0][2] << std::endl;
            std::cout << "\t" << "-\t|\t-\t|\t-" << std::endl;
            std::cout << "\t" << vcSpace[1][0] << "\t|\t" << vcSpace[1][1] << "\t|\t" << vcSpace[1][2] << std::endl;
            std::cout << "\t" << "-\t|\t-\t|\t-" << std::endl;
            std::cout << "\t" << vcSpace[2][0] << "\t|\t" << vcSpace[2][1] << "\t|\t" << vcSpace[2][2] << std::endl;
            std::cout << std::endl;
        } //end ShowBoard

        //checks for win conditions:
        char CheckWin()
        {
            //begins assuming Cat's game
            char cWinner = 'C';

            //rows:
            for (int i = 0;i < 3;i++)
            {
                if (vcSpace[i][0] == vcSpace[i][1] && 
                    vcSpace[i][1] == vcSpace[i][2])
                {
                    cWinner = vcSpace[i][1];
                }
            }

            //columns:
            for (int j = 0;j < 3;j++)
            {
                if (vcSpace[0][j] == vcSpace[1][j] && 
                    vcSpace[1][j] == vcSpace[2][j])
                {
                    cWinner = vcSpace[1][j];
                }
            }
            
            //and diagonals:
            if (vcSpace[0][0] == vcSpace[1][1] && 
                vcSpace[1][1] == vcSpace[2][2]
                || 
                vcSpace[2][0] == vcSpace[1][1] && 
                vcSpace[1][1] == vcSpace[0][2])
            {
                cWinner = vcSpace[1][1];
            }
            return cWinner;
        }//end CheckWin

        //checks if all spaces are unavailable:
        bool FullBoard() 
        {
            //begins assuming full board
            bool FullBoard = true;
            for (int i = 0;i < vbAvailability[0].size();i++)
            {
                for (int j = 0;j < vbAvailability[0].size();j++)
                {
                    if (vbAvailability[i][j] == true)
                    {
                        FullBoard = false;
                        break;
                    }//end if
                }
            }//end fors
            return FullBoard;
        }//end FullBoard

};//end class Board2D


//3D inherits from 2D
class Board3D : public Board2D
{
    private:
        //there's nothing here!

    protected:
        std::vector < std::vector< std::vector<bool> > > vbAvailability;
        std::vector < std::vector< std::vector<std::string> > > vcSpace;

    public:
        //constructor; sets board values and marks spaces as "available":
        Board3D() 
        {
            //1D:
            vbAvailability.resize(3);
            vcSpace.resize(3);
            //2D:
            for (int i = 0; i < 3; i++)
            {
                vbAvailability[i].resize(3);
                vcSpace[i].resize(3);
            }
            //3D:
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    vbAvailability[i][j].resize(3);
                    vcSpace[i][j].resize(3);
                }
            }
            //fills in created spaces:
            int iNumberer = 1;
            for (int k = 0;k < 3;k++)
            {
                for (int i = 0;i < 3;i++)
                {
                    for (int j = 0;j < 3;j++)
                    {
                        vbAvailability[i][j][k] = true;
                        vcSpace[i][j][k] = std::to_string(iNumberer++);
                    }
                }
            }//end fors
        }//end 3D Board constructor

        //destructor:
        ~Board3D() {};

        //converts user selection to cell row index:
        int SpaceToRow(int PlayerMove)
        {
            switch (PlayerMove) 
            {
                case 1:
                case 2:
                case 3:
                case 10:
                case 11:
                case 12:
                case 19:
                case 20:
                case 21: return 0;
                case 4:
                case 5:
                case 6:
                case 13:
                case 14:
                case 15:
                case 22:
                case 23:
                case 24: return 1;
                case 7:
                case 8:
                case 9:
                case 16:
                case 17:
                case 18:
                case 25:
                case 26:
                case 27: return 2;
            }
        }//end SpaceToRow

        //converts user selection to cell column index:
        int SpaceToColumn(int PlayerMove)
        {
            switch (PlayerMove) 
            {
                case 1:
                case 4:
                case 7:
                case 10:
                case 13:
                case 16:
                case 19:
                case 22:
                case 25: return 0;
                case 2:
                case 5:
                case 8:
                case 11:
                case 14:
                case 17:
                case 20:
                case 23:
                case 26: return 1;
                case 3:
                case 6:
                case 9:
                case 12:
                case 15:
                case 18:
                case 21:
                case 24:
                case 27: return 2;
            }
        }//end SpaceToColumn

        //translates user selection to cell aisle index
        int SpaceToAisle(int PlayerMove)
        {
            return (PlayerMove <= 9) ? 0 
                    : (PlayerMove >= 10 && PlayerMove <= 18) ? 1 
                    : 2;
        }//end SpaceToAisle

        //checks if player selected space is unavailable:
        bool IsTaken(int PlayerMove)
        {
            int row = SpaceToRow(PlayerMove);
            int column = SpaceToColumn(PlayerMove);
            int aisle = SpaceToAisle(PlayerMove);

            //catching bad input:
            if (PlayerMove < 1 || PlayerMove > 27)
            {
                return true;
            }
            else if (vbAvailability[row][column][aisle] == false)
            {
                return true;
            }
            else
            {
                return false;
            }
        }//end IsTaken

        //marks space with X or O and as unavailable:
        void MarkSpace(int PlayerMove, char PlayerPiece)
        {
            int row = SpaceToRow(PlayerMove);
            int column = SpaceToColumn(PlayerMove);
            int aisle = SpaceToAisle(PlayerMove);
            vcSpace[row][column][aisle] = PlayerPiece;
            vbAvailability[row][column][aisle] = false;
        }//MarkSpace

        //displays the game board:
        void ShowBoard()
        {
            std::cout << std::endl;
            std::cout << "\t" << vcSpace[0][0][2] << "\t|\t" << vcSpace[0][1][2] << "\t|\t" << vcSpace[0][2][2] << std::endl;
            std::cout << "\t" << "--\t|\t--\t|\t--" << std::endl;
            std::cout << "\t" << vcSpace[1][0][2] << "\t|\t" << vcSpace[1][1][2] << "\t|\t" << vcSpace[1][2][2] << std::endl;
            std::cout << "\t" << "--\t|\t--\t|\t--" << std::endl;
            std::cout << "\t" << vcSpace[2][0][2] << "\t|\t" << vcSpace[2][1][2] << "\t|\t" << vcSpace[2][2][2] << std::endl;
            std::cout << std::endl;
            
            std::cout << std::endl;
            std::cout << "\t\t" << vcSpace[0][0][1] << "\t|\t" << vcSpace[0][1][1] << "\t|\t" << vcSpace[0][2][1] << std::endl;
            std::cout << "\t\t" << "--\t|\t--\t|\t--" << std::endl;
            std::cout << "\t\t" << vcSpace[1][0][1] << "\t|\t" << vcSpace[1][1][1] << "\t|\t" << vcSpace[1][2][1] << std::endl;
            std::cout << "\t\t" << "--\t|\t--\t|\t--" << std::endl;
            std::cout << "\t\t" << vcSpace[2][0][1] << "\t|\t" << vcSpace[2][1][1] << "\t|\t" << vcSpace[2][2][1] << std::endl;
            std::cout << std::endl;

            std::cout << std::endl;
            std::cout << "\t\t\t" << vcSpace[0][0][0] << "\t|\t" << vcSpace[0][1][0] << "\t|\t" << vcSpace[0][2][0] << std::endl;
            std::cout << "\t\t\t" << "-\t|\t-\t|\t-" << std::endl;
            std::cout << "\t\t\t" << vcSpace[1][0][0] << "\t|\t" << vcSpace[1][1][0] << "\t|\t" << vcSpace[1][2][0] << std::endl;
            std::cout << "\t\t\t" << "-\t|\t-\t|\t-" << std::endl;
            std::cout << "\t\t\t" << vcSpace[2][0][0] << "\t|\t" << vcSpace[2][1][0] << "\t|\t" << vcSpace[2][2][0] << std::endl;
            std::cout << std::endl;
        } //end ShowBoard

        //checks for win conditions:
        char CheckWin()
        {
            //begins assuming Cat's game
            char cWinner = 'C';

            //rows:
            for (int i = 0;i < 3;i++)
            {
                for (int k = 0;k < 3;k++)
                {
                    if (vcSpace[i][0][k] == vcSpace[i][1][k] && 
                        vcSpace[i][1][k] == vcSpace[i][2][k])
                    {
                        cWinner = (char)vcSpace[i][1][k][0];
                    }
                }
            }

            //columns:
            for (int j = 0;j < 3;j++)
            {
                for (int k = 0;k < 3;k++)
                {
                    if (vcSpace[0][j][k] == vcSpace[1][j][k] && 
                        vcSpace[1][j][k] == vcSpace[2][j][k])
                    {
                        cWinner = vcSpace[1][j][k][0];
                    }
                }
            }

            //aisles:
            for (int i = 0;i < 3;i++)
            {
                for (int j = 0;j < 3;j++)
                {
                    if (vcSpace[i][j][0] == vcSpace[i][j][1] && 
                        vcSpace[i][j][1] == vcSpace[i][j][2])
                    {
                        cWinner = vcSpace[i][j][1][0];
                    }
                }
            }

            //and diagonals:
            //Front to Back
            for (int k = 0;k < 3;k++)
            {
                if (vcSpace[0][0][k] == vcSpace[1][1][k] && 
                    vcSpace[1][1][k] == vcSpace[2][2][k]
                    ||
                    vcSpace[2][0][k] == vcSpace[1][1][k] && 
                    vcSpace[1][1][k] == vcSpace[0][2][k])
                {
                    cWinner = vcSpace[1][1][k][0];
                }
            }
            //Left to Right
            for (int j = 0;j < 3;j++)
            {
                if (vcSpace[0][j][0] == vcSpace[1][j][1] && 
                    vcSpace[1][j][1] == vcSpace[2][j][2]
                    ||
                    vcSpace[2][j][0] == vcSpace[1][j][1] && 
                    vcSpace[1][j][1] == vcSpace[0][j][2])
                {
                    cWinner = vcSpace[1][j][1][0];
                }
            }
            //Top to Bottom
            for (int i = 0;i < 3;i++)
            {
                if (vcSpace[i][0][0] == vcSpace[i][1][1] && 
                    vcSpace[i][1][1] == vcSpace[i][2][2]
                    ||
                    vcSpace[i][2][0] == vcSpace[i][1][1] && 
                    vcSpace[i][1][1] == vcSpace[i][0][2])
                {
                    cWinner = vcSpace[i][1][1][0];
                }
            }
            //3D
            if (vcSpace[0][0][0] == vcSpace[1][1][1] && 
                vcSpace[1][1][1] == vcSpace[2][2][2]
                ||
                vcSpace[2][0][0] == vcSpace[1][1][1] && 
                vcSpace[1][1][1] == vcSpace[0][2][2]
                ||
                vcSpace[0][2][0] == vcSpace[1][1][1] && 
                vcSpace[1][1][1] == vcSpace[2][0][2]
                ||
                vcSpace[0][0][2] == vcSpace[1][1][1] && 
                vcSpace[1][1][1] == vcSpace[2][2][0])
            {
                cWinner = vcSpace[1][1][1][0];
            }
            return cWinner;
        }//end CheckWin

        //checks if all spaces are unavailable:
        bool FullBoard()
        {
            //begins assuming full board
            bool FullBoard = true;
            for (int i = 0;i < vbAvailability[0].size();i++)
            {
                for (int j = 0;j < vbAvailability[0].size();j++)
                {
                    for (int k = 0;k < vbAvailability[0].size();k++)
                    {
                        if (vbAvailability[i][j][k] == true)
                        {
                            FullBoard = false;
                            break;
                        }//end if
                    }
                }
            }//end fors
            return FullBoard;
        }//end FullBoard

};//end inherited class 3DBoard


//randomly chooses player one (X):
bool IsPlayerOne();

//asks player for move and marks it:
void UserPlay(Board2D*, char);
void UserPlay(Board3D*, char);

//randomly chooses space for computer and marks it:
void CPUPlay(Board2D*, char);
void CPUPlay(Board3D*, char);


int main(void) 
{
    using namespace std;
    string sPlayerName = "";
    bool bPlayerOne = false;
    char cUserPiece = 'O';
    char cCPUPiece = 'X';
    char cContinuePlay = 'Y';

    //greetings from the computer:
    cout << "Greetings, Tic-Tac-Toe contender." << endl;
    cout << "What is your name? ";
    getline(cin, sPlayerName);
    cout << endl << "Welcome, " << sPlayerName << ". ";
    cout << "Let us begin:" << endl;
    std::system("PAUSE");

    do {
        std::system("CLS");
        //Board2D game;
        Board3D game;
        bPlayerOne = IsPlayerOne();
        if (bPlayerOne == false) 
        {
            cUserPiece = 'O';
            cCPUPiece = 'X';
            std::cout << "I go first. " << endl;
            game.ShowBoard();
            std::system("PAUSE");
            while (!game.FullBoard())
            {
                CPUPlay(&game, cCPUPiece);
                if (game.CheckWin()!='C' || game.FullBoard()) { break; }
                UserPlay(&game, cUserPiece);
                if (game.CheckWin() != 'C' || game.FullBoard()) { break; }
            }//end while
        }//end if
        else if (bPlayerOne == true) 
        {
            cUserPiece = 'X';
            cCPUPiece = 'O';
            cout << "You go first." << endl;
            game.ShowBoard();
            while(!game.FullBoard())
            {
                UserPlay(&game, cUserPiece);
                if (game.CheckWin() != 'C' || game.FullBoard()) { break; }
                CPUPlay(&game, cCPUPiece);
                if (game.CheckWin() != 'C' || game.FullBoard()) { break; }
            }//end while
        }//end else

        //declaring the winner:
        std::system("CLS");
        if (bPlayerOne == false && game.CheckWin() == 'O'
            || 
            bPlayerOne == true && game.CheckWin() == 'X')
        {
            std::cout << sPlayerName << " wins!!!\n";
            game.ShowBoard();
        }
        else if (bPlayerOne == false && game.CheckWin() == 'X'
                 || 
                 bPlayerOne == true && game.CheckWin() == 'O') 
        {
            std::cout << "The Computer wins!!!\n";
            game.ShowBoard();
        }
        else
        {
            std::cout << "The Cat wins!!!\n";
            game.ShowBoard();
        }

        //allows the user to continue playing if desired:
        cout << "Do you wish to play again? (Y/N) ";
        cin >> cContinuePlay;
        std::system("CLS");
    } while (cContinuePlay == 'Y' || cContinuePlay == 'y');

    std::system("CLS");
    cout << "Good game." << endl;
    return 0;

} //End main


//randomly chooses player one (X)
bool IsPlayerOne() 
{
    std::mt19937 mersenne 
    { 
        static_cast<std::mt19937::result_type>(std::time(0)) 
    };
    std::uniform_int_distribution<> die{ 0, 1 };
    return (die(mersenne) == 1) ? true : false;
}//end IsPlayerOne


void UserPlay(Board2D* board, char UserPiece)
{
    int iUserSelection = 0;
    std::cout << "Please select a number between one and nine: ";
    std::cin >> iUserSelection;

    //to catch any bad input:
    while (board->IsTaken(iUserSelection) || iUserSelection < 1 || 
        iUserSelection > 9) 
    {
        //std::cin.clear(); //erases entry if incorrect
        std::cout << "Invalid Move! Please choose a valid, empty location: ";
        std::cin >> iUserSelection;
    } //end while

    //marks entered space for player:
    board->MarkSpace(iUserSelection, UserPiece);
    std::system("CLS");
    board->ShowBoard();

}//end PlayGame


void UserPlay(Board3D* board, char UserPiece)
{
    int iUserSelection = 0;
    std::cout << "Please select a number between one and nine: ";
    std::cin >> iUserSelection;

    //to catch any bad input:
    while (board->IsTaken(iUserSelection) || iUserSelection < 1 ||
        iUserSelection > 27)
    {
        //std::cin.clear(); //erases entry if incorrect
        std::cout << "Invalid Move! Please choose a valid, empty location: ";
        std::cin >> iUserSelection;
    } //end while

    //marks entered space for player:
    board->MarkSpace(iUserSelection, UserPiece);
    std::system("CLS");
    board->ShowBoard();

}//end PlayGame


void CPUPlay(Board2D* board, char CPUPiece) 
{
    int iCPUSelection = 0;
    std::mt19937 mersenne
    { 
        static_cast<std::mt19937::result_type>(std::time(0)) 
    };
    std::uniform_int_distribution<> die{ 1, 9 };

    //generates random selection until available space is found:
    do { iCPUSelection = die(mersenne); } while (board->IsTaken(iCPUSelection));

    //board marks space for computer:
    board->MarkSpace(iCPUSelection, CPUPiece);
    std::system("CLS");
    std::cout << "I choose " << iCPUSelection << "." << std::endl;
    board->ShowBoard();

} //end PlayGame


void CPUPlay(Board3D* board, char CPUPiece) 
{
    int iCPUSelection = 0;
    std::mt19937 mersenne
    {
        static_cast<std::mt19937::result_type>(std::time(0))
    };
    std::uniform_int_distribution<> die{ 1, 27 };

    //generates random selection until available space is found:
    do { iCPUSelection = die(mersenne); } while (board->IsTaken(iCPUSelection));

    //board marks space for computer:
    board->MarkSpace(iCPUSelection, CPUPiece);
    std::system("CLS");
    std::cout << "I choose " << iCPUSelection << "." << std::endl;
    board->ShowBoard();

} //end PlayGame

