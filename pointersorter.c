#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//Given two strings consiting of only characters, stringComp compares them
//character by character and returns the following:
// 1 if str1 < str2 - str1 comes before str2
// 0 if str1 = str2 - str1 is the same as str2
// 2 if str1 > str2 - str1 comes after str2
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

//test comment
int main(int argc, char ** argv){
        if(argc != 3)
                return -1;
        char * str1 = argv[1];
        char * str2 = argv[2];

        int x = stringComp(str1,str2);

        if(x == 2)
                printf("%s\n%s\n", str2, str1);
        else
                printf("%s\n%s\n", str1, str2);

        return 0;
}
