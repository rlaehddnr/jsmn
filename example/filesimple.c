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

// read txt file(json file)
// edit here to change reading data.json file
char* readJSONFile(){
	char* JSON_STRING;
	char oneline[255];
	int count = 0;

	FILE *fp;
	fp = fopen("data3.json", "r");

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

#define JSMN_PARENT_LINKS

// Example 8
// void jsonObjectList(char *jsonstr, jsmntok_t *t, int tokcount, int *objectTokIndex){
// 	int i = 1;
// 	int j = 1;
// 	printf("****** Object List ******\n");
// 	while(i < tokcount){
// 		if(t[i].size >= 1 && t[i].type == JSMN_OBJECT){	//객체의 첫번째 데이터 value
// 			if(t[i].parent == 2){	// object 안의 또 다른 object를 거르기 위한 조건
// 			objectTokIndex[j] = i + 2;
// 			printf("[NAME%2d] %.*s\n", j, t[objectTokIndex[j]].end - t[objectTokIndex[j]].start, jsonstr + t[objectTokIndex[j]].start);
// 			j++;
// 			}
// 		}
// 		i++;
// 	}
// 	objectTokIndex[0] = j - 1;	//각 객체의 첫 번째 데이터의 개수
// }

// Example 9
// void jsonObjectList(char *jsonstr, jsmntok_t *t, int tokcount, int *objectTokIndex, int *valueTokIndex){
// 	int i = 1;
// 	int j = 1;	// object tok 저장변수
//  int k = 1;	// value tok 저장변수
// 	printf("****** Object List ******\n");
// 	while(i < tokcount){
// 		if(t[i].size >= 1 && t[i].type == JSMN_OBJECT){	//객체의 첫번째 데이터 value
// 			if(t[i].parent == 2){	// object 안의 또 다른 object를 거르기 위한 조건
// 				objectTokIndex[j] = i;
// 				// 저장된 수에 +2 를 해주어야 첫 오브젝트의 value값이 나오게 된다.
// 				printf("[NAME%2d] %.*s\n", j, t[objectTokIndex[j]+2].end - t[objectTokIndex[j]+2].start, jsonstr + t[objectTokIndex[j]+2].start);
// 				j++;
// 			}
// 		}
// 		if(t[i].size >= 1 && t[i].type == JSMN_STRING){	//child를 가진 string 저장하기위한 조건
// 			valueTokIndex[k] = i;
// 				// 저장된 수에 +2 를 해주어야 첫 오브젝트의 value값이 나오게 된다.
// 				// printf("[Value%2d] %.*s\n", k, t[valueTokIndex[k]].end - t[valueTokIndex[k]].start, jsonstr + t[valueTokIndex[k]].start);
// 				k++;
// 			}
// 		i++;
// 	}
// 	objectTokIndex[0] = j - 1;	//각 객체의 첫 번째 데이터의 개수
// 	valueTokIndex[0] = k - 1;
// }
// void selectObject(char *jsonstr, jsmntok_t *t, int tokcount,int *objectTokIndex, int *valueTokIndex){
// 	int num = 0;
// 	int valueCount = 0;
//
// 	printf("---------------------------------\n");
//
// 	while(1){
// 		int i = 2;
// 		printf("원하는 번호 입력 (exit : 0) ");
// 		scanf("%d", &num);
// 		if(num == 0) break;
//
// 			else if(num > objectTokIndex[0]){
// 				printf("Too big\n");
// 			}
// 			else if(num > 0){
// 				while(t[valueTokIndex[num+i]].end <= t[objectTokIndex[num]].end){
// 						printf("[%.*s]", t[valueTokIndex[i]].end - t[valueTokIndex[i]].start, jsonstr + t[valueTokIndex[i]].start);
// 						printf("%.*s\n", t[valueTokIndex[i]+1].end - t[valueTokIndex[i]+1].start, jsonstr + t[valueTokIndex[i]+1].start);
//
// 						i++;
// 					//
// 				// if(t[objectTokIndex[num]].type == JSMN_OBJECT && t[objectTokIndex[num]].size > 0){
// 				// 	printf("%d", (t[objectTokIndex[num]+i].start - t[objectTokIndex[num]+(i-1)].start) - 1);
// 				// 	printf("[%.*s]", (t[objectTokIndex[num]+i].start - t[objectTokIndex[num]+(i-1)].start) - 1, jsonstr + t[objectTokIndex[num]+(i-1)].start + 5);
// 				// }
// 				// // printf("%.*s\n", t[objectTokIndex[num+1]].end - t[objectTokIndex[num]].start, jsonstr + t[objectTokIndex[num]-1].start);
// 				// i++;
// 				// printf("\n");
// 			}
// 		}
// 	}
// }

// Example 10
// void jsonList(char *jsonstr, jsmntok_t *t, int tokcount, int *objectTokIndex){
// 	int i = 1;
// 	int j = 1;
// 	int k = 1;
// 	while(i < tokcount){
// 		if(t[i].size >= 1 && t[i].type == JSMN_STRING){	//객체의 첫번째 데이터 value
// 			 if(t[i].parent < 1){	// object 안의 또 다른 object를 거르기 위한 조건
// 				objectTokIndex[j] = i;
// 				// 저장된 수에 +2 를 해주어야 첫 오브젝트의 value값이 나오게 된다.
// 				j++;
// 			}
// 		}
// 		if(t[i].size >= 1 && t[i].type == JSMN_STRING){	//child를 가진 string 저장하기위한 조건
// 			valueTokIndex[k] = i;
// 				// 저장된 수에 +2 를 해주어야 첫 오브젝트의 value값이 나오게 된다.
// 				k++;
// 			}
// 		i++;
// 	}
// 	objectTokIndex[0] = j - 1;	//각 객체의 첫 번째 데이터의 개수
// 	valueTokIndex[0] = k - 1;
// }
// void printList(char *jsonstr, jsmntok_t *t, int tokcount, int *objectTokIndex){
// 	int i = 1;
//
// 	printf("****** Name List ******\n");
//
// 	while(i <= objectTokIndex[0]){
// 		printf("[NAME %2d] %.*s\n", i, t[objectTokIndex[i]].end - t[objectTokIndex[i]].start, jsonstr + t[objectTokIndex[i]].start);
// 		i++;
// 	}
// 	printf("\n\n****** Object List ******\n");
// 	i = 1;
// 	printf("[NAME %d] %.*s\n", i, t[objectTokIndex[i]+1].end - t[objectTokIndex[i]+1].start, jsonstr + t[objectTokIndex[i]+1].start);
// }
// void printselectList(char *jsonstr, jsmntok_t *t, int tokcount, int *objectTokIndex){
// 	int num;
// 	printf("\n원하는 번호를 입력 (Exit : 0)");
// 	scanf("%d", &num);
//
// 	printf("%.*s : %.*s\n", t[objectTokIndex[num]].end - t[objectTokIndex[num]].start, jsonstr + t[objectTokIndex[num]].start,
// 	 t[objectTokIndex[num]+1].end - t[objectTokIndex[num]+1].start, jsonstr + t[objectTokIndex[num]+1].start);
//
// 	if(num <= objectTokIndex[0] && num > 0){
// 		int i = num + 1;
// 		while(i < objectTokIndex[0]){
// 			printf("\t[%.*s]%.*s\n", t[objectTokIndex[i]].end - t[objectTokIndex[i]].start, jsonstr + t[objectTokIndex[i]].start,
// 			 t[objectTokIndex[i]+1].end - t[objectTokIndex[i]+1].start, jsonstr + t[objectTokIndex[i]+1].start);
//
// 			i++;
// 		}
// 	}
// }

// Example 11
void jsonList(char *jsonstr, jsmntok_t *t, int tokcount, int *nameTokIndex,
	 int *objectTokIndex){

	int i = 1, nameCount = 1;
	int name;

	for(i = 1; i < tokcount; i++){
		if(t[i].type == JSMN_STRING && t[i].size > 0){
			nameTokIndex[nameCount] = i;
			nameCount++;
		}
	}
	nameTokIndex[0] = nameCount - 1;

	int objectCount = 1;
	int object;

	for(i = 1; i < tokcount; i++){
		if(t[i].type == JSMN_OBJECT){
			objectTokIndex[objectCount] = i;
			objectCount++;
		}
	}
	objectTokIndex[0] = objectCount - 1;
}

void printList(char *jsonstr, jsmntok_t *t, int tokcount, int *nameTokIndex,
		int *objectTokIndex){

	int i = 1;
	int j = 1;

	printf("****** Name List ******\n");

	while(i <= nameTokIndex[0]){
		printf("[NAME%2d] %.*s\n", i, t[nameTokIndex[i]].end - t[nameTokIndex[i]].start, jsonstr + t[nameTokIndex[i]].start);
 		i++;
 	}

 	printf("\n****** Object List ******\n");
 	while(j <= objectTokIndex[0]){
 		printf("[NAME %d] %.*s\n", j, t[objectTokIndex[j]+2].end - t[objectTokIndex[j]+2].start, jsonstr + t[objectTokIndex[j]+2].start);
		j++;
	}
	printf("\n");
}

void printselectList(char *jsonstr, jsmntok_t *t, int tokcount, int *nameTokIndex, int *objectTokIndex){
	int num;

	while(1){
		printf("원하는 번호 입력 (Exit:0) : ");
		scanf("%d", &num);

		if(num <= objectTokIndex[0] && num > 0){
		printf("%.*s : %.*s\n", t[objectTokIndex[num]+1].end - t[objectTokIndex[num]+1].start, jsonstr + t[objectTokIndex[num]+1].start,
			 t[objectTokIndex[num]+2].end - t[objectTokIndex[num]+2].start, jsonstr + t[objectTokIndex[num]+2].start);

			int i = num;
			int j = 2;
			while(t[nameTokIndex[i]+j].start < t[objectTokIndex[i]].end){
				printf("\t[%.*s]%.*s\n", t[nameTokIndex[i]+j].end - t[nameTokIndex[i]+j].start, jsonstr + t[nameTokIndex[i]+j].start,
				 t[nameTokIndex[i]+j+1].end - t[nameTokIndex[i]+j+1].start, jsonstr + t[nameTokIndex[i]+j+1].start);
				j = j + 2;
			}
		}
		else if(num == 0) break;
		else printf("No object\n");
	}
}

// Example 15
typedef enum{
	NONGSHIM = 0,
	PALDO = 1,
	SAMYANG = 2,
	OTTUGI = 3,
} company_t;

typedef struct{
	company_t company;	// 제조사
	char name[20];			// 제품명
	int price;					// 가격
	int like;						// 찜하기
	int evaluation;			// 상품평가 수
} product_t;

// int makeProduct(const char *json, jsmntok_t *t, int tokcount, product_t *p[]){
//
// }


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
	// jsonNameList(string, t, r, array);
	// printNameList(string, t, array);
	// selectNameList(string, t, array);

	// Example 8
	// jsonObjectList(string, t, r, array);

	int name[50];
	int object[50];

	// Example 9
	/*
	1. malloc  assert, realloc,  free (t[i].size)
	*/
	// jsonObjectList(string, t, r, object, value);
	// selectObject(string, t, r,object, value);

	 // Example 10
	 // jsonList(string, t, r, object);
	 // printList(string, t, r, object);
	 // printselectList(string, t, r, object);

	 // Example 11
	 jsonList(string, t, r, name, object);
	 printList(string, t, r, name, object);
	 printselectList(string, t, r, name, object);


	return EXIT_SUCCESS;
}
