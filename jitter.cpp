#include <iostream>
#include <cassert>
#include <cstring>
#include <cctype>

using namespace std;

const int MAX_WORD_LENGTH = 20;
const int MAX_JEET_LENGTH = 280;

// check how to initialize arrays (does empty strings work?)
// nStandards = 0?
// THOROUGH testing

int editStandards(int distance[],
                  char word1[][MAX_WORD_LENGTH+1],
                  char word2[][MAX_WORD_LENGTH+1],
                  int nStandards);

int determineMatchLevel(const int distance[],
                        const char word1[][MAX_WORD_LENGTH+1],
                        const char word2[][MAX_WORD_LENGTH+1],
                        int nStandards,
                        const char jeet[]);

int main() {

    // test set 1
    
    const int TEST1_NSTANDARDS = 4;
    int test1dist[TEST1_NSTANDARDS] = {
        1,2,3,4
    };
    char test1w1[TEST1_NSTANDARDS][MAX_WORD_LENGTH+1] = {
        "nakul", "nakul", "nakul", "wordone"
    };
    char test1w2[TEST1_NSTANDARDS][MAX_WORD_LENGTH+1] = {
        "khambhati", "khambhati", "khambhati", "wordtwo"
    };
    
    int test1result[TEST1_NSTANDARDS] = {3,4};
    int r1 = editStandards(test1dist, test1w1, test1w2, TEST1_NSTANDARDS);
    assert(r1 == 2); // works with a triplicate as well
    for (int i = 0; i < r1; i++){
        assert(test1result[i] == test1dist[i]);
    }
    
    // test set 2
    
    const int TEST2_NSTANDARDS = 8;
    int test2dist[TEST2_NSTANDARDS] = {
        -1, 0, 1, 3, 2, 1, 13, 6
    };
    char test2w1[TEST2_NSTANDARDS][MAX_WORD_LENGTH+1] = {
        "eccentric",   "space",  "ELECTRIC","tunnel-boring", "space", "Electric", "were", "electric"
    };
    char test2w2[TEST2_NSTANDARDS][MAX_WORD_LENGTH+1] = {
        "billionaire", "capsule", "CAR",  "equipment",   "capsule", "car", "eccentric", "car"
    };
    
    int test2result[TEST2_NSTANDARDS] = {2, 13, 6};
    int r2 = editStandards(test2dist, test2w1, test2w2, TEST2_NSTANDARDS);
    assert(r2 == 3); // works for the test case in the project spec
    for (int i = 0; i < r2; i++){
        assert(test2result[i] == test2dist[i]);
    }
    
    // test set 3
    
    const int TEST3_NSTANDARDS = 5;
    int test3dist[TEST3_NSTANDARDS] = {
        1, 2, 3, 4, 5
    };
    char test3w1[TEST3_NSTANDARDS][MAX_WORD_LENGTH+1] = {
        "nakul",   "angad",  "arnav","ani-rudh", "angAD"
    };
    char test3w2[TEST3_NSTANDARDS][MAX_WORD_LENGTH+1] = {
        "khambhati", "kapOOr", "mierd0",  "rao",   "kapoor"
    };
    
    int test3result[TEST3_NSTANDARDS] = {1, 5};
    int r3 = editStandards(test3dist, test3w1, test3w2, TEST3_NSTANDARDS);
    assert(r3 == 2); // checking that upper is converted, non alpha is not counted
    for (int i = 0; i < r3; i++){
        assert(test3result[i] == test3dist[i]);
    }
    
    // test set 4
    
    const int TEST4_NSTANDARDS = 0;
    int test4dist[TEST4_NSTANDARDS] = {
        
    };
    char test4w1[TEST4_NSTANDARDS][MAX_WORD_LENGTH+1] = {
        
    };
    char test4w2[TEST4_NSTANDARDS][MAX_WORD_LENGTH+1] = {
        
    };
    
    int test4result[TEST4_NSTANDARDS] = {}; // if n standards is 0, everything should be 0
    int r4 = editStandards(test4dist, test4w1, test4w2, TEST4_NSTANDARDS);
    assert(r4 == 0); // returns 0 retained elements cuz there are 0 elements
    for (int i = 0; i < r4; i++){
        assert(test4result[i] == test4dist[i]);
    }
    
    
    // test set 5
    
    const int TEST5_NSTANDARDS = 4;
    int test5dist[TEST5_NSTANDARDS] = {
        1, 2, 3, 4
    };
    char test5w1[TEST5_NSTANDARDS][MAX_WORD_LENGTH+1] = {
        "", "naku1", "kham bhati", "0"
    };
    char test5w2[TEST5_NSTANDARDS][MAX_WORD_LENGTH+1] = {
        "word", "word", "word", "word"
    };
    
    int test5result[TEST5_NSTANDARDS] = {};
    int r5 = editStandards(test5dist, test5w1, test5w2, TEST5_NSTANDARDS);
    assert(r5 == 0);
    for (int i = 0; i < r5; i++){ // the empty string is not allowed
        assert(test5result[i] == test5dist[i]);
    }
    
    // *** determining match level for jeets ***
    
    
    const int TEST6_NSTANDARDS = 4;
    int test6dist[TEST6_NSTANDARDS] = {
        2,             4,         1,         13
    };
    char test6w1[TEST6_NSTANDARDS][MAX_WORD_LENGTH+1] = {
        "eccentric",   "space",  "electric", "were"
    };
    char test6w2[TEST6_NSTANDARDS][MAX_WORD_LENGTH+1] = {
        "billionaire", "capsule", "car",     "eccentric"
    };
    
    assert(determineMatchLevel(test6dist, test6w1, test6w2, TEST6_NSTANDARDS,
        "The eccentric outspoken billionaire launched a space station cargo capsule.") == 2);
    assert(determineMatchLevel(test6dist, test6w1, test6w2, TEST6_NSTANDARDS,
        "The eccentric outspoken billionaire launched    a space capsule.") == 2);
    assert(determineMatchLevel(test6dist, test6w1, test6w2, TEST6_NSTANDARDS,
        "**** 2022 ****") == 0);
    assert(determineMatchLevel(test6dist, test6w1, test6w2, TEST6_NSTANDARDS,
        "  It's an ELECTRIC car!") == 1);
    assert(determineMatchLevel(test6dist, test6w1, test6w2, TEST6_NSTANDARDS,
        "space space capsule space capsule capsule") == 1);
    assert(determineMatchLevel(test6dist, test6w1, test6w2, TEST6_NSTANDARDS,
        "Two eccentric billionaires were space-capsule riders.") == 0);
    
    // works for the test cases in the spec
    
    assert(determineMatchLevel(test6dist, test6w1, test6w2, TEST6_NSTANDARDS,
        "The eCcen8tric    weird BILLION999AIRE") == 1); //caps, nonalpha and spaces don't matter
    assert(determineMatchLevel(test6dist, test6w1, test6w2, TEST6_NSTANDARDS,
        "electric c car") == 0); // doesn't work for distance of 2 if it's meant to be 1
    assert(determineMatchLevel(test6dist, test6w1, test6w2, TEST6_NSTANDARDS,
        "eccentric billionaire space capsule electric car were eccentric") == 4); // match levels stack up
    assert(determineMatchLevel(test6dist, test6w1, test6w2, TEST6_NSTANDARDS,
        "eccentric billionaire space capsule electric car were eccentric were eccentric were eccentric") == 4); // doesn't double count
    
    
    const int TEST7_NSTANDARDS = 4;
    int test7dist[TEST7_NSTANDARDS] = {
        2,             4,         1,         13
    };
    char test7w1[TEST7_NSTANDARDS][MAX_WORD_LENGTH+1] = {
        "nakul",  "nakul",  "and", "smartest"
    };
    char test7w2[TEST7_NSTANDARDS][MAX_WORD_LENGTH+1] = {
        "barkha", "crocs", "the", "alive"
    };
    
    assert(determineMatchLevel(test7dist, test7w1, test7w2, TEST7_NSTANDARDS,
        "nakul and barkha see nakul wearing crocs and the consensus is that he is the smartest man alive.") == 4); // checking that all 4 work even when there are words that occur twice in the jeet
    assert(determineMatchLevel(test7dist, test7w1, test7w2, TEST7_NSTANDARDS,
        "barkha and nakul see the the the crocs wearing nakul the and consensus is that he is the alive smartest man.") == 0); // reversing order doesn't count
    assert(determineMatchLevel(test7dist, test7w1, test7w2, TEST7_NSTANDARDS,
        "nakul and barkha nakul and barkha") == 1); // checking that a double match isn't counted twice
    assert(determineMatchLevel(test7dist, test7w1, test7w2, TEST7_NSTANDARDS,
        "nakul and barkha and crocs and the smartest thing to do is to check whether the living people are still alive") == 4); // spacing each out at its maximum
    assert(determineMatchLevel(test7dist, test7w1, test7w2, TEST7_NSTANDARDS,
        "nakul khambhati and barkha and crocs and I think the smartest thing to do is to check whether the living people are all still alive") == 0); // exceeding each's maximum by 1
    assert(determineMatchLevel(test7dist, test7w1, test7w2, TEST7_NSTANDARDS,
        "") == 0); // empty jeet
    assert(determineMatchLevel(test7dist, test7w1, test7w2, TEST7_NSTANDARDS,
        "nakul nakul and smartest") == 0); // all just from w1
    assert(determineMatchLevel(test7dist, test7w1, test7w2, TEST7_NSTANDARDS,
        "barkha crocs the alive") == 0); // all just from w2
    assert(determineMatchLevel(test7dist, test7w1, test7w2, TEST7_NSTANDARDS,
        "nakul  3957203&$9035- and//4530790 barkha se4590e nakul wear343ing     3434 cr3o4cs and the conse!!nsu!3s 35is t53hat5 3he 5is t32552he 513smartest ma-0325_)*0-5831n ali351-0ve.") == 4); // putting random non-alphabets in the middle has absolutely no effect
    
    const int TEST8_NSTANDARDS = 0; // with nStandards = 0, absolutely everything returns 0 as the match level
    int test8dist[TEST8_NSTANDARDS] = {

    };
    char test8w1[TEST8_NSTANDARDS][MAX_WORD_LENGTH+1] = {

    };
    char test8w2[TEST8_NSTANDARDS][MAX_WORD_LENGTH+1] = {

    };
    
    assert(determineMatchLevel(test8dist, test8w1, test8w2, TEST8_NSTANDARDS,
        "nakul and barkha see nakul wearing crocs and the consensus is that he is the smartest man alive.") == 0);
    assert(determineMatchLevel(test8dist, test8w1, test8w2, TEST8_NSTANDARDS,
        "nakul and barkha nakul and barkha") == 0);
    assert(determineMatchLevel(test8dist, test8w1, test8w2, TEST8_NSTANDARDS,
        "nakul and barkha and crocs and the smartest thing to do is to check whether the living people are still alive") == 0);
    assert(determineMatchLevel(test8dist, test8w1, test8w2, TEST8_NSTANDARDS,
        "nakul khambhati and barkha and crocs and I think the smartest thing to do is to check whether the living people are all still alive") == 0);
    assert(determineMatchLevel(test8dist, test8w1, test8w2, TEST8_NSTANDARDS,
        "") == 0);
    assert(determineMatchLevel(test8dist, test8w1, test8w2, TEST8_NSTANDARDS,
        "nakul nakul and smartest") == 0);
    assert(determineMatchLevel(test8dist, test8w1, test8w2, TEST8_NSTANDARDS,
        "barkha crocs the alive") == 0);
    
    
    const int TEST9_NSTANDARDS = 4; // trying things where swaps are in the standard
    int test9dist[TEST9_NSTANDARDS] = {
            2, 3, 2, 3
    };
    char test9w1[TEST9_NSTANDARDS][MAX_WORD_LENGTH+1] = {
        "happy", "sad", "up", "down"
    };
    char test9w2[TEST9_NSTANDARDS][MAX_WORD_LENGTH+1] = {
        "sad", "happy", "down", "up"
    };
    
    
    assert(determineMatchLevel(test9dist, test9w1, test9w2, TEST9_NSTANDARDS,
        "I'm happy and sad. Happy because things are looking up. Down bad though because down is sometimes up") == 4); // including both ends isn't an issue
    
    assert(determineMatchLevel(test9dist, test9w1, test9w2, TEST9_NSTANDARDS,
        "happy x x sad x x happy. up x x down x x up") == 2); // distances aren't getting mixed up (out of bounds still works

    
    
    
    
    cerr << "All tests succeeded" << endl;
    
    
//    cerr << r1 << endl;
//
//
//    for (int i = 0; i < r1; i++){
//
//        cerr << test1dist[i] << " " << test1w1[i] << " " << test1w2[i] << endl;
//
//    }
//
//    determineMatchLevel(test2dist, test2w1 , test2w2, TEST2_NSTANDARDS, "I'm upset that on Apr. 29th, 2022, my 2 brand-new BMW i7s were stolen abcdefghijklmnopqrstuvwxyz wdkqjw!!");
    
    
    
    return 0;
}

int editStandards(int distance[],
                  char word1[][MAX_WORD_LENGTH+1],
                  char word2[][MAX_WORD_LENGTH+1],
                  int nStandards){
    
    // how to deal w nStandards <= 0 ?
    
    if (nStandards < 0) nStandards = 0;
    
    /*
     
     **SHORT NOTE**
     
     I initally declared:
     
     int positions[nStandards];
     
     for (int i = 0; i < nStandards; i++){ // initialize all to 1, indicating true
         positions[i] = 1;
     }
     
     to create an array of positions so that I can just set everything that should be removed to 0 step-by-step
     
     While this compiled on Xcode, it didn't compile on g31 as I used a variable for the size of the array.
     
     To get around this, I have kind of "cheated" the system by setting distance to 0 here whenever we actually needed to set positions to 0. This is allowed as 0 distance is anyway not counted as a standard match.
     */
    

    
    for (int i = 0; i < nStandards; i++){
        if (distance[i] <= 0){
            distance[i] = 0;
//            break;
            continue;
        } // set to false for positions of non-positive distances, break and go to the next i
        
        if (strcmp(word1[i],"") == 0 || strcmp(word2[i],"") == 0){
            distance[i] = 0;
//            break;
            continue;
        }  // set to false for empty strings
        
        
        
        for (int j = 0; j < strlen(word1[i]); j++){
            if (!isalpha(word1[i][j])){
                distance[i] = 0;
                break;
            }
        }
        

        
        for (int j = 0; j < strlen(word2[i]); j++){
            if (!isalpha(word2[i][j])){
                distance[i] = 0;
                break;
            }
        }
        
        
    }
    

    
    // at this point, there might be some uppercase and dups
    
    for (int i = 0; i < nStandards; i++){ // looping through all characters and make them lower case
        for (int j = 0; j < strlen(word1[i]); j++){
            word1[i][j] = tolower(word1[i][j]); // why doesn't just tolower work??
        }
        for (int j = 0; j < strlen(word2[i]); j++){
            word2[i][j] = tolower(word2[i][j]); // why doesn't just tolower work??
        }
    }
    
    // need to fix dups now
    
    /*
     
     if there is a dup, set false to the smaller distances and if same, keep only one
     
     */
    
    
    // check for dups in w1, if a dupe is found, check for if the same indices are equal in w2 as well.
    
    for (int i = 0; i < nStandards; i++){
        
        if (distance[i] != 0){ // only do this for the good positions
            char target[MAX_WORD_LENGTH+1];
            strcpy(target, word1[i]);
            
            for (int j = i + 1; j < nStandards; j++){
                if (strcmp(word1[j], target) == 0){ // can use word[i] instead of target, but target can be used to improve readability
                    if (strcmp(word2[i], word2[j]) == 0){
                        // set the one with less or equal distance to 0
                        if (distance[i] < distance[j]){
                            distance[i] = 0;
//                            continue;
                        }// reading this can be a bit confusing but basically the distance in brackets corresponds to the actual distance and in "distance = 0" we are using it as the position
                        else {
                            distance[j] = 0;
//                            continue;
                        }// so if equal it does this where it removes the latter one, not the first
                    }
                }
            }
            
        }
        
    }
    
//    for (int i = 0; i < nStandards; i++) cerr << distance[i] << " "; // just for debugging, comment out later
//    cerr << endl;
    
    int r = 0; // create a variable to count the # of "good" variables
    
    for (int i = 0; i < nStandards; i++){
        if (distance[i]){
            distance[r] = distance[i];
            
            if (r != i){                // to avoid the overlap error mentioned in spec
            strcpy(word1[r], word1[i]);
            strcpy(word2[r], word2[i]);
            }
                
                
            r++;
        }
    }
    
//    for (int i = 0; i < r; i++) cerr << distance[i] << " "; // just for debugging, comment out later
//    cerr << endl;
    
    // ideally r will be the number of good variables now
    
    // for int i from 0 to nStandards - 1
        // if the positions value is right, put it in the r'th position of distances and increment r
    
    return r;
}

/*
 
 we have an nStandards length array of distance
                                    of words (with a max word length)
                                and of words (with a max word length)
 
 we want to remove some first directly:
    - negative or 0 distance
    - empty string or non letter
 
 and then fix the others:
    - transform all upper case chars to lower case ones
    - if two or more positions have same w1 and w2, remove all but one with greatest distance
 
 method:
    maybe create an array of indices, set positions of words that don't match to 0, others to 1 (negative and empty/non-letter is easy, how to remove dups? (FIRST TRANSFORM TO LOWER)
    count the numbers of 1s and call it r
    change the first r elements of each array to the "good" elements (r of them)
 
 */


int determineMatchLevel(const int distance[],
                        const char word1[][MAX_WORD_LENGTH+1],
                        const char word2[][MAX_WORD_LENGTH+1],
                        int nStandards,
                        const char jeet[]){
    
    if (nStandards < 0) nStandards = 0;
    
    /*
     We first create an equivalent jeet that's easier to deal with
     
     We then store all the "words" in that jeet in an array of cstrings
     
     We then test for how many standards match
     */
    
    
    char jeet_good[MAX_JEET_LENGTH+1] = ""; // not const char cuz we are changing things
    
    
    int r = 0; // to store length of good_jeet
    
    for (int i = 0; i < strlen(jeet); i++){ // create an "equivalent" jeet in lowercase letters only
        if (isalpha(jeet[i]) || (jeet[i] == ' ')){
            jeet_good[r] = tolower(jeet[i]);
            r++;
        }
    }
    
    int num_words = 0; // to store the number of "words" in the jeet
    
    for (int i = 0; i < r - 1; i++){
        if (jeet_good[i] == ' ' && jeet_good[i+1] != ' '){ // count numbers of spaces (except if last is a space)
            num_words ++;
        }
    } // if the last one is a space, we anyway don't want to count it
    
    if (jeet_good[0] != ' ') num_words++;// if the first is not a space, increment num_words
    
    char words[MAX_JEET_LENGTH +1][MAX_WORD_LENGTH+1] = {""};// create an array of the words in the jeet, there can't be more words than the number of characters
    
    int word_index = 0; //
    
    for (int i = 0; i < r; i++){ // iterate through every char if good_jeet
        
        if (jeet_good[i] != ' '){ // only do this if good_jeet doesn't have a space here. If it does, move to the next non-space
        
            int j = i; // initialize another parameter (to denote the start index of the word within good_jeet
            
            while (jeet_good[j] != ' ' && j < r){ // second condition so that for the last one (after all spaces) j doesn't keep increasing infinitely
                j++;

            } // j will be 1 + end index of the word after this
            
            int l = 0; // to increment through the position (from 0 till j - i - 1) of words[word_index]
            for (int k = i; k < j; k++){ // set 0 to j - i - 1 of words[word_index] = i to j - 1 of jeet_good
                
                if (l >= MAX_WORD_LENGTH) break; // this lets l go to 19th position (so enter 20 useful characters) and when l = 20, it breaks. i.e we only store first 20 chars of each word, which isn't an issue here for matching.
                
                words[word_index][l] = jeet_good[k];
                l++;
            }
            
            // l ends at the length of the word in words[word_index]
            // gets reset in the next occurence of a "word"
            
            word_index ++; // go the next word position (row) in words
            
            i = j; // for the next word to be found set i to j (which was 1 + end index of the word after the first) it has to be a space by definition. so the loop +1 sends it to the next word (if no consecutive spaces)
            
        }
    }
    
    //for (int i = 0; i < num_words; i++) cout << words[i] << endl;

    
    // at this point, there can be multiple space gaps between the words
    
    // find the number of words in this jeet (so number of spaces + 1)
    // create an array with dimension [num_words]

    
//    for (int i = 0; i < r; i++){
//        cerr << jeet_good[i];
//    } cerr << endl;
    
    
    /*
     now for each index uptil nStandards, we need to check:
     
     int matchLevel = 0;
     
     loop through w1
        look for w1[i] in the jeet (0 <= i <= nStandards - 1)
        say we find such a match: words[j] (0 <= j <= num_words - 1)
        look at d:= distance[i], check if there exist d many words
                                i.e. avoid out of bounds error if d > num_words - 1 - j
                                so d to how many are left to search
        search for w2[i] in words[k] where k ranges from j + 1 till j + d
                                matchLevel ++ and break if found
        
    
    */
    
    int matchLevel = 0;
    
    for (int i = 0; i < nStandards; i++){
//        bool found = false;
        int j = 0;
        
        bool match = false;
        for (j = 0; j < num_words - 1; j++){
            if (strcmp(words[j], word1[i]) == 0){
                int d = distance[i]; // check edge case where j = num - 1, should return matchlevel = 0.
                if (d > num_words - 1 - j){
                    d = num_words - 1 - j;
                } // match found at j-th index, so num - 1 - j left to look through. If d is bigger than that number, set d to that number
                
                for (int k = j + 1; k <= j + d; k++){// used <= d here because it's more clear (goes from j + 1 to j + d so total d after j are checked
                    if (strcmp(words[k], word2[i]) == 0){
                        match = true;
                        break;
                    }
                } if (match) continue;
            }
        }
        
        if (match) matchLevel ++;

    }
    
    
    return matchLevel;
}

