#include <iostream>
using namespace std;
class Stack {
    private:
        int maxLength,top;
        char* stackPtr;
    public:
        Stack(){
            this->maxLength = 20;
            this->stackPtr = (char*) malloc(this->maxLength*sizeof(char));
            this->top = -1;
        }
        int is_empty(){
            return (this->top == -1) ? 1:0;
        }
        int is_full(){
            return (this->top == this->maxLength-1) ? 1:0;
        }
        int push(char input_var){
            if(!this->is_full()){
                this->top++;
                *(this->stackPtr+this->top)=input_var;
                return 1;
            }
            else{
                return 0;
            }
        }
        char pop(){
            if(!this->is_empty()){
                char return_var = *(this->stackPtr+this->top);
                this->top--;
                return return_var;
            }
            else{
                return 0;
            }
        }
        int get_top_val(){
            return this->top;
        }
};
class Operation : public Stack{
    private:
        string infix,postfix;
    public:
        Operation(){
            cout<<"Please enter arethmetic operation : ";
            cin>>this->infix;
        }
        bool is_operator(char item){
            int i=0;
            char operator_array[5] = {'+','-','/','*','^'};
            while(i<5){
                if(item == operator_array[i]){
                    return true;
                }
                else{
                    i++;
                }
            }
            return false;
        }
        int precedence(char item){
            int return_val;
            switch(item){
                case '+':
                    return_val = 1;
                    break;
                case '-':
                    return_val = 1;
                    break;
                case '*':
                    return_val = 2;
                    break;
                case '/':
                    return_val = 2;
                    break;
                case '^':
                    return_val = 3;
                    break;
            }
            return return_val;
        }
        void infixToPostfix(){
            int i=0,j=0,topVal;
            char item,stackitem;
            while(this->infix[i]!='\0'){
                item = infix[i];
                i++;
                if(item =='('){
                    this->push(item);
                }
                else if((item >= 'A' && item <= 'Z') || (item >= 'a' && item <= 'z')){
                    postfix[j] = item;
                    j++;
                }
                else if(this->is_operator(item)==true){
                    stackitem = this->pop();
                    while(this->is_operator(stackitem)==true && (this->precedence(stackitem)>=this->precedence(item))){
                        postfix[j] = stackitem;
                        j++;
                        stackitem = this->pop();
                    }
                    this->push(stackitem);
                    this->push(item);
                }
                else if(item == ')'){
                    stackitem = this->pop();
                    while(stackitem != '('){
                        postfix[j] = stackitem;
                        j++;
                        stackitem = this->pop();
                    }
                }
            }
            topVal = this->get_top_val();
            while(topVal>-1){
                postfix[j] = this->pop();
                j++;
                topVal = this->get_top_val();
            }
        }
        void getPostfix(){
            int i=0;
            while(postfix[i]!='\0'){
                cout<<postfix[i];
                i++;
            }
            cout<<endl;
        }
};

int main(){
    Operation operationobj;
    operationobj.infixToPostfix();
    operationobj.getPostfix();
    return 0;
}