#include <iostream>
#include <stack>
#include <string>
#include <cctype>

using namespace std;

// Define a binary tree node to represent expressions
struct TreeNode {
    char value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(char val) : value(val), left(nullptr), right(nullptr) {}
};

// Function to check if a character is an operator (+, -, *, /)
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Function to build an expression tree from a string
TreeNode* buildExpressionTree(const string& expression) {
    stack<TreeNode*> treeStack;
    stack<char> operatorStack;

    for (char c : expression) {
        if (isspace(c)) {
            continue; // Skip whitespace
        } else if (isdigit(c)) {
            TreeNode* newNode = new TreeNode(c);
            treeStack.push(newNode);
        } else if (isOperator(c)) {
            while (!operatorStack.empty() && operatorStack.top() != '(' && 
                   ((c == '+' || c == '-') && (operatorStack.top() == '*' || operatorStack.top() == '/'))) {
                TreeNode* rightOperand = treeStack.top();
                treeStack.pop();
                TreeNode* leftOperand = treeStack.top();
                treeStack.pop();
                TreeNode* operatorNode = new TreeNode(operatorStack.top());
                operatorStack.pop();

                operatorNode->left = leftOperand;
                operatorNode->right = rightOperand;

                treeStack.push(operatorNode);
            }
            operatorStack.push(c);
        } else if (c == '(') {
            operatorStack.push(c);
        } else if (c == ')') {
            while (!operatorStack.empty() && operatorStack.top() != '(') {
                TreeNode* rightOperand = treeStack.top();
                treeStack.pop();
                TreeNode* leftOperand = treeStack.top();
                treeStack.pop();
                TreeNode* operatorNode = new TreeNode(operatorStack.top());
                operatorStack.pop();

                operatorNode->left = leftOperand;
                operatorNode->right = rightOperand;

                treeStack.push(operatorNode);
            }
            operatorStack.pop(); // Pop the '('
        }
    }

    while (!operatorStack.empty()) {
        TreeNode* rightOperand = treeStack.top();
        treeStack.pop();
        TreeNode* leftOperand = treeStack.top();
        treeStack.pop();
        TreeNode* operatorNode = new TreeNode(operatorStack.top());
        operatorStack.pop();

        operatorNode->left = leftOperand;
        operatorNode->right = rightOperand;

        treeStack.push(operatorNode);
    }

    return treeStack.top();
}

// Function to evaluate an expression tree
int evaluateExpression(TreeNode* root) {
    if (!root) {
        return 0;
    }
    if (!root->left && !root->right) {
        return root->value - '0';
    }

    int leftVal = evaluateExpression(root->left);
    int rightVal = evaluateExpression(root->right);

    switch (root->value) {
        case '+': return leftVal + rightVal;
        case '-': return leftVal - rightVal;
        case '*': return leftVal * rightVal;
        case '/': return leftVal / rightVal;
        default: return 0; // Handle invalid operators
    }
}

int main() {
    string expression;
    cout << "Enter an arithmetic expression: ";
    getline(cin, expression);

    TreeNode* expressionTree = buildExpressionTree(expression);
    int result = evaluateExpression(expressionTree);

    cout << "Result: " << result << endl;

    return 0;
}
