/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*File:   Game.cpp
 *Author: Yasmeen Allahaleh
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


class Node{
  public:  
    int num;
    Node* left;
    Node* right;
    
    Node(int j) : num(j), left(nullptr), right(nullptr){}
};

class Tree{
public:
    Node* root;
    Tree();
    ~Tree();
    
    void card(Node*& n, int num);
    void displayCard(Node* n);

};

Tree::Tree() : root(nullptr){}

void destroy(Node* n){
    if(n != nullptr)
    {
        destroy(n->left);
        destroy(n->right);
        delete n;
    }
}

Tree::~Tree(){
    destroy(root);
    root = nullptr;
}


void Tree::card(Node*& n, int num)
{
        if(n == nullptr)
        {
            n = new Node(num);
        }
        else if(num < n->num){
            card(n->left, num);
        }
        else{
            card(n->right, num);
        }
 
}

void Tree::displayCard(Node* n){
    if(n != nullptr)
    {
        displayCard(n->left);
        cout << n->num << " ";
        displayCard(n->right);
        
    }
}


//Prototypes for functions from CardFunction.CPP
void createDeck(list<int> *deck);
void shuffle(list<int> *deck);
void displayDeck(list<int> * play);
int disperse(list<int> *cards);
int checkEmpty(list<int> *play, list<int> *opp, list<int> *opp2, int dis, list<int> *deck);
void gameRules();
void displayCoins(map<string, int> a, string name, int coins);
void recSort(list<int> *play, int n);

//Prototypes for functions from GOFISH.CPP
void addRemoveCards(list<int> *play, list<int> *opp, list<int> *deck, int value);
void askAI(list<int> *play, list<int> *opp, list<int> *deck, set<int> *a, set<int> *b);
void aiAsks(list<int> *play, list<int> *opp, list<int> *deck, set<int> *a, set<int> *b, string name); 
void goFish(list<int> *play, list<int> *deck);
void checkPair(list<int> *play, set<int> *pair, int b);
int rec(int m, int n, list<int> *play, list<int> *deck);


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
        cout << "1.) Play GoFish! AI bot" << endl; // cin >> 1 for this option
        cout << "2.) See History" << endl; // cin >> 3 for this option
        cout << "========================" << endl;
        cout << "Choice: ";
        int choice;
        cin >> choice; // where player makes choice

        switch(choice)// for menu options
        {

            case 1: // choice to play against 1 bot
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
                    
                    Tree tree;
                    int cards = 1;
                    cout << "These are the cards you can receive: " << endl;
                    
                    for(int i =0; i < 10; i++)
                    {
                        tree.card(tree.root, cards);
                        cards++;
                    }
                    
                    tree.displayCard(tree.root);
                    cout << endl << endl;
                    
                    cout << "========== GoFish! =============" << endl;

                    list<int>* deck = new list<int>(); // creates main deck
                    list<int>* playerDeck = new list<int>(); // creates player deck
                    list<int>* AIDeck = new list<int>(); // creates Ai deck

                    set<int>* playerpairs = new set<int>(); // set to hold the matching card for player(you)
                    set<int>* Aipairs = new set<int>();// set to hold the matching cards for AI player


                    //Start Game
                    createDeck(deck); // creates the deck
                    shuffle(deck); // shuffle deck
                    
                    int m = 0;
                    int n = 5;
                    rec(m, n, playerDeck,deck);
                   
                    m = 0;
                    n = 5;
                    rec(m, n, AIDeck,deck);
                    
                    recSort(playerDeck, 5); // sorts player deck to make it easier to track cards
                    
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


