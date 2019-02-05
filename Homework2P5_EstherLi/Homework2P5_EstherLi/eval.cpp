#include "Set.h"  // with ItemType being a type alias for char
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;


string infixToPostfix(string infix);
bool precedence(char me, char other);
bool checkOperators(string infix);
bool checkParentheses(string infix);
void removeSpace(string& infix);

int evaluate(string infix, const Set& trueValues, const Set& falseValues, string& postfix, bool& result) {

	removeSpace(infix);

	infix += ' '; //appends a white space to prevent index out of bounds in loops below

	for (int i = 0; i < infix.size() - 1; i++) {
		if (isalpha(infix[i])) {
			if (isupper(infix[i]) || isalpha(infix[i + 1])) //a letter is uppercase or followed by another letter
				return 1;
			if (!trueValues.contains(infix[i]) && !falseValues.contains(infix[i])) //a char is not in either set
				return 2;
			if (trueValues.contains(infix[i]) && falseValues.contains(infix[i])) //a char is in both sets
				return 3;
		}
		else if (infix[i] != '(' && infix[i] != ')' && infix[i] != '&' && infix[i] != '|' && infix[i] != '!') //if other symbols are used
			return 1;
	}
	if (!checkOperators(infix) || !checkParentheses(infix)) //check valid operator syntax and parentheses syntax
		return 1;

	postfix = infixToPostfix(infix); //convert infix to postfix

	char yes; //represents a char with true value 
	char no; //represents a char with false value
	for (int i = 0; i < trueValues.size(); i++) {
		char temp;
		trueValues.get(i, temp);
		if (!falseValues.contains(temp)) { //ensure the yes variable does not appear in both sets
			yes = temp;
			break;
		}
	}
	for (int i = 0; i < falseValues.size(); i++) {
		char temp;
		falseValues.get(i, temp);
		if (!trueValues.contains(temp)) { //ensure the no variable does not appear in both sets
			no = temp;
			break;
		}
	}

	char operand1;
	char operand2;
	stack<char> operand;

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
	string postfix = "";
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
			while (!operators.empty() && operators.top() != '(' && precedence(operators.top(), ch)) {
				postfix += operators.top();
				operators.pop();
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

bool precedence(char me, char other) { //returns true if me has higher or equal precedence than other
	if (me == '!')
		return true;
	else if (me == '&' && other != '!')
		return true;
	else if (me == '|' && other == '|')
		return true;
	else
		return false;
}

bool checkOperators(string infix) { //returns true if all operators are followed by valid characters
	if (infix.size() == 0)
		return false;
	if (!(isalpha(infix[0]) || infix[0] == '!' || infix[0] == '('))
		return false;
	for (int i = 0; i < infix.size() - 1; i++) {
		char ch = infix[i];
		char chnext = infix[i + 1];
		switch (ch) {
		case '&':
		case '|':
			if (isalpha(chnext) || chnext == '(' || chnext == '!') //checks '&' and '|' are followed by valid chars
				break;
			else
				return false;
		case '!':
			if (isalpha(chnext) || chnext == '!' || chnext == '(') //checks '!' is followed by valid chars
				break;
			else
				return false;
		case '(':
			if (isalpha(chnext) || chnext == '!' || chnext == '(') //checks '(' is followed by valid chars
				break;
			else
				return false;
		case ')':
			if (chnext == '|' || chnext == '&' || chnext == ')' || chnext == ' ') //checks ')' is followed by valid chars
				break;
			else
				return false;
		default:
			if (chnext == '|' || chnext == '&' || chnext == ')' || chnext == ' ') //if a letter is followed by valid opearator, or is the last 
				break;
			else
				return false;
		}
	}
	int n = infix.size() - 2;
	if (isalpha(infix[n]) || infix[n] == ')') //returns true if infix ends in a letter or ')'
		return true;
	else
		return false;
}


bool checkParentheses(string infix) {
	int count = 0;
	int operand = 0;
	for (int i = 0; i < infix.size(); i++) {
		if (infix[i] == '(') {
			if (i != 0 && !(infix[i - 1] == '(' || infix[i - 1] == '!' || infix[i - 1] == '&' || infix[i - 1] == '|'))
				return false;
			count++; //records number of '(' 
			operand = 0;
		}
		if (infix[i] == ')') {
			if (count <= 0 || operand == 0) //invalid syntax if no '(' or operand before ')'
				return false;
			else
				count--; //records number of ')'
		}
		if (count != 0 && isalpha(infix[i])) //if we're inside an open parenthesis, start recording number of operands
			operand++;
	}
	if (count != 0) //if number of '(' doesn't match number of ')'
		return false;
	else
		return true;
}

void removeSpace(string& infix) { //updates infix so it has no white space
	string noSpace;
	for (int i = 0; i < infix.size(); i++)
		if (infix[i] != ' ')
			noSpace += infix[i];
	infix = noSpace;
}

int main()
{
	Set t;
	Set f;
	t.insert('t');
	t.insert('x');
	f.insert('f');
	f.insert('x');
	string pf;
	bool answer;

	string trueChars = "tywz";
	string falseChars = "fnx";
	Set trues;
	Set falses;
	for (int k = 0; k < trueChars.size(); k++)
		trues.insert(trueChars[k]);
	for (int k = 0; k < falseChars.size(); k++)
		falses.insert(falseChars[k]);

	assert(evaluate("w| f", trues, falses, pf, answer) == 0 && pf == "wf|" &&  answer);
	assert(evaluate("y|", trues, falses, pf, answer) == 1);
	assert(evaluate("n t", trues, falses, pf, answer) == 1);
	assert(evaluate("nt", trues, falses, pf, answer) == 1);
	assert(evaluate("()", trues, falses, pf, answer) == 1);
	assert(evaluate("y(n|y)", trues, falses, pf, answer) == 1);
	assert(evaluate("t(&n)", trues, falses, pf, answer) == 1);
	assert(evaluate("(n&(t|7)", trues, falses, pf, answer) == 1);
	assert(evaluate("", trues, falses, pf, answer) == 1);
	assert(evaluate("f  |  !f & (t&n) ", trues, falses, pf, answer) == 0
		&& pf == "ff!tn&&|" && !answer);
	assert(evaluate(" x  ", trues, falses, pf, answer) == 0 && pf == "x" && !answer);
	trues.insert('x');
	assert(evaluate("((x))", trues, falses, pf, answer) == 3);
	falses.erase('x');
	assert(evaluate("((x))", trues, falses, pf, answer) == 0 && pf == "x"  &&  answer);
	trues.erase('w');
	assert(evaluate("w| f", trues, falses, pf, answer) == 2);
	falses.insert('w');
	assert(evaluate("w| f", trues, falses, pf, answer) == 0 && pf == "wf|" && !answer);
	
	assert(evaluate("x|t", t, f, pf, answer) == 3);
	assert(evaluate("b|t", t, f, pf, answer) == 2);
	assert(evaluate("t|t|t", t, f, pf, answer) == 0 && answer);
	assert(evaluate("!f&!f&!f", t, f, pf, answer) == 0 && answer);
	assert(evaluate("|", t, f, pf, answer) == 1);
	assert(evaluate("&", t, f, pf, answer) == 1);
	assert(evaluate("!", t, f, pf, answer) == 1);
	assert(evaluate("t!", t, f, pf, answer) == 1);
	assert(evaluate("t&", t, f, pf, answer) == 1);
	assert(evaluate("t|", t, f, pf, answer) == 1);
	assert(evaluate("|&", t, f, pf, answer) == 1);
	assert(evaluate("|!", t, f, pf, answer) == 1);
	assert(evaluate("||", t, f, pf, answer) == 1);
	assert(evaluate("&&", t, f, pf, answer) == 1);
	assert(evaluate("&!", t, f, pf, answer) == 1);
	assert(evaluate("&|", t, f, pf, answer) == 1);
	assert(evaluate("!!", t, f, pf, answer) == 1);
	assert(evaluate("!|", t, f, pf, answer) == 1);
	assert(evaluate("!&", t, f, pf, answer) == 1);
	assert(evaluate("", t, f, pf, answer) == 1);
	assert(evaluate("t", t, f, pf, answer) == 0 && answer);
	assert(evaluate("|!", t, f, pf, answer) == 1);
	assert(evaluate("||", t, f, pf, answer) == 1);
	assert(evaluate("&&", t, f, pf, answer) == 1);
	assert(evaluate("t|", t, f, pf, answer) == 1);
	assert(evaluate("f f", t, f, pf, answer) == 1);
	assert(evaluate("tf", t, f, pf, answer) == 1);
	assert(evaluate("()", t, f, pf, answer) == 1);
	assert(evaluate("t(f|t)", t, f, pf, answer) == 1);
	assert(evaluate("t(&t)", t, f, pf, answer) == 1);
	assert(evaluate("(t&(f|f)", t, f, pf, answer) == 1);
	assert(evaluate("", t, f, pf, answer) == 1);
	assert(evaluate("f  |  !f & (t&f) ", t, f, pf, answer) == 0
		&& pf == "ff!tf&&|" && !answer);
	assert(evaluate(" f  ", t, f, pf, answer) == 0 && pf == "f" && !answer);
	assert(evaluate("((t))", t, f, pf, answer) == 0 && pf == "t"  &&  answer);
	assert(evaluate("t", t, f, pf, answer) == 0 && answer);
	assert(evaluate("(f)", t, f, pf, answer) == 0 && !answer);
	assert(evaluate("t&(f)", t, f, pf, answer) == 0 && !answer);
	assert(evaluate("t & !f", t, f, pf, answer) == 0 && answer);
	assert(evaluate("!(f|t)", t, f, pf, answer) == 0 && !answer);
	assert(evaluate("!f|t", t, f, pf, answer) == 0 && answer);
	assert(evaluate("t|f&f", t, f, pf, answer) == 0 && answer);
	assert(evaluate("t&!(f|t&t|f)|!!!(f&t&f)", t, f, pf, answer) == 0 && answer);
	assert(evaluate("f!", t, f, pf, answer) == 1);
	assert(evaluate("!f", t, f, pf, answer) == 0 && answer);
	assert(evaluate("dsvfwerg", t, f, pf, answer) == 1 && answer);
	cout << "Passed all tests" << endl;
}