#include <iostream>
#include <cstdlib>
#include <ctime>
#include "dice.h"
#include "player.h"
#include <string>

using namespace std;

int main()
{
    srand(static_cast<unsigned int>(time(0)));

    Player *player1 = new Player();
    Player *player2 = new Player();

    cout << "Welcome to Liar's Dice!" << endl;
    cout << "Hotseat mode: 2 players share the keyboard." << endl;
    cout << "Each player starts with 5 dice." << endl;
    cout << "Take turns bidding or calling bluffs." << endl;
    cout << "Lose a die when you're wrong. Last player with dice wins!" << endl;
    cout << "Press Enter to continue..." << endl;
    cin.ignore();

    bool gameOver = false;
    int currentPlayer = 1;
    int bid = 0;

    while (!gameOver)
    {
        cout << "\n=========================" << endl;
        cout << "New Round Begins" << endl;

        cout << "Player 1, press Enter to roll your dice...";
        cin.ignore();
        player1->rollDice(player1->getNumDice());

        cout << "Player 1, your dice: ";
        for (int i = 0; i < player1->getNumDice(); ++i)
            cout << player1->getDice(i) << " ";
        cout << endl;

        cout << "Pass to Player 2 and press Enter...";
        cin.ignore();

        cout << "Player 2, press Enter to roll your dice...";
        cin.ignore();
        player2->rollDice(player2->getNumDice());

        cout << "Player 2, your dice: ";
        for (int i = 0; i < player2->getNumDice(); ++i)
            cout << player2->getDice(i) << " ";
        cout << endl;

        bid = 0;
        bool bluffCalled = false;
        currentPlayer = 1;

        while (!bluffCalled)
        {
            cout << "\n--- Player " << currentPlayer << "'s Turn ---" << endl;
            cout << "Current bid: " << (bid == 0 ? "None" : to_string(bid)) << endl;
            cout << "1 - Raise bid\n2 - Call bluff\nChoice: ";
            int choice;
            cin >> choice;

            if (choice == 1)
            {
                int newBid;
                cout << "Enter new bid (must be higher than " << bid << "): ";
                cin >> newBid;

                if (newBid <= bid)
                {
                    cout << "Invalid bid. Must be higher than current." << endl;
                    continue;
                }

                bid = newBid;
                currentPlayer = (currentPlayer == 1) ? 2 : 1;
            }
            else if (choice == 2)
            {
                bluffCalled = true;
            }
            else
            {
                cout << "Invalid choice." << endl;
            }
        }

        cout << "\nBluff called! Revealing dice..." << endl;

        int total = 0;
        for (int i = 0; i < player1->getNumDice(); ++i)
            total += player1->getDice(i);
        for (int i = 0; i < player2->getNumDice(); ++i)
            total += player2->getDice(i);

        cout << "Total of all dice: " << total << endl;

        int bidder = (currentPlayer == 1) ? 2 : 1;

        if (total >= bid)
        {
            cout << "The bid was correct! Player " << currentPlayer << " loses a die." << endl;
            if (currentPlayer == 1)
                player1->loseDie();
            else
                player2->loseDie();
        }
        else
        {
            cout << "The bid was wrong! Player " << bidder << " loses a die." << endl;
            if (bidder == 1)
                player1->loseDie();
            else
                player2->loseDie();
        }

        if (player1->getNumDice() == 0 || player2->getNumDice() == 0)
        {
            gameOver = true;
            cout << "\nGame Over!" << endl;
            if (player1->getNumDice() == 0 && player2->getNumDice() == 0)
                cout << "It's a tie!" << endl;
            else if (player1->getNumDice() == 0)
                cout << "Player 2 wins!" << endl;
            else
                cout << "Player 1 wins!" << endl;
        }
        else
        {
            cout << "\nPlayer 1 has " << player1->getNumDice() << " dice remaining." << endl;
            cout << "Player 2 has " << player2->getNumDice() << " dice remaining." << endl;
            cout << "Press Enter for next round..." << endl;
            cin.ignore();
            cin.get();
        }
    }

    return 0;
}