#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <string>

struct Token
{
	std::string value;
	std::string type;
}tokens[1000];

int tokenCount = 0;

// Returns 'true' if the character is a DELIMITER.
bool isDelimiter(char ch)
{
	if (ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
		ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
		ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
		ch == '[' || ch == ']' || ch == '{' || ch == '}' || ch == '\n')
		return (true);
	return (false);
}
// Returns 'true' if the character is a SEPERATOR.
bool isSeperator(char ch)
{
	if (ch == ';' || ch == ',' ||
		ch == '(' || ch == ')' || ch == '[' || ch == ']' ||
		ch == '{' || ch == '}')
		return (true);
	return (false);
}

// Returns 'true' if the character is an OPERATOR.
bool isOperator(char ch)
{
	if (ch == '+' || ch == '-' || ch == '*' ||
		ch == '/' || ch == '>' || ch == '<' ||
		ch == '=' || ch == '!')
		return (true);
	return (false);
}

// Returns 'true' if the string is a VALID IDENTIFIER.
bool validIdentifier(char *str)
{
	if (str[0] == '0' || str[0] == '1' || str[0] == '2' ||
		str[0] == '3' || str[0] == '4' || str[0] == '5' ||
		str[0] == '6' || str[0] == '7' || str[0] == '8' ||
		str[0] == '9' || isDelimiter(str[0]) == true)
		return (false);
	return (true);
}

// Returns 'true' if the string is a KEYWORD.
bool isKeyword(char *str)
{
	if (!strcmp(str, "if") || !strcmp(str, "else") ||
		!strcmp(str, "while") || !strcmp(str, "do") ||
		!strcmp(str, "break") || !strcmp(str, "for") ||
		!strcmp(str, "continue") || !strcmp(str, "int") || !strcmp(str, "double") || !strcmp(str, "float") || !strcmp(str, "return") || !strcmp(str, "char") || !strcmp(str, "case") || !strcmp(str, "#include") || !strcmp(str, "sizeof") || !strcmp(str, "long") || !strcmp(str, "short") || !strcmp(str, "typedef") || !strcmp(str, "switch") || !strcmp(str, "unsigned") || !strcmp(str, "void") || !strcmp(str, "static") || !strcmp(str, "struct") || !strcmp(str, "goto"))
		return (true);
	return (false);
}

// Returns 'true' if the string is an INTEGER.
bool isInteger(char *str)
{
	int i, len = strlen(str);

	if (len == 0)
		return (false);
	for (i = 0; i < len; i++)
	{
		if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5' && str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9' || (str[i] == '-' && i > 0))
			return (false);
	}
	return (true);
}

// Returns 'true' if the string is a REAL NUMBER.
bool isRealNumber(char *str)
{
	int i, len = strlen(str);
	bool hasDecimal = false;

	if (len == 0)
		return (false);
	for (i = 0; i < len; i++)
	{
		if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != '3' && str[i] != '4' && str[i] != '5' && str[i] != '6' && str[i] != '7' && str[i] != '8' && str[i] != '9' && str[i] != '.' ||
			(str[i] == '-' && i > 0))
			return (false);
		if (str[i] == '.')
			hasDecimal = true;
	}
	return (hasDecimal);
}

// Extracts the SUBSTRING.
char *subString(char *str, int left, int right)
{
	int i;
	char *subStr = (char *)malloc(
		sizeof(char) * (right - left + 2));

	for (i = left; i <= right; i++)
		subStr[i - left] = str[i];
	subStr[right - left + 1] = '\0';
	return (subStr);
}

// Parsing the input STRING.
void parse(char *str)
{
	int left = 0, right = 0;
	int len = strlen(str);

	while (right <= len && left <= right)
	{
		if (isDelimiter(str[right]) == false)
			right++;

		if (isDelimiter(str[right]) == true && left == right)
		{
			if (isOperator(str[right]) == true)
			{
				// printf("'%c' IS AN OPERATOR\n", str[right]);
				tokens[tokenCount].type = "operator";
				tokens[tokenCount].value = str[right];
				tokenCount++;
			}

			else if (isSeperator(str[right]) == true)
			{
				// printf("'%c' IS A SEPERATOR\n", str[right]);
				tokens[tokenCount].type = "seperator";
				tokens[tokenCount].value = str[right];
				tokenCount++;
			}

			right++;
			left = right;
		}
		else if (isDelimiter(str[right]) == true && left != right || (right == len && left != right))
		{
			char *subStr = subString(str, left, right - 1);

			if (isKeyword(subStr) == true)
			{
				// printf("'%s' IS A KEYWORD\n", subStr);
				tokens[tokenCount].type = "keyword";
				tokens[tokenCount].value = subStr;
				tokenCount++;
			}

			else if (isInteger(subStr) == true)
			{
				// printf("'%s' IS AN INTEGER\n", subStr);
				tokens[tokenCount].type = "integer";
				tokens[tokenCount].value = subStr;
				tokenCount++;
			}

			else if (isRealNumber(subStr) == true)
			{
				// printf("'%s' IS A REAL NUMBER\n", subStr);
				tokens[tokenCount].type = "real number";
				tokens[tokenCount].value = subStr;
				tokenCount++;
			}

			else if (validIdentifier(subStr) == true && isDelimiter(str[right - 1]) == false)
			{
				// printf("'%s' IS A VALID IDENTIFIER\n", subStr);
				tokens[tokenCount].type = "valid identifier";
				tokens[tokenCount].value = subStr;
				tokenCount++;
			}

			else if (validIdentifier(subStr) == false && isDelimiter(str[right - 1]) == false)
			{
				// printf("'%s' IS NOT A VALID IDENTIFIER\n", subStr);
				tokens[tokenCount].type = "invalid identifier";
				tokens[tokenCount].value = subStr;
				tokenCount++;
			}

			left = right;
		}
	}
	return;
}

void printToken(struct Token t)
{
	std::cout<< "{" << "'" << t.type << "'" << " : " << "'" << t.value << "'" << "}" << std::endl;
};

// print AST recursively
void printASTRec(int i)
{

	if (tokens[i].type == "keyword")
	{
		// case include
		if (tokens[i].value == "#include")
		{
			//printf("{include\n	{'keyword' : 'include'}\n");
			std::cout << "{'include' :\n{'keyword' : '#include'}\n";
			i++;
			printToken(tokens[i]); // <
			i++;
			printToken(tokens[i]); // stdio.h
			i++;
			printToken(tokens[i]); // >;
			std::cout<<"}" << std::endl;
			i++;
			printASTRec(i);
			return;
		}
		// case main
		if (tokens[i].value == "int" && tokens[i + 1].value == "main")
		{
			//printf("{main :\n");
			std::cout << "{'function' : \n{'main' :\n";
			printToken(tokens[i]); // {'keyword' : 'int'}
			i++;
			printASTRec(i);
			return;
		}
		// case assignment
		if (tokens[i].value == "int" || tokens[i].value == "char" || tokens[i].value == "double" || tokens[i].value == "float" || tokens[i].value == "short" || tokens[i].value == "long")
		{
			//printf("{assignment :\n");
			std::cout << "{assignment :\n";
			printToken(tokens[i]); // {'keyword' : 'int'}
			i++;
			printASTRec(i);
			return;
		}
		// case while
		if (tokens[i].value == "while")
		{
			//printf("{while\n :{'keyword' : 'while'}\n");
			std::cout << "{'while' :\n{'condition' :\n{'keyword' : 'while'}\n";
			i++;
			printASTRec(i);
			return;
		}

		// case if
		if (tokens[i].value == "if")
		{
			//printf("{if\n :{'keyword' : 'if'}\n");
			std::cout << "{'if' :\n'condition' :\n{'keyword' : 'if'}\n";
			i++;
			printASTRec(i);
			return;
		}

		// case for
		if (tokens[i].value == "for")
		{
			std::cout<<"{for\n :{'keyword' : 'for'}\n";
			i++;
			std::cout<<"{'condition' :\n";
			i++;
			printASTRec(i);
			return;
		}

		printToken(tokens[i]);
		i++;
		printASTRec(i);
		return;
	}

	else if (tokens[i].type == "operator")
	{
		printToken(tokens[i]);
		i++;
		printASTRec(i);
		return;
	}
	else if (tokens[i].type == "seperator")
	{
		// case end
		if (tokens[i].value == "}" && i+2 >= tokenCount)
		{
			printToken(tokens[i]);
			std::cout<<"}\n";
			return;
		}

		// case ), }, :
		if ((tokens[i].value == ")" && tokens[i+1].value != ";") || tokens[i].value == "}" || tokens[i].value == ";")
		{
			printToken(tokens[i]);
			std::cout << "}\n";
			i++;
			printASTRec(i);
			return;
		}

		printToken(tokens[i]);
		i++;
		printASTRec(i);
		return;
	}
	else if (tokens[i].type == "integer")
	{
		std::cout << "{'integer' - '" << tokens[i].value << "'" << "}" << std::endl;
		i++;
		printASTRec(i);
		return;
	}
	else if (tokens[i].type == "real number")
	{
		printToken(tokens[i]);
		i++;
		printASTRec(i);
		return;
	}
	else if (tokens[i].type == "valid identifier")
	{
		// case operation
		if (tokens[i + 1].value == "+" || tokens[i + 1].value == "-" || tokens[i + 1].value == "*" || tokens[i + 1].value == "/")
		{
			std::cout<<"{'operation' :\n";
			printToken(tokens[i]);
			i++;
			printASTRec(i);
			return;
		}

		// case scanf
		if (tokens[i].value == "scanf")
		{
			std::cout<<"{'function': \n{'valid identifier' : 'scanf'}\n";
			i++;
			printASTRec(i);
			return;
		}

		// case printf
		if (tokens[i].value == "printf")
		{
			std::cout<<"{'function': \n{'valid identifier' : 'printf'}\n";
			i++;
			printASTRec(i);
			return;
		}

		// case strlen
		if (tokens[i].value == "strlen")
		{
			std::cout<<"{'function': \n{'valid identifier' : 'strlen'}\n";
			i++;
			printASTRec(i);
			return;
		}
		
		std::cout << "{'identifier' : " << "'" << tokens[i].value << "'" << "}\n";
		i++;
		printASTRec(i);
		return;
	}
	else if (tokens[i].type == "invalid identifier")
	{
		//printf("{invalid identifier - '%s'}", tokens[i].value);
		std::cout << "{'invalid identifier': " << tokens[i].value << "'" << "}\n";
		i++;
		printASTRec(i);
		return;
	}
}

void printIndent(int indent){
	for(int i=0; i<indent; i++)
		std::cout<<"\t";
	return;
}

// print python code recursively
void printPyRec(int i, int indent){
	
	if (i >= tokenCount)
		return;

	if (tokens[i].type == "keyword"){
		// case include, for this case just pass through the tokens
		if(tokens[i].value == "#include")
		{
			i+=4;
			printPyRec(i, indent);
			return;
		}

		// case main
		if(tokens[i].value == "int" && tokens[i+1].value == "main")
		{
			std::cout<<"if __name__ == \"__main__\"";
			i+=4;
			printPyRec(i, indent);
			return;
		}

		// case return
		if(tokens[i].value == "return")
		{
			std::cout<<"return ";
			i++;
			printPyRec(i, indent);
			return;
		}
		// case assignment
		if(tokens[i].value == "int" || tokens[i].value == "double" || tokens[i].value == "short" || tokens[i].value == "long")
		{
			i++;
			std::cout<<tokens[i].value;
			// direct assignment
			if(tokens[i+1].value == ";")
			{
				std::cout<<" = 0";
				i++;
				printPyRec(i, indent);
				return;
			}
			// array assignment
			if(tokens[i+1].value == "[")
			{
				std::cout<<" = []";
				i+=2;
				std::cout<<"*"<<tokens[i].value;
				i+=2;
				printPyRec(i, indent);
				return;
			}
			if(tokens[i+1].value == "=")
			{
				std::cout<<" = ";
				i+=2;
				printPyRec(i, indent);
				return;
			}
			printPyRec(i, indent);
			return;
		}
		if(tokens[i].value == "char")
		{
			printIndent(indent);
			i++;
			std::cout<<tokens[i].value;
			// direct assignment
			if(tokens[i+1].value == ";")
			{
				std::cout<<" = '0'";
				i++;
				printPyRec(i, indent);
				return;
			}
			// array assignment
			if(tokens[i+1].value == "[")
			{
				std::cout<<" = []";
				i+=2;
				std::cout<<"*"<<tokens[i].value;
				i+=2;
				printPyRec(i, indent);
				return;
			}
			if(tokens[i+1].value == "=")
			{
				std::cout<<" = ";
				i+=2;
				printPyRec(i, indent);
				return;
			}
			printPyRec(i, indent);
			return;
		}
		if(tokens[i].value == "float")
		{
			printIndent(indent);
			i++;
			std::cout<<tokens[i].value;
			// direct assignment
			if(tokens[i+1].value == ";")
			{
				std::cout<<" = 0.0";
				i++;
				printPyRec(i, indent);
				return;
			}
			// array assignment
			else if(tokens[i+1].value == "[")
			{
				std::cout<<" = []";
				i+=2;
				std::cout<<"*"<<tokens[i].value;
				i+=2;
				printPyRec(i, indent);
				return;
			}
			if(tokens[i+1].value == "=")
			{
				std::cout<<" = ";
				i+=2;
				printPyRec(i, indent);
				return;
			}
			printPyRec(i, indent);
			return;
		}

		// case while
		if(tokens[i].value == "while")
		{
			std::cout<<"while";
			i++;
			printPyRec(i, indent);
			return;
		}

		// case if
		if(tokens[i].value == "if")
		{
			std::cout<<"if";
			i++;
			printPyRec(i, indent);
			return;
		}

		// case for, this for case only considers possibility of "i <" as condition
		if(tokens[i].value == "for")
		{	
			std::cout<<tokens[i+3].value<<tokens[i+4].value<<tokens[i+5].value<<"\n"; // for(int i = 0; i < n - 1; i++)
			printIndent(indent);
			std::cout<<"for "<<tokens[i+3].value << " in range(" << tokens[i+5].value << ", ";
			while (tokens[i].value != ";")
			{	
				i++;
			}
			i++;
			// condition checking logic i < n - 1 into for x in range(0, n - 1)
			while(tokens[i].value!="<")
			{
				i++;
			}
			i++;
			// n - 1
			while(tokens[i].value!=";")
			{
				std::cout<<tokens[i].value;
				i++;
			}
			i++;
			std::cout<<")";
			// i++, probably could have more checks but currently only considering i++ as increment
			while(tokens[i].value!=")")
			{
				i++;
			}
			i++;
			printPyRec(i, indent);
			return;
		}
	}
	else if (tokens[i].type == "operator")
	{
		std::cout<<tokens[i].value;
		i++;
		printPyRec(i, indent);
		return;
	}
	else if (tokens[i].type == "seperator")
	{
		// case end
		if (tokens[i].value == "}" && i+2 >= tokenCount)
		{
			std::cout<<"\n";
			return;
		}
		// case {, start of a block, indent ++
		else if (tokens[i].value == "{")
		{
			indent++;
			i++;
			std::cout<<":\n";
			printIndent(indent);
			printPyRec(i, indent);
			return;
		}
		// case }, end of a block, indent --
		else if (tokens[i].value == "}")
		{
			std::cout<<"\n";
			indent--;
			i++;
			printIndent(indent);
			printPyRec(i, indent);
			return;
		}
		// case ;
		else if (tokens[i].value == ";")
		{
			i++;
			std::cout<<"\n";
			printIndent(indent);
			printPyRec(i, indent);
			return;
		}
		else 
		{
			std::cout<<tokens[i].value;
			i++;
			printPyRec(i, indent);
			return;
		}
	}
	else if (tokens[i].type == "integer")
	{
		std::cout << tokens[i].value;
		i++;
		printPyRec(i, indent);
		return;
	}
	else if (tokens[i].type == "real number")
	{
		std::cout << tokens[i].value;
		i++;
		printPyRec(i, indent);
		return;
	}
	else if (tokens[i].type == "valid identifier")
	{
		// ! case scanf
		// scanf("%d", &n); => n = input()
		if(tokens[i].value == "scanf")
		{
			while(tokens[i].value != ")")
			{
				i++;
			}

			std::cout<<tokens[i-1].value << " = input()";
			i++;
			printPyRec(i, indent);
			return;
		}

		// ! case printf, only considering the following two cases for simplicity
		// printf("%d ", n); => print(n, end = " ")
		// printf("False\n"); => print("False \n")
		if(tokens[i].value == "printf")
		{
			while(tokens[i].value != ")")
			{
				i++;
			}
			i--;
			// case of printf("something")
			if(tokens[i].value == "\"")
			{
				std::cout<<"print(";
				i--;
				while(tokens[i].value != "")
				{
					i--;
				}
				i++;
				while(tokens[i].value != "\"")
				{
					std::cout<<tokens[i].value;
					i++;
				}
				std::cout<<")";
				i++;
				printPyRec(i, indent);
				return;
			}
			else
			{	// !this is very specific case, only works for this program
				std::cout<<"print("<<tokens[i].value<<", end = \" \")";
			}
			i++;
			printPyRec(i, indent);
			return;
		}
		// ! case strlen
		// strlen(str)
		if(tokens[i].value == "strlen")
		{
			while(tokens[i].value != ")")
			{
				i++;
			}
			i--;
			std::cout<<"len("<<tokens[i].value<<")";
			i+=2;
			printPyRec(i, indent);
			return;
		}

		// else case
		std::cout << tokens[i].value;
		i++;
		printPyRec(i, indent);
		return;
	}
	return;
}

// DRIVER FUNCTION
int main()
{
	FILE *fp;
	fp = fopen("test2.c", "r");

	char source[1000];

	while (!feof(fp))
	{
		fgets(source, 1000, fp);
		parse(source);
	}

	// for (int i = 0; i < 20; i++)
	// {
	// 	tokens[i].value = "valid identifier";
	// }
	
	
	// for (int i = 0; i < tokenCount; i++)
	// {
	// 	printToken(tokens[i]);
	// }
	
	// int temp = 0;
	// printASTRec(temp);
	printPyRec(0, 0);
	return 0;
}
