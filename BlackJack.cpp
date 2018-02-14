/*Daniel Novotny
# Step by step

1) Cards are valued at 1 - 10.
2) The computer gives 2 random cards to you and 1 random cards to a "dealer"
3) The player can take another card(Hit) or keep with the cards they have(Stick).

## Hit
1) If another card is selected, the computer deals that random card.The players hand is then evaluated and it the total value of their hand is OVER 21 they loose immately.
2) If not over 21, the player can take another card of stay with the cards they have

## Stick
1) The dealer than gets a second random card.
2) If the total value of the dealers hand is 16 or less, the dealer HAS Hit.
3) If the total value of the dealers hand is 17 or greater, the dealer has to stay.

## Finish
1) When both the player and the dealer have Sticked... the hand of the player is compared to the dealer.Whomever has the larger hand wins.
2) Ties go to the dealer.
3) The game asks the player if they would like to play again.

convert your blackjack program to use functions, include showing facecards and calculating their value as well*/


#include <string>
#include <iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;
int wins = 0;
int loses = 0;

//pics a card
int cardNum() {
	int num13 = rand() % 13 + 1;
	return num13;
}

//picks a suit
string suit() {
	string suit;
	int rnd4 = rand() % 4 + 1;
	switch (rnd4) {
	case 1:
		suit = "diamonds";
		break;
	case 2:
		suit = "hearts";
		break;
	case 3:
		suit = "clubs";
		break;
	case 4:
		suit = "spades";
		break;
	}
	
	return suit;
}

//changes to 10s 
int cardVal(int num13) {
	int num10;
	if (num13 > 10) {
		num10 = 10;
	}
	else { num10 = num13; }
	return num10;
}

//translates card to face
string fac(int num) {
	string face;
	if (num == 1) {
		face = "Ace";
	}
	else if (num == 11) {
		face = "Jack";
	}
	else if (num == 12) {
		face = "Queen";
	}
	else if (num == 13) {
		face = "King";
	}
	else {
		face = std::to_string(num);
	}
	return face;
}
//continue or quit
bool keepGo() {
	bool out;
	char charIn;
	cout << endl << "Please type 'y' to restart. ";
	cin >> charIn;
	if ((charIn == 'y') || (charIn == 'Y')) {
		out = true;
	}
	else {
		out = false;
	}
	return out;
}

//uses cardNum to gen 1-13. fac to find the face value, suit to rnd the suit, and cardVal to find point value of card
int deal(){
	int deal = cardNum();
	//cout << deal << endl;
	cout << fac(deal) << " of " << suit();
	int out = cardVal(deal);
	return out;	
}
//asks user to hit or stay
int askHit( int player) {
	char userIn;
	bool go = true;
	while (go) {
		cout << "Would you like to (h)it or (s)tay?" << endl;
		cin >> userIn;
		if (userIn == 'h' || userIn == 'H') {
			player += deal();
			if (player > 21) {
				cout << endl << "Your total is now " << player << endl;
				go = false;
			}
			else {
				cout << endl << "Your total is now " << player << endl;
			}
		}
		else if (userIn == 's' || userIn == 'S') {
			go = false;
		}
		else {
			cout << "Enter 'h' to hit, or 's' to stay" << endl;
		}
	}
	
	return player;
}


//game logic to see who wins
void hitStay(int player, int dealer) {
	bool go = true; 
	askHit(player);
	while (go) {
		
		if (player <=21) {
			//dealer draws
			if (dealer <= 16) {
				cout << "\nDealer draws ";
				dealer += deal();
				cout << "\nDealer has " << dealer << endl;
			}
			//dealer busts
			else if (dealer > 21) {
				cout << "Dealer busts, Player wins. ";
				wins++;
				go = false;
			}
			else {
				//tie game
				if (dealer == player) {
					cout << "Tie, the house wins. ";
					loses++;
					go = false;
				}
				//dealer wins
				else if (dealer > player) {
					cout << "The dealer wins";
					loses++;
					go = false;
				}
				//player wins
				else if (dealer < player) {
					cout << "player wins!";
					wins++;
					go = false;
				}
			}
		}
		else {
			cout << endl << "You Busted, You loose";
			loses++;
			go = false;
		}
	}
	
}

int main() {
	srand(time(NULL));
	bool keepGoing = true;
	

	//loops game 
	while (keepGoing) {
		//hold cards for player and dealer.
		int dealerTotal = 0;
		int playerTotal = 0;


		cout << "\nYou have " << wins << " wins, and " << loses << " loses.\n";
		cout << "shuffling!" << endl << "You got ";
		playerTotal += deal();
		cout << " and ";
		playerTotal += deal();
		cout << endl << "For a total of " << playerTotal << endl << endl;

		cout << "The dealer has ";
		dealerTotal += deal();
		cout << " showing" << endl;

		hitStay(playerTotal, dealerTotal);

		
		//gets input to restart or not
		keepGoing = keepGo();
	}
}

