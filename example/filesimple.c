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
	FILE *fp;
	fp = fopen("data.json", "r");
	char* JSON_STRING;
	char oneline[255];
	int count = 0;

	while(1){
		fgets(oneline, 255, fp);
		if(feof(fp)) break;
		count = count + strlen(oneline) + 1;
		JSON_STRING = (char*)realloc(JSON_STRING, count*sizeof(char));
		strcat(JSON_STRING, oneline);
	}
	return JSON_STRING;
}

int main() {
	char* string;
	string = (char*)malloc(sizeof(readJSONFile())+1);
	string = readJSONFile();
	puts(string);
}
