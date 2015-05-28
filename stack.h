class Stack {
    private:
        char* stack;
        int capacity, tail;

    public:
        Stack(int stackCapacity = 10);
        ~Stack();

        bool isEmpty();
        char& top();
        void push(char item);
        void pop();
};
