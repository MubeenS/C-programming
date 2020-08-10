#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "cards.h"
#include "deck.h"
#include "eval.h"
#include "future.h"
#include "input.h"

<<<<<<< HEAD
void free_hands(deck_t **hands, size_t n_hands){
  if(hands!=NULL){
    for(size_t i=0;i<n_hands;i++){
      free_deck(hands[i]);
    }
  }
  free(hands);
}

void free_future_cards(future_cards_t *fc){
  for(size_t i=0;i<fc->n_decks;i++){
    free(fc->decks[i].cards);
  }
  free(fc->decks);
  /*free(fc)*/;
}

size_t *create_wins_or_ties(size_t n){
  size_t *ans=malloc((n+1)*sizeof(*ans));
  if(ans!=NULL){
    for(size_t i=0;i<n+1;i++){
      ans[i]=0;
    }
  }
  return ans;
}

void Monte_Carlo_trials(size_t n_trials, deck_t **hands, size_t n_hands, future_cards_t *fc, deck_t *r_deck, size_t *wins_or_ties){
  for(size_t i=0;i<n_trials;i++){
    shuffle(r_deck);
    future_cards_from_deck(r_deck,fc);
    size_t *wt=create_wins_or_ties(n_hands);
    for(size_t j=0;j<n_hands-1;j++){
      for(size_t k=j+1;k<n_hands;k++){
	int compare=compare_hands(hands[j],hands[k]);
	if(compare>0){
	  wt[j]++;
	}
	else if(compare<0){
	  wt[k]++;
	}
	else{
	  wt[n_hands]++;
	}
      }
    }
    size_t index=0;
    for(size_t l=0; l<n_hands+1; l++){
      if(wt[index]<wt[l]){
	index=l;
      }
    }
    wins_or_ties[index]++;
    free(wt);
  }
}

void print_trials(size_t *w_or_t, size_t n_hands, size_t n_trials){
  for(size_t i=0;i<n_hands;i++){
    unsigned int wins=w_or_t[i];
    unsigned int trials=n_trials;
    double per=(w_or_t[i]/(double)trials)*100;
    printf("Hand %zu won %u / %u times (%.2f%%)\n", i, wins, trials, per);
  }
  unsigned int ties=w_or_t[n_hands];
  printf("And there were %u ties\n", ties);
}

int main(int argc, char ** argv) {
  //YOUR CODE GOES HERE
  if(argc>3 || argc<2){
    fprintf(stderr,"%s : Invalid number of arguments!\n",argv[0]);
    return EXIT_FAILURE;
  }
  FILE *f=fopen(argv[1],"r");
  if(f==NULL){
    fprintf(stderr,"%s : Invalid input file %s!\n",argv[0],argv[1]);
    return EXIT_FAILURE;
  }
  size_t n_trials=10000;
  if(argc==3){
    if(atol(argv[2])>0){
      n_trials=atol(argv[2]);
    }
    else{
      fprintf(stderr,"%s : Invalid number of Monte Carlo trials %s!\n",argv[0],argv[2]);
      return EXIT_FAILURE;
    }
  }
  size_t n_hands=0;
  future_cards_t fc={NULL,0};
  deck_t **hands=read_input(f,&n_hands,&fc);
  deck_t *rem_deck=build_remaining_deck(hands,n_hands);
  size_t *wins_or_ties=create_wins_or_ties(n_hands);
  if(wins_or_ties==NULL){
    fprintf(stderr,"%s : Invalid memory allocation @create_wins_or_ties!\n",argv[0]);
    return EXIT_FAILURE;
  }
  
  Monte_Carlo_trials(n_trials,hands,n_hands,&fc,rem_deck,wins_or_ties);
  
  print_trials(wins_or_ties,n_hands,n_trials);
  
  free_hands(hands,n_hands);
  free_future_cards(&fc);
  free_deck(rem_deck);
  free(wins_or_ties);

  if(fclose(f)!=0){
    fprintf(stderr,"%s : Can not close %s!\n",argv[0],argv[1]);
    return EXIT_FAILURE;
  }
  
=======
int win_hand(deck_t ** deck_array,int n_hands){
  int w[n_hands+1];
  for(int u=0;u<n_hands+1;u++) w[u]=0;  
  int v=0;
  for(int i =0;i<n_hands-1;i++){
    for (int j=i+1;j<n_hands;j++){
      // print_hand(deck_array[i]);
      //            print_hand(deck_array[j]);
      // printf("\n");
      v=compare_hands(deck_array[i],deck_array[j]);
      if(v>0) w[i]++;
      else if (v<0) w[j]++;
      else w[n_hands]++;  
    }
  }
  unsigned largest= 0;
  for(int x=0;x<n_hands+1;x++){
    if(w[x] > w[largest])largest=x;
  }
   int count=0;  
    if(w[n_hands]>0){ 
      for(int x=0;x<n_hands+1;x++){
      	if(w[x] == w[largest]) count++;
	 }
     }
    if(count>1) return n_hands;
  return  largest;  
}

int main(int argc, char ** argv) {
  //check arguments
  if (argc < 2 ){
    fprintf(stderr, "not enough number of arguments\n");
    return EXIT_FAILURE ;
  }
  //Open the input file and read the hands in it
  FILE* f=fopen(argv[1],"r");
  if(f == NULL) {
    fprintf(stderr, "not valid  input file\n");
    return EXIT_FAILURE ;
  }
  deck_t ** deck_array=NULL;
  size_t n_hands =0 ;
  future_cards_t * fc=malloc(sizeof(*fc));
  fc->decks=NULL;
  fc->n_decks=0;
  deck_array=read_input(f,&n_hands,fc);
  //Create a deck with the remaining cards
  deck_t* sh=build_remaining_deck(deck_array, n_hands);
  int win_array[n_hands+1];
   for(int u=0;u<n_hands+1;u++) win_array[u]=0;
  // Do each Monte Carlo trial (repeat num_trials times)
  int num_trials = 10000;
  if (argc ==3) num_trials=atoi(argv[2]);
  for(int i=0;i<num_trials;i++){
    //Shuffle the deck of remaining cards
    shuffle(sh);
    //Assign unknown cards from the shuffled deck
    future_cards_from_deck(sh,fc);
    //Use compare_hands (from Course 3)
    int c =win_hand(deck_array,n_hands);
    win_array[c]++;
  }
  //you just need to print your results
  for(size_t j=0;j<n_hands;j++){
    printf("Hand %zu won %u / %u times (%.2f%%)\n",j,win_array[j],num_trials,(((float)win_array[j])/num_trials)*100);
  }
  printf( "And there were %u ties\n",win_array[n_hands]);
  //free any memory you allocated
  for(int x=0;x<n_hands;x++){
    free_deck(deck_array[x]);
  }
  free(deck_array);
  for(int o=fc->n_decks-1 ;o>=0;o--){
    if(fc->decks[o].n_cards != 0) free(fc->decks[o].cards);
  }
  free(fc->decks);
  free(fc);
  free_deck(sh);
 
  if(fclose(f) != 0){
    fprintf(stderr, "close file");
    return EXIT_FAILURE;
  }
>>>>>>> d85dc27bad99c8facdff761b58cec679d21f9388
  return EXIT_SUCCESS;
}
