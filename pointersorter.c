#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*
 * Struct: Node
 * --------------------
 * Single node of a linked list
 *
 * token: the token to be stored in the node
 * next: the link (or pointer) to the next node
 */
typedef struct node {
        char* token;
        struct node * next;
} node_t;

/*
 * Function: getNextToken
 * --------------------
 * starts at the given index and gives the next consecutive group of letters
 * and increments the inputPosition pointer accordingly.
 *
 *  inputString: pointer to the inputString(probably argv[1])
 *  analChar: the number of analyzed characters. Used for pointer arithmetic on
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
                                return 1;
                        }
                } else if(isupper(*str2)) {//str2 is upper but str1 is not
                        return 2;

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

/*
 * Function: createNode
 * --------------------
 * creates a node that can be used in a linked list
 *
 * token: the token that is to be placed
 *
 *
 *  returns: pointer to the node
 */
node_t * createNode(char* token){
        node_t * newNode = malloc(sizeof(node_t)); //allocates too much space, need to fix second sizeof

        if (newNode == NULL) {
                fprintf(stderr, "Malloc failed.\n");
        }

        (*newNode).next = NULL;
        (*newNode).token = token;

        return newNode;
}

/*
 * Function: placeNode
 * --------------------
 * places the node in teh linked list
 *
 * node: the node to be placed in the LL
 * linkedList: pointer to the head of the list
 *
 *  returns: pointer to the node
 */
node_t* placeNode (node_t* ins, node_t* front){
        if(front == NULL)
                return ins;

        if(stringComp((*ins).token,(*front).token) != 2) {
                (*ins).next = front;
                return ins;
        }

        node_t * ptr = (*front).next;
        node_t * prv = front;

        while(ptr != NULL) {
                if(stringComp((*ins).token,(*ptr).token) != 2) {
                        (*ins).next = ptr;
                        (*prv).next = ins;

                        return front;
                }
                prv = ptr;
                ptr = (*ptr).next;
        }

        (*prv).next = ins;
        return front;
}

void printLL(node_t* ll){ //WORKS
        node_t* temp = ll;
        while (temp != NULL) {
                printf("%s\n", temp->token);
                temp = temp->next;
        }
}

void freeLL(node_t * front){
  node_t * temp;
  while(front != NULL){
    free((*front).token);
    temp = front;
    front = (*front).next;
    free(temp);
  }
}

int main(int argc, char ** argv){
        if(argc != 2) {
                fprintf(stderr, "ERROR: Impoper number of arguments.\n");
                exit(1);
        }

        int skip = 0;
        char * tokenStream = argv[1];

        char * token = getNextToken(tokenStream, &skip);
        tokenStream += skip;

        if(token == NULL) {
                fprintf(stderr, "ERROR: No valid token in stream.\n");
                exit(1);
        }

        node_t * front = placeNode(createNode(token), NULL);

        while(token != NULL) {
                skip = 0;
                token = getNextToken(tokenStream, &skip);
                tokenStream += skip;

                if(token != NULL)
                        front = placeNode(createNode(token), front);
        }

        printLL(front);

        freeLL(front);

        return 0;
}
