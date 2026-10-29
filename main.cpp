
/*
 * File:   main.cpp
 * Author: Professor Terri Sipantzi
 *
 * Created on August 25, 2012, 8:49 AM
 * Modified on October 24, 2020, 9:27 PM
 * Modified on October 12, 2022, 1:09 PM
 * Modified on May 15, 2023, 12:44 PM
 * Modified on Novermber 30, 2023, 12:44 PM
 * Modified on March 31, 2024, 12:44 PM
 * Modified on October 31, 2024, 12:44 PM
 * Modified on April 24, 2025, 14:45 PM
 * Modified on November 10, 2025, 14:45 PM
 * Modified on April 22, 2026, 16:03 PM
 */

#include "constants.h"
#include "LRUBufferPool.h"

int main() {
    //initialize buffer pool
    LRUBufferPool* bp = new LRUBufferPool("mydatafile.txt", POOL_SIZE, BLOCKSIZE);

    //get data from the buffer
    char* data = new char[10];
    bp->getBytes(data, 10, 5045);
    printChars(data, 10, 5045 / BLOCKSIZE);
    bp->printBufferBlockOrder();
    cout << "LRU Buffer is " << bp->getLRUBlockID() << endl << endl;
    /*  
      My data for block 1 is: "you do not"
      My buffer block order from most recently used to LRU is:
              1, 0, 2, 3, 4,
      LRU Buffer is 4
	*/

    //re-initialize the char array and get the next block of data
    initializeCharArray(10, data);
    bp->getBytes(data, 10, 16505);
    printChars(data, 10, 16505 / BLOCKSIZE);
    bp->printBufferBlockOrder();
    cout << "LRU Buffer is " << bp->getLRUBlockID() << endl << endl;
    /*
        My data for block 4 is: "main.cpp a"
        My buffer block order from most recently used to LRU is:
                4, 1, 0, 2, 3,
        LRU Buffer is 3
    */

    //re-initialize the char array and get the next block of data
    initializeCharArray(10, data);
    bp->getBytes(data, 10, 24655);
    printChars(data, 10, 24655 / BLOCKSIZE);
    bp->printBufferBlockOrder();
    cout << "LRU Buffer is " << bp->getLRUBlockID() << endl << endl;
    /*
        My data for block 6 is: "T (BufferP"
        My buffer block order from most recently used to LRU is:
                6, 4, 1, 0, 2,
        LRU Buffer is 2
    */

    //re-initialize the char array and get the next block of data
    initializeCharArray(10, data);
    bp->getBytes(data, 10, 28815);
    printChars(data, 10, 28815 / BLOCKSIZE);
    bp->printBufferBlockOrder();
    cout << "LRU Buffer is " << bp->getLRUBlockID() << endl << endl;

    //re-initialize the char array and get the next block of data
    initializeCharArray(10, data);
    bp->getBytes(data, 10, 16620);
    printChars(data, 10, 16620 / BLOCKSIZE);
    bp->printBufferBlockOrder();
    cout << "LRU Buffer is " << bp->getLRUBlockID() << endl << endl;

    //re-read block 2 into the pool
    initializeCharArray(10, data);
    bp->getBytes(data, 10, 8245);
    printChars(data, 10, 8245 / BLOCKSIZE);
    bp->printBufferBlockOrder();
    cout << "LRU Buffer is " << bp->getLRUBlockID() << endl << endl;

    //close program
    cout << endl << endl;
    system("pause");
    return 0;
}
