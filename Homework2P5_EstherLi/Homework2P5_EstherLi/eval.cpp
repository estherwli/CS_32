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

	char operand1; 
	char operand2;
	stack<bool> operand; //holds all operands' bool values

	for (int i = 0; i < postfix.size(); i++) {
		char ch = postfix[i];
		if (isalpha(ch) && trueValues.contains(ch))
			operand.push(true); //store's corresponding bool
		else if (isalpha(ch) && falseValues.contains(ch))
			operand.push(false); //store's char's corresponding bool
		else if (ch == '!') {
			char temp = operand.top();
			operand.pop();
			operand.push(!temp); //pushes opposite value to stack
		}
		else {
			operand2 = operand.top(); //compares second-to-top and top operands
			operand.pop();
			operand1 = operand.top();
			operand.pop();
			switch (ch) {
			case '&':
				if (operand1 && operand2) 
					operand.push(true);
				else
					operand.push(false);
				break;
			case '|':
				if (operand1 || operand2)
					operand.push(true);
				else
					operand.push(false);
				break;
			}
		}
	}
	if (!operand.empty() && operand.top()) 
		result = true;
	else
		result = false;
	return 0; //successfully evaluated expression
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
			while (!operators.empty() && operators.top() != '(' && precedence(operators.top(), ch)) { //checks operator precedence
				postfix += operators.top();
				operators.pop();
			}
			operators.push(ch);
			break;
		case ' ':
			break;
		default:
			postfix += ch; //append chars that are just letters
		}
	}
	while (!operators.empty()) {
		postfix += operators.top(); //append operators after letters 
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

void test1()
{
	string trueChars = "tywz";
	string falseChars = "fnx";
	Set trues;
	Set falses;
	for (unsigned k = 0; k < trueChars.size(); k++)
		trues.insert(trueChars[k]);
	for (unsigned k = 0; k < falseChars.size(); k++)
		falses.insert(falseChars[k]);

	string pf;
	bool answer;

	//additional tests
	assert(evaluate("(w| f", trues, falses, pf, answer) == 1);
	assert(evaluate("(w| f)", trues, falses, pf, answer) == 0 && answer);
	assert(evaluate("(w| f)", trues, falses, pf, answer) == 0 && answer);
	assert(evaluate("(((w| f)))", trues, falses, pf, answer) == 0 && answer);
	assert(evaluate("((w)| (f))", trues, falses, pf, answer) == 0 && answer);
	assert(evaluate("((w)| (f)))", trues, falses, pf, answer) == 1 && answer);
	assert(evaluate("(W | f )", trues, falses, pf, answer) == 1 && answer); // upper case letter
	assert(evaluate("(0 | f )", trues, falses, pf, answer) == 1 && answer); // digit number
	cout << "Passed all tests in test1()" << endl;
}

void test2()  //Test cases
{
	string pf;
	bool answer;
	string trueChars = "t";
	string falseChars = "f";

	Set trues;
	Set falses;
	for (unsigned k = 0; k < trueChars.size(); k++)
		trues.insert(trueChars[k]);
	for (unsigned k = 0; k < falseChars.size(); k++)
		falses.insert(falseChars[k]);

	assert(evaluate("t| f", trues, falses, pf, answer) == 0 && pf == "tf|" && answer);
	assert(evaluate("t|", trues, falses, pf, answer) == 1);
	assert(evaluate("f f", trues, falses, pf, answer) == 1);
	assert(evaluate("tf", trues, falses, pf, answer) == 1);
	assert(evaluate("()", trues, falses, pf, answer) == 1);
	assert(evaluate("t(f|t)", trues, falses, pf, answer) == 1);
	assert(evaluate("t(&t)", trues, falses, pf, answer) == 1);
	assert(evaluate("(t&(f|f)", trues, falses, pf, answer) == 1);
	assert(evaluate("", trues, falses, pf, answer) == 1);
	assert(evaluate("f  |  !f & (t&f) ", trues, falses, pf, answer) == 0
		&& pf == "ff!tf&&|" && !answer);
	assert(evaluate(" f  ", trues, falses, pf, answer) == 0 && pf == "f" && !answer);
	assert(evaluate("((t))", trues, falses, pf, answer) == 0 && pf == "t"  &&  answer);
	assert(evaluate("t", trues, falses, pf, answer) == 0 && answer);
	assert(evaluate("(f)", trues, falses, pf, answer) == 0 && !answer);
	assert(evaluate("t&(f)", trues, falses, pf, answer) == 0 && !answer);
	assert(evaluate("t & !f", trues, falses, pf, answer) == 0 && answer);
	assert(evaluate("!(f|t)", trues, falses, pf, answer) == 0 && !answer);
	assert(evaluate("!f|t", trues, falses, pf, answer) == 0 && answer);
	assert(evaluate("t|f&f", trues, falses, pf, answer) == 0 && answer);
	assert(evaluate("t&!(f|t&t|f)|!!!(f&t&f)", trues, falses, pf, answer) == 0 && answer);
	assert(evaluate("f!", trues, falses, pf, answer) == 1);
	assert(evaluate("!f", trues, falses, pf, answer) == 0 && answer);
	assert(evaluate("dsvfwerg", trues, falses, pf, answer) == 1 && answer);
	cout << "Passed all tests in test2()" << endl;
}

void test3()
{
	string pf;
	bool answer;
	string trueChars = "abc";
	string falseChars = "defhijk";

	Set trues;
	Set falses;
	for (unsigned k = 0; k < trueChars.size(); k++)
		trues.insert(trueChars[k]);
	for (unsigned k = 0; k < falseChars.size(); k++)
		falses.insert(falseChars[k]);

	assert(evaluate("c", trues, falses, pf, answer) == 0 && pf == "c" && answer == true);
	assert(evaluate("c| d", trues, falses, pf, answer) == 0 && pf == "cd|"  &&  answer);
	assert(evaluate("(d)", trues, falses, pf, answer) == 0 && pf == "d" && !answer);
	assert(evaluate("c&(d)", trues, falses, pf, answer) == 0 && pf == "cd&" && !answer);
	assert(evaluate("a & !k", trues, falses, pf, answer) == 0 && pf == "ak!&" && answer);
	assert(evaluate("!(i|j)", trues, falses, pf, answer) == 0 && pf == "ij|!" && answer);
	assert(evaluate("!i|j", trues, falses, pf, answer) == 0 && pf == "i!j|" && answer);
	assert(evaluate("h|e&f", trues, falses, pf, answer) == 0 && pf == "hef&|" && !answer);
	assert(evaluate("b&!(k|b&b|k) | !!!(k&b&k)", trues, falses, pf, answer) == 0 && pf == "bkbb&|k|!&!!kb&k&!|" && answer);
	assert(evaluate("j|", trues, falses, pf, answer) == 1);
	assert(evaluate("e f", trues, falses, pf, answer) == 1);
	assert(evaluate("ab", trues, falses, pf, answer) == 1);
	assert(evaluate("()", trues, falses, pf, answer) == 1);
	assert(evaluate("c(k|j)", trues, falses, pf, answer) == 1);
	assert(evaluate("c(&j)", trues, falses, pf, answer) == 1);
	assert(evaluate("(h&(i|i)", trues, falses, pf, answer) == 1);
	assert(evaluate("", trues, falses, pf, answer) == 1);
	assert(evaluate("e  |  !d & (a&d) ", trues, falses, pf, answer) == 0 && pf == "ed!ad&&|" && !answer);
	assert(evaluate(" k  ", trues, falses, pf, answer) == 0 && pf == "k" && !answer);
	cout << "Passed all tests in test3()" << endl;
}

void test_spec()
{
	string trueChars = "tywz";
	string falseChars = "fnx";
	Set trues;
	Set falses;
	for (unsigned k = 0; k < trueChars.size(); k++)
		trues.insert(trueChars[k]);
	for (unsigned k = 0; k < falseChars.size(); k++)
		falses.insert(falseChars[k]);

	string pf;
	bool answer;
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

	cout << "Passed all tests in test_spec()" << endl;
}

int main()
{
	test1();
	test2();
	test3();
	test_spec();
}

