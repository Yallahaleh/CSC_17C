/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CardFunction.cpp
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

//Prototypes:
void createDeck(list<int> *deck);
void shuffle(list<int> *deck);
void displayDeck(list<int>* play);
int disperse(list<int> *cards);
int checkEmpty(list<int> *play, list<int> *opp, list<int> *opp2, int dis, list<int> *deck);
void gameRules();
void displayCoins(map<string, int> a, string name, int coins);

/**
 * Putting the cards in the main deck
 * @param deck- the list of the main deck
 */
void createDeck(list<int> *deck)
{
    int cardNum[] = {1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5
            ,6,6,6,6,7,7,7,7,8,8,8,8,9,9,9,9,10,10,10,10}; // the cards being into the main deck
    
    copy(begin(cardNum), end(cardNum), back_inserter(*deck));// copy the values into deck

}

/**
 * Shuffles the main deck
 * @param deck - the list of the main deck
 */
void shuffle(list<int> *deck)
{
    int p1, p2;// hold the values of cards
    
    for(int i = 0; i < 1000; i++)// iterates to shuffle
    {
       p1 = rand() % deck->size();// picks a position to swap
       p2 = rand() % deck->size();// picks a position to swap
        
       list<int>::iterator pt1 = deck->begin();//iterates to the card
       advance(pt1, p1);
       list<int>::iterator pt2 =deck->begin();//iterates to the card
       advance(pt2, p2);

       swap(*pt1, *pt2);//swaps the two cards

       if(i>= 2){
            break;
        }
    
    }
}

/**
 * Displays the deck 
 * @param play - the list of the player's deck
 */
void displayDeck(list<int> * play)
{
    for(auto i : *play)
    {
        cout << i << " ";
    }
    cout << endl;
}

/**
 * deals a card to put in a player's deck
 * @param cards - the list of the main deck
 * @return the value of the card
 */
int disperse(list<int> *cards)
{
    int num;

    num = cards->back();//pull from the back of the deck
    cards->pop_back();//remove it from main deck
   
    return num;//return the value of card
}

/**
 * Check of any deck is empty
 * @param play - the list of the player's deck
 * @param opp - the list of the opposing AI deck
 * @param dis - indicates if message should be displayed
 * @param deck - the list of the main deck
 * @return value 1 if any deck is empty
 */
int checkEmpty(list<int> *play, list<int> *opp, list<int> *opp2, int dis, list<int> *deck)
{
    int value = 0;// zero mean no deck is empty
    
    if(play->size() == 0){// your deck has a size of zero, then its empty and game is over
        
        if(dis == 1)
        {    
            cout << endl;
            cout << "*=======================*" << endl;
            cout << "   Your deck is empty!" << endl;
            cout << ". . . Game is over  . . ." << endl;
            cout << "*=======================*" << endl << endl;
        }
            
        value = 1;// 1 is returned to indicate that its empty
        return value;
    }
    else if(opp->size() == 0){// AI 1 deck has a size of zero, then its empty and game is over
        
        if(dis == 1)
        {    
            cout << endl;
            cout << "*=======================*" << endl;
            cout << "   AI 1's deck is empty!" << endl;
            cout << ". . . Game is over  . . ." << endl;
            cout << "*=======================*" << endl << endl;
        }
            
        value = 1;// 1 is returned to indicate that its empty
        return value;
    }
    else if(opp2->size() == 0){// AI 2 deck has a size of zero, then its empty and game is over
        
        if(dis == 1)
        {
            cout << endl;
            cout << "*=======================*" << endl;
            cout << " AI 2's deck is empty!" << endl;
            cout << ". . . Game is over  . . ." << endl;
            cout << "*=======================*" << endl <<endl;
        }
            
        value = 1;// 1 is returned to indicate that its empty
        return value;
    }
    else if(deck->size() == 0){// AI 2 deck has a size of zero, then its empty and game is over
        
        if(dis == 1)
        {
            cout << endl;
            cout << "*=======================*" << endl;
            cout << " The main deck is empty!" << endl;
            cout << ". . . Game is over  . . ." << endl;
            cout << "*=======================*" << endl <<endl;
        }
            
        value = 1;// 1 is returned to indicate that its empty
        return value;
    }
   
    return value;
}

/**
 * Describes the rules for  the card game GoFish
 */
void gameRules()
{
    cout << "==================== Game Rules =====================" << endl;
    cout << "* Note: This game is played against an AI player " << endl;
    cout << "  that will simulate a real person playing" << endl;
    cout << "Objective: To win get the most pairs of the cards" << endl;
    cout << "before your, the opposing player, or the middle " << endl;
    cout << "deck runs out." << endl;
    cout << "1.) You and the AI player are dealt 5 cards" << endl;
    cout << "    from the shuffled deck." << endl;
    cout << "2.) The first player will ask if the opposing player" << endl;
    cout << "    has a certain value" << endl;
    cout << "3.) If the opposing player that value, then they must " << endl;
    cout << "    give all of their cards with the asked value" << endl;
    cout << "4.) When this happens, your get to go again and ask" << endl;
    cout << "    for another card" << endl;
    cout << "5.) If they do not have the value, they call GO FISH!" << endl;
    cout << "    and you must pull from the middle deck and then" << endl;
    cout << "    it's the opposing player's turn" << endl;
    cout << "6.) The same goes whenever it's the opposing player's " << endl;
    cout << "    turn to ask" << endl;
    cout << "7.) If you pull card from the deck or receive them from " << endl;
    cout << "    from the opposing player that match in a total of 4" << endl;
    cout << "    cards, then you put them to the side as you have a " << endl;
    cout << "    a set of those values. " << endl;
    cout << "*REMEMBER* The more sets you have the better! " << endl;   
    cout << "8.) When your cards, the opposing player's cards, or the" << endl;
    cout << "    the deck finishes, the game ends and whoever has the " << endl;
    cout << "    most sets of matching cards wins the game!" << endl;
    cout << "IMPORTANT: If you tie against an AI nobody wins. If two" << endl;
    cout << "           AIs tie, you loses." << endl;
    cout << "======================================================" << endl;
    
}   

/**
 * display the player's inserted name and amount of coins available
 * @param a - the map
 * @param name - the name that the player inputted
 * @param coins - the amount of coins the player has currently
 */
void displayCoins(map<string, int> a, string name, int coins)
{
    a[name] = coins;
    
    map<string, int>::iterator c = a.begin();// 
    
    while (c != a.end()) {
        cout << "Player Name: " << c->first
             << ", Coins: " << c->second << endl;
           ++c;
         } // display the map
}

