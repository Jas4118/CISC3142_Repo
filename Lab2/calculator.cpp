//Jason Li CISC 3142
//Professor Katherine Chuang
//Lab 2

#include <iostream>
#include <stack>
#include <locale>
#include <stdio.h>
#include <math.h>
using namespace std;
struct Calculator{
};
//Due to time-constraints I didn't implement enum
//This program is a calculator that allows the user to input an expression
//Expression is then changed to postfix notation to make calculations easier than infix

int orderOfOp(char op) { //Order of operations is used to compare which one has higher priority
	if(op == '^') {
      		return 3;   
	}
	if(op == '*' || op == '/') {
      		return 2;   
	}
   	if(op == '+' || op == '-') {
      		return 1; 
	}
      	return 0;	
}

string changeToPost(string s){
	//initializing stack and pushing to prevent segmentation fault
	stack<char> op;
	op.push('!');
	
	string post= "";
	string::iterator it;
	
	//for loop to check for every character in entered string
	for(it = s.begin(); it!=s.end(); it++){
		if(isalnum(char(*it))){ // adds alphanumericals into string post which is the string we return

         		post = post + *it;

		}	
      		else if(*it == '('){ // checks for open parenthesis if number wasn't found

         		op.push('(');

		}
      		else if(*it == '^'){ // checks for exponent if open parenthesis or number wasn't found

         		op.push('^');

		}
      		else if(*it == ')') { // on closed parenthesis the program checks the stack making sure while the top isn't ! or ( it will add numbers

         		while(op.top() != '!' && op.top() != '(') {
           			post = post +" "+ op.top();
            			op.pop();

         		}
         		op.pop();   //pop out the open parenthesis
      		}
		else{

         		if(orderOfOp(*it) > orderOfOp(op.top())){ // pushing based on operators order of operations
            			op.push(*it);
				post=post + " ";

			}
         		else{
            			while(op.top() != '!' && orderOfOp(*it) <= orderOfOp(op.top())) { //

               				post = post + " " + op.top(); 
               				op.pop();

            			}
				//
				post=post + " ";
            			op.push(*it);

         		}
      		}
   	}

   	while(op.top() != '!') {// pop out of stack until empty
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
		if(*it == ' ') { //Skips whitespace in postfix form
			continue;
		}
		if(isdigit(*it)){ //Checks for first digit it hits

			int number=0;
			while(isdigit(*it)){ //While there are digits multiplying each char by 10 to increase place value and make full number

				number = number *10 +(int)(*it - '0');
				it++;

			}

			num.push(number);
			it--;

		}//Operator
		else{
			//numbers to be added
			int a = num.top();
			num.pop();
			int b = num.top();
			num.pop();
			//checks operator and uses specific case
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
			//push the answer back to stack
			num.push(answer);

		}
	}
	//only num.top() has the answer within the stack
	return num.top();

}

int main() {
	string equation;
	bool qEnter=true; //value to break out of loop
	while(qEnter){// program ends with q
		cout << "Enter your equation ('q' to exit) : " << endl;
		cin >> equation;

		if(equation == "q"){
			qEnter=false;
			break;
		}
		//output
		cout << "Equation is " << equation;
		cout << " "<<changeToPost(equation) << endl;
		cout << "Evaluation result: " <<calcPost(changeToPost(equation))<<endl;
	}
}
