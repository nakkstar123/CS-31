//
//  main.cpp
//  Project_4
//
//  Created by Nakul Khambhati on 4/28/22.
//


#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int enumerate(const string a[], int n, string target);

int findMatch(const string a[], int n, string target);

bool findRun(const string a[], int n, string target, int& begin, int& end);

int findMin(const string a[], int n);

int moveToEnd(string a[], int n, int pos);

int moveToBeginning(string a[], int n, int pos);

int findDifference(const string a1[], int n1, const string a2[], int n2);

int removeDups(string a[], int n);

bool subsequence(const string a1[], int n1, const string a2[], int n2);

int makeMerger(const string a1[], int n1, const string a2[], int n2,
                    string result[], int max);

int divide(string a[], int n, string divider);

int main(){
    
    string h[7] = { "neil", "sonia", "john", "amy", "", "elena", "john" };
    string g[0];
    string d[9] = {
        "clarence", "neil", "amy", "amy", "ketanji", "ketanji", "ketanji", "amy", "amy"
    };
    string p[5] = { "john", "sonia", "samuel", "elena", "neil" };
    string gg[4] = { "neil", "sonia", "amy", "elena" };
    string r[4] = { "nakul", "sana", "angad", "angad" };
 
    //declaring some arrays to be used for testing (of functions which don't modify arrays)
    
    
    assert(enumerate(h, 7, "john") == 2); //checking for multiple occurences
    assert(enumerate(h, 7, "") == 1); // checking for empty string
    assert(enumerate(h, 7, "brett") == 0); // checking for missing element
    assert(enumerate(h, 0, "john") == 0); // look at the first 0 elmts
    

    
    assert(enumerate(g, 0, "john") == 0); // output 0 for empty (unitialized) array
    assert(enumerate(g, 0, "") == 0); // output 0 for empty (unitialized) array
    assert(enumerate(g, 0, "brett") == 0); // output 0 for empty (unitialized) array
    assert(enumerate(g, 0, "john") == 0); // output 0 for empty (unitialized) array
    assert(enumerate(g, -1, "nakul") == -1); //error works for empty array
    

    
    assert(findMatch(d, 9, "ketanji") == 4); // mutliple occurences returns first
    assert(findMatch(d, 4, "ketanji") == -1); // not found when looking at first n elmts
    assert(findMatch(h, 7, "john") == 2); // checking different array to be sure
    assert(findMatch(h, 2, "john") == -1); // not found when looking at first n elmts
    assert(findMatch(g, 0, "nakul") == -1); // can't return a position if no elmts in array
    
    
    
    
    int bg = -999;
    int en = -999;
    assert(! findRun(h, 7, "nakul", bg, en) && bg == -999 && en == -999); // false if elmt not present
    assert(! findRun(h, -1, "nakul", bg, en) && bg == -999 && en == -999); // false if n <0
    assert(! findRun(d, 2, "amy", bg, en) && bg == -999 && en == -999); // only looks at first n elts
    assert(! findRun(d, 0, "clarence", bg, en) && bg == -999 && en == -999); // false because it won't be found in 0 elements
    assert(! findRun(d, 9, "samuel", bg, en) && bg == -999 && en == -999); // false if not found at all

    assert(findRun(h, 7, "amy", bg, en) && bg == 3 && en == 3); // checking that it finds first run
    assert(findRun(d, 9, "ketanji", bg, en) && bg == 4 && en == 6); // works for multiple consecutive
    assert(findRun(d, 4, "amy", bg, en) && bg == 2 && en == 3); // check with a shorter version of array (checking for some one-off error)
    assert(findRun(d, 3, "amy", bg, en) && bg == 2 && en == 2); // should say 2 and 2, not 2 and 3 because it's only checking the first 3 elements of the array
    assert(findRun(h, 7, "", bg, en) && bg == 4 && en == 4); // works for empty string as well
    assert(findRun(d, 9, "amy", bg, en) && bg == 2 && en == 3); // in spec
    assert(findRun(d, 9, "neil", bg, en) && bg == 1 && en == 1); // in spec
    assert(findRun(r, 4, "angad", bg, en) && bg == 2 && en == 3); // checking one-off error again
    assert(findRun(r, 3, "angad", bg, en) && bg == 2 && en == 2); // checking one-off error again
    

    assert(findMin(d, 9) == 2); //finds first occurence of the min
    assert(findMin(d, 2) == 0); // returns 0 as a position (no error)
    assert(findMin(h, 7) == 4); // empty string is the minimum
    assert(findMin(g, 0) == -1); // can't return a position for 0 elmts
    assert(findMin(p, 5) == 3); // extra check with different array
    
    string mte_1[4] = { "neil", "sonia", "amy", "elena" };
    assert(moveToEnd(mte_1, 0, 0) == -1); //can't find a position in a 0 array elmt
    assert(moveToEnd(mte_1, 1, 0) == 0); // with one element, it will always return 0
    assert(moveToEnd(mte_1, 4, -1) == -1); // position can't be negative
    assert(moveToEnd(mte_1, 4, 4) == -1); // position n doesn't exist in n elt array
    
    assert(moveToEnd(mte_1, 4, 1) == 1 && mte_1[1] == "amy" && mte_1[3] == "sonia"); // checking for proper functionality of moveToEnd for normal case
    assert(moveToEnd(mte_1, 0, 1) == -1); // checking of n = 0 error even when pos != 0
    
    string mtb_1[4] = { "elena", "amy", "sonia", "john" };
    
    assert(moveToBeginning(mtb_1, 0, 0) == -1); //can't find a position in a 0 array elmt
    assert(moveToBeginning(mtb_1, 1, 0) == 0); // with one element, it will always return 0
    assert(moveToBeginning(mtb_1, 4, -1) == -1); // position can't be negative
    assert(moveToBeginning(mtb_1, 4, 4) == -1); // position n doesn't exist in n elt array
    
    assert(moveToBeginning(mtb_1, 4, 2) == 2 && mtb_1[0] == "sonia" && mtb_1[2] == "amy"); // checking for proper functionality of moveToEnd for normal case
    
    
    
    assert(findDifference(h, 4, gg, 4) == 2); // normal functioning
    assert(findDifference(h, 2, gg, 2) == 2); // return length if equal until end
    assert(findDifference(h, 2, gg, 3) == 2); // return length if equal until end
    assert(findDifference(h, 3, gg, 3) == 2); // shortened array not equal to return length
    assert(findDifference(h, 0, gg, 0) == -1); // can't return a position for a zero elt array
    assert(findDifference(h, 0, gg, 1) == -1); // can't return a position for a zero elt array
    assert(findDifference(h, 5, p, 5) == 0); // returns 0 if first elmt is different
    
                                                        
    string dups1[4] = {"nakul", "arnav", "nakul", "nakul"};
    assert(removeDups(dups1, 4) == 3 && dups1[0] == "nakul" && dups1[1] == "arnav" && dups1[2] == "nakul"); // check normal functioning for dup elements occuring non-consecutively
    
    string dups2[10] = {"a", "b", "b", "c", "c", "c", "a", "b", "a", "a"};
    assert(removeDups(dups2, 10) == 6 && dups2[0] == "a" && dups2[1] == "b" && dups2[2] == "c" && dups2[3] == "a" && dups2[4] == "b" && dups2[5] == "a"); // works with complicated combinations of duplicate sequences as well
    
    string dups3[20] = {"1", "", "", "", "1", "2", "2"};
    assert(removeDups(dups3, 7) == 4 && dups3[0] == "1" && dups3[1] == "" && dups3[2] == "1" && dups3[3] == "2"); // works for the empty string as well
    
    string dups4[10] = {"", "", "", "", ""};
    assert(removeDups(dups4, 4) == 1 && dups4[0] == ""); // works with all elmts equal
    
    
    assert(removeDups(dups2, 0) == 0); // no elmts there so no elmts are dups so no elmts are removed so 0 elmts are retained
    assert(removeDups(dups2, -5) == -1); // error if n < 0
    
    

    
    
    
    string big[10] = { "elena", "john", "amy", "ketanji", "neil", "amy" };
    
    string little1[10] = { "john", "ketanji", "neil" };
    assert(subsequence(big, 6, little1, 3));  // returns true (from spec)
    string little2[10] = { "amy", "john" };
    assert(! subsequence(big, 6, little2, 2));  // returns false (from spec)
    string little3[10] = { "john", "amy", "amy" };
    assert(subsequence(big, 6, little3, 3));  // returns true (from spec)
    string little4[10] = { "john", "john", "amy" };
    assert(! subsequence(big, 6, little4, 3));  // returns false (from spec)
    assert(subsequence(big, 6, little4, 0));  // returns true (from spec)
    string rlittle[3] = {"nakul", "sana", "angad"};
    assert(subsequence(r, 4, rlittle, 3)); // normal functioning for my own example
    assert(subsequence(big, 0, little1, 0)); // a 0 length substring is a subsequence even of the 0 length array
    assert(! subsequence(big, 2, little1, 3)); // false if little is bigger than big
    for (int i = 0; i <= 6; i++) assert(subsequence(big, 6, big, i)); // checking that all subarrays are subsequences
    
    string big2[5] = {"a", "a", "a", "a", "b"};
    string little21[4] = {"a", "a", "a", "a"};
    string little22[5] = {"a", "a", "a", "a", "a"};
    
    assert(subsequence(big2, 5, little21, 4)); // checking for one-off errors
    assert(!subsequence(big2, 5, little22, 5)); // checking for one-off errors
    
    
    
    
        
    
    string x1[5] = { "amy", "elena", "elena", "ketanji", "samuel" };
    string y1[4] = { "clarence", "elena", "john", "sonia" };
    string z1[20];
    
    string result1[20] = {"amy",
        "clarence",
        "elena",
        "elena",
        "elena",
        "john",
        "ketanji",
        "samuel",
        "sonia"};
    
    for (int i = 0; i < makeMerger(x1, 5, y1, 4, z1, 20);i++){ // checking all elmts are as desired by creating a results array that it should match
        assert(z1[i] == result1[i]);
    }  // returns 9
    
    string x2[4] = { "john", "john", "samuel", "sonia" };
    string y2[4] = { "amy", "elena", "john", "ketanji" };
    string z2[10];
    assert(makeMerger(x2, 4, y2, 4, z2, 10) == 8 && z2[5] == "ketanji"); // returns the right number
    
//    for (int i = 0; i < 8; i++){
//        cout << z2[i] << endl;;
//    }
    
    string x3[4] = { "john", "john", "sonia", "samuel" };
    string y3[4] = { "amy", "elena", "john", "ketanji" };
    string z3[10];
    assert(makeMerger(x3, 4, y3, 4, z3, 10) == -1); // error because inputs not sorted
    
    string x4[4] = { "john", "john", "samuel", "sonia" };
    string y4[4] = { "amy", "elena", "john", "ketanji" };
    string z4[10];
    assert(makeMerger(x4, 4, y4, 4, z4, 7) == -1); // error because max is too small
    
    string x5[5] = {"1", "3", "5", "7", "9"};
    string y5[5] = {"2", "4", "6", "8", "9"};
    string z5[20];
    
    string result5[10] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "9"};
    assert(makeMerger(x5, 5, y5, 5, z5, 10) == 10); // works for numbers (easy to see order)
    
    for (int i = 0; i < 10; i++){
        assert(z5[i] == result5[i]); // works for numbers (easy to see order)
    }
    
    
    
    
    //unsure about whether 0 should return an error here or not.
    //current logic is spec says "or return n if no elements not less than divider" and since there are no elements at all in the array this is a vacuous truth. n is 0 so return 0.
    
    string sc[6] = { "john", "amy", "samuel", "elena", "sonia", "neil" };
    assert(divide(sc, 6, "ketanji") == 3);  // sorts correctly for an array of names (without the divider)
    assert(divide(sc, 0, "ketanji") == 0); // returns 0 for n = 0 but does not return an error

    
    string sc2[4] = { "john", "sonia", "amy", "neil" };
    assert(divide(sc2, 4, "neil") == 2 && sc2[2] == "neil");  // returns position of divider if it is present

    string sc3[6] = {"c", "c", "c", "c", "a", "b"};
    assert(divide(sc3, 6, "b") == 1); // works with repeats as well

    
    string sc4[7] = {"aanya", "nakul", "sana", "saachi", "anirudh", "shaurya", "mihir"};
    assert(divide(sc4, 7, "arnav") == 2); // dividing with a name not present
    assert(divide(sc4, 7, "tahaa") == 7); // dividing with a name not present but greater than all
    assert(divide(sc4, 7, "ronit") == 4); // dividing with a name not present in the middle
    assert(divide(sc4, 7, "nakul") == 3); // dividing with a name that is present
    
    cerr << "All tests passed" << endl;
    
    return 0;
}

int enumerate(const string a[], int n, string target){
    
    if (n < 0) return -1;
    
    int count = 0;
    for (int i = 0; i < n; i++){
        if (a[i] == target) count++; // create a loop to increment count for every elmt = target in the array
    }
    
    return count;
}

int findMatch(const string a[], int n, string target){
    if (n < 0) return -1;
    
    for (int i = 0; i < n; i++){
        if (a[i] == target) return i; // create a loop that returns the first occurence of target
    }
    
    return -1;
}

bool findRun(const string a[], int n, string target, int& begin, int& end){
    //if n is negative or no string is equal to target return false
    
    if (n < 0 || enumerate(a, n, target) == 0) return false;
    
    // repeatedly, if there is a match with target set beg to index, break out of the loop
    // set end = beg, increment through rest of the loop (use diff index) only if the next one is also target, increment end everytime it is the target
    
    int i;
    for (i = 0; i < n; i++){
        if (a[i] == target){
            begin = i;
            break;
        }
    }
    
    int j = begin; // if it doesn't enter the loop, end should stay the same as begin
    
    while (a[j+1] == target && j + 1 < n){ //second condition so that it does not go                                             outside the first n elements
        j++;
    }
    
    end = j;

    return true;
}


int findMin(const string a[], int n){
    
    if (n <= 0) return -1; // if there are zero elements in the array, can't return a position
    
    string min = a[0]; // initialize it to some element of the array
    for (int i = 0; i < n; i++){
        if (a[i] < min) min = a[i]; // update the min if we find a smaller element
    }
    
    return findMatch(a, n, min); // return the first position of the minimum
    
}

int moveToEnd(string a[], int n, int pos){
    
    if (n <= 0) return -1; // can't do anything to a certain position if array is empty
    
    if (pos < 0 || pos >= n) return -1; // checking for pos being out of range
    
    //temp = .[pos]
    // for pos = 3, take all elmts i = pos + 1 till <n, move them to i - 1, make the (n-1)th = temp
    string temp = a[pos];                                       // saving temp for last term
    for (int i = pos + 1; i < n; i++){                  // moving those after pos uptil last
        a[i-1] = a[i];                                  // to the left by one
    }
    a[n-1] = temp;                                  // assigning moved value to last one

    return pos;
    
}

int moveToBeginning(string a[], int n, int pos){
    
    if (n <= 0) return -1; // can't do anything to a certain position if array is empty
    
    if (pos < 0 || pos >= n) return -1; // checking for pos being out of range
    
    //temp = .[pos]
    // for pos = 3, take all elmts i = pos + 1 till <n, move them to i - 1, make the (n-1)th = temp
    string temp = a[pos];                                       // saving temp for last term
    for (int i = pos - 1; i >= 0; i--){               // moving those before pos uptil 0th
        a[i+1] = a[i];                                  // to the right by one
    }
    a[0] = temp;                                  // assigning moved value to first one

    return pos;
}

/*
 
 *** trying out moveToBeginning and seeing whether it works ***
 
  0 1 2 3 4 pos 6 7 8 9 n
pos 0 1 2 3 4   6 7 8 9 n
 
 */

int findDifference(const string a1[], int n1, const string a2[], int n2){
    if (n1 <= 0 || n2 <= 0) return -1;
    
    int n;
    
    if (n1 <= n2) n = n1;
    else n = n2; // set n to the smaller array length
    
    for (int i = 0; i < n; i++){
        if (a1[i] != a2[i]) return i;
    }
    
    return n; // if no difference, return the length of the (smaller) array
    
}

int removeDups(string a[], int n){
 
    if (n < 0) return -1;
        
    int movedToEnd = 0;
    
    int n0 = n; // since n is changed in the loop, create var to store initial value
    
    for (int j = 0; j < n; j++){
        for (int i = j + 1; i < n; i++){ // decrement n because we don't want to look through discarded dups
            if (a[i] == a[j]){ // if a dup is found, move the next few to the end
                moveToEnd(a, n0, i);
                movedToEnd ++; // temp var which was created for other implementation, now redundant
                
                i--;
                n--;
                
            } else break; // else break out and check dup for next element
        }
    }
    
    return n; // total number of elmts - those moved to end (dups)
}


bool subsequence(const string a1[], int n1, const string a2[], int n2){
    
    if (n1 < 0 || n2 < 0 || n1 < n2) return false;
    
    int last_index = -1;
    
    for (int j = 0; j < n2; j++){
        bool isThere = false;
        for (int i = last_index + 1; i < n1; i++){
            if (a1[i] == a2[j]){
                last_index = i; // created a last index variable so that order is preserved
                isThere = true; // if the required element is found in array, break out and go to the next element to be found
                break;
            }
        } if (!isThere) return false; // return false if for any elmts in the subsequence, there is no occurence found in the array
        
    }
    
    return true;
}


int makeMerger(const string a1[], int n1, const string a2[], int n2,
               string result[], int max){ // basically modified merge sort algorithm
    
    
    // compare the two elements, add the smaller one to result, increment smaller's index
    // if either of the indices exceed n1/n2 -1, then break the loop and add the rest of the remaining loops elements to result
    
    if (n1 < 0 || n2 < 0) return -1;
    
    for (int i = 0; i < n1 - 1; i++){
        if (a1[i+1] < a1[i]) return -1;
    }
    
    for (int j = 0; j < n2 - 1; j++){
        if (a2[j+1] < a2[j]) return -1;
    }
    
    
    int i = 0;
    int j = 0;
    int k = 0;
    

    while(i < n1 && j < n2){
        if (k >= max) return -1;
        if (a1[i] <= a2[j]){
            result[k] = a1[i];
            i++;

        }
        else {
            result[k] = a2[j];
            j++;
            
        }
        k++;
    }
    // reaches here when either i reaches n1 or i reaches n2
    
    if (i == n1){
        // add rest of a2 to result
        for (int p = j; p < n2; p++){
            if (k >= max) return -1;
            result[k] = a2[p];
            k++;
        }
    }
    
    else if (j == n2){
        // add rest of n1 to result
        for (int q = i; q < n1; q++){
            if (k >= max) return -1;
            result[k] = a1[q];
            k++;
        }
    }
    
    return k;
}

int divide(string a[], int n, string divider){
    
    if (n < 0) return -1;
    
    for(int i = 0; i < n; i++) if (a[i] == divider) moveToBeginning(a, n, i); // if divider is present, move it to the beginning
    
    for(int i = 0; i < n; i++) if (a[i] < divider) moveToBeginning(a, n, i); // move elmts less than the divider to before the dividers
    
    for (int i = 0; i < n; i++) if (a[i] >= divider) return i; // return the first elmt greater than or equal to the divider
    
    return n;
}

// EXTRA COMMENTS WRITTEN DURING DEVELOPMENT

// Working out removeDups()

/*
 
 [7] n1, n2, n3, a1, a2, n4, n5,  (WE ONLY CARE ABOUT 0 to 5 HERE)
 
 for j 0 to n - 1
    for i = j+1 to n - 1
    if a[i] == a[j]
        moveToEnd(a, n, i)
    else break                          (other future dups will be counted)
 n = 7
 j = 0
 i = 1
 
 a[1] == a[0] so move a[1] to the end
 n1, n3, a1, a2, n3, n4, n2
 decrement i to check again, decrement n to reduce search length so i = 0, n = 6
 
 n = 6
 i = 1
 
 a[1] == a[0] again so move a[1] to the end of 6 elt array
 n1, a1, a2, n3, n4, n3, n2
 i = 0, n = 5
 
 n = 5
 i = 1
 a[1] != a[0] now so break
 
 j = 1
 i = 2
 
 a[2] == a[1] so move a[2] to the end of 5 elmt array
 n1, a1, n3, n4, a2, n3, n2, i = 1, n = 4
 
 n = 4
 i = 2
 
 a[2] != a[1] so break
 
 j = 2
 i = 3
 
 a[3] == a[2] so move a[3] to the end of 4 elt array
 n1, a1, n3, n4, a2, n3, n2, i = 2, n = 3
 
 n = 3
 i = 3
 
 exits loop
 j = 3, exits loop

 
 */
