/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Game.cpp
 * Author: Yasmeen Allahaleh
 */

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <map>
#include <list>
#include <set>
#include <stack>
#include <queue>
#include <algorithm>
#include <iterator>


using namespace std;


int main(int argc, char** argv) {
    
    //set random seed time
    srand(static_cast<unsigned int>(time(0)));
    
    //starting amount of coins for player
    int coins = 100;
    //for player to answer if they want to play
    string answer;
    
    // asks the player their name
    string name;
    cout << "Please enter your name player: ";
    cin >> name;
    
    //Queue that's stores number of wins in front, and losses in back
    queue<int> wltracker;
    //stack stores the outcome of each round, such as "Won" or "lost"
    stack<string> winsLose;
    
    //Tracks user's wins and losses
    int loses = 0;
    int wins = 0;
    
    //pushes values into queue
    wltracker.push(wins);
    wltracker.push(loses);

    //for player to answer if they want to 
    //go back to menu
    string menu;
    
    //Map stores player name and amount of coins
    map<string, int> mp;
    mp[name] = coins;
    
    //Start of program output
    do
    {
        cout << "Hi " << name << ", you need coins to play this game of Go Fish!" << endl;
        
        
        cout << "------------------------------------------------" << endl;
        cout << "This Game Costs : 20 coins . . ." << endl;
        cout << "Do you want to play?" << endl; // asks if player wants to play
        cin >> answer;

        if(tolower(answer[0]) != 'y') // if no then exit program
        {
            cout << endl << "Welp bye then . . ." << endl;
            return 0;
        }

        cout << endl << endl;
        
        cout << "======== Menu ========== " << endl;
        cout << "Please choose an option:" << endl;
        cout << "1.) Play GoFish! against 1 AI bot" << endl; // cin >> 1 for this option
        cout << "2.) Play GoFish! against 2 AI bots" << endl; // cin >> 2 for this option
        cout << "3.) See History" << endl; // cin >> 3 for this option
        cout << "========================" << endl;
        cout << "Choice: ";
        int choice;
        cin >> choice; // where player makes choice

        switch(choice)// for menu options
        {

            case 1: // choice to play against 1 bot
            {   
                break;// break out of case
            }
            case 2:
            {
                break;
            }
            case 3:
            {
                break;
            }
            default:// if input not 1, 2, or 3
                cout << "Invalid input . . ." << endl;
              
        } 
        
       
        
        cout << "Would you like to go back to the menu?" << endl;// if they want to go back to menu
        cin >> menu;
        
    }while(tolower(menu[0]) == 'y'); //will go back if yes

        cout << "GOOD-BYE!" << endl;

}
