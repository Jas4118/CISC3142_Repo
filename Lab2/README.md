# CISC 3142 Lab 2 Jason Li
# Professor Katherine Chuang
This is a calculator program. 
At first I was thinking of using two stacks to hold the numbers and operators, but I saw there was an easier solution in making it in postfix notation and then parsing the string.
While making the program I found it difficult dealing with strings in C++ and due to time constraints not allowing me to, I ended up not including several features.
One of issues is that this program doesn't allow float points or whitespace in the input. I've added an image including test cases due to my console having issues copying from it.
What the program does is that it sets the user input 'equation' into a postfix notation string with whitespace inbetween each using a method called changeToPost. changeToPost sorts the string by going through each character and checking by priority whether its a number.
It then goes through several else if statements pushing depending on priority. If the string sees a) it will append to string post and add a whitespace in between.
If the program doesn't see any numbers, parenthesis or exponent, then the program assumes it is an operator and then push by comparing order of operations.
The final loop checks for any other operators/numbers in the stack and pops it into the string post and returns post to the method.

Afterwards, we use a function called calcPost which essentially loops through the postfix equation. It skips any of the whitespace and checks if the char is a number with isdigit(it).
It keeps checking the characters for digits until there isn't and pushs the full number calculated into the variable number. If the loop does reach something that isn't a number, then the stack is popped twice for each number to be added, subtracted, multiplied, divided or used with an exponent.
The answer is then pushed to the stack and then it continues until the only thing in the stack is the answer.

The main method() has a boolean value called qEnter which is set to true. Until the user types q, the user is allowed to keep using the loop. 
User is only allowed to enter strings that have no whitespace. If there is only one of a open parenthesis or closed parenthesis the program will have segmentation fault. Those are current bugs I have found. Otherwise the program will take no whitespace input and translate it to postfix.
After that the program translates that postfix notation and evaluates the string to an int. Once the user types q it breaks out of the program.
