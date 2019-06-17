#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <stack>
#include <string>
#include <cctype>
/*
 You will have to use matching opening and closing parenthesis' to get the right output
 Allowed Operators: Alphanumeric characters (a-z) ,(A-Z), (0-9)
 Allowed Operators:  '^'(Exponents), '*'(Multiplication), '/'(Division), '+'(Addition), '-'(Subtraction)
 Allowed Seperators: ' '(Blank Space), ','(Comma), ':'(Colon), ';'(Semi-Colon)
 */
using namespace std;
bool isOpening(char token) // Checking for an opening brace
{
    if(token == '(' || token == '{' || token == '[') return true;
    else return false;
}
char OpeningCharacter(char token) //Finding the corresponding opening character
{
  if(token == ')') return '(';
  else if (token == '}')  return '{';
  else if (token == ']')  return '[';
  else
   {
    cout<<"ERRORRRRR..........!!!!!\n" <<endl;
    exit(0);
   }
}
bool isClosing(char token) //Checking for a closing brace
{
    if(token == ')' || token == '}' || token == ']') return true;
    else return false;
}
bool isSeperator(char val) //Checking for a seperator
{
    if(val == ' ' || val == ',' || val ==':' || val == ';') return true;
    else return false;
}
bool isOperand(char value) //Checking for an operand
{
    if ( value >='0' && value <= '9' ) return true;
    if(isalpha(value)) return true;
    else return false;
}
bool isOperator(char value) //Checking for an operator
{
    if(value == '+' || value == '-' || value == '*' || value == '/' || value == '^') return true;
    else return false;
}
int OperatorPrecedence(char token) // Assigning order of precedence as per operator
{
    if( token == '^' ) return 1;
    else if( token == '*' || token == '/' )  return 2;
    else if ( token == '+' || token == '-' ) return 3;
    else
    {
     cout<<"\n There is no such token available please choose from '+' , '-' '*' ,'/' and '^'(for exponents) \n";
     exit(0);
    }
}
bool RightAssociativity(char symbol) // Right Associativity is true only for exponents
{
    if(symbol == '^') return true;
    else return false;
}
bool hasHigherPrecedence(char token1, char token2) //Operator with lower return values (higher precedence) has higher precedence 
{
    if(OperatorPrecedence(token1) < OperatorPrecedence(token2))
    {
        return true;
    } 
    else if( OperatorPrecedence(token1) == OperatorPrecedence(token2)) // If equal then it is true only for left associativity.
    {
        if(RightAssociativity(token1)) return false;
        else return true;
    }
    else 
     return false;
}

string InfixToPostfix(string expression) // A function to convert the infix expression to a Postfix expression
{
    string finalExp = "";
    char openingToken;
    stack<char> S;
    for(int i=0;i<expression.length();i++)
    {
        if(isSeperator(expression[i])) continue; // Skipping in case of seperator
        
        else if(isOperand(expression[i]) ) // Order of operand does not change so we append to final expression
        {
            finalExp+=expression[i];
        }
        
         if(isOpening(expression[i])) // Pushing opening brace to stack
         {
             S.push(expression[i]);
         }
         else if(isClosing(expression[i])) // Appending all operators to the final expression until it's opening brace is reached.
         {
             openingToken = OpeningCharacter(expression[i]);
             while( !S.empty() && S.top()!=openingToken)
             {
                if(isOpening(S.top()) && S.top()!=openingToken)
                {
                    cout<<"\nPlease make sure the opening and closing brackets are compliments of each other and try again..\n";
                    cout<<"Also, make sure that all opened brackes are closed correctly\n";
                    exit(0);
                }
                 finalExp+=S.top();
                 S.pop(); 
             }
             if(S.top()==openingToken)
              S.pop(); // Popping the opening brace
         }
         else if(isOperator(expression[i])) //Appending operators to the final expression as long operator in stack has higher precedence.
         {
         while(!S.empty() && !isOpening(S.top()) && hasHigherPrecedence(S.top(),expression[i]))
         {
            finalExp+=S.top();
            S.pop();
         }
         S.push(expression[i]);
        }
    }
    while(!S.empty()) // Appending all the remaining operators (if any) remaining in the stack
    {
        finalExp+=S.top();
        S.pop();
    }
    return finalExp; // Returning the final Postfix expression
}
int main()
{
    string expression;
    string Postfix_expression;
    cout<<"\n Enter the INFIX expression to be converted to a POSTFIX expresssion with all terms seprated by a ',' : \n";
    getline(cin,expression);
    Postfix_expression = InfixToPostfix(expression);
    cout<<"The POSTFIX expression is: " << Postfix_expression <<endl;
    return 0;
}