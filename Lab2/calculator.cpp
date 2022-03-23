#include <iostream>
#include <stack>
#include <locale>
#include <stdio.h>
#include <math.h>
using namespace std;
struct Calculator{
};

int orderOfOp(char ch) {
   	if(ch == '+' || ch == '-') 
      		return 1;          
   	if(ch == '*' || ch == '/') 
      		return 2;           
   	if(ch == '^') {
      		return 3;           
   	}
      	return 0;	
}

string changeToPost(string s){

	stack<char> op;
	op.push('!');
	string post= "";
	string::iterator it;

	for(it = s.begin(); it!=s.end(); it++){
		if(isalnum(char(*it))){

         		post = post + *it;

		}	
      		else if(*it == '('){

         		op.push('(');

		}
      		else if(*it == '^'){

         		op.push('^');

		}
      		else if(*it == ')') {

         		while(op.top() != '!' && op.top() != '(') {
           			post = post +" "+ op.top();
            			op.pop();

         		}
         		op.pop();     
      		}
		else{

         		if(orderOfOp(*it) > orderOfOp(op.top())){
            			op.push(*it);
				post=post + " ";

			}
         		else{
            			while(op.top() != '!' && orderOfOp(*it) <= orderOfOp(op.top())) {

               				post = post + " " + op.top(); 
               				op.pop();

            			}

				post=post + " ";
            			op.push(*it);

         		}
      		}
   	}

   	while(op.top() != '!') {
      		post = post +" "+ op.top();        
      		op.pop();
   	}

   	return post;
}
int calcPost(string postfix){

	stack<int> num;
	int answer;
	num.push(-1);
	string equ;
	string::iterator it;

	for(it = postfix.begin();it!=postfix.end();it++){
		if(*it == ' ') {
			continue;
		}
		if(isdigit(*it)){

			int number=0;
			while(isdigit(*it)){

				number = number *10 +(int)(*it - '0');
				it++;

			}

			num.push(number);
			it--;

		}
		else{

			int a = num.top();
			num.pop();
			int b = num.top();
			num.pop();

			switch (*it) {
				case '+':
					answer = b + a;
					break;
				case '-':
					answer = b - a;
					break;
				case '*':
					answer = b * a;
					break;
				case '/':
					answer = b / a;
					break;
				case '^':
					answer = pow(b , a);
					break;
			}

			num.push(answer);

		}
	}
	return num.top();

}

int main() {
	string equation;
	bool qEnter=true;
	while(qEnter){
		cout << "Enter your equation ('q' to exit) : " << endl;
		cin >> equation;

		if(equation == "q"){
			qEnter=false;
		}
		cout << "Equation is " << equation;
		cout << " "<<changeToPost(equation) << endl;
		cout << "Evaluation result: " <<calcPost(changeToPost(equation))<<endl;
	}
}
