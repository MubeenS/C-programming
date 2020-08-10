#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
void print_hand(deck_t * hand){
  card_t **card =hand->cards;
  card_t card1;
  for(size_t i=0;i<hand->n_cards;i++){
    card1 = **(card+i);
    print_card(card1);
    printf(" ");
  }
}
int equals(card_t c1,card_t c2) {
  if(c1.value== c2.value && c1.suit== c2.suit) return 1;
  return 0;
}

int deck_contains(deck_t * d, card_t c) {
  card_t **cards = d->cards;
  for(size_t i=0;i<d->n_cards;i++) {
    int a=equals(**(cards+i),c);
    if(a==1) return 1;
  }
  return 0 ;
}

void shuffle(deck_t * d){
  card_t **cards = d->cards;
  int r;
  card_t *temp;
  size_t n=d->n_cards;
  for(size_t k=0;k<n/2;k++) {
    r=random()%(n-k)+k;
    temp= cards[k];
    cards[k] = cards[r];
    cards[r] = temp;
  }
void assert_full_deck(deck_t * d) {
  int count ;
  card_t **cards = d->cards;
  card_t c;
  for(size_t i=0;i<d->n_cards;i++){
    c= **(cards+i);
    count=0;
    for(size_t j=0;j<d->n_cards;j++) {
    if(equals(**(cards+j),c)) count++;
     }
  assert(count==1);
    }
}
  
  void add_card_to( deck_t * deck, card_t c){
  //add a particular card to a given deck (realloc)
  //deck_t has card_t **cards, size_t n_cards
  //card_t has uint value, suit_t suit
  card_t ** cards = malloc(sizeof(card_t*));
  cards[0] = malloc(sizeof(card_t));
  *cards[0] = c;

  int newLen = deck->n_cards + 1;
  deck->cards = realloc(deck->cards, newLen*sizeof(card_t *));
  deck->cards[newLen-1] = cards[0];
  //printf("added %d: value: %d, suit: %d\n", newLen-1, deck->cards[deck->n_cards]->value, deck->cards[deck->n_cards]->suit);
  deck->n_cards++;
}

card_t * add_empty_card(deck_t * deck){
  //adds an empty card (value 0, suit 0) to a deck and returns a pointer to it
  static card_t empty;
  empty.value = 0;
  empty.suit = NUM_SUITS;
  add_card_to(deck, empty);
  card_t * ans = deck->cards[deck->n_cards-1];
  return ans;
}


void printDeck(deck_t * deck){
  printf("\n");
  for ( int i = 0; i < deck->n_cards; i++){
    print_card(*(deck->cards[i]));
    printf(" ");
  }
  printf("\n");
}

deck_t * make_deck_exclude(deck_t * excluded_cards){
  //creates a full deck minus the cards in excluded_cards
  //use card_from_num and deck_contains
  //0-12 hearts, 13-25 diamonds, 26-38 clubs, 39-51 spades
  //  0. allocate the card_t deck and each card object in it
  //  1. allocate the deck struct
  //  2. allocate the cards array in the deck
  //  3. allocate each card in the array
  int len = 52 - excluded_cards->n_cards;
  
  card_t ** cards = malloc(len*sizeof(card_t*));
  
  deck_t * ans = malloc(sizeof(deck_t));
  ans->cards = malloc(len*sizeof(card_t*));
  
  int k = 0;
  for ( int i = 0; i < 13; i++ ){
    for ( int j = 0; j < 4; j++ ){
      if ( deck_contains(excluded_cards, card_from_num(i+13*j)) == 0){ 
	cards[k] = malloc(sizeof(card_t));
	*cards[k] = card_from_num(i+13*j);
	ans->cards[k] = cards[k];
	k++;
      }
    }
  }

  ans->n_cards = len;
  return ans;
}

deck_t * build_remaining_deck( deck_t ** hands, size_t n_hands){
  //build the deck that remains once the hands have been dealt
  //find total number of cards in all hands
  //  0. allocate the card_t deck and each card object in it (done before hands??)
  //     hands is an array of pointers to deck that point to arrays of card_t pointers
  //  1. allocate the deck struct
  //  2. allocate the cards array in the deck
  //  3. allocate each card in the array

  //ans is a one element array where the one element is a struct holidng all of the cards
  //  from the hands array of pointers to deck_t structs
  
  deck_t * all = malloc(sizeof(deck_t));
  int len = 0;

  for (int i = 0; i < n_hands; i++){
    len+= hands[i]->n_cards;
  }

  card_t ** cards = malloc(len*sizeof(card_t*));

  all->cards = malloc(len*sizeof(card_t*));
  all->n_cards = len;

  int k = 0;
  for (int i = 0; i < n_hands; i++){
    for (int j = 0; j < hands[i]->n_cards; j++){
      cards[k] = malloc(sizeof(card_t));
      *cards[k] = *(hands[i]->cards[j]);
      all->cards[k] = cards[k];
      k++;
    }
  }

  printDeck(all);

  deck_t * ans = make_deck_exclude(all);
  free_deck(all);
  /*
  for ( int i = 0; i < len; i++){
    free(cards[i]);
  }
  free(cards);
  */
  return ans;
}

void free_deck(deck_t * deck){
  //free(*(deck->cards));
  for ( int i = 0; i < deck->n_cards; i++){
    free((deck->cards[i]));
    //deck->cards[i] = NULL;
  }
  free(deck->cards);
  //deck->cards = NULL;
  free(deck);
  //deck = NULL;
}
}

