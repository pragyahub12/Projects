#include<stdio.h>
#include<stdlib.h>
#include"BigInteger.h"
struct node* truncate(struct node* head) {
    struct node* newHead = NULL;
    struct node* current = head;
    int leadingZeros = 1; 

    while (current != NULL) {
        if (current->data != 0) {
            leadingZeros = 0;
        }

        if (!leadingZeros) {
           
            insert(current->data, &newHead);
        }

        current = current->next;
    }

    if (newHead == NULL) {
        
        insert(0, &newHead);
    }

    return newHead;
}
int length(struct node *head)
{
  int count=0;
  while(head)
  {
    count++;
    head=head->next;
  }
  return count;
}
int compare(struct BigInteger n1, struct BigInteger n2) {
  
    if (n1.sign < n2.sign)
        return -1;
    if (n1.sign > n2.sign)
        return 1;

    int len1 = length(n1.head);
    int len2 = length(n2.head);
    if (len1 < len2)
        return -1;
    if (len1 > len2)
        return 1;

   
    struct node* p1 = n1.head;
    struct node* p2 = n2.head;

    while (p1 != NULL) {
        if (p1->data < p2->data)
            return -1;
        if (p1->data > p2->data)
            return 1;
        p1 = p1->next;
        p2 = p2->next;
    }

    
    return 0;
}
void insert(int data,struct node **head)
{
    struct node *temp=(struct node *)malloc(sizeof(struct node ));
    temp->data=data;
    temp->next=NULL;
    if(*head==NULL)
    {
        *head=temp;
         return;
     }
     temp->next=*head;
     *head=temp;
}
struct node *newnode(int val)
{
   struct node *temp=(struct node *)malloc(sizeof(struct node ));
   if(temp==NULL)
   {
      printf("memory not allocated\n");
      exit(EXIT_FAILURE);
   }
   temp->data=val;
   temp->next=NULL;
    return temp;
}
struct BigInteger initialize(char *s)
{
    struct BigInteger num;
    int i=0;
    num.length=0;
    num.head=NULL;
    if(s[i]=='-')
    {
      num.sign=1;
      i++;
    }
    else
    {
      num.sign=0;
    }
    while(s[i]!='\0') 
    {
       insert(s[i]-'0',&(num.head));
       i++;
    }
    return num;
}

struct BigInteger add(struct BigInteger n1, struct BigInteger n2) {
    struct BigInteger res;

    
    if (n1.sign == 1 && n2.sign == 0) {
      
        n1.sign = 0;
        n2.sign = 0;
        return sub(n1, n2);
    }

   
    if (n1.sign == 0 && n2.sign == 1) {
     
        n2.sign = 0;
        return sub(n1, n2);
    }

  
    if (n1.sign == 1 && n2.sign == 1) {
        
        n1.sign = 0;
        n2.sign = 0;
        res = add(n1, n2);
        res.sign = 1;
    }

    struct node *p1 = n1.head;
    struct node *p2 = n2.head;
    struct node *add_res = NULL;
    int carry = 0;
    int sum = 0;

    while (p1 != NULL || p2 != NULL) {
        sum = carry + (p1 ? p1->data : 0) + (p2 ? p2->data : 0);
        carry = sum / 10;
        struct node *temp = newnode(sum % 10);

        if (add_res == NULL) {
            add_res = temp;
        } else {
            temp->next = add_res;
            add_res = temp;
        }

        if (p1)
            p1 = p1->next;
        if (p2)
            p2 = p2->next;
    }

    if (carry > 0) {
        struct node *temp = newnode(carry);
        temp->next = add_res;
        add_res = temp;
    }

    res.head = add_res;

    return res;
}
struct BigInteger sub(struct BigInteger n1, struct BigInteger n2) {
    struct BigInteger res;
    struct node *p1 = n1.head;
    struct node *p2 = n2.head;
    struct node *sub_res = NULL;
    int borrow = 0;
    struct BigInteger temp;
    int com;
    com = compare(n1, n2);
    int sign1 = n1.sign;
    int sign2 = n2.sign;

    if (sign1 == 1 && sign2 == 1) {
        if (compare(n1, n2) == 1) {
         
            res.sign = 1;
        } else if (com == -1) {
           
            res.sign = 0;
            temp = n1;
            n1 = n2;
            n2 = temp;
            p1 = n1.head;
            p2 = n2.head;
        } else {
           
            res.sign = 1;
        }
    } else if (sign1 == 1 && sign2 == 0) {
      
        res.sign = 1;
        return add(n1, n2);
    } else if (sign1 == 0 && sign2 == 1) {

        res.sign = 0;
        return add(n1, n2);
    } else {
        if (com == -1) {
           
            res.sign = 1;
            temp = n1;
            n1 = n2;
            n2 = temp;
            p1 = n1.head;
            p2 = n2.head;
        } else if (com == 0) {
         
            res.sign = 0;
        }
    }

    while (p1 != NULL || p2 != NULL) {
        int diff = (p1 ? p1->data : 0) - (p2 ? p2->data : 0) - borrow;
        if (diff < 0) {
            diff += 10; 
            borrow = 1;
        } else {
            borrow = 0; 
        }

        struct node *temp = newnode(diff);

        if (sub_res == NULL) {
            sub_res = temp;
        } else {
            temp->next = sub_res;
            sub_res = temp;
        }

        if (p1)
            p1 = p1->next;
        if (p2)
            p2 = p2->next;
    }

   
    struct node* reversedResult = NULL;
    struct node* current = truncate(sub_res);
    while (current != NULL) {
        insert(current->data, &reversedResult);
        current = current->next;
    }

    res.head = reversedResult;

    return res;
}
struct BigInteger mul(struct BigInteger num1, struct BigInteger num2) {
 
    if (compare(num1, initialize("0")) == 0 || compare(num2, initialize("0")) == 0) {
        return initialize("0"); 
    }

    int len1 = length(num1.head);
    int len2 = length(num2.head);
    int resultLen = len1 + len2;

    int* intermediateResults = (int*)malloc(sizeof(int) * resultLen);
    for (int i = 0; i < resultLen; i++) {
        intermediateResults[i] = 0;
    }

    struct node* p1 = num1.head;
    for (int i = 0; p1 != NULL; i++) {
        int carry = 0;
        struct node* p2 = num2.head;
        for (int j = 0; p2 != NULL; j++) {
            int product = p1->data * p2->data + carry + intermediateResults[i + j];
            carry = product / 10;
            intermediateResults[i + j] = product % 10;
            p2 = p2->next;
        }
        intermediateResults[i + len2] += carry;
        p1 = p1->next;
    }

    
    int zerosCount = 0;
    for (int i = resultLen - 1; i >= 0; i--) {
        if (intermediateResults[i] == 0) {
            zerosCount++;
        } else {
            break;
        }
    }

    struct node* result = NULL;
    for (int i = resultLen - zerosCount - 1; i >= 0; i--) {
        insert(intermediateResults[i], &result);
    }

    
    struct node* reversedResult = NULL;
    struct node* current = result;
    while (current != NULL) {
        insert(current->data, &reversedResult);
        current = current->next;
    }

    struct BigInteger finalResult;
    finalResult.head = reversedResult;

    
    finalResult.sign = (num1.sign + num2.sign) % 2;

    
    if ((num1.sign == 1 && num2.sign == 0) || (num1.sign == 0 && num2.sign == 1)) {
        finalResult.sign = 1; 
    }

    free(intermediateResults);

    return finalResult;
}
int compareAbsolute(struct BigInteger n1, struct BigInteger n2) {
   
    struct node* p1 = n1.head;
    struct node* p2 = n2.head;

    while (p1 != NULL && p1->next != NULL) {
        p1 = p1->next;
    }

    while (p2 != NULL && p2->next != NULL) {
        p2 = p2->next;
    }

   
    int len1 = length(n1.head);
    int len2 = length(n2.head);
    if (len1 < len2)
        return -1;
    if (len1 > len2)
        return 1;

    while (p1 != NULL && p2 != NULL) {
        if (p1->data < p2->data)
            return -1;
        if (p1->data > p2->data)
            return 1;

        p1 = p1->next;
        p2 = p2->next;
    }

   
    return 0;
}
struct BigInteger div1(struct BigInteger dividend, struct BigInteger divisor) {
    struct BigInteger quotient = initialize("0");
    struct BigInteger rem = initialize("0");
    struct BigInteger one = initialize("1");
    while (compareAbsolute(rem, dividend) < 0) {
        rem = add(rem, divisor);
        quotient = add(quotient, one);
    }
    return quotient;
}
void display(struct BigInteger num)
{
  if(num.sign==1)
    {
      printf("-");
    }
    struct node *itr=num.head;
  
    while(itr!=NULL)
    {
       printf("%d",itr->data);
       itr=itr->next;
    }
    printf("\n");
}
