#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int coeff;
    int exp;
    struct Node* next;
} Node;
Node* createNode(int coeff, int exp) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = NULL;
    return newNode;
}
void insertTerm(Node** head, int coeff, int exp) {
    if (coeff == 0) return;
    Node* newNode = createNode(coeff, exp);
    if (*head == NULL || (*head)->exp < exp) {
        newNode->next = *head;
        *head = newNode;
        return;
    }
    Node* current = *head;
    Node* prev = NULL;

    while (current != NULL && current->exp > exp) {
        prev = current;
        current = current->next;
    }

    if (current != NULL && current->exp == exp) {
        current->coeff += coeff;
        free(newNode);
        if (current->coeff == 0) {  
            if (prev == NULL) {
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
        }
    } else {
        if (prev == NULL) {
            newNode->next = *head;
            *head = newNode;
        } else {
            newNode->next = current;
            prev->next = newNode;
        }
    }
}
Node* addPolynomials(Node* poly1, Node* poly2) {
    Node* result = NULL;

    while (poly1 != NULL && poly2 != NULL) {
        if (poly1->exp == poly2->exp) {
            int sumCoeff = poly1->coeff + poly2->coeff;
            insertTerm(&result, sumCoeff, poly1->exp);
            poly1 = poly1->next;
            poly2 = poly2->next;
        } else if (poly1->exp > poly2->exp) {
            insertTerm(&result, poly1->coeff, poly1->exp);
            poly1 = poly1->next;
        } else {
            insertTerm(&result, poly2->coeff, poly2->exp);
            poly2 = poly2->next;
        }
    }

    while (poly1 != NULL) {
        insertTerm(&result, poly1->coeff, poly1->exp);
        poly1 = poly1->next;
    }
    while (poly2 != NULL) {
        insertTerm(&result, poly2->coeff, poly2->exp);
        poly2 = poly2->next;
    }

    return result;
}
void printPolynomial(Node* poly) {
    if (poly == NULL) {
        printf("0");
        return;
    }
    while (poly != NULL) {
        if (poly != NULL && poly->coeff > 0 && poly != poly) printf("+");
        printf("%dx^%d", poly->coeff, poly->exp);
        poly = poly->next;
        if (poly != NULL) printf(" ");
    }
    printf("\n");
}
void inputPolynomial(Node** poly) {
    int terms, coeff, exp;
    printf("Enter number of terms: ");
    scanf("%d", &terms);

    for (int i = 0; i < terms; i++) {
        printf("Enter coefficient and exponent of term %d: ", i + 1);
        scanf("%d %d", &coeff, &exp);
        insertTerm(poly, coeff, exp);
    }
}
void freePolynomial(Node* poly) {
    Node* temp;
    while (poly != NULL) {
        temp = poly;
        poly = poly->next;
        free(temp);
    }
}
int main() {
    Node* poly1 = NULL;
    Node* poly2 = NULL;
    printf("Input first polynomial:\n");
    inputPolynomial(&poly1);
    printf("Input second polynomial:\n");
    inputPolynomial(&poly2);
    printf("Polynomial 1: ");
    printPolynomial(poly1);
    printf("Polynomial 2: ");
    printPolynomial(poly2);
    Node* sum = addPolynomials(poly1, poly2);
    printf("Sum: ");
    printPolynomial(sum);
    freePolynomial(poly1);
    freePolynomial(poly2);
    freePolynomial(sum);
    return 0;
}
