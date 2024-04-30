/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GOFISH.cpp
 * Author: Yasmeen Allahaleh
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
void askAIThree(list<int> *play, list<int> *opp,list<int> *opp2, list<int> *deck, set<int> *a, set<int> *b, set<int> *c);
void aiAsksThree(list<int> *play, list<int> *opp, list<int> *opp2, list<int> *deck, set<int> *a, set<int> *b, set<int> *c, int d, string name);
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
        cout << "Player AI 1 found a set of " << card << " in his Deck!" << endl;
        cout << endl;
     }
     if(b == 2 && card != 0)//if AI 2's deck contained 4 matching cards
     {
        cout << endl;
        cout << "Player AI 2 found a set of " << card << " in his Deck!" << endl;
        cout << endl;
     }
 }

 
 /**
  * This is for 3 player mode
  * This function allows for AI's turn to ask either AI or you for a card
  * If your or the other AI has it, it continues to be the current AI's turn until they ask for a 
  * card your or the other AI doesn't have
  * @param play - the list for the player's (you) deck
  * @param opp - the list for player AI 1's deck
  * @param opp2 - the list for player AI 2's deck
  * @param deck - the list for the main deck
  * @param a - the set that holds the matching pairs for the player's (you) deck
  * @param b - the set that holds the matching pairs for the player AI 1s (you) deck
  * @param c - the set that holds the matching pairs for the player AI 2's (you) deck
  */
 void aiAsksThree(list<int> *play, list<int> *opp, list<int> *opp2, list<int> *deck, set<int> *a, set<int> *b, set<int> *c, int d, string name)
 {
    
    int empty = 0;// hold if any deck is empty
    bool found = true; // hold if card was found
    
    do
    {
        int randPlay =rand()%2+1;// Ai chooses random player to ask
        
        if(randPlay == 1)// if choice is 1 the Ai asks you as the player  for a card
        {    
            int card = opp->back();// card they are asking for from their deck
            
            cout << "Hey " << name << ", do you have a : " << card << endl;

            list<int>::iterator findCard = find(play->begin(), play->end(), card);// goes through your deck to find they card they want
            found = (findCard != play->end());// hold if they found card

            if(found)// if they found card in your deck
            {
                cout << "You found the card he was looking for : 'Here you go . . .'" << endl;
                addRemoveCards(opp, play, deck, card);// remove from your deck amd add to theirs

            }
            else
            {
                cout << "You do not have that card : 'Too Bad . . .GO FISH!'" << endl;
                goFish(opp, deck);// AI pulls from main deck 
            }

            cout << endl << endl;
        }
        else
        {
            int card = opp->back();// card they are asking for from their deck
            
            string aiplay = "2";// indicates which Ai is being asked
            
            if(d == 2)// indicates which Ai is being asked
            {
                aiplay = "1";
            }
            
            cout << "Hey AI " << aiplay << ", do you have a : " << card << endl;

            list<int>::iterator findCard = find(opp2->begin(), opp2->end(), card);// goes through the opposing AI's deck to find they card they want
            found = (findCard != opp2->end());// hold if they found card

            
                if(found)// if the AI who was being asked has the card the opposing AI wants
                {
                    cout << "AI " << aiplay << " found the card he was looking for : 'Here you go . . .'" << endl;
                    addRemoveCards(opp, opp2, deck, card);

                }
                else 
                {
                    cout << "You do not have that card : 'Too Bad . . .GO FISH!'" << endl;
                    goFish(opp, deck);// pulls from main deck id card not found
                }

            cout << endl << endl;

        }
        
        
            checkPair(play, a, 0);//checks if you have any 4 matching cards
            checkPair(opp, b, 1);//checks if AI 1 have any 4 matching cards
            checkPair(opp2, c, 2);//checks if AI 2 have any 4 matching cards

            empty = checkEmpty(play, opp, opp2, 0, deck); // checks if any deck is empty
        
    }while(found && empty == 0);  // runs until a card isn't found or deck is found empty
     
    cout << endl; 
     
     
 }
 
 /**
  * This is for 3 player mode
  * This function allows for your turn to ask either AI  for a card
  * if they have it, it continues to be your turn until you ask for a 
  * card they don't have
  * @param play - the list for the player's (you) deck
  * @param opp - the list for player AI 1's deck
  * @param opp2 - the list for player AI 2's deck
  * @param deck - the list for the main deck
  * @param a - the set that holds the matching pairs for the player's (you) deck
  * @param b - the set that holds the matching pairs for the player AI 1s (you) deck
  * @param c - the set that holds the matching pairs for the player AI 2's (you) deck
  */
 void askAIThree(list<int> *play, list<int> *opp,list<int> *opp2, list<int> *deck, set<int> *a, set<int> *b, set<int> *c)
{
    int empty = 0;//to hold if any decks are empty
    int value; //the value the Ai asked for
    bool found;// if the card was found in either your or the other AI's deck

    do
    {
        cout << "Here are your cards: ";
        displayDeck(play);// display your deck
        
        int aiplay = 0;// to identify which AI you asked for
        cout << "Which AI player do you want to ask for a card, AI 1(1) or AI 2 (2)?: " << endl;
        cin >> aiplay;// which Ai you want to ask
        
        if(aiplay == 1)// if you chose
        {    
            cout << "-----------------------------------------------" << endl;
            cout << "Here are your Cards: " << endl;
            displayDeck(play);// displays your deck
            cout << "Asking AI for a value . . ." << endl;

            cout << "What value do you want to ask Player AI 1? : " << endl;
            cin >> value;// what card you asked for

            cout << "AI 1 is looking through His Cards . . ." << endl;

            list<int>::iterator findCard = find(opp->begin(), opp->end(), value);// iterate through AI 1's deck to find value
            found = (findCard != opp->end());// holds if card was found

            if(found)// if found
            {
                cout << "AI 1 found the card you're looking for : 'Here you go . . .'" << endl;
                addRemoveCards(play, opp, deck, value);// adds the cards to your deck and remove it from AI 1's deck

            }
            else
            {
                cout << "AI 1 does not have the card you want : 'Too Bad . . .GO FISH!'" << endl;
                goFish(play, deck);// you pull if AI 1 doesn't have card
            }
            
        }
        else{
            
            cout << "-----------------------------------------------" << endl;
            cout << "Asking AI for a value . . ." << endl;

            cout << "What value do you want to ask Player AI 2? : " << endl;
            cin >> value;

            cout << "AI is looking through His Cards . . ." << endl;

            list<int>::iterator findCard = find(opp2->begin(), opp2->end(), value);// iterate through AI 2's deck to find value
            found = (findCard != opp2->end());// holds if card was found

            if(found)
            {
                cout << "AI 2 found the card you're looking for : 'Here you go . . .'" << endl;
                addRemoveCards(play, opp2, deck, value);// adds the cards to your deck and remove it from AI 2's deck

            }
            else
            {
                cout << "AI 2 does not have the card you want : 'Too Bad . . .GO FISH!'" << endl;
                goFish(play, deck);// you pull if AI 2 doesn't have card
            }
            
        }
            
        cout << endl;
        
        checkPair(play, a, 0);//checks if you have any 4 matching cards
        checkPair(opp, b, 1);//checks if AI 1 have any 4 matching cards
        checkPair(opp2, c, 2);//checks if AI 2 have any 4 matching cards
        
        empty = checkEmpty(play, opp, opp2, 0, deck);// checks if any decks are empty
       
    }while(found && empty == 0);// run while card is found and deck is not empty
    
}