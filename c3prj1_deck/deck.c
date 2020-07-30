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
