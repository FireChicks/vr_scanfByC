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

	// �ε����� ���ڿ� ���̸� ����� ��� NULL�� ��ȯ�մϴ�.
	if (index >= length || index < 0) {
		return NULL;
	}

	int substringLength = length - index + 1;
	char* substring = (char*)malloc(substringLength * sizeof(char));

	// ������ �ε��� ������ ���ڿ��� ���ο� ���ڿ��� �����մϴ�.
	int j = 0;
	for (int i = index; i < length; i++) {
		substring[j] = string[i];
		j++;
	}
	substring[j] = '\0';  // ���ڿ��� ���� ��Ÿ���� �� ���ڸ� �߰��մϴ�.
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
	// vr_scanf �Լ��� ������ �ڷ������� ��ȯ���ִ� �Լ��Դϴ�.
	// str : �Է¹��� ���� ������ ������ ���ڿ�
	// a, b, c, d : �Է¹��� ���� ������ ������ �ּҸ� ����Ű�� ������
	char input_str[1024];  // �Է¹��� ���ڿ��� ������ �迭
	char* token;  // �Է¹��� ���ڿ��� �����ڸ� �̿��� ���� �� ����� ������
	int index = 0;  // �Էµ� ���� ������ ������ ����

	fgets(input_str, sizeof(input_str), stdin);  // ǥ�� �Է¿��� �Է¹��� ���� input_str �迭�� �����մϴ�.

	token = strtok(input_str, "|\t, ");  // strtok �Լ��� �̿��� '|'�� ','�� �����ڷ� ����� input_str�� ������ �����մϴ�.
	while (token != NULL) {
		if (index == 0) {  // ù ��° �Է� ���� ��
			strcpy((char*)d, token);  // �Է¹��� ���ڿ��� ���ڿ� ���·� d �����Ͱ� ����Ű�� ������ �����մϴ�.
			
		}
		else if (index == 1) {  // �� ��° �Է� ���� ��
			*((int*)a) = atoi(token);  // �Է¹��� ���ڿ��� ���������� ��ȯ�Ͽ� a �����Ͱ� ����Ű�� ������ �����մϴ�.			
		}
		else if (index == 2) {  // �� ��° �Է� ���� ��
			*((char*)b) = token[0];  // �Է¹��� ���ڿ��� ù ��° ���ڸ� b �����Ͱ� ����Ű�� ������ �����մϴ�.
		}
		else {  // �ټ� ��° �̻��� �Է� ���� ��
			return -1;  // �Է°��� �ʹ� ���� ��� -1�� ��ȯ�մϴ�.
		}
		index++;  // ���� �Է� ���� ������ ������ ������ ������ŵ�ϴ�.
		token = strtok(NULL, "|\t, ");  // ���� �Է� ������ �Ѿ�ϴ�.
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

	 // ���� ���ڿ��� ���̰� ���� ���ڿ����� ������ ���� �� �����Ƿ� ���� ó��
	 if (targetLength < formatLength) {
		 printf("Invalid input.\n");
		 return;
	 }

	 // ���� ���ڿ��� ���� ���ڿ��� ��ġ ���θ� üũ
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

	 // `%` ��ȣ �տ� �ִ� ���ڿ� ���� Ȯ��
	 for (i = 0; i < length; i++) {
		 if (string[i] == '%' && i > 0 && string[i - 1] != '%') {
			 prefixCount++;
		 }
	 }

	 if (prefixCount == 0) {
		 *count = 0;
		 return NULL;
	 }

	 // ���ڿ� ���� �� ����
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

	 // ���ڿ� ������ ������ ã�Ƽ� ������ �ܾ��� ���۰� �� �ε��� ã��
	 for (int i = length - 1; i >= 0; i--) {
		 if (string[i] != ' ' && end == -1) {
			 end = i + 1;
		 }
		 if (end != -1 && string[i] == ' ') {
			 start = i + 1;
			 break;
		 }
	 }

	 // ������ �ܾ� ����
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

	 // ù ��° ���ڿ����� �� ��° ���ڿ� ã��
	 char* ptr = strstr(str1, str2);
	 if (ptr != NULL) {
		 // "���� ��������"�� ���� ��ġ ���
		 int nameStart = ptr - str1;

		 // "���� ��������" �պκ� ����
		 name = (char*)malloc((nameStart + 1) * sizeof(char));
		 strncpy(name, str1, nameStart);
		 name[nameStart] = '\0';
	 }

	 return name;
 }


 int main() {
	 FILE* file = fopen("input.txt", "r"); // ���� ����
	 if (file == NULL) {
		 printf("������ �� �� �����ϴ�.\n");
		 return 1;
	 }

	 char formatString[1024]; //ù��° �� ����
	 char inputString[1024]; // �ι�° �� ����

	 fgets(formatString, sizeof(formatString), file);
	 fgets(inputString, sizeof(inputString), file); //���� �κ� ����
	 fgets(inputString, sizeof(inputString), file);

	 fclose(file); //���� �ݱ�

	 int indices[10]; //%��ġ �ε���
	 int lastIndices[10]; //% ���� ù ���� ��ġ �ε���
	 int count = 0;

	 char resultString[100] = "";
	 int resultInt = 0;
	 char resultChar = NULL;

	 findFormatIndices(formatString, indices, &count); 

	 count = 0;
	 char** prefixes = extractPrefixes(formatString, &count); 

	 freePrefixes(prefixes, count);  //%��ġ ã�Ƽ� indice�� �־��ֱ�

	 for (int i = 0; i < count; i++) 
	 {
		 lastIndices[i] = indices[i] + 2; // %���� ù ���� ��ġ +2 �ؼ� ã���ֱ�
		 char* substring = getSubstringFromIndex(formatString, lastIndices[i]); // %���� ���ڵ��� ��� ���ڿ� subString
		 mergeFirstAndSecondWord(substring); // ������� ù��°�� �ι�° ���ڿ� �и��� ����
		 removeNewline(substring);// �� �ڿ� �پ��ִ� \n �����ֱ�
		 char* targetString = strstr(inputString, substring);  //substring�� ������� ���� �Է� ���忡�� ���� ���ڿ� ã��		 
		 
		 char readType = formatString[indices[i]+1]; //%���ʿ� ����ִ� ���ڷ� �Է� �ڷ��� Ȯ��
		 char preString[200] = "";

		 for (int k = 0; k < indices[i]; k++) //% ���� ���ڿ� ã�� �ݺ���
		 {
			 int len = strlen(preString);	
			 preString[len] = formatString[k];
			 preString[len + 1] = '\0'; //���ڿ��̶� �������� ���� ����
		 }

		 int startIndex = strlen(preString);
		 char* preWord = getLastWord(preString); //% ���ʿ� �ܾ� ã��
		 int preWordLen = strlen(preWord) + 1; //%���ʿ� �ܾ��� ���� ������ ��(�̰� �����ָ� %��ġ)
		 char* targetLoc = strstr(inputString, preWord); //�ܾ� ���� ��ġ

		 if (readType == 's') //���ڿ��� ���
		 {
			 char* name = extractName((targetLoc + preWordLen), substring); //ù��° �Ű����� �ܾ� ���� ��ġ�� preWordLen�� �����ָ� %�� �����ϴ� ��ġ�� ã�� �� ����
			 if (name != NULL) {
				 printf("����� �̸�: %s\n", name);
				 free(name);
			 }
			 else {
				 printf("�̸��� ������ �� �����ϴ�.\n");
			 }

		 }
		 else if (readType == 'c') //������ ���
		 {
			 char charcter = extractName((targetLoc + preWordLen), substring)[0];
			 if (charcter != NULL) {
				 printf("����� ����: %c\n", charcter);
			 }
			 else {
				 printf("���ڸ� ������ �� �����ϴ�.\n");
			 }
		 }
		 else if (readType == 'd') // ������ ��� 
		 {
			 int d = atoi(extractName((targetLoc + preWordLen), substring));
			 if (d != NULL) {
				 printf("����� ����: %d\n", d);
			 }
			 else {
				 printf("������ ������ �� �����ϴ�.\n");
			 }
		 }
		 else {
			 printf("Ÿ�� ���� ���� �߻�");
			 exit(1);
		 }
		 
	 }

	 printf("\n");

}