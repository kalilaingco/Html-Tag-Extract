/*
 ============================================================================
 Name        : KIngcoHTMLSrcList.c
 Author      : kalila Ingco
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int countSrc(char *htmlDocCat);
void tagName(char *htmlDocCat);
void url(char *htmlDocCat);

int main(void) {
	setvbuf(stdout, NULL, _IONBF, 0);

	printf("URL:/ \n"); // prints "URL:/ " to standard output

	//gets the URL of the HTML doc
	char temp[BUFSIZ]; // holds the string of url before concat
	char curl[BUFSIZ] = "curl -s "; // holds curl
	char *ptemp = curl; // pointer that points at curl
	char htmlUrl[BUFSIZ]; // array that holds url that is concat
	char htmlDoc[260000]; // array that holds html src info thats from url doc
	FILE *pInFile; // opens file
	fgets(temp, BUFSIZ, stdin); // gets url from user
	ptemp = strcat(curl, temp); // function to concatenate string
	strncpy(htmlUrl, ptemp, BUFSIZ); // copies concatenated string into new array
	htmlUrl[strlen(htmlDoc) - 1] = '\0'; // gets rid of /0
	pInFile = popen(htmlUrl, "r"); // opens file from url provided

	//loop that will concatenate to make big string containing all lines of the HTML source code
	char htmlDocCat[260000]; // array to hold new concatenated string
	while (!feof(pInFile)) { // loop
		fgets(htmlDoc, 260000, pInFile); //gets first string from html src doc
		strcat(htmlDocCat, htmlDoc); // concatenates the lines to form one big string
	}
	pclose(pInFile); // close file
	// gets command to execute
	char command[BUFSIZ];
	while (command[0] != 'q') {
		printf("Ready\n");
		fgets(command, BUFSIZ, stdin);
		switch (command[0]) {
		case 'c':
			printf("%d\n", countSrc(htmlDocCat));
			break;
		case 't':
			tagName(htmlDocCat);
			break;
		case 'u':
			url(htmlDocCat);
			break;
		case 'q':
			break;
		default:
			printf("not valid");
		}
	}
	printf("Complete\n");
	return EXIT_SUCCESS;

}

int countSrc(char *htmlDocCat) {
	int countSrc = 0;  // counts # of src attributes found
	char *pSrc = "src=\""; // pointer that holds string to find Src took out a space here
	char *pFindSrc = htmlDocCat; // pointer to find the src tag
	pFindSrc = strstr(htmlDocCat, pSrc); // looks for instance of src=\ inside htmldoccat
	while (pFindSrc != NULL) { // loops until end of string
		if (isspace(*(pFindSrc - 1))) {
				countSrc++; // increments count
				}
		pFindSrc = pFindSrc + 1; // move pointer to next character
		pFindSrc = strstr(pFindSrc, pSrc); // finds next instance of src after moved pointer
	}
	return countSrc;

}

void tagName(char *htmlDocCat) {

	char *pSrc = "src=\""; // pointer that holds string to find Src / got rid of space here
	char *pFindSrc; // pointer to find the src tag
	pFindSrc = strstr(htmlDocCat, pSrc);
	while (pFindSrc != NULL) { // loops until end of string
		if (isspace(*(pFindSrc - 1))) {
			char *pSpace = pFindSrc;
			while (*pSpace != '<') {
				pSpace--;
			}
			pSpace = pSpace + 1;

			while (!(isspace(*pSpace))) {
				printf("%c", *pSpace);
				pSpace++;
			}
			printf("\n");
		}
		pFindSrc++;
		pFindSrc = strstr(pFindSrc, pSrc);
	}
}

void url(char *htmlDocCat) {
	char *pSrc = "src=\""; // pointer that holds string to find Src
	char *pFindSrc; // pointer to find the src tag
	pFindSrc = strstr(htmlDocCat, pSrc);
	while (pFindSrc != NULL) {
		if (isspace(*(pFindSrc - 1))) {
			char *pQ1 = pFindSrc; // starts pQ1 pointer at pFindSrc
			while (*pQ1 != '\"') {
				pQ1++;
			}
			pQ1++;

			while (*pQ1 != '\"') {
				printf("%c", *pQ1);
				pQ1++;
			}
			printf("\n");
		}
		pFindSrc++;
		pFindSrc = strstr(pFindSrc, pSrc);
	}
}

