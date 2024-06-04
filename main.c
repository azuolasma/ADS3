#include "LOANS.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to calculate the monthly payment
float calculateMonthlyPayment(float principal, float annualRate, int term) {
    float monthlyRate = (annualRate / 12.0) / 100.0;
    return principal * (monthlyRate * pow(1 + monthlyRate, term)) / (pow(1 + monthlyRate, term) - 1);
}

// Function to simulate the outcome if we apply the strategy of paying loans by date in an ascending order (from oldest to newest)
void simulateMonthWithQueue(Loan *loan, float availableFunds, Queue *historyQueue, float *totalPaid) {
    float monthlyInterest = loan->originalAmount * (loan->interestRate / 12 / 100);
    float paymentDue = calculateMonthlyPayment(loan->originalAmount, loan->interestRate, loan->termMonths);

    float totalPayment = fmin(availableFunds, paymentDue + monthlyInterest);
    *totalPaid += totalPayment;

    float principalPaid = fmin(loan->originalAmount, totalPayment - monthlyInterest);
    loan->originalAmount -= principalPaid;
}

// Function to simulate the outcome if we pay the loan by priorities: principal, interest, late fees
void simulateMonthWithPriorityQueue(Loan *loan, float availableFunds, PriorityQueue *priorityQueue, float *totalPaid) {
    float monthlyInterest = loan->originalAmount * (loan->interestRate / 12 / 100);
    float lateFee = loan->originalAmount * (loan->lateInterestRate / 12 / 100);

    // Pay off the principal first (priority 1)
    float principalPayment = fmin(loan->originalAmount, availableFunds);
    availableFunds -= principalPayment;

    // Pay off the interest second (priority 2)
    float interestPayment = fmin(monthlyInterest, availableFunds);
    availableFunds -= interestPayment;

    // Pay off the late fees lastly (priority 3)
    float lateFeePayment = fmin(lateFee, availableFunds);

    *totalPaid += (principalPayment + interestPayment + lateFeePayment);
    loan->originalAmount -= principalPayment;
}

// Function to print nicely formatted results
void printResults(float totalPaidQueue, float totalPaidPriorityQueue) {
    printf("Total Paid with Queue: $%.2f\n", totalPaidQueue);
    printf("Total Paid with Priority Queue: $%.2f\n", totalPaidPriorityQueue);

    if (totalPaidQueue < totalPaidPriorityQueue) {
        printf("The Queue strategy is more beneficial, saving $%.2f.\n", totalPaidPriorityQueue - totalPaidQueue);
    } else if (totalPaidPriorityQueue < totalPaidQueue) {
        printf("The Priority Queue strategy is more beneficial, saving $%.2f.\n", totalPaidQueue - totalPaidPriorityQueue);
    } else {
        printf("Both strategies result in the same total payment of $%.2f. No savings between strategies.\n", totalPaidQueue);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 5) {
        printf("Usage: %s <originalAmount> <interestRate> <lateInterestRate> <termMonths>\n", argv[0]);
        return 1;
    }

    float originalAmount = atof(argv[1]);
    float interestRate = atof(argv[2]);
    float lateInterestRate = atof(argv[3]);
    int termMonths = atoi(argv[4]);

    // Initialize loans
    Loan loanQueue = {originalAmount, interestRate, lateInterestRate, termMonths, NULL};
    Loan loanPriorityQueue = {originalAmount, interestRate, lateInterestRate, termMonths, NULL};

    float monthlyPayment = calculateMonthlyPayment(originalAmount, interestRate, termMonths);

    // Initialize data structures
    Queue *historyQueue = CreateQueue();
    PriorityQueue *priorityQueue = createPriorityQueue(100);

    float totalPaidQueue = 0, totalPaidPriorityQueue = 0;

    // Simulate payment scenarios
    for (int month = 1; month <= termMonths; month++) {
        float availableFunds = monthlyPayment;
        simulateMonthWithQueue(&loanQueue, availableFunds, historyQueue, &totalPaidQueue);
        simulateMonthWithPriorityQueue(&loanPriorityQueue, availableFunds, priorityQueue, &totalPaidPriorityQueue);
    }

    // Printr results and comparisons
    printResults(totalPaidQueue, totalPaidPriorityQueue);

    // Clean up
    DestroyQueue(&historyQueue);
    destroyPriorityQueue(priorityQueue);

    return 0;
}
