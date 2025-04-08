int stack[100];
int tos = 0;            //top of stack

void push(int data){ // -> TODO: check overflow
    stack[tos++] = data;
    // stack[tos] = data;
    // ++tos;
}

int pop(void){ // -> TODO: check underflow
    return stack[--tos];
    // tos--;
    // return stack[tos];
}
