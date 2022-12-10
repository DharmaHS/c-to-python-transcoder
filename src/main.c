#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Token {
	char* value;
	char* type;
}tokens[1000];

// Returns 'true' if the character is a DELIMITER.
bool isDelimiter(char ch) {
	if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
		ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
		ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
		ch == '[' || ch == ']' || ch == '{' || ch == '}' || ch == '\n')
		return (true);
	return (false);
}
// Returns 'true' if the character is a SEPERATOR.
bool isSeperator(char ch) {
	if (ch == ';' || ch == ','||
		ch == '(' || ch == ')' || ch == '[' || ch == ']' ||
		ch == '{' || ch == '}')
		return (true);
	return (false);
}

// Returns 'true' if the character is an OPERATOR.
bool isOperator(char ch) {
	if (ch == '+' || ch == '-' || ch == '*' ||
		ch == '/' || ch == '>' || ch == '<' ||
		ch == '=' || ch == '!')
		return (true);
	return (false);
}

// Returns 'true' if the string is a VALID IDENTIFIER.
bool validIdentifier(char* str) {
	if (str[0] == '0' || str[0] == '1' || str[0] == '2' ||
		str[0] == '3' || str[0] == '4' || str[0] == '5' ||
		str[0] == '6' || str[0] == '7' || str[0] == '8' ||
		str[0] == '9' || isDelimiter(str[0]) == true)
		return (false);
	return (true);
}

// Returns 'true' if the string is a KEYWORD.
bool isKeyword(char* str) {
	if (!strcmp(str, "if") || !strcmp(str, "else") ||
		!strcmp(str, "while") || !strcmp(str, "do") ||
		!strcmp(str, "break") || !strcmp(str, "for") ||
		!strcmp(str, "continue") || !strcmp(str, "int")
		|| !strcmp(str, "double") || !strcmp(str, "float")
		|| !strcmp(str, "return") || !strcmp(str, "char")
		|| !strcmp(str, "case") || !strcmp(str, "#include")
		|| !strcmp(str, "sizeof") || !strcmp(str, "long")
		|| !strcmp(str, "short") || !strcmp(str, "typedef")
		|| !strcmp(str, "switch") || !strcmp(str, "unsigned")
		|| !strcmp(str, "void") || !strcmp(str, "static")
		|| !strcmp(str, "struct") || !strcmp(str, "goto"))
		return (true);
	return (false);
}

// Returns 'true' if the string is an INTEGER.
bool isInteger(char* str) {
	int i, len = strlen(str);

	if (len == 0)
		return (false);
	for (i = 0; i < len; i++) {
		if (str[i] != '0' && str[i] != '1' && str[i] != '2'
			&& str[i] != '3' && str[i] != '4' && str[i] != '5'
			&& str[i] != '6' && str[i] != '7' && str[i] != '8'
			&& str[i] != '9' || (str[i] == '-' && i > 0))
			return (false);
	}
	return (true);
}

// Returns 'true' if the string is a REAL NUMBER.
bool isRealNumber(char* str) {
	int i, len = strlen(str);
	bool hasDecimal = false;

	if (len == 0)
		return (false);
	for (i = 0; i < len; i++) {
		if (str[i] != '0' && str[i] != '1' && str[i] != '2'
			&& str[i] != '3' && str[i] != '4' && str[i] != '5'
			&& str[i] != '6' && str[i] != '7' && str[i] != '8'
			&& str[i] != '9' && str[i] != '.' ||
			(str[i] == '-' && i > 0))
			return (false);
		if (str[i] == '.')
			hasDecimal = true;
	}
	return (hasDecimal);
}

// Extracts the SUBSTRING.
char* subString(char* str, int left, int right) {
	int i;
	char* subStr = (char*)malloc(
				sizeof(char) * (right - left + 2));

	for (i = left; i <= right; i++)
		subStr[i - left] = str[i];
	subStr[right - left + 1] = '\0';
	return (subStr);
}

// Parsing the input STRING.
void parse(char* str) {
	int left = 0, right = 0;
	int len = strlen(str);
	int i = 0;

	while (right <= len && left <= right) {
		if (isDelimiter(str[right]) == false)
			right++;

		if (isDelimiter(str[right]) == true && left == right) {
			if (isOperator(str[right]) == true){
				// printf("'%c' IS AN OPERATOR\n", str[right]);
				tokens[i].type = "operator";
				tokens[i].value = str[right];
				}

			else if (isSeperator(str[right]) == true){
				// printf("'%c' IS A SEPERATOR\n", str[right]);
				tokens[i].type = "seperator";
				tokens[i].value = str[right];
				}

			right++;
			left = right;
		} else if (isDelimiter(str[right]) == true && left != right
				|| (right == len && left != right)) {
			char* subStr = subString(str, left, right - 1);

			if (isKeyword(subStr) == true)
			{
				// printf("'%s' IS A KEYWORD\n", subStr);
				tokens[i].type = "keyword";
				tokens[i].value = str[right];
			}

			else if (isInteger(subStr) == true){
				// printf("'%s' IS AN INTEGER\n", subStr);
				tokens[i].type = "integer";
				tokens[i].value = str[right];
			}

			else if (isRealNumber(subStr) == true){
				// printf("'%s' IS A REAL NUMBER\n", subStr);
				tokens[i].type = "real number";
				tokens[i].value = str[right];
			}

			else if (validIdentifier(subStr) == true
					&& isDelimiter(str[right - 1]) == false){
				// printf("'%s' IS A VALID IDENTIFIER\n", subStr);
				tokens[i].type = "valid id";
				tokens[i].value = str[right];
			}

			else if (validIdentifier(subStr) == false
					&& isDelimiter(str[right - 1]) == false){
				// printf("'%s' IS NOT A VALID IDENTIFIER\n", subStr);
				tokens[i].type = "invalid identifier";
				tokens[i].value = str[right];
			}
			
			left = right;
		}
		i++;
	}
	return;
}

void printToken(struct Token t){
	printf("'%s' : '%s',", t.type, t.value);
};

// print AST recursively
void printAstRec(int i){

	// case end
	if(tokens[i].value == "}" && tokens[i+2].value == NULL) {
		printf("}\n");
		return;
		}
	if(tokens[i].type == "keyword"){
		// case include
		if(tokens[i].value == "#include"){
			printf("{include\n	{'keyword' : 'include'}\n");
			i++;
			printAstRec(i); // <
			i++;
			printAstRec(i); // stdio.h
			i++;
			printAstRec(i); // >
			i++;
			printAstRec(i); //
		}
		//TODO case main
		if(tokens.){

		}
		//TODO case assignment

		//TODO case while
	}
	else if(tokens[i].type == "operator"){
		printf("{operator - '%s'}", tokens[i].value);
		return;
	}
	else if(tokens[i].type == "seperator"){
		printf("{seperator - '%s'}", tokens[i].value);
		return;
	}
	else if(tokens[i].type == "integer"){
		printf("{integer - '%s'}", tokens[i].value);
		return;
	}
	else if(tokens[i].type == "real number"){
		printf("{real number - '%s'}", tokens[i].value);
		return;
	}
	else if(tokens[i].type == "valid identifier"){
		// case scanf
		if(tokens[i].value == "scanf"){ //TODO still have issues
			printf("{function: \n	{'valid identifier' : 'scanf'}\n");
			i++;
			printAstRec(i); // (
			i++;
			printAstRec(i); // "
			i++;
			printAstRec(i); // %d
			i++;
			printAstRec(i); // "
			i++;
			printAstRec(i); // ,
			i++;
			printAstRec(i); // &
			i++;
			printAstRec(i); // a
			i++;
			printAstRec(i); // )
			i++;
			printAstRec(i); // ;
		}
		printf("{identifier - '%s'}", tokens[i].value);
		return;
	}
	else if(tokens[i].type == "invalid identifier"){
		printf("{invalid identifier - '%s'}", tokens[i].value);
		return;
	}
}


// DRIVER FUNCTION
int main() {
	FILE *fp;
	fp = fopen("test.c", "r");

	char source[1000];

	while(!feof(fp)) {
		fgets(source, 1000, fp);
		parse(source);
	}
	printAST();

	return (0);
}
