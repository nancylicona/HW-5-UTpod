#include <iostream>
#include "UtPod.h"
#include <cstdlib>
#include <stdlib.h>
#include <time.h>

using namespace std;

//Default constructor
//set the memory size to MAX_MEMORY
UtPod::UtPod(){
    memSize=MAX_MEMORY;     //set to 512
}

//Constructor with size parameter
//The user of the class will pass in a size.
//If the size is greater than MAX_MEMORY or less than or equal to 0,
//set the size to MAX_MEMORY.
UtPod::UtPod(int size){
    if(size>MAX_MEMORY || size<=0){     //if greaater than max or less than or equal to 0
        memSize=MAX_MEMORY;     //set to 512
    }
    else{
        memSize=size;       //set the size by user
    }
}


/* FUNCTION - int addSong
 * attempts to add a new song to the UtPod
     o returns a 0 if successful
     o returns -1 if not enough memory to add the song

 precondition: s is a valid Song

 input parms - Pointer of the head of the of the LinkList

 output parms - SUCCESS=0 and NO_MEMORY=-1
*/
int UtPod::addSong(Song const &s) {
//check memory to see if there is enough space to add song
    SongNode *current=songs;       //temporary
    int remaining=getRemainingMemory();     //call function

    if(s.getArtist() == "" || s.getTitle() == ""){      //if blank title or artist
        cout << "Title and artist cannot be blank" << endl;
        return NO_MEMORY;
    }
    else if(s.getSize() <= 0){      //if 0 or less MB size
        cout << "Size must be greater than zero" << endl;
        return NO_MEMORY;
    }
    else if (remaining >= s.getSize()) {
        SongNode *newNode = new SongNode();        //allocate space
        newNode->s = s;     //initialize pointer
        if (remaining == memSize) {     //if empty link list
            songs = newNode;                //set the header pointer
            newNode->next = NULL;
        } else {
            while (current->next != NULL) {     //if current next is not null
                current = current->next;        //add to the end of the link list
            }
            current->next = newNode;        //change the next of the early last node
            newNode->next = NULL;           //set the end of list
        }
        return SUCCESS;     //return succes
    } else {
        return NO_MEMORY;       //when no memory
    }
}


/* FUNCTION - int removeSong
 * attempts to remove a song from the UtPod
 * removes the first instance of a song that is in the the UtPod multiple times
     o returns 0 if successful
     o returns -1 if nothing is removed


   input parms - address of song node

   output parms - integer 0 success or -1 failed
*/
int UtPod::removeSong(Song const &s){
    int size=0;
    if(songs== NULL){            //because there is nothing to remove
        return -1;
    }
    else if(s.getArtist() == "" || s.getTitle() == ""){
        cout << "Title and artist cannot be blank" << endl;     //cant remove empty title or artist
        return NO_MEMORY;
    }
    else if(s.getSize() <= 0){
        cout << "Size must be greater than zero" << endl;       //cant remove when size is >=0
        return NO_MEMORY;
    }
    else{
        SongNode *current=songs;  //create a pointer and initialize it to the header
        SongNode *previous=songs;   //create a pointer and initialize it to the header
        while(current!= NULL){     //do we are not at the end of the linklist
            if(current->s == s){        //if match
                if(current==songs){    //remove head
                    songs=songs->next;      //if current is the head means move song
                } else{
                    previous->next=current->next;       //set the link between the previous one and the next one from current
                }
                delete current;
                return 0;
            } else{
                previous=current;       //update previous
                current=current->next;      //update current
            }
        }
        return -1;
    }
}

/* FUNCTION - int numberSongs
 * attempts to know the number of songs in the link list
 * counts how many number of songs are in UTPOD
     o returns number of songs


   input parms - no inputs

   output parms - integer with the number of songs in the link list
*/
int UtPod::numberSongs() {
    SongNode *pointer = songs;      //initialize new pointer
    int nSongs = 0;     //initialize number of songs
    while (pointer != NULL) {       //while not the end of the list
        nSongs++;       //increment number of song
        pointer = pointer->next;        //check next node
    }
    return (nSongs);        //returns the number of songs
}



/* FUNCTION - void shuffle
 *  shuffles the songs into random order
    o will do nothing if there are less than two songs in the current list

   input parms - not input

   output parms - not output, just changes the nodes of the list multiple times
*/
void UtPod::shuffle(){
    int nSongs, random1, random2, looptime;
    SongNode *song1;
    SongNode *song2;
    Song temp;
    nSongs=numberSongs();
    looptime=nSongs*4;
    if(nSongs>1) {
        do {
            song1 = songs;        //initialize pointer1
            song2 = songs;        //initialize pointer2
            random1 = rand() % nSongs + 1;  //get first random number
            random2 = rand() % nSongs + 1;  //get second random number
            if (random1 != random2) {
                while (random1 > 1) {       //to select song1
                    song1 = song1->next;      //points to the node we want to swap
                    random1--;      //decrement random1
                }
                while (random2 > 1) {       //to select song2
                    song2 = song2->next;      //points to the node we want to swap
                    random2--;      //decrement random2
                }
                temp = song1->s;        //temp holds copy of song1
                song1->s = song2->s;        //move node of song2 to song1
                song2->s = temp;    //song 1 is on temp so gets copy to song2
            }
            looptime--;     //decrement looptime
        } while (looptime != 0);        //do until looptime is 0
    }
}


/* FUNCTION - void showSongList
 * prints the current list of songs in order from first to last to standard output
 * format - Title, Artist, size in MB (one song per line)

   input parms - not inputs

   output parms - not output, just prints the current song list
*/

void UtPod::showSongList(){
    SongNode *temp=songs;       //head pointer
 //   sortSongList();
    while(temp!=NULL){      //while not the end of list
        Song prints=temp->s;        //print holds the song node
        cout<<prints.getTitle() << ", " << prints.getArtist() << ", " << prints.getSize()<<"MB"<< "\n" << endl;     //print song
        temp=temp->next;        //move to next song
    }
}


/*SWAP FUNCTION
 *Gets call by sort to swap
 * inputs = pointers to the song linked List
 * output = none
 */
void UtPod::swap(struct SongNode *a,struct SongNode *b){
    Song temp = a->s;       //temp holds song1 node
    a->s = b->s;        //song2 gets song1
    b->s = temp;        //song2 gets temp
    return;
}


/* FUNCTION - void sortSongList
 *  sorts the songs in ascending order
    o will do nothing if there are less than two songs in the current list

   input parms - not input

   output parms - not output, just puts the songs in order(by artist, then title, then size)
*/
void UtPod::sortSongList() {
    Song t;                             //Song type variable to get...
    Song m;                             //Song type variable to get...
    SongNode *ptr1=songs;                     //Node that starts pointing at songs (head of the linked list
    SongNode *ptr2;       //Node that points at the next position of ptr1
    SongNode *ptr3;

    while (ptr1!=NULL) {
        ptr2=songs;
        ptr3=songs->next;
        while (ptr3 != NULL) {
            t = ptr2->s;             //To access the rhs
            m = ptr3->s;            //To access the lfs ONE IN FRONT OF PTR1

            if (t> m) {
                swap(ptr2, ptr3);
            }
            ptr2= ptr2->next;                  //Move the pointer to the next position
            ptr3 = ptr3->next;                  //Moving the pointer to the next location from ptr1
        }
        ptr1 = ptr1->next;                           //when done going through once - then you start again
    }
    return;
}



/* FUNCTION - void clearMemory
 * clears all the songs from memory

   input parms - none

   output parms -none, just clear link list
*/
void UtPod::clearMemory(){
    SongNode *dptr2=songs;      //initialize pointer
    while(songs!=NULL){
        songs=songs->next;  //move header to next song
        delete dptr2;       //delete current song pt
        dptr2=songs;        //update current song pt
    }
}


/* FUNCTION - int getRemainingMemory
 *  returns the amount of memory available for adding new songs

   input parms -none

   output parms -int remaining memory
*/

int UtPod::getRemainingMemory(){
    int remainingmem=0;
    SongNode *pt=songs;         //pointer to transverse the link list initialize to head pt
    Song stemp;
    while(pt!=NULL) {
        stemp = pt->s;                       //getting info of node
        remainingmem += stemp.getSize();       //get memory size of the song
        pt=pt->next;                           //next node in link list
    }
    if(memSize!=remainingmem){
        return memSize-remainingmem;    //to get remaining memory
    }
    else{
        return memSize;     //empty list = total memory
    }
}


UtPod::~UtPod(){
    clearMemory();  //call to clear link list
}


