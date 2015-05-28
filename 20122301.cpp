#include <iostream>
#include <string.h>
#include "stack.h"

using namespace std;

int getPriority(char input);

int main(int argc, char *argv[]) {

    for(int j = 0; j < 50000; j++) {
        Stack s; // stack 선언
        int digit = 0; // 피연산자가 연속적으로 몇 번 들어왔는지 카운팅하기 위한 변수 
        int operation = 0; // 연산자가 연속적으로 몇 번 들어왔는지 카운팅하기 위한 변수
        char input[10000] = {0}; // input 배열 선언 및 초기화
        char output[10000] = {0}; // output 배열 선언 및 초기화
        int index = 0; // output을 인덱싱하기 위한 변수

        cin >> input;

        if(strlen(input) == 0) {
            break;
        }

        for(int i = 0; i < strlen(input); i++) {
            if((input[i] != '+') && (input[i] != '-') && (input[i] != '*') && (input[i] != '/') && (input[i] != '(') && (input[i] != ')')) { // 숫자일 경우
                digit++;

                if(i == 1 && operation > 0) { // 첫 입력이 unary일 경우 연산자 처리
                    output[index++] = s.top();
                    s.pop();
                }

                if((operation > 1)) { // unary 연산자 처리
                    if(input[i-2] != ')') { //두번째 전 연산자가 ) 가 아닐 때
                        if(input[i-1] == '+') { // unary 연산자가 +일 경우
                            s.pop();

                        } else if(input[i-1] == '-') { // unary 연산자가 -일 경우
                            s.pop();
                            output[index++] = '-'; // -를 output에 넣기

                        }
                    }
                }

                output[index++] = input[i]; // output에 value 넣기

                operation = 0;

            } else { // 연산자일 경우
                if((i != 0) && (digit >= 1)) { // digit이 0이 아니고, input[0]이 아닐 때 
                    if(output[index-1] != ' ') {
                        output[index++] = ' ';
                    }
                }

                digit = 0;
                operation++;

                if( !s.isEmpty() ) { // stack에 연산자가 있을 경우
                    int inValue; 
                    int newValue = getPriority(input[i]);
                    
                    if(s.top() == '(') { // ( 는 스택 안에 있을 때와 밖에 있을 때 우선순위가 다르므로
                        inValue = 3;
                    } else {
                        inValue = getPriority(s.top());
                    }

                    if(inValue <= newValue) { // 들어오는 연산자의 우선순위가 stack 안의 우선순위보다 작을 경우
                        if(operation < 2) { // unary 연산자가 아닐 경우에만
                            output[index++] = s.top();
                            s.pop();
                        }
                    }  
                }

                switch(input[i]) {
                    case '+':
                        s.push(input[i]);
                        break;

                    case '-':
                        s.push(input[i]);
                        break;

                    case '*':
                        s.push(input[i]);
                        break;

                    case '/':
                        s.push(input[i]);
                        break;

                    case '(':
                        s.push(input[i]);
                        break;

                    case ')': // ( 부터 스택 안에 있는 연산자 다 꺼냄
                        while(s.top() != '(') { // '(' 을 찾을 때까지 반복해야 됨
                            output[index++] = s.top();
                            output[index++] = ' ';

                            s.pop();
                        }

                        if(s.top() == '(') {
                            s.pop();
                        }

                        break;

                    default:
                        throw "Something wrong\n";
                }

                if(index != 0) {
                    if(output[index-1] != ' ') {
                        output[index++] = ' ';
                    }
                }
            }
        }

        while(!s.isEmpty()) { // input으로 받은 한 줄이 끝날 때까지 스택에 남아있는 걸 output 배열로 옮긴다.
            if(output[index-1] != ' ') {
                output[index++] = ' ';
            }
            output[index++] = s.top();
            s.pop();
        }

        cout << output << endl;
    }
    
    return 0;
}

int getPriority(char input) { // 연산자 우선순위
    int priority;

    switch(input) {
        case '+':
        case '-':
            priority = 2;

            break;

        case '*':
        case '/':
            priority = 1;

            break;
        case '(':
        case ')':
            priority = 0;

            break;
    }

    return priority;
}
