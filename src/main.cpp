#include <iostream>
#include <cstdlib>
#include <ctime>
#include "dice.h"
#include "player.h"
#include <string>

using namespace std;

struct Bid
{
    int count;
    int value;
};

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
    Bid currentBid = {0, 0};
    bool firstRound = true;

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

        bool bluffCalled = false;
        currentPlayer = 1;

        while (!bluffCalled)
        {
            int choice;
            cout << "\n--- Player " << currentPlayer << "'s Turn ---" << endl;
            cout << "Current bid: " << (currentBid.count == 0 ? "None" : to_string(currentBid.count) + " " + to_string(currentBid.value) + "s") << endl;
            if (!firstRound)
            {
                cout << "1 - Raise bid\n2 - Call bluff\nChoice: ";
                cin >> choice;
            }
            else
                choice = 1;

            if (choice == 1)
            {
                int newCount, newValue;
                if (firstRound)
                {
                    cout << "Enter the dice value you wish to bid on (1-6): ";
                    cin >> newValue;

                    while (newValue < 1 || newValue > 6)
                    {
                        cout << "Invalid value. Enter a number between 1 and 6: ";
                        cin >> newValue;
                    }

                    cout << "Enter the number of dice you wish to bid on: ";
                    cin >> newCount;

                    while (newCount < 1 || newCount > 30)
                    {
                        cout << "Invalid count. Enter a number between 1 and 30: ";
                        cin >> newCount;
                    }

                    while (newCount <= currentBid.count)
                    {
                        cout << "You must raise the bid. Enter a higher count: ";
                        cin >> newCount;
                    }

                    currentBid.count = newCount;
                    currentBid.value = newValue;
                    firstRound = false;
                }
                else
                {
                    cout << "Enter the new count of dice you wish to bid on: ";
                    cin >> newCount;

                    while (newCount < 1 || newCount > 30)
                    {
                        cout << "Invalid count. Enter a number between 1 and 30: ";
                        cin >> newCount;
                    }

                    currentBid.count = newCount;
                }

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

        int totalDiceCount = 0;

        for (int i = 0; i < player1->getNumDice(); ++i)
            if (player1->getDice(i) == currentBid.value)
                totalDiceCount++;

        for (int i = 0; i < player2->getNumDice(); ++i)
            if (player2->getDice(i) == currentBid.value)
                totalDiceCount++;

        cout << "Total dice showing " << currentBid.value << ": " << totalDiceCount << endl;

        int bidder = (currentPlayer == 1) ? 2 : 1;

        if (totalDiceCount >= currentBid.count)
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