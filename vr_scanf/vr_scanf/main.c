#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LENGTH 1000

void findFormatIndices(const char* formatString, int* indices, int* count) {
	*count = 0;

	int length = strlen(formatString);
	for (int i = 0; i < length; i++) {
		if (formatString[i] == '%') {
			indices[*count] = i;
			(*count)++;
		}
	}
}

void removeNewline(char* string) {
	int length = strlen(string);
	if (length > 0 && string[length - 1] == '\n') {
		string[length - 1] = '\0';
	}
}

char* getSubstringFromIndex(const char* string, int index) {
	int length = strlen(string);

	// 인덱스가 문자열 길이를 벗어나는 경우 NULL을 반환합니다.
	if (index >= length || index < 0) {
		return NULL;
	}

	int substringLength = length - index + 1;
	char* substring = (char*)malloc(substringLength * sizeof(char));

	// 지정한 인덱스 이후의 문자열을 새로운 문자열에 복사합니다.
	int j = 0;
	for (int i = index; i < length; i++) {
		substring[j] = string[i];
		j++;
	}
	substring[j] = '\0';  // 문자열의 끝을 나타내는 널 문자를 추가합니다.
	return substring;
}

void removeQuotes(const char* source, char* destination) {
	int length = strlen(source);
	int j = 0;

	for (int i = 0; i < length; i++) {
		if (source[i] != '\"') {
			destination[j] = source[i];
			j++;
		}
	}

	destination[j] = '\0';
}


 int vr_scanf(const char* str, void* a, void* b, void* c, void* d)
{
	// vr_scanf 함수는 지정한 자료형으로 변환해주는 함수입니다.
	// str : 입력받을 값의 형식을 지정한 문자열
	// a, b, c, d : 입력받은 값을 저장할 변수의 주소를 가리키는 포인터
	char input_str[1024];  // 입력받은 문자열을 저장할 배열
	char* token;  // 입력받은 문자열을 구분자를 이용해 나눌 때 사용할 포인터
	int index = 0;  // 입력된 값의 순서를 저장할 변수

	fgets(input_str, sizeof(input_str), stdin);  // 표준 입력에서 입력받은 값을 input_str 배열에 저장합니다.

	token = strtok(input_str, "|\t, ");  // strtok 함수를 이용해 '|'와 ','를 구분자로 사용해 input_str을 나누어 저장합니다.
	while (token != NULL) {
		if (index == 0) {  // 첫 번째 입력 값일 때
			strcpy((char*)d, token);  // 입력받은 문자열을 문자열 형태로 d 포인터가 가리키는 변수에 저장합니다.
			
		}
		else if (index == 1) {  // 두 번째 입력 값일 때
			*((int*)a) = atoi(token);  // 입력받은 문자열을 정수형으로 변환하여 a 포인터가 가리키는 변수에 저장합니다.			
		}
		else if (index == 2) {  // 세 번째 입력 값일 때
			*((char*)b) = token[0];  // 입력받은 문자열의 첫 번째 글자를 b 포인터가 가리키는 변수에 저장합니다.
		}
		else {  // 다섯 번째 이상의 입력 값일 때
			return -1;  // 입력값이 너무 많은 경우 -1을 반환합니다.
		}
		index++;  // 다음 입력 값의 순서를 저장할 변수를 증가시킵니다.
		token = strtok(NULL, "|\t, ");  // 다음 입력 값으로 넘어갑니다.
	}

	if (index < 4) {
		return -1;
	}

	return 0;
}

 void compareAndPrint( const char* inputString, const char* formatString, int startIndex) {
	 const char* targetString = &inputString[startIndex];
	 int formatLength = strlen(formatString);
	 int targetLength = strlen(targetString);

	 // 비교할 문자열의 길이가 형식 문자열보다 작으면 비교할 수 없으므로 오류 처리
	 if (targetLength < formatLength) {
		 printf("Invalid input.\n");
		 return;
	 }

	 // 형식 문자열과 비교할 문자열의 일치 여부를 체크
	 if (strncmp(formatString, targetString, formatLength - 1) == 0) {
		 printf("%.*s\n", formatLength - 1, targetString);
	 }
	 else {
		 printf("No match found.\n");
	 }
 }


 void mergeFirstAndSecondWord(char* string) {
	 char* token;
	 char* rest;
	 char firstWord[1024];
	 char secondWord[1024];

	 token = strtok(string, " ");
	 if (token != NULL) {
		 strcpy(firstWord, token);
		 token = strtok(NULL, " ");
		 if (token != NULL) {
			 strcpy(secondWord, token);
			 sprintf(string, "%s %s", firstWord, secondWord);
		 }
	 }
 }

 char** extractPrefixes(const char* string, int* count) {
	 int length = strlen(string);
	 int i, j;
	 int prefixCount = 0;
	 char** prefixes = NULL;

	 // `%` 기호 앞에 있는 문자열 개수 확인
	 for (i = 0; i < length; i++) {
		 if (string[i] == '%' && i > 0 && string[i - 1] != '%') {
			 prefixCount++;
		 }
	 }

	 if (prefixCount == 0) {
		 *count = 0;
		 return NULL;
	 }

	 // 문자열 추출 및 저장
	 prefixes = (char**)malloc(prefixCount * sizeof(char*));
	 if (prefixes == NULL) {
		 *count = 0;
		 return NULL;
	 }

	 j = 0;
	 for (i = 0; i < length; i++) {
		 if (string[i] == '%' && i > 0 && string[i - 1] != '%') {
			 int start = i;
			 while (start > 0 && string[start - 1] != ' ') {
				 start--;
			 }
			 int end = i;

			 int prefixLength = end - start;
			 char* prefix = (char*)malloc((prefixLength + 1) * sizeof(char));
			 strncpy(prefix, string + start, prefixLength);
			 prefix[prefixLength] = '\0';

			 prefixes[j] = prefix;
			 j++;
		 }
	 }

	 *count = prefixCount;
	 return prefixes;
 }

 void freePrefixes(char** prefixes, int count) {
	 if (prefixes == NULL) {
		 return;
	 }

	 for (int i = 0; i < count; i++) {
		 free(prefixes[i]);
	 }

	 free(prefixes);
 }
 char* getLastWord(const char* string) {
	 int length = strlen(string);
	 int start = -1;
	 int end = -1;

	 // 문자열 끝부터 공백을 찾아서 마지막 단어의 시작과 끝 인덱스 찾기
	 for (int i = length - 1; i >= 0; i--) {
		 if (string[i] != ' ' && end == -1) {
			 end = i + 1;
		 }
		 if (end != -1 && string[i] == ' ') {
			 start = i + 1;
			 break;
		 }
	 }

	 // 마지막 단어 추출
	 if (start != -1 && end != -1) {
		 int wordLength = end - start;
		 char* lastWord = (char*)malloc((wordLength + 1) * sizeof(char));
		 strncpy(lastWord, string + start, wordLength);
		 lastWord[wordLength] = '\0';
		 return lastWord;
	 }

	 return NULL;
 }

 char* extractName(const char* str1, const char* str2) {
	 char* name = NULL;

	 // 첫 번째 문자열에서 두 번째 문자열 찾기
	 char* ptr = strstr(str1, str2);
	 if (ptr != NULL) {
		 // "멋진 이은석님"의 시작 위치 계산
		 int nameStart = ptr - str1;

		 // "멋진 이은석님" 앞부분 추출
		 name = (char*)malloc((nameStart + 1) * sizeof(char));
		 strncpy(name, str1, nameStart);
		 name[nameStart] = '\0';
	 }

	 return name;
 }


 int main() {
	 FILE* file = fopen("input.txt", "r"); // 파일 열기
	 if (file == NULL) {
		 printf("파일을 열 수 없습니다.\n");
		 return 1;
	 }

	 char formatString[1024]; //첫번째 줄 문자
	 char inputString[1024]; // 두번째 줄 문자

	 fgets(formatString, sizeof(formatString), file);
	 fgets(inputString, sizeof(inputString), file); //공백 부분 제거
	 fgets(inputString, sizeof(inputString), file);

	 fclose(file); //파일 닫기

	 int indices[10]; //%위치 인덱스
	 int lastIndices[10]; //% 이후 첫 문자 위치 인덱스
	 int count = 0;

	 char resultString[100] = "";
	 int resultInt = 0;
	 char resultChar = NULL;

	 findFormatIndices(formatString, indices, &count); 

	 count = 0;
	 char** prefixes = extractPrefixes(formatString, &count); 

	 freePrefixes(prefixes, count);  //%위치 찾아서 indice에 넣어주기

	 for (int i = 0; i < count; i++) 
	 {
		 lastIndices[i] = indices[i] + 2; // %이후 첫 문자 위치 +2 해서 찾아주기
		 char* substring = getSubstringFromIndex(formatString, lastIndices[i]); // %이후 문자들이 담긴 문자열 subString
		 mergeFirstAndSecondWord(substring); // 공백기준 첫번째와 두번째 문자열 분리후 저장
		 removeNewline(substring);// 맨 뒤에 붙어있는 \n 지워주기
		 char* targetString = strstr(inputString, substring);  //substring을 기반으로 실제 입력 문장에서 뒤쪽 문자열 찾기		 
		 
		 char readType = formatString[indices[i]+1]; //%뒤쪽에 담겨있는 문자로 입력 자료형 확인
		 char preString[200] = "";

		 for (int k = 0; k < indices[i]; k++) //% 앞쪽 문자열 찾는 반복문
		 {
			 int len = strlen(preString);	
			 preString[len] = formatString[k];
			 preString[len + 1] = '\0'; //문자열이라 마지막에 공백 문자
		 }

		 int startIndex = strlen(preString);
		 char* preWord = getLastWord(preString); //% 앞쪽에 단어 찾기
		 int preWordLen = strlen(preWord) + 1; //%앞쪽에 단어의 수와 공백의 수(이걸 더해주면 %위치)
		 char* targetLoc = strstr(inputString, preWord); //단어 시작 위치

		 if (readType == 's') //문자열일 경우
		 {
			 char* name = extractName((targetLoc + preWordLen), substring); //첫번째 매개변수 단어 시작 위치에 preWordLen을 더해주면 %가 시작하는 위치를 찾을 수 있음
			 if (name != NULL) {
				 printf("추출된 이름: %s\n", name);
				 free(name);
			 }
			 else {
				 printf("이름을 추출할 수 없습니다.\n");
			 }

		 }
		 else if (readType == 'c') //문자일 경우
		 {
			 char charcter = extractName((targetLoc + preWordLen), substring)[0];
			 if (charcter != NULL) {
				 printf("추출된 문자: %c\n", charcter);
			 }
			 else {
				 printf("문자를 추출할 수 없습니다.\n");
			 }
		 }
		 else if (readType == 'd') // 정수일 경우 
		 {
			 int d = atoi(extractName((targetLoc + preWordLen), substring));
			 if (d != NULL) {
				 printf("추출된 정수: %d\n", d);
			 }
			 else {
				 printf("정수를 추출할 수 없습니다.\n");
			 }
		 }
		 else {
			 printf("타입 지정 오류 발생");
			 exit(1);
		 }
		 
	 }

	 printf("\n");

}