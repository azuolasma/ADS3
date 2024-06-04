#ifndef LOANS_H
#define LOANS_H

typedef struct PaymentNode {
    float paymentAmount;        // Total amount paid that month
    float principlePaid;        // Amount of payment applied to the principal
    float interestPaid;         // Amount of payment applied to the interest
    float lateFeesPaid;         // Amount of payment applied to late fees
    struct PaymentNode *next;   // Pointer to the next month's payment
} PaymentNode;

typedef struct Loan {
    float originalAmount;       // The original amount of the loan
    float interestRate;         // Annual interest rate of the loan
    float lateInterestRate;     // Additional interest rate applied for late payments
    int termMonths;             // Total duration of the loan in months
    PaymentNode *paymentHistory;// Pointer to a linked list of PaymentNodes
} Loan;

//Loan IssueLoan(float originalAmount, float interestRate, float,);
//void SettleOldestDebts(Queue *loans, float availableCash);
//void SettleDebtsByPriority(Node* priorityLoans, float availableCash);

// Module owner: azma9922
typedef struct Priority_queue {
    PaymentNode **data;         // Array to store pointers to individual month nodes in the priority queue
    int *priorities;            // Corresponding array of priorities 1 - principle, 2 - interest, 3 - late fees (1 is highest priority)
    int size;                   // Number of elements in the priority queue
    int capacity;               // Total capacity of the priority queue
} PriorityQueue;

PriorityQueue* createPriorityQueue(int initialCapacity);
int isEmpty(PriorityQueue *pq);
int isFull(PriorityQueue *pq);
void enqueue(PriorityQueue *pq, PaymentNode *element, int priority);
PaymentNode* dequeue(PriorityQueue *pq);
PaymentNode* peek(PriorityQueue *pq);
void destroyPriorityQueue(PriorityQueue *pq);

// Module owner: iesi9959
typedef struct Queue
{
    int front;
    int tail;
    int size;
    int capacity;
    PaymentNode **array;          // Array of pointers to PaymentNode elements
} Queue;

Queue* CreateQueue();
int isQueueEmpty(Queue *queue);
int isQueueFull(Queue *queue);
void Enqueue(Queue *queue, PaymentNode *data);
PaymentNode* Dequeue(Queue *queue);
PaymentNode* GetFrontData(Queue *queue);
int GetQueueSize(Queue *queue);
void DestroyQueue(Queue **queuePointer);
#endif // LOANS_H
