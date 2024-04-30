/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
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

/*File:   Game.cpp
 *Author: Yasmeen Allahaleh
 */
//Prototypes for functions from CardFunction.CPP
void createDeck(list<int> *deck);
void shuffle(list<int> *deck);
void displayDeck(list<int> * play);
int disperse(list<int> *cards);
int checkEmpty(list<int> *play, list<int> *opp, list<int> *opp2, int dis, list<int> *deck);
void gameRules();
void displayCoins(map<string, int> a, string name, int coins);

//Prototypes for functions from GOFISH.CPP
void addRemoveCards(list<int> *play, list<int> *opp, list<int> *deck, int value);
void askAI(list<int> *play, list<int> *opp, list<int> *deck, set<int> *a, set<int> *b);
void aiAsks(list<int> *play, list<int> *opp, list<int> *deck, set<int> *a, set<int> *b, string name); 
void askAIThree(list<int> *play, list<int> *opp,list<int> *opp2, list<int> *deck, set<int> *a, set<int> *b, set<int> *c);
void aiAsksThree(list<int> *play, list<int> *opp, list<int> *opp2, list<int> *deck, set<int> *a, set<int> *b, set<int> *c, int d, string name);
void goFish(list<int> *play, list<int> *deck);
void checkPair(list<int> *play, set<int> *pair, int b);


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
            
        // if player has no coins
        //they cant play anymore
        if(coins == 0)
        {
            cout << "You ran out of coins! No more gaming . . . GOODBYE !" << endl;
            return 0;
        }
         
        
        cout << "------------------------------------------------" << endl;
        cout << "This Game Costs : 20 coins . . ." << endl;
        cout << "Do you want to play?" << endl; // asks if player wants to play
        cin >> answer;

        if(tolower(answer[0]) != 'y') // if no then exit program
        {
            cout << endl << "Welp bye then . . ." << endl;
            return 0;
        }

        //Display the map with player name and amount of coins
        displayCoins(mp,name,coins);
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

            case 1: // choic to play against 1 bot
            {    
                string option;

                do
                {    
                    coins = coins - 20; // subtract 20 to play game
                    displayCoins(mp,name,coins);// displays user's name and amount of coins
                    cout << endl;
                    
                    
                    cout << "Great! Game in session . . .  " << endl << endl;
                    gameRules();

                    cout << endl;
                    cout << "========== GoFish! =============" << endl;

                    list<int>* deck = new list<int>(); // creates main deck
                    list<int>* playerDeck = new list<int>(); // creates player deck
                    list<int>* AIDeck = new list<int>(); // creates Ai deck

                    set<int>* playerpairs = new set<int>(); // set to hold the matching card for player(you)
                    set<int>* Aipairs = new set<int>();// set to hold the matching cards for AI player


                    //Start Game
                    createDeck(deck); // creates the deck
                    shuffle(deck); // shuffle deck
                    
                    //Give the player Cards
                    for(int i = 0; i < 5; i++)
                    {
                        playerDeck->push_back(disperse(deck)); // deals the player 5 cards from deck
                    }

                    //Give AI Player 1 Cards
                    for(int i = 0; i < 5; i++)
                    {
                       AIDeck->push_back(disperse(deck));  // deals the AI player 5 cards from deck
                    }
                    
                    playerDeck->sort(); // sorts player deck to make it easier to track cards
                    
                    cout << endl << endl<< "Here are your cards " << name << ": ";
                    displayDeck(playerDeck); // display your deck

                    cout << endl;
                    checkPair(playerDeck, playerpairs, 0); // check if you have any matching cards
                    checkPair(AIDeck, Aipairs, 1); // check if AI has any matching cards
                    cout << endl;

                    int p = 0; //track value for empty decks

                    do
                    {
                        askAI(playerDeck, AIDeck, deck, playerpairs, Aipairs); // players turn 
                        
                        for(int i =0; i < 5; i++)
                        {
                            checkPair(playerDeck, playerpairs, 0);// check if you have any matching cards
                            checkPair(AIDeck, Aipairs, 1);// check if AI has any matching cards
                        }
                        
                        //check if you, AI, or the main decks are empty
                        p = checkEmpty(playerDeck, AIDeck, AIDeck, 1, deck); 

                        if(p == 1) // if p =1 then one of them is and game over
                        {
                            break;
                        }
                   
                        cout << "Here are your cards " << name << ": ";
                        displayDeck(playerDeck); // Displays your cards

                        
                        aiAsks(playerDeck, AIDeck, deck, playerpairs, Aipairs, name);// Ai turns
                        
                        for(int i =0; i < 5; i++)
                        {
                            checkPair(playerDeck, playerpairs, 0); // check if you have any matching cards
                            checkPair(AIDeck, Aipairs, 1); // check if Ai has any matching cards
                        }
                            
                        cout << "Here are your cards " << name << ": ";
                        displayDeck(playerDeck); // Displays your cards

                         //check if you, AI, or the main decks are empty
                        p = checkEmpty(playerDeck, AIDeck, AIDeck, 1, deck);

                    }while(p != 1); 

                    int setYou = playerpairs->size();//counts the size of your matching sets of cards
                    int setAI = Aipairs->size();//counts the size of Ai's matching sets of cards

                    if(setYou > setAI)// if your set is larger then you win
                    {
                        winsLose.push("Won");
                        wins++;
                        wltracker.pop();//Updates the winning and losing numbers in the queue
                        wltracker.pop();
                        wltracker.push(wins);
                        wltracker.push(loses);
                        cout << "You Win This Round!" << endl;
                    }
                    else if(setYou < setAI)// if your set is smaller then you lose
                    {
                        winsLose.push("Lost");
                        loses++;
                        wltracker.pop();//Updates the winning and losing numbers in the queue
                        wltracker.pop();
                        wltracker.push(wins);
                        wltracker.push(loses);
                        cout << "You Lost . . . To AI?" << endl;
                    }
                    else
                    {
                        winsLose.push("Draw"); // you don't win or lose with draw
                        cout << "Its a draw!" << endl;
                    }

                    if(coins == 0)// if no more coins can't play again
                    {
                        cout << "No more coins, so no more plays! Sorry . . ." << endl;
                        break;
                    }
                    
                    cout << "Do you want to play Again?" << endl; // ask if they want to play again
                    cin >> option;
                    
                    if(tolower(option[0]) == 'y')
                    {
                        cout << "New Round Created. . . " << endl;
                    } 

                }while(tolower(option[0]) == 'y');//if yes, the round restarts

                break;// break out of case
            }
            case 2:
            {
                string option;// to see if player wants to playe again

                do
                {    
                    coins = coins - 20;//subtracts 20 from total coins
                    displayCoins(mp,name,coins);//displays map with player name and coins
                    cout << endl;
                    
                    cout << "Great! Game in session . . .  " << endl << endl;
                    gameRules(); // displays the rules of Go Fish

                    cout << endl;
                    cout << "========== GoFish! =============" << endl;

                    list<int>* deck = new list<int>();//creates list for main deck
                    list<int>* playerDeck = new list<int>();// creates list for player deck
                    list<int>* AIDeck1 = new list<int>();//creates list for player AI 1 deck
                    list<int>* AIDeck2 = new list<int>();//creates list for player AI 2 deck

                    set<int>* playerpairs = new set<int>();//creates set for matching cards for player (you)
                    set<int>* Ai1pairs = new set<int>();//creates set for matching cards for AI 1
                    set<int>* Ai2pairs = new set<int>();//creates st for matching cards for AI 2

                    //Start Game
                    createDeck(deck);//puts cards in main deck
                    shuffle(deck);//shuffles main deck

                    for(int i = 0; i < 5; i++)
                    {
                        playerDeck->push_back(disperse(deck)); //Give player Cards
                    }

                    for(int i = 0; i < 5; i++)
                    {
                       AIDeck1->push_back(disperse(deck));  //Give AI Player 1 Cards
                    }
                    
                    for(int i = 0; i < 5; i++)
                    {
                       AIDeck2->push_back(disperse(deck));//Give AI Player 2 Cards  
                    }

                    cout << "Here are your cards " << name << ": ";
                    displayDeck(playerDeck);// Displays player Deck

                    cout << endl;
                    checkPair(playerDeck, playerpairs, 0);//checks if player has 4 matching cards
                    checkPair(AIDeck1, Ai1pairs, 1);//checks if AI 1 has 4 matching cards
                    checkPair(AIDeck1, Ai2pairs, 2);//checks if Ai 2 has 4 matching cards
                    cout << endl;

                    int p = 0;// to hold if deck is empty

                    do
                    {
                        cout << "******** Your Turn *********" << endl;
                        //allows you ask any Ai player for a card
                        askAIThree(playerDeck, AIDeck1, AIDeck2, deck, playerpairs, Ai1pairs, Ai2pairs);
                        
                        for(int i =0; i < 5; i++)
                        {
                            checkPair(playerDeck, playerpairs, 0); //checks if player has 4 matching cards
                            checkPair(AIDeck1, Ai1pairs, 1);//checks if AI 1 has 4 matching cards
                            checkPair(AIDeck2, Ai2pairs, 2);//checks if AI 2 has 4 matching cards
                        }
                        
                        p = checkEmpty(playerDeck, AIDeck1, AIDeck2, 1, deck);//checks of any decks are empty
                        
                        if(p == 1)// if any deck are empty, game over and break out of loop
                        {
                            break;
                        }
                        
                        cout << "Here are your cards " << name << ": ";
                        displayDeck(playerDeck);// displays your cards

                        cout << "-----------------------------------------------" << endl;
                        cout << "******** Player AI 1 Turn *********" << endl;
                        //Ai 1's turn to ask anyone for card values
                        aiAsksThree(playerDeck, AIDeck1, AIDeck2, deck, playerpairs, Ai1pairs, Ai2pairs, 1, name);
                        
                        //Ai 2's turn to ask anyone for card values
                        cout << "-----------------------------------------------" << endl;
                        cout << "******** Player AI 2 Turn *********" << endl;
                        aiAsksThree(playerDeck, AIDeck2, AIDeck1, deck, playerpairs, Ai2pairs, Ai1pairs, 2, name);
                        
                        p = checkEmpty(playerDeck, AIDeck1, AIDeck2, 1, deck);//checks of any decks are empty

                    }while(p != 1); // end of any decks are empty

                    int setYou = playerpairs->size();// size for matching cards for player
                    int setAI1 = Ai1pairs->size();// size for matching cards for AI 1
                    int setAI2 = Ai2pairs->size();// size for matching cards for AI 2

                    if(setYou > setAI1 && setYou > setAI2)// if your set are bigger than AI 1 and AI 2, you win
                    {
                        winsLose.push("Won");
                        wins++;
                        wltracker.pop();//updates queue for wins and losses
                        wltracker.pop();
                        wltracker.push(wins);
                        wltracker.push(loses);
                        cout << "You Win This Round!" << endl;
                    }
                    else if(setYou < setAI1 && setAI2 < setAI1)// if AI 1 set are greater than you and AI 2, you loose
                    {
                        winsLose.push("Lost");
                        loses++;
                        wltracker.pop();//updates queue for wins and losses
                        wltracker.pop();
                        wltracker.push(wins);
                        wltracker.push(loses);
                        cout << "Player AI 1 won this match!" << endl;
                        cout << "You Lost To AI . . . ?" << endl;
                    }
                    else if(setYou < setAI2 && setAI1 < setAI2)//if Ai 2 set is greater, they win
                    {
                        winsLose.push("Lost");
                        loses++;
                        wltracker.pop();//updates queue for wins and losses
                        wltracker.pop();
                        wltracker.push(wins);
                        wltracker.push(loses);
                        cout << "Player AI 2 won this match!" << endl;
                        cout << "You Lost To AI . . . ?" << endl; 
                    }
                    else if(setYou == setAI1)// tied with AI 1, then draw
                    {
                        winsLose.push("Draw");
                        cout << "You and Player AI 1 tied!" << endl;
                    }
                    else if(setYou == setAI2)// tied with AI 2 then draw
                    {
                        winsLose.push("Draw");
                        cout << "You and Player AI 2 tied!" << endl;
                    }
                    else if(setAI2 == setAI1)//AI 1 and AI 2 draw, you lose
                    {
                        cout << "Player AI 1 and Player AI 2 tied!" << endl;
                        winsLose.push("Lost");
                        loses++;
                        wltracker.pop();//updates queue for wins and losses
                        wltracker.pop();
                        wltracker.push(wins);
                        wltracker.push(loses);
                    }
                    else{//everyone draws
                        cout <<"Its a draw for everyone!" << endl;
                    }
                    
                    if(coins == 0)// if no more coins left cant play again
                    {
                        cout << "No more coins, so no more plays! Sorry . . ." << endl;
                        break;
                    }

                    cout << "Do you want to play Again?" << endl;// if they want to play this mode again
                    cin >> option;

                }while(tolower(option[0]) == 'y');// continue if yes

                break;
            }
            case 3:
            {
                //case 3 displays total wins and loses and outcome of each round in order
                cout << "============== Win/Lost History =============" << endl;
                cout << "Total Wins: " << wltracker.front() << "     Total Loses: " << wltracker.back() << endl;
                cout << endl;
                cout << "---------- Track Each Round Outcome ---------" << endl;

                while(!winsLose.empty())
                {   //display stack
                    cout << winsLose.top() << endl;
                    winsLose.pop();
                }

                cout << "---------------------------------------------" << endl << endl;
                 
                break;
            }
            default:// if input not 1, 2, or 3
                cout << "Invalid input . . ." << endl;
              
        } 
        
        if(coins == 0)// if no more coins then cant play anymore
        {
            cout << "You have exhausted your Coins . . ." << endl;
            break;
        }
        
        cout << "Would you like to go back to the menu?" << endl;// if they want to go back to menu
        cin >> menu;
        
    }while(tolower(menu[0]) == 'y'); //will go back if yes
    
    if(coins == 0)// if coins are zero it says Goodbye and exits
        {
            cout << "GOOD-BYE!" << endl;
        }
}

