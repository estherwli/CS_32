class Set;

#include "Set.h"  // with ItemType being a type alias for char
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;


string infixToPostfix(string infix);
bool precedence(char me, char other);

int evaluate(string infix, const Set& trueValues, const Set& falseValues, string& postfix, bool& result) {
	for (int i = 0; i < infix.size() - 1; i++) {
		if (isalpha(infix[i])) {
			if (isupper(infix[i]) || isalpha(infix[i + 1]))
				return 1;
			if (trueValues.contains(infix[i]) && falseValues.contains(infix[i]))
				return 2;
			if (!trueValues.contains(infix[i]) && !falseValues.contains(infix[i]))
				return 3;
		}			
		else if (infix[i] != '&' && infix[i] != '|' && infix[i] != '!' && infix[i] != ' ')
			return 1;
	}

	postfix = infixToPostfix(infix);

	char operand1;
	char operand2;
	stack<char> operand;
	char yes;
	char no;
	trueValues.get(0, yes);
	falseValues.get(0, no);

	for (int i = 0; i < postfix.size(); i++) {
		char ch = postfix[i];
		if (isalpha(ch))
			operand.push(ch);
		else if (ch == '!') {
			char temp = operand.top();
			operand.pop();
			if (trueValues.contains(temp))
				operand.push(no);
			else if (falseValues.contains(temp))
				operand.push(yes);
		}
		else {
			operand2 = operand.top();
			operand.pop();
			operand1 = operand.top();
			operand.pop();
			switch (ch) {
			case '&':
				if (trueValues.contains(operand1) && trueValues.contains(operand2))
					operand.push(yes);
				else
					operand.push(no);
				break;
			case '|':
				if (trueValues.contains(operand1) || trueValues.contains(operand2))
					operand.push(yes);
				else
					operand.push(no);
				break;
			}
		}
	}
	if (trueValues.contains(operand.top()))
		result = true;
	else
		result = false;
	return 0;
}


string infixToPostfix(string infix) {
	string postfix;
	stack<char> operators;
	for (int i = 0; i < infix.size(); i++) {
		char ch = infix[i];
		switch (ch) {
		case '(':
			operators.push(ch);
			break;
		case ')':
			while (operators.top() != '(') { // pop stack until matching '('
				postfix += operators.top();
				operators.pop();
			}
			operators.pop(); //pop '('
			break;
		case '&':
		case '|':
		case '!':
			while (!operators.empty() && operators.top() != '(') {
				if (operators.top() == '&' || operators.top() == '|' || operators.top() == '!')
					if (precedence(operators.top(), ch)) {
						postfix += operators.top();
						operators.pop();
					}
			}
			operators.push(ch);
			break;
		case ' ':
			break;
		default:
			postfix += ch;
		}
	}
	while (!operators.empty()) {
		postfix += operators.top();
		operators.pop();
	}
	return postfix;
}

bool precedence(char me, char other) {
	if (me == '!')
		return true;
	if ((me == '&' && other == '|') || (me == '&' && other == '&'))
		return true;
	if (me == '|' && other == '|')
		return true;
	else
		return false;
}

int main()
{
	string trueChars = "tywz";
	string falseChars = "fnx";
	Set trues;
	Set falses;
	for (int k = 0; k < trueChars.size(); k++)
		trues.insert(trueChars[k]);
	for (int k = 0; k < falseChars.size(); k++)
		falses.insert(falseChars[k]);

	string pf;
	bool answer;
	assert(evaluate("w| f", trues, falses, pf, answer) == 0 && pf == "wf|" &&  answer);
	assert(evaluate("y|", trues, falses, pf, answer) == 1);
	
	cout << "Passed all tests" << endl;
}