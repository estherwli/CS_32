#include "Set.h"  // with ItemType being a type alias for char
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;

int evaluate(string infix, const Set& trueValues, const Set& falseValues, string& postfix, bool& result) {
	for (int i = 0; i < infix.size(); i++) {
		if (isalpha(infix[i]) && isupper(infix[i]))
			return 1;
	}
	for (int i = 0; i < infix.size(); i++) {
		if (!(trueValues.contains(infix[i]) && falseValues.contains(infix[i])) && (trueValues.contains(infix[i] || falseValues.contains(infix[i])))
			
	}
	

	//   If infix is a syntactically valid infix boolean expression whose
	//   only operands are single lower case letters:
	//
	//      If every operand letter in the expression appears in either
	//      trueValues or falseValues but not both, then result is set to the
	//      result of evaluating the expression (using for each letter in the
	//      expression the value true if that letter appears in trueValues or
	//      false if that letter appears in false values) and the function
	//      returns 0.
	//
	//      Otherwise, result is unchanged and the value the function returns
	//      depends on these two conditions:
	//        at least one letter in the expression is in neither the
	//            trueValues nor the falseValues sets; and
	//        at least one letter in the expression is in both the
	//            trueValues and the falseValues set.
	//      If only the first condition holds, the function returns 2; if
	//      only the second holds, the function returns 3.  If both hold
	//      the function returns either 2 or 3 (and the function is not
	//      required to return the same one if called another time with the
	//      same arguments).
}
