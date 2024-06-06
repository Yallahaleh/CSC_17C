/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GOFISH.cpp
 * Author: Yasmeen Allahaleh
 *
 * 
 */

using namespace std;

/*
 * 
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

//Prototypes:
//Card Function
void createDeck(list<int> *deck);
void shuffle(list<int> *deck);
void displayDeck(list<int>* play);
int disperse(list<int> *cards);
int checkEmpty(list<int> *play, list<int> *opp, list<int> *opp2, int dis, list<int> *deck);
void gameRules();
//Go Fish
void addRemoveCards(list<int> *play, list<int> *opp, list<int> *deck, int value);
void askAI(list<int> *play, list<int> *opp, list<int> *deck, set<int> *a, set<int> *b);
void aiAsks(list<int> *play, list<int> *opp, list<int> *deck, set<int> *a, set<int> *b, string name);
void goFish(list<int> *play, list<int> *deck);
void checkPair(list<int> *play, set<int> *pair, int b);

/**
 * (For 2 player mode): allow you ask the Ai for value
 * if they have the cards they ask, it continues to be your turn until
 * they don't have a card you want
 * @param play- list for players current deck
 * @param opp- list for AI deck
 * @param deck - list main in deck
 * @param a - set for player (you) that hold matching cards
 * @param b - set for player AI that holds matching cards
 */
void askAI(list<int> *play, list<int> *opp, list<int> *deck, set<int> *a, set<int> *b)
{
    int empty = 0; // see if deck empty
    int value; // card you want
    bool found; // to see if card found in opposing player's deck

    do
    {
        cout << "     ******** Your Turn *********" << endl;
        cout << "-----------------------------------------------" << endl;
        cout << "Here are your Cards: " << endl;
        displayDeck(play);// displays your deck
        cout << "Asking AI for a value . . ." << endl;
        cout << "What value do you want to ask Player AI? : " << endl;
        cin >> value; // ask Ai for a value of the card

        cout << "AI is looking through His Cards . . ." << endl;

        list<int>::iterator findCard = find(opp->begin(), opp->end(), value); // iterator to find card
        found = (findCard != opp->end()); //returns if found card

        if(found)// if found
        {
            cout << "AI found the card you're looking for : 'Here you go . . .'" << endl;
            addRemoveCards(play, opp, deck, value); //allows the cards to be remove from opposing player and into your deck

        }
        else
        {
            cout << "AI does not have the card you want : 'Too Bad . . .GO FISH!'" << endl;
            goFish(play, deck);// You have to draw from Deck
        }

        cout << endl;
        
        checkPair(play, a, 0);// check if you have 4 matching cards
        checkPair(opp, b, 1);// check if AI have 4 matching cards
        
        empty = checkEmpty(play, opp, opp, 0, deck);// check if decks are empty
       
    }while(found && empty == 0);// continue to be your turn until deck empty or card value not found
    
}
  
/**
 * Add cards found in opposing player's deck into yours and remove it from theirs
 * @param play- list of player's deck who asked for value
 * @param opp - list of player who was asked deck
 * @param deck - list main deck
 * @param value - value that player asked for
 */
 void addRemoveCards(list<int> *play, list<int> *opp, list<int> *deck, int value)  
 {
    
    int countCard = count(opp->begin(), opp->end(), value);// counts how many cards they have of asked value
     
    cout << "He had : " << countCard << " card(s) with the value of: " 
            << value << endl; // displays ho many cards he had of that value
     
    for(int i=0; i < 52; i++)
    {
        opp->remove(value);// remove it from opposing deck
    }
    
    for(int i=0; i < countCard; i++)
    {
        play->push_back(value);// adds them to player who asked deck's
    }
    
 }
 
 /**
  * for 2 Player Mode
  * Allows the Ai to ask your for the card they want
  * If you have the value they want its their turn again until they ask for value
  * you don't have or deck is empty
  * @param play - list of the player (your)'s current deck of cards
 * @param play- list for players current deck
 * @param opp- list for AI deck
 * @param deck - list main in deck
 * @param a - set for player (you) that hold matching cards
 * @param b - set for player AI that holds matching cards
  * @param name - the name of the player
  */
 void aiAsks(list<int> *play, list<int> *opp, list<int> *deck, set<int> *a, set<int> *b, string name)
 {
    
    int empty = 0;// hold if any deck is empty
    bool found = true; // if balue of card was found
     
    do
    {
        cout << "     ******** AI's Turn *********" << endl;
        cout << "-----------------------------------------------" << endl;
        int card = opp->back();// asks for the card in the back of their deck

        cout << "Hey " << name << ", do you have a : " << card << endl; // asks if you have the certain card

        list<int>::iterator findCard = find(play->begin(), play->end(), card);// iterates through your deck
        found = (findCard != play->end()); // holds if card was found

        if(found)// if the card was found in your deck
        {
            cout << "You found the card he was looking for : 'Here you go . . .'" << endl;
            addRemoveCards(opp, play, deck, card);// adds the cards to the AI's deck and removes them from yours

        }
        else
        {
            cout << "You do not have that card : 'Too Bad . . .GO FISH!'" << endl;
            goFish(opp, deck);// if card not found in your deck, Ai pulls from main deck
        }
        
        cout << endl << endl;
        
        checkPair(play, a, 0);//check if you have any 4 matching cards
        checkPair(opp, b, 1);// checks if Ai has any 4 matching cards
        
        empty = checkEmpty(play, opp, opp, 0, deck);// checks if any decks are empty
        
    }while(found && empty == 0);  // counties if they asks you for card you have and decks aren't empty
        
    
    cout << endl; 
     
     
 }
 
 /**
  * Allows the player to pull from main deck
  * @param play - the player's list of their deck who pulls from deck
  * @param deck - the main deck that the card gets pulled from
  */
 void goFish(list<int> *play, list<int> *deck)
 {
     cout << "Pulling card from deck. . ." << endl;
     int pull = disperse(deck);//card pulled from deck
     
     play->push_back(pull);// puts it into the players deck
 }
 
 /**
  * Checks if player has 4 matching cards in their deck
  * @param play - the list of player deck that's being checked
  * @param pair - the set that hold matching cards
  * @param b - number that indicates which player is being checked
  */
 void checkPair(list<int> *play, set<int> *pair, int b)
 {
     
     int countCard = 0;//counts the number cards for a certain value
     int card = 0;
     
     for(auto i : *play)// goes through list to find number of cards
     {
        countCard = count(play->begin(), play->end(), i);//goes through and counts how many cards their are for each card
        if(countCard == 4)
        {
            card = i;// assign the cards value found with 4 matching cards
 
        }
     }

     if (card != 0)// if no card found
     {
        pair->insert(card);// insert the value of card into set
        play->remove(card); //removes from current player's deck
     }   
     
     if(b == 0 && card != 0)//if your deck contained 4 matching cards
     {
        cout << endl;
        cout << "You found a set of " << card << " in your Deck!" << endl;
        cout << endl;
     }
     if(b == 1 && card != 0)//if AI 1's deck contained 4 matching cards
     {
        cout << endl;
        cout << "Player AI found a set of " << card << " in his Deck!" << endl;
        cout << endl;
     }
 }

 
 void recSort(list<int> *play){
     
 }
 
 