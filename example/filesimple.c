#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../jsmn.h"

/*
 * A small example of jsmn parsing when JSON structure is known and number of
 * tokens is predictable.
 */

static const char *JSON_STRING =
	"{\"user\": \"johndoe\", \"admin\": false, \"uid\": 1000,\n  "
	"\"groups\": [\"users\", \"wheel\", \"audio\", \"video\"]}";

static int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
	if (tok->type == JSMN_STRING && (int) strlen(s) == tok->end - tok->start &&
			strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
		return 0;
	}
	return -1;
}

char* readJSONFile(){
	char* JSON_STRING;
	char oneline[255];
	int count = 0;

	FILE *fp;
	fp = fopen("data.json", "r");

	while(1){
		fgets(oneline, 255, fp);
		if(feof(fp)) break;
		count = count + strlen(oneline) + 1;
		JSON_STRING = (char*)realloc(JSON_STRING, count*sizeof(char));
		strcat(JSON_STRING, oneline);
	}
	return JSON_STRING;
}

// Example 4
// void jsonNameList(char *jsonstr, jsmntok_t *t, int tokcount){
// 	int num = 1;
// 	int i = 0;
//
// 	printf("-----Name List-----\n");
//
// 	while(i < tokcount){
// 		if(t[i].type == JSMN_STRING && t[i].size >= 1){
// 			printf("[NAME%2d] %.*s\n", num, t[i].end - t[i].start, jsonstr + t[i].start);
// 			num++;
// 		}
// 		i++;
// 		}
// 	}

// Example 5
void jsonNameList(char *jsonstr, jsmntok_t *t, int tokcount, int *nameTokIndex){
	int num = 1;
	int i = 0;
	while(i < tokcount){
		if(t[i].type == JSMN_STRING && t[i].size >= 1){
			nameTokIndex[num] = i;
			num++;
		}
		i++;
	}
	nameTokIndex[0]= num-1;
	printf("size = %d\n", nameTokIndex[0]);
}
void printNameList(char *jsonstr, jsmntok_t *t, int *nameTokIndex){
	int i = 1;
	printf("-----Name List-----\n");
	while(i <= nameTokIndex[0]){
		printf("[NAME%2d] %.*s\n", i, t[nameTokIndex[i]].end - t[nameTokIndex[i]].start, jsonstr + t[nameTokIndex[i]].start);
		i++;
	}
}
int main() {
	char* string;
	char* jsonstr;

	string = (char*)malloc(sizeof(readJSONFile())+1);
	string = readJSONFile();
	//puts(string);

	int i;
	int r;
	int array[100];
	jsmn_parser p;
	jsmntok_t t[128]; /* We expect no more than 128 tokens */

	jsmn_init(&p);
	r = jsmn_parse(&p, string, strlen(string), t, sizeof(t)/sizeof(t[0]));
	if (r < 0) {
		printf("Failed to parse JSON: %d\n", r);
		return 1;
	}

	/* Assume the top-level element is an object */
	if (r < 1 || t[0].type != JSMN_OBJECT) {
		printf("Object expected\n");
		return 1;
	}

	// Example 3
	//
	// /* Loop over all keys of the root object */
	// for (i = 1; i < r; i++) {
	// 	if (jsoneq(string, &t[i], "name") == 0) {
	// 		/* We may use strndup() to fetch string value */
	// 		printf("- name: %.*s\n", t[i+1].end-t[i+1].start,
	// 				string + t[i+1].start);
	// 		i++;
	// 	} else if (jsoneq(string, &t[i], "keywords") == 0) {
	// 		/* We may additionally check if the value is either "true" or "false" */
	// 		printf("- keywords: %.*s\n", t[i+1].end-t[i+1].start,
	// 				string + t[i+1].start);
	// 		i++;
	// 	} else if (jsoneq(string, &t[i], "description") == 0) {
	// 		/* We may want to do strtol() here to get numeric value */
	// 		printf("- UID: %.*s\n", t[i+1].end-t[i+1].start,
	// 				string + t[i+1].start);
	// 		i++;
	// 	} else if (jsoneq(string, &t[i], "examples") == 0) {
	// 		int j;
	// 		printf("- exsmples:\n");
	// 		if (t[i+1].type != JSMN_ARRAY) {
	// 			continue; /* We expect groups to be an array of strings */
	// 		}
	// 		for (j = 0; j < t[i+1].size; j++) {
	// 			jsmntok_t *g = &t[i+j+2];
	// 			printf("  * %.*s\n", g->end - g->start, string + g->start);
	// 		}
	// 		i += t[i+1].size + 1;
	// 	}
	// }

	// Example 4
	//jsonNameList(string, t, r);

	//Example 5
	// int count = jsonNameList(string, t, r, array);
	// printNameList(string, t, array, count);

	int nameTokIndex[100];
	jsonNameList(string, t, r, nameTokIndex);
	printNameList(string, t, nameTokIndex);

	return EXIT_SUCCESS;
}
