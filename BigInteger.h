#ifndef BigInteger_h
#define BigInteger_h
struct BigInteger
{
    struct node *head;
    int length;
    int sign;
};
struct node
{
    int data;
    struct node *next;
};
struct BigInteger initialize(char *s);
struct BigInteger add(struct BigInteger,struct BigInteger);
struct BigInteger sub(struct BigInteger,struct BigInteger);
struct BigInteger mul(struct BigInteger,struct BigInteger);
struct BigInteger div1(struct BigInteger,struct BigInteger);
//struct BigInteger mod(struct BigInteger,struct BigInteger);
void display(struct BigInteger);
#endif






















