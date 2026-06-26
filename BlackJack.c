#include <windows.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    uint8_t value;
    const char *suit;
} Cards;

void user_prompt(char *choice){
    printf("\nPlease enter your choice (Type 'hit' or 'stand' or 'Randomize' or 'Deal' or you may type 'quit'): ");

    scanf("%s", choice);

    for (int i = 0; choice[i]; i++) {
        choice[i] = tolower(choice[i]);
    }

    printf("You chose to : %s\n\n", choice);
}

void test_show_deck(Cards *Cards_deck){
    for (int i = 0; i < 52; i++){
        printf("%d%s ", Cards_deck[i].value, Cards_deck[i].suit);
        if (i % 13 == 0 && i != 0){
            printf("\n");   
        }
    }
    printf("\n");
}

void shuffle_deck(Cards *Cards_deck){
    srand(time(NULL));
    for (int i = 0; i < 52; i++){
        int j = rand() %52;
        Cards temp_card = Cards_deck[i];
        Cards_deck[i] = Cards_deck[j];
        Cards_deck[j] = temp_card;

    }
}

void deal(Cards *Cards_deck, Cards *dealer, Cards *player){

    shuffle_deck(Cards_deck);
    int dealer_counter = 0;
    int player_counter = 0;
    for (int i = 0; i < 4; i++){
        if(i % 2 == 1){
            dealer[dealer_counter] = Cards_deck[i];
            dealer_counter++;
        } else {
            player[player_counter] = Cards_deck[i];
            player_counter++;
        }
    }
    printf("Dealer's hand:");
    for (int i = 0; i < 2; i++){
        printf("%d%s", dealer[i].value, dealer[i].suit);
    }
    printf("\nYour hand:");
    for (int i = 0; i < 2; i++){
        printf("%d%s", player[i].value, player[i].suit);
    }
    printf("\n");
    int player_score = 0;
    int dealer_score = 0;
    for (int i = 0; i < 2; i++){
        player_score += (player[i].value);
        dealer_score += (dealer[i].value);
    }
    switch (player_score){
        case 21:
            printf("Blackjack! You win!\n");
            if (dealer_score == 21){
                printf("Dealer also has a blackjack! It's a tie!\n");
            }
            break;
    }
    if(player_score > 21){
        printf("You busted! Dealer wins!\n");
    } else if(dealer_score > 21){
        printf("Dealer busted! You win!\n");
    }

}
// You were working on the function `validate_blackjack` which is intended to validate the scores of the player and dealer in a blackjack game. Below is a possible implementation of this function:
void validate_score(Cards *player, Cards *dealer){
    int player_score = 0;
    int dealer_score = 0;
    for (int i = 0; i < 2; i++){
        player_score += (player[i].value);
        dealer_score += (dealer[i].value);
    }
    // printf("Player score: %d\n", player_score);
    // printf("Dealer score: %d\n", dealer_score);
    switch (player_score){
        case 21:
            printf("Blackjack! You win!\n");
            if (dealer_score == 21){
                printf("Dealer also has a blackjack! It's a tie!\n");
            }
            break;
    }
    if(player_score > 21){
        printf("You busted! Dealer wins!\n");
    } else if(dealer_score > 21){
        printf("Dealer busted! You win!\n");
    } else if(player_score > dealer_score){
        printf("You win with a score of %d against the dealer's %d!\n", player_score, dealer_score);
    } else if(dealer_score > player_score){
        printf("Dealer wins with a score of %d against your %d!\n", dealer_score, player_score);
    } 

}

//void hit(Cards *Cards_deck, Cards *player, int *player_counter){}

int main() {
    SetConsoleOutputCP(CP_UTF8);

     Cards Cards_deck[52] = {
        {1, "♠"}, {2, "♠"}, {3, "♠"}, {4, "♠"}, {5, "♠"}, {6, "♠"}, {7, "♠"},
        {8, "♠"}, {9, "♠"}, {10, "♠"}, {11, "♠"}, {12, "♠"}, {13, "♠"},

        {1, "♥"}, {2, "♥"}, {3, "♥"}, {4, "♥"}, {5, "♥"}, {6, "♥"}, {7, "♥"},
        {8, "♥"}, {9, "♥"}, {10, "♥"}, {11, "♥"}, {12, "♥"}, {13, "♥"},

        {1, "♦"}, {2, "♦"}, {3, "♦"}, {4, "♦"}, {5, "♦"}, {6, "♦"}, {7, "♦"},
        {8, "♦"}, {9, "♦"}, {10, "♦"}, {11, "♦"}, {12, "♦"}, {13, "♦"},

        {1, "♣"}, {2, "♣"}, {3, "♣"}, {4, "♣"}, {5, "♣"}, {6, "♣"}, {7, "♣"},
        {8, "♣"}, {9, "♣"}, {10, "♣"}, {11, "♣"}, {12, "♣"}, {13, "♣"}
    };

    printf("\nThis is blackjack\nYou have 4 options hit or stand or randomize or deal and may shuffle the deck at any time\n\n");

    char choice[10];    //Set up a char array to hold the user input
    Cards dealer[52];
    Cards player[52];
    while (1){

        user_prompt(choice);

        switch (choice[0]){
            case 'h':
                break;
            case 'r':
                shuffle_deck(Cards_deck);
                printf("Deck has been shuffled!:\n");
                test_show_deck(Cards_deck);
                break;
            case 's':
                if (dealer[0].value == 0 || player[0].value == 0){
                    printf("You need to deal the cards first!\n");
                    break;
                }else {
                    validate_score(player, dealer);
                }
                break;
            case 'd': // Here we will also validate for a blackjack after dealing the cards
                deal(Cards_deck, dealer, player);

                break;
            case 'q':
                printf("See you later!\n");
                return 0;
        }

    }
}
