// CPP Program to generate minimum expression containing
// only given digit D that evaluates to number N.
#include <climits>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>

// limit of Digits in the expression
#define LIMIT 10

using namespace std;

// map that store if a number is seen or not
map<int, int> seen;

// stack for storing operators
stack<char> operators;
int minimum = LIMIT;

// function to find minimum levels in the recursive tree
void minLevel(int total, int N, int D, int level) {

// if total is equal to given N
if (total == N) {

	// store if level is minimum
	minimum = min(minimum, level);
	return;
}

// if the last level is reached
if (level == minimum)
	return;

// if total can be divided by D.
// recurse by dividing the total by D
if (total % D == 0)
	minLevel(total / D, N, D, level + 1);

// recurse for total + D
minLevel(total + D, N, D, level + 1);

// if total - D is greater than 0
if (total - D > 0)

	// recurse for total - D
	minLevel(total - D, N, D, level + 1);

// recurse for total multiply D
minLevel(total * D, N, D, level + 1);
}

// function to generate the minimum expression
bool generate(int total, int N, int D, int level) {
// if total is equal to N
if (total == N)
	return true;

// if the last level is reached
if (level == minimum)
	return false;

// if total is seen at level greater than current level
// or if we haven't seen total before. Mark the total
// as seen at current level
if (seen.find(total) == seen.end() ||
	seen.find(total)->second >= level) {
	
	seen[total] = level;

	int divide = INT_MAX;

	// if total is divisible by D
	if (total % D == 0) {
	divide = total / D;

	// if divide isn't seen before
	// mark it as seen
	if (seen.find(divide) == seen.end())
		seen[divide] = level + 1;
	}

	int addition = total + D;

	// if addition isn't seen before
	// mark it as seen
	if (seen.find(addition) == seen.end())
	seen[addition] = level + 1;

	int subtraction = INT_MAX;
	// if D can be subtracted from total
	if (total - D > 0) {
	subtraction = total - D;

	// if subtraction isn't seen before
	// mark it as seen
	if (seen.find(subtraction) == seen.end())
		seen[subtraction] = level + 1;
	}

	int multiply = total * D;

	// if multiply isn't seen before
	// mark it as seen
	if (seen.find(multiply) == seen.end())
	seen[multiply] = level + 1;

	// recurse by dividing the total if possible
	if (divide != INT_MAX)
	if (generate(divide, N, D, level + 1)) {

		// store the operator.
		operators.push('/');
		return true;
	}

	// recurse by adding D to total
	if (generate(addition, N, D, level + 1)) {

	// store the operator.
	operators.push('+');
	return true;
	}

	// recurse by subtracting D from total
	if (subtraction != INT_MAX)
	if (generate(subtraction, N, D, level + 1)) {

		// store the operator.
		operators.push('-');
		return true;
	}

	// recurse by multiplying D by total
	if (generate(multiply, N, D, level + 1)) {

	// store the operator.
	operators.push('*');
	return true;
	}
}

// expression is not found yet
return false;
}

// function to print the expression
void printExpression(int N, int D) {
// find minimum level
minLevel(D, N, D, 1);

// generate expression if possible
if (generate(D, N, D, 1)) {
	// stringstream for converting to D to string
	ostringstream num;
	num << D;

	string expression;

	// if stack is not empty
	if (!operators.empty()) {

	// concatenate D and operator at top of stack
	expression = num.str() + operators.top();
	operators.pop();
	}

	// until stack is empty
	// concatenate the operator with parenthesis for precedence
	while (!operators.empty()) {
	if (operators.top() == '/' || operators.top() == '*')
		expression = "(" + expression + num.str() + ")" + operators.top();
	else
		expression = expression + num.str() + operators.top();
	operators.pop();
	}

	expression = expression + num.str();

	// print the expression
	cout << "Expression: " << expression << endl;
}

// not possible within 10 digits.
else
	cout << "Expression not found!" << endl;
}

// Driver's Code
int main() {
int N = 7, D = 4;

// print the Expression if possible
printExpression(N, D);

// print expression for N =100, D =7
minimum = LIMIT;
printExpression(100, 7);

// print expression for N =200, D =9
minimum = LIMIT;
printExpression(200, 9);

return 0;
}
