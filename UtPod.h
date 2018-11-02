//DOCUMENT HERE

#ifndef UTPOD_H
#define UTPOD_H
#include "Song.h"
#include <cstdlib>

//UtPod class declaration
class UtPod
{
private:
    static const int MAX_MEMORY = 512;
    static const int SUCCESS = 0;
    static const int NO_MEMORY = -1;
    static const int NOT_FOUND = -2;
/* FUNCTION - int numberSongs
 * attempts to know the number of songs in the link list
 * counts how many number of songs are in UTPOD
     o returns number of songs


   input parms - no inputs

   output parms - integer with the number of songs in the link list
*/
    int numberSongs();

    struct SongNode   //to create our LinkList of songs
    {
        Song s;
        SongNode *next;

        SongNode():s(),next(NULL){}        //default constructor for song node
    };

    SongNode *songs;  //the head pointer

    int memSize;

public:
    //Default constructor
    //set the memory size to MAX_MEMORY
    UtPod();

    //Constructor with size parameter
    //The user of the class will pass in a size.
    //If the size is greater than MAX_MEMORY or less than or equal to 0,
    //set the size to MAX_MEMORY.
    UtPod(int size);

/* FUNCTION - int addSong
 * attempts to add a new song to the UtPod
     o returns a 0 if successful
     o returns -1 if not enough memory to add the song

 precondition: s is a valid Song

 input parms - Pointer of the head of the of the LinkList

 output parms - SUCCESS=0 and NO_MEMORY=-1
*/

    int addSong(Song const &s);


/* FUNCTION - int removeSong
 * attempts to remove a song from the UtPod
 * removes the first instance of a song that is in the the UtPod multiple times
     o returns 0 if successful
     o returns -1 if nothing is removed


   input parms - address of song node

   output parms - integer 0 success or -1 failed
*/

    int removeSong(Song const &s);



/* FUNCTION - void shuffle
 *  shuffles the songs into random order
    o will do nothing if there are less than two songs in the current list

   input parms - not input

   output parms - not output, just changes the nodes of the list multiple times
*/

    void shuffle();


/* FUNCTION - void showSongList
 * prints the current list of songs in order from first to last to standard output
 * format - Title, Artist, size in MB (one song per line)

   input parms - not inputs

   output parms - not output, just prints the current song list
*/

    void showSongList();


    /* FUNCTION - void sortSongList
     *  sorts the songs in ascending order
        o will do nothing if there are less than two songs in the current list

       input parms -

       output parms -
    */
/* FUNCTION - void sortSongList
 *  sorts the songs in ascending order
    o will do nothing if there are less than two songs in the current list

   input parms - not input

   output parms - not output, just puts the songs in order(by artist, then title, then size)
*/
    void sortSongList();
/*SWAP FUNCTION
 *Gets call by sort to swap
 * inputs = pointers to the song linked List
 * output = none
 */
    void swap(struct SongNode *a,struct SongNode *b);



/* FUNCTION - void clearMemory
 * clears all the songs from memory

   input parms - none

   output parms -none, just clear link list
*/
    void clearMemory();


    /* FUNCTION - int getTotalMemory
     *  returns the total amount of memory in the UtPod
        o will do nothing if there are less than two songs in the current list

       input parms - none

       output parms - integer with memSize value
    */

    int getTotalMemory() {
        return memSize;
    }




/* FUNCTION - int getRemainingMemory
 *  returns the amount of memory available for adding new songs

   input parms -none

   output parms -int remaining memory
*/


    int getRemainingMemory();


    ~UtPod();

};

#endif