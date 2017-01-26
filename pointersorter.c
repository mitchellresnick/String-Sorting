#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*
 * Function: getNextToken
 * --------------------
 * starts at the given index and gives the next consecutive group of letters
 * and increments the inputPosition pointer accordingly.
 *
 *  inputString: pointer to the inputString(probably argv[1])
 *  analChar: the number of analyzed characters. Used for pointer arithmatic on
 *            inputString after the function completes.
 *
 *  returns: the next token
 */
char* getNextToken (char* inputString, int* analChar){
        //first we have to strip any non-alpha character from the begining of the token
        while(isalpha(*inputString) == 0) {
                // printf("inputString: %c\n", inputString[]);
                //check for a null byte
                if (*inputString == '\0') {
                        return NULL;
                }
                (*analChar)++;
                inputString++;
        }

        //get the size of the token
        int tokenSize = 0;
        while(isalpha(inputString[tokenSize]) != 0) {
                if (inputString[tokenSize] == '\0') {
                        return NULL;
                }
                tokenSize++;
                (*analChar)++;
        }

        //create your return char*
        char* returnToken = malloc((tokenSize+1)*sizeof(char));
        returnToken[tokenSize] = '\0';

        //copy n characters of the inputString where n is tokenSize
        strncpy(returnToken, inputString, (size_t)tokenSize);
        return returnToken;
}

/*Given two strings consiting of only characters, stringComp compares them
 * character by character and returns the following:
 * 1 if str1 < str2 - str1 comes before str2
 * 0 if str1 = str2 - str1 is the same as str2
 * 2 if str1 > str2 - str1 comes after str2 */
int stringComp(char * str1, char * str2){
        while(1 == 1) {
                //End method if one or both are done
                if(*str1 == '\0') {
                        if(*str2 == '\0')
                                return 0; //The same string
                        return 1; //Identical, except str2 is longer
                }

                if(*str2 == '\0')
                        return 2; //Identical, except str1 is longer
                //Compare the two current characters
                if(isupper(*str1)) { //str1 is upper case
                        char s1 = *str1 + 32; //effectively makes it lowercase

                        if(isupper(*str2)) { //Both are upper case
                                char s2 = *str2 + 32; //effectively makes it lowercase

                                if(s1 < s2)
                                        return 1;
                                if(s1 > s2)
                                        return 2;
                        } else { //Just str1 is upper case
                                return (s1 <= *str2) ? 1 : 2;
                        }
                } else if(isupper(*str2)) {//str2 is upper but str1 is not
                        return (*str2 + 32 <= *str1) ? 2 : 1;

                } else { //both are lower case
                        if(*str1 < *str2)
                                return 1;
                        if(*str2 < *str1)
                                return 2;
                }

                str1++;
                str2++;
        }
}

int main(int argc, char ** argv){
        if(argc != 2) {
                fprintf(stderr, "ERROR: Impoper number of arguments.\n");
                exit(1);
        }

        char ** tokens = malloc(10*sizeof(char*)); //Stores an array of strings
        if(tokens == NULL) { //Checks for failure
                fprintf(stderr, "ERROR: Malloc failure.\n");
                exit(1);
        }

        int tokenNumber = 0; //Keeps track of the number of tokens in char ** tokens
        int skip = 0; //Tells original sting where to begin looking for next token
        char * tokenStream = argv[1]; //Creates new pointer to parse argv[1]

        tokens[0] = getNextToken(tokenStream, &skip); //Places first token in first pos
        if(*tokens == NULL) { //throw error if no token was found
                fprintf(stderr, "ERROR: No token was found.\n");
                exit(1);
        }
        tokenStream += skip; //Skips characters already parsed

        while(tokens[tokenNumber] != NULL) { //While a token was found
                tokenNumber++; //Count the previous token (this is also the potential
                // position of the next token)

                if(tokenNumber % 10 == 0) { //If the current 10 char*s are used, malloc 10 more
                        if(realloc(tokens, (tokenNumber + 10)*sizeof(char*)) == NULL) { //Error check
                                fprintf(stderr, "ERROR: Realloc failure.\n");
                                exit(1);
                        }
                }

                skip = 0; //Reset skip
                tokens[tokenNumber] = getNextToken(tokenStream, &skip); //Potential next token
                tokenStream += skip; //Skips characters already parsed
        }

        //Print and then free each token
        int i = 0;
        for(; i < tokenNumber; i++) {
                printf("Token: %s\n", tokens[i]);
                free(tokens[i]);
        }
        free(tokens); //Free the pointer array once done

        return 0;
}
