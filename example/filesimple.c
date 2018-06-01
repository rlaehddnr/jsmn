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
// void jsonNameList(char *jsonstr, jsmntok_t *t, int tokcount, int *nameTokIndex){
// 	int num = 1;
// 	int i = 0;
// 	while(i < tokcount){
// 		if(t[i].type == JSMN_STRING && t[i].size >= 1){
// 			nameTokIndex[num] = i;
// 			num++;
// 		}
// 		i++;
// 	}
// 	nameTokIndex[0]= num-1;
// }
// void printNameList(char *jsonstr, jsmntok_t *t, int *nameTokIndex){
// 	int i = 1;
// 	printf("-----Name List-----\n");
// 	while(i <= nameTokIndex[0]){
// 		printf("[NAME%2d] %.*s\n", i, t[nameTokIndex[i]].end - t[nameTokIndex[i]].start, jsonstr + t[nameTokIndex[i]].start);
// 		i++;
// 	}
// }

// Example 6
// void jsonNameList(char *jsonstr, jsmntok_t *t, int tokcount, int *nameTokIndex){
// 	int num = 1;
// 	int i = 0;
// 	while(i < tokcount){
// 		if(t[i].type == JSMN_STRING && t[i].size >= 1){
// 			nameTokIndex[num] = i;
// 			num++;
// 		}
// 		i++;
// 	}
// 	nameTokIndex[0] = num - 1;
// }
// void selectNameList(char *jsonstr, jsmntok_t *t, int *nameTokIndex){
// 	while(1){
// 		int number;
// 		int valueTok;
//
// 		printf("Select Name's no (exit : 0) >> ");
// 		scanf("%d", &number);
// 		if(number == 0)
// 			break;		//exit
// 		if(number <= nameTokIndex[0] - 1){
// 		int index = number + 1;
// 		printf("[NAME%2d] %.*s\n", number , t[nameTokIndex[index]].end - t[nameTokIndex[index]].start, jsonstr + t[nameTokIndex[index]].start);
//
//
// 			valueTok = nameTokIndex[index] + 1;
// 			printf("%.*s\n", t[valueTok].end - t[valueTok].start, jsonstr + t[valueTok].start);
// 		}
// 		else
// 			printf("No contents, Max indext is %d\n",nameTokIndex[0] - 1);
//
// 	}
// }

// Example 7
// void jsonNameList(char *jsonstr, jsmntok_t *t, int tokcount, int *nameTokIndex){
// 	int num = 1;
// 	int i = 0;
// 	while(i < tokcount){
// 		if(t[i].type == JSMN_STRING && t[i].size >= 1){
// 			nameTokIndex[num] = i;
// 			num++;
// 		}
// 		i++;
// 	}
// 	nameTokIndex[0]= num-1;
// }
// void printNameList(char *jsonstr, jsmntok_t *t, int *nameTokIndex){
// 	int i = 1;
// 	printf("-----Name List-----\n");
// 	while(i <= nameTokIndex[0] - 1){
// 		printf("[NAME%2d] %.*s\n", i, t[nameTokIndex[i+1]].end - t[nameTokIndex[i+1]].start, jsonstr + t[nameTokIndex[i+1]].start);
// 		i++;
//
// 	}
// }
//
// void selectNameList(char *jsonstr, jsmntok_t *t, int *nameTokIndex){
// 	while(1){
// 		int number;
// 		int valueTok;
//
// 		printf("\nSelect Name's no (exit : 0) >> ");
// 		scanf("%d", &number);
// 		if(number == 0)
// 			break;		//exit
// 		if(number <= nameTokIndex[0] - 1){
// 		int index = number + 1;
// 		printf("[NAME%2d] %.*s\n", number , t[nameTokIndex[index]].end - t[nameTokIndex[index]].start, jsonstr + t[nameTokIndex[index]].start);
//
//
// 			valueTok = nameTokIndex[index] + 1;
// 			printf("%.*s\n", t[valueTok].end - t[valueTok].start, jsonstr + t[valueTok].start);
// 		}
// 		else
// 			printf("No contents, Max indext is %d\n",nameTokIndex[0] - 1);
//
// 	}
// }

// Example 8
#define JSMN_PARENT_LINKS

void jsonObjectList(char *jsonstr, jsmntok_t *t, int tokcount, int *objectTokIndex){
	int i = 1;
	int j = 1;
	printf("****** Object List ******\n");
	while(i < tokcount){
		if(t[i].size >= 1 && t[i].type == JSMN_OBJECT){	//객체의 첫번째 데이터 value
			if(t[i].parent == 2){	// object 안의 또 다른 object를 거르기 위한 조건
			objectTokIndex[j] = i + 2;
			printf("[NAME%2d] %.*s\n", j, t[objectTokIndex[j]].end - t[objectTokIndex[j]].start, jsonstr + t[objectTokIndex[j]].start);
			j++;
			}
		}
		i++;
	}
	objectTokIndex[0] = j - 1;	//각 객체의 첫 번째 데이터의 개수
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
	// jsonNameList(string, t, r, array);
	// printNameList(string, t, array);

	//Example 6
	// jsonNameList(string, t, r, array);
	// selectNameList(string, t, array);

	//Example 7
	//jsonNameList(string, t, r, array);
	// printNameList(string, t, array);
	// selectNameList(string, t, array);

	// Example 8
	// object 정보를 입력받기 위한 array
	//
	// int objectArray[20];
	//
	// jsonObjectList(string, t, r, objectArray);
	// printObjectValue(string, t, r, objectArray);

	int objectTokIndex[100];
	int dataTokIndex[100];
	jsonObjectList(string, t, r, objectTokIndex);


	return EXIT_SUCCESS;
}
