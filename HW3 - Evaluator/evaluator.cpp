#include <iostream>
#include <string>
#include <vector>

using namespace std;

int hasPrecedence(const string& val1, const string& val2){
    if ((val1 == "*" || val1 == "/") && (val2 == "+" || val2 == "-")){
        return 1;
    }
    return 0;
}
//Creates tokens for each operator (including paranthesis) and operands.
void parseExpr(const string& expr, vector<string>& tokens){
    string token = "";
    for (auto& c : expr){
        switch (c){
            case '-':
                if (token.length() == 0){
                    token += c;
                    break;
                }
            case '(':
            case ')':
            case '+':
            case '/':
            case '*':
                if (token.length() != 0){
                    tokens.push_back(token);
                }
                token = c;
                tokens.push_back(token);
                token = "";
                break;
            case ' ':
                break;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '.':
                token += c;
        }
    }
    if (token.length() != 0){
        tokens.push_back(token);
    }
}


int main(){
    string expr;
    vector<string> tokens;
    vector<string> postfix;
    cout << "Enter an expression: " << endl;
    cin.clear();
    getline(cin, expr);
    parseExpr(expr, tokens);
    return 0;
}
