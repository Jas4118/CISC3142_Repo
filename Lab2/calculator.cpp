#include <iostream>
#include <stack>
#include <locale>
#include <stdio.h>
#include <math.h>
using namespace std;
struct Calculator{

};

int orderOfOp(char op) { //Order of operations determined by number ordered PEMDAS
	if(op == '^'){
		return 3;
	}
	if(op == '*' || op == '/'){
		return 2;
	}
   	if(op == '+' || op == '-'){
      		return 1;                     
	}
      	return 0;	
}

int calcTwo(int a, int b, char op){ //Checks op and then calcs using two int parameters
	int answer;
	switch (op) {
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
	return answer;
}

string changeToPost(string s){ // changing to postfix taking in user input
	//stack to hold operators
	stack<char> op; 
	op.push('!');
	//string to return 
	string post= "";
	string::iterator it;

	for(it = s.begin(); it!=s.end(); it++){ // iterating through the user input
		if(isalnum(char(*it))){ //checks for alpha nurmerical at 'it'

         		post = post + *it; // appends

		}	
      		else if(*it == '('){// checks for open parenthesis first

         		op.push('(');// if found put into stack

		}
      		else if(*it == '^'){// checks for exponent since its highest after parenthesis

         		op.push('^');

		}
      		else if(*it == ')') {// checks for closed 

         		while(op.top() != '!' && op.top() != '(') {// once closed parenthesis is found  it keeps appending to the string until it reaches open parenthesis
           			post = post +" "+ op.top();
            			op.pop();

         		}
         		op.pop(); // pop the open parenthesis    
      		}
		else{

         		if(orderOfOp(*it) > orderOfOp(op.top())){ // checks for orderOfOp for priority of operations
            			op.push(*it); //current is higher than top so it gets pushed
				post=post + " "; 

			}
         		else{
            			while(op.top() != '!' && orderOfOp(*it) <= orderOfOp(op.top())) {// checks if current string operation is lower than stack

               				post = post + " " + op.top(); //appends
               				op.pop();

            			}

				post=post + " ";
            			op.push(*it);

         		}
      		}
   	}

   	while(op.top() != '!') {// pops out the rest
      		post = post +" "+ op.top();        
      		op.pop();
   	}

   	return post; // string in postfix
}
int calcPost(string postfix){
	
	stack<int> num; // int stack used to calculate
	int answer;
	num.push(-1); //push to prevent underflow
	
	string equ;
	string::iterator it;

	for(it = postfix.begin();it!=postfix.end();it++){//iterating through postfix
		if(*it == ' ') {//skips the whitespace created from changeToPostfix
			continue;
		}
		if(isdigit(*it)){// checks if string is num

			int number=0;
			while(isdigit(*it)){// checks next few char if num

				number = number *10 +(int)(*it - '0');// casts the string char to int and than add it to the number
				it++;

			}

			num.push(number); //full number is pushed to stack
			it--;

		}
		else{// if it hits operator
			
			int a = num.top();//pops two numbers to perform operation 
			num.pop();
			int b = num.top();
			num.pop();
			
			answer = calcTwo(a,b,*it);//checks for which operation to do
			num.push(answer);

		}
	}
	return num.top(); //answer is the top of stack

}

int main() {
	string equation;
	bool qEnter=true;
	
	// until user presses q it loops
	while(qEnter){
		cout << "Enter your equation ('q' to exit) : " << endl;
		cin >> equation;

		if(equation == "q"){
			qEnter=false;
			break;
		}
		//output
		cout << "Equation is " << equation << endl;
		cout << "Postfix notation: "<<changeToPost(equation) << endl;
		cout << "Evaluation result: " <<calcPost(changeToPost(equation))<<endl;
	}
}
