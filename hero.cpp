//
//  main.cpp
//  Project_3
//
//  Created by Nakul Khambhati on 4/20/22.
//


#include <iostream>
#include <string>
#include <cctype>
#include <cassert>

using namespace std;

bool hasProperSyntax(string tune);

bool isColor(char c);

int countSlashes(string substring);

int convertTune(string tune, string& instructions, int& badBeat);

int main() {

    assert(hasProperSyntax("G/g/R/r/Y/y/B/b/O/o/")); // checking all colors
    assert(hasProperSyntax("")); // no beats
    assert(hasProperSyntax("////")); // empty beats
    assert(hasProperSyntax("g3///")); // color followed by correct number
    assert(hasProperSyntax("g9///")); // color followed by incorrect number
    assert(hasProperSyntax("g03/")); // color followed by a two digit number
    assert(hasProperSyntax("g0/")); // 0 is syntactically correct, just not convertible
    assert(hasProperSyntax("g0/g1/g01/g00//g9//Y3////")); // checking all of the above together
    
    
    assert( ! hasProperSyntax("g/z//")); // checking for a letter out of color range
    assert( ! hasProperSyntax("r")); // checking for a color without a slash
    assert( ! hasProperSyntax("r/ g/")); // space should cause an error
    assert( ! hasProperSyntax("Password:Nakk*123%")); //checking random stuff
    assert( ! hasProperSyntax("r100/")); // checking 3 digits
    
    string instrs;
    int badb;
    badb = -999;  // so we can detect whether this gets changed
    assert(convertTune("", instrs, badb) == 0  &&  instrs == ""  &&  badb == -999); // empty string returns empty string
    assert(convertTune("/", instrs, badb) == 0  &&  instrs == "x"  &&  badb == -999); // slash returns x
    assert(convertTune("////", instrs, badb) == 0  &&  instrs == "xxxx"  &&  badb == -999); // empty slashes return x's
    assert(convertTune("G/g/R/r/Y/y/B/b/O/o/", instrs, badb) == 0  &&  instrs == "ggrryybboo"  &&  badb == -999); // checking all colors
    assert(convertTune("g3///", instrs, badb) == 0  &&  instrs == "GGG"  &&  badb == -999); // sustained note works correctly
    assert(convertTune("G/", instrs, badb) == 0  &&  instrs == "g"  &&  badb == -999); // upper goes to lower
    assert(convertTune("g03///", instrs, badb) == 0  &&  instrs == "GGG"  &&  badb == -999); // works for 2 digits
    assert(convertTune("g11///////////", instrs, badb) == 0  &&  instrs == "GGGGGGGGGGG"  &&  badb == -999); // works for big 2 digit numbers as well
    assert(convertTune("g02//Y2//o///", instrs, badb) == 0  &&  instrs == "GGYYoxx"  &&  badb == -999); // sustained notes along with empty beats
    assert(convertTune("r10///////////y03///O/", instrs, badb) == 0  &&  instrs == "RRRRRRRRRRxYYYo"  &&  badb == -999); // a lot of random things, checking for any off-by-one errors
    assert(convertTune("r//y/g3///o/", instrs, badb) == 0  &&  instrs == "rxyGGGo"  &&  badb == -999); // checking the last example from the spec
    
    instrs = "WOW";  // so we can detect whether this gets changed
    badb = -999;  // so we can detect whether this gets changed
    assert(convertTune("r", instrs, badb) == 1  &&  instrs == "WOW"  &&  badb == -999); // something syntactically incorrect returns 1, leaves instrs and badb unchanged
    assert(convertTune("o/r3//y/", instrs, badb) == 2  &&  instrs == "WOW"  &&  badb == 4); // non-slash in a sustained note
    assert(convertTune("o/r03//y/", instrs, badb) == 2  &&  instrs == "WOW"  &&  badb == 4); // non-slash in a sustained note
    assert(convertTune("r0/", instrs, badb) == 3  &&  instrs == "WOW"  &&  badb == 0); // not convertible if the digit is 0,1,00,01, badbeat returns one's digit
    assert(convertTune("r1/", instrs, badb) == 3  &&  instrs == "WOW"  &&  badb == 1); // not convertible if the digit is 0,1,00,01, badbeat returns one's digit
    assert(convertTune("r00/", instrs, badb) == 3  &&  instrs == "WOW"  &&  badb == 0); // not convertible if the digit is 0,1,00,01, badbeat returns one's digit
    assert(convertTune("r01/", instrs, badb) == 3  &&  instrs == "WOW"  &&  badb == 1); // not convertible if the digit is 0,1,00,01, badbeat returns one's digit
    assert(convertTune("r3//", instrs, badb) == 4  &&  instrs == "WOW"  &&  badb == 3); // ends prematurely, add num(slashes) + 1
    assert(convertTune("r03//", instrs, badb) == 4  &&  instrs == "WOW"  &&  badb == 3); // ends prematurely, add num(slashes) + 1
    assert(convertTune("r03//Y1//", instrs, badb) == 2  &&  instrs == "WOW"  &&  badb == 3); // returns the leftmost error
    

    cerr << "All tests succeeded" << endl;
}

bool isColor(char c){ //checking that a character is a color, usually implemented for each char in tune
    
    char arr[10] = {'G', 'g', 'R', 'r', 'Y', 'y', 'B', 'b', 'O', 'o'};
    
    for (int i = 0; i < 10; i++){
        if (c==arr[i]){
            return true;
        }
    } return false;
}

int countSlashes(string substring){ //counting the number of slashes in a string, used to set badBeat
    int count = 0;
    for (int i = 0; i < substring.size(); i++){
        if (substring[i] == '/'){
            count ++;
        }
    }
    return count;
}

bool hasProperSyntax(string tune){ //checking syntax as defined by the spec
    
    if (tune == ""){
        return true;
    }
    // if not empty
    // must either be a slash
    // or a color followed by a slash
                        //    or a digit
                        
                        //         or two digits
                            
                                
    
    int i = 0;
    while (i < tune.size()){
        if (!(isColor(tune[i]) || tune[i] == '/' || isdigit(tune[i]))){
            return false;
        }
        if (isColor(tune[i])){
            if (!(isdigit(tune[i+1]) || tune[i+1] == '/')){
                return false;
            }
        }
        
        if (isdigit(tune[i])){
            
            if (!isdigit(tune[i+1])){ // if there is only 1 digit
                
                if (tune[i+1] != '/'){
                    return false;
                }
            }
            
            if (isdigit(tune[i+1])){ // if there are 2 digits
                if (tune[i+2] != '/'){
                    return false;
                } if (isdigit(tune[i+2])) return false; // return false if 3 digits are entered
            }
        }
        
        i++;
        }
    
    return true;
}

int convertTune(string tune, string& instructions, int& badBeat){
    
                    
    // not syntactically correct, return 1
    if (!hasProperSyntax(tune)){
        return 1;
    }
    
    int i = 0;
    while (i < tune.size()){
        
        if (isdigit(tune[i])){ // try to merge code for      (didn't end up doing this)                                1 and 2 digit situations
            //ideas: create an if statement:
                // if 2 digits:int num = 10*(tune[i] - '0') + (tune[i+1] - '0');
            //                 i++ ;
            //      if 1 digit: int num = (tune[i] - '0');
            
            if (!isdigit(tune[i+1])){ // if there is only 1 digit
                
                if (tune[i] - '0' == 0 || tune[i] - '0' == 1){
                    badBeat = tune[i] - '0';
                    return 3;
                } // checking for the number being 0 or 1, return 3
                
                // if at least those many more strings don't exist, return 4
                if ((tune.size() - i - 1)<(tune[i] - '0')){
                    // but only return 4 if all the remaining chars are slashes, (cuz otherwise we need to return 2)
                    bool allSlashes = true;
                    for (int j = i+1; j < tune.size(); j++){
                        if (tune[j] != '/'){
                             allSlashes = false;
                        }
                    } if (allSlashes){
                        badBeat = countSlashes(tune) + 1;
                        return 4;
                    }
                }
                // if any of them is not a slashes, return 2
                
                for (int j = i+1; j < i + 1 + (tune[i] - '0'); j++){
                    if (tune[j] != '/'){
                        badBeat = countSlashes(tune.substr(0,j)) + 1;
                        return 2;
                    }
                }
            }
            
            if (isdigit(tune[i+1])){ // if there are 2 digits (lots of redundant reusage)
                
                if (((tune[i] - '0' == 0) && (tune[i+1] - '0' == 0)) || ((tune[i] - '0' == 0) && (tune[i+1] - '0' == 1))){
                    badBeat = tune[i+1] - '0';
                    return 3;
                } // checking for the number being 00 or 01, return 3
                
                int num = 10*(tune[i] - '0') + (tune[i+1] - '0');
                i++ ;
                
                // if at least those many more strings don't exist, return 4
                if ((tune.size() - i - 1)<num){
                    // but only return 4 if all the remaining chars are slashes, (cuz otherwise we need to return 2)
                    bool allSlashes = true;
                    for (int j = i+1; j < tune.size(); j++){
                        if (tune[j] != '/'){
                             allSlashes = false;
                        }
                    } if (allSlashes){
                        badBeat = countSlashes(tune) + 1;
                        return 4;
                    }
                }
                // if any of them is not a slash, return 2
                
                for (int j = i+1; j < i + 1 + num; j++){
                    if (tune[j] != '/'){
                        badBeat = countSlashes(tune.substr(0,j)) + 1;
                        return 2;
                    }
                }
            }
        }
        
        i++;
        }
    
    
    /* LOGIC MIND MAP FOR MAIN CONVERSION [implementation is slightly different as code for second digit has been shortened :) ]
     
     if tune[i] is a slash (in isolation) then add an x
     
i    if tune[i] is a color
i+1        if tune[i+1] is slash: add tune[i] (lower) to instructions
                             increment i by 1
i+1        if tune[i+1] is number
i+2            if tune[i+2] is not number:
                    define int amt = tune[i+1] - '0'
                    add amt # of tune[i] (upper) to instructions
                    increment i by amt + 2
i+2            if tune[i+2] is number:
                    define int amt = 10*(tune[i+1] - '0') + (tune[i+2] - '0')
                    add amt # of tune[i] (upper) to instructions
                    increment i by amt + 3
     
     */
    
    instructions = "";
    
    i = 0; //if it survived the error cases, i must have some value which we wanna refresh
    while (i < tune.size()){
        
        if (tune[i] == '/'){ // if its a slash in isolation then add an x
            instructions += 'x';
            i++;
        }
        
        if (isColor(tune[i])){
            if (tune[i+1] == '/'){ // if a color is followed by a slash, add the color to instructions and increment i by 2
                instructions += tolower(tune[i]);
                i += 2;
                continue;
            }
            
            if (isdigit(tune[i+1])){ // if color is followed by a digit, first check if its one or two and then define amt (conv of digits to int) accordingly
                    
                int amt;
                bool hasTwoDigits;
                if (!isdigit(tune[i+2])){
                    amt = tune[i+1] - '0';
                    hasTwoDigits = false;
                }
                else {
                    amt = 10*(tune[i+1] - '0') + (tune[i+2] - '0');
                    hasTwoDigits = true;
                }
                
                for (int j = 0; j < amt; j++){ // add amount number of colors to instructions and incremenet accordingly
                    instructions += toupper(tune[i]);
                }
                
                i += 2 + amt;
                if (hasTwoDigits) i++;

                }
            }
        }
    
    return 0;
}


