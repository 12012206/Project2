#include <iostream>
#include <stack>
using namespace std;
stack<int> numbers;
stack<char> operators;
int priority(char c) {  //判断运算符优先级
  switch (c) {
    case '+':
    case '-':
      return 1;
      break;
    case '*':
    case '/':
    case '%':
      return 2;
      break;
    case '(':
    default:
      return 0;
      break;
  }
}
void calculator() {  //实现运算符计算
  int num2 = numbers.top();
  numbers.pop();
  int num1 = numbers.top();
  numbers.pop();
  char c = operators.top();
  operators.pop();
  switch (c) {
    case ('+'):
      numbers.push(num1 + num2);
      break;
    case ('-'):
      numbers.push(num1 - num2);
      break;
    case ('*'):
      numbers.push(num1 * num2);
      break;
    case ('/'):
      numbers.push(num1 / num2);
      break;
    case ('%'):
      numbers.push(num1 % num2);
      break;
    default:
      break;
  }
}
int main() {
  string s;
  cin >> s;
  for (int i = 0; i < s.size(); i++) {
    char c = s[i];
    if (isdigit(c)) {
      int num = 0;
      int j = i;
      while (j < s.size() && isdigit(s[j])) {  //获取数字
        num = num * 10 + s[j] - '0';
        j++;
      }
      numbers.push(num);
      i = j - 1;
    } else if (c == '(') {
      operators.push(c);
    } else if (c == ')') {  //括号内计算
      while (!operators.empty() && operators.top() != '(') {
        calculator();
      }
      operators.pop();
    } else {
      while (!operators.empty() &&
             priority(operators.top()) >= priority(c)) {  //按优先级计算
        calculator();
      }
      operators.push(c);
    }
  }
  while (!operators.empty()) {  //完成可能剩余的计算
    calculator();
  }
  cout << numbers.top() << "\n";  //输出位于栈顶的最终结果
  return 0;
}