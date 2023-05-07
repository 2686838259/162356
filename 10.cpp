#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#define TRUE 1
#define ERROR 0
using namespace std;
typedef struct tnode
{
int dat;//������
int height;//�ڵ��������ϸ߶�
tnode* left;//����
tnode* right;//�Һ���
}tnode, * tree;//tnode �����ڷ�ӳ�ڵ�����Ĵ洢�ռ�
tnode* buynode(int key)//����һ���ڵ㣬�������ɽڵ�ĵ�ַ
{
tnode* ntemp = (tnode*)malloc(sizeof(tnode));
if (ntemp == NULL)
exit(0);//����洢�ֿռ�ʧ��
ntemp->dat = key;
ntemp->left = NULL;
ntemp->right = NULL;
ntemp->height = 1;
return ntemp;//�������ɽڵ�ĵ�ַ
}
int Max(int a, int b)//�������ýڵ�߶�
{if (a > b)
return a;
else
return b;
}
int Height(tnode* a)//��ȡ��ǰ�ڵ�߶�
{
if (a == NULL)//Ҷ�ӽ��
�������պ����ѧ�γ���Ʊ���
9
{
return 0;
}
return a->height;
}
int getbalance(tnode* a)//��ȡƽ������
{
if (a == NULL)//�ڵ�Ϊ��
{
return 0;
}
return Height(a->left) - Height(a->right);
}
tnode* rotateright(tnode* a)//����
{
tnode* y = a->left;//���� RL �����Ľڵ㣨RL Ҫ�������������� ���� ��ǰ���ĸ��ڵ�
a->left = y->right;
y->right = a;
a->height = Max(Height(a->left), Height(a->left)) + 1;
y->height = Max(Height(y->left), Height(y->left)) + 1;
return y;
}
tnode* rotateleft(tnode* a)//����
{
tnode* y = a->right;
a->right = y->left;
y->left = a;
a->height = Max(Height(a->left), Height(a->left)) + 1;
y->height = Max(Height(y->left), Height(y->left)) + 1;
return y;
}
tnode* rebalance(tnode* a)//�Զ���������ƽ�⻯
{
int balancefactor = getbalance(a);
if (balancefactor > 1 && getbalance(a->left) > 0)//LL �辭��һ��ƽ�⻯
{
return rotateright(a);//���� ��������
�������պ����ѧ�γ���Ʊ���
}
if (balancefactor > 1 && getbalance(a->left) <= 0)//LR �辭������ƽ�⻯
{
tnode* t = rotateleft(a->left);//�ȶ������������������� �ٶ�����������
a->left = t;
return rotateright(a);
}
if (balancefactor < -1 && getbalance(a->right) <= 0)//RR �辭��һ��ƽ�⻯
{
return rotateleft(a);//���� �����Һ���
}
if (balancefactor < -1 && getbalance(a->right)>0)//RL �辭������ƽ�⻯
{
tnode* t = rotateright(a->right);//�ȶ������������������� �ٶ�����������
a->right = t;
return rotateleft(a);
}
return a;
}
bool insert(tree& a, int key)//���õݹ� �˴�Ҳ��ʹ�ö���ָ��
{
if (a == NULL)//�������Ϊ�գ����ڴ˴�����
{
a = buynode(key);
}
//�����Ϊ����
else if (key > a->dat)
insert(a->right, key);
else if (key < a->dat)
insert(a->left, key);
else //���ҵ���
{
cout << "node " << key << " has existed";
return false;
}
a->height = Max(Height(a->left), Height(a->right)) + 1;//�ݹ� �ı�ڵ�߶�
a = rebalance(a);//�ݹ齫��ƽ�⻯
return true;
}
void preodertraverse(tnode* a)//ǰ��
{
if (a)
10
�������պ����ѧ�γ���Ʊ���
{
cout << a->dat << ' ';
preodertraverse(a->left);
preodertraverse(a->right);
}
}
void prekey(tnode* a)//ǰ��
{
if (a)
{
cout << getbalance(a) << ' ';
prekey(a->left);
prekey(a->right);
}
}
void ineodertraverse(tnode* a)//����
{
if (a)
{
ineodertraverse(a->left);
cout << a->dat << ' ';
ineodertraverse(a->right);
}
}
void inkey(tnode* a) {
if (a) {
inkey(a->left);
cout << getbalance(a) << ' ';
inkey(a->right);
}
}
void postodertraverse(tnode* a)//����
{
if (a)
{
postodertraverse(a->left);
postodertraverse(a->right);
cout << a->dat << ' ';
11
�������պ����ѧ�γ���Ʊ���
}
}
void postkey(tnode* a)//����
{
if (a)
{
postkey(a->left);
postkey(a->right);
cout << getbalance(a)<< ' ';
}
}
void preOrder(tnode* T) {
tnode* stack[15];
int top = -1;
tnode* p = T;
while (p != NULL || top != -1) {
if (p != NULL) {
stack[++top] = p;
printf("%d ", p->dat); //��ջʱ���������
p = p->left;
}
else {
p = stack[top--];
p = p->right;
}
}
}
void prekkey(tnode* T) {
tnode* stack[15];
int top = -1;
tnode* p = T;
while (p != NULL || top != -1) {
if (p != NULL) {
stack[++top] = p;
printf("%d ", getbalance(p)); //��ջʱ���������
p = p->left;
}
else {
p = stack[top--];
p = p->right;
}
12
�������պ����ѧ�γ���Ʊ���
13
}
}
void inOrder(tnode* T) {
tnode* stack[15];
int top = -1;
tnode* p = T;
while (p != NULL || top != -1) {
if (p != NULL) {
stack[++top] = p;
p = p->left;
}
else {
p = stack[top--];
printf("%d ", p->dat); //��ջʱ���������
p = p->right;
}
}
}
void inkkey(tnode* T) {
tnode* stack[15];
int top = -1;
tnode* p = T;
while (p != NULL || top != -1) {
if (p != NULL) {
stack[++top] = p;
p = p->left;
}
else {
p = stack[top--];
printf("%d ", getbalance(p)); //��ջʱ���������
p = p->right;
}
}
}
void postOrder(tnode* T) {
tnode* stack[15];
int top = -1;
int flagStack[15]; //��¼ÿ���ڵ���ʴ���ջ
tnode* p = T;
while (p != NULL || top != -1) {
if (p != NULL) { //��һ�η��ʣ�flag �� 1����ջ
stack[++top] = p;
flagStack[top] = 1;
�������պ����ѧ�γ���Ʊ���
14
p = p->left;
}
else {//��p == NULL��
if (flagStack[top] == 1) { //�ڶ��η��ʣ�flag �� 2��ȡջ��Ԫ�ص�����ջ
p = stack[top];
flagStack[top] = 2;
p = p->right;
}
else { //�����η��ʣ���ջ
p = stack[top--];
printf("%d ", p->dat); //��ջʱ���������
p = NULL; //p �ÿգ��Ա������ջ
}
}
}
}
void postkkey(tnode* T) {
tnode* stack[15];
int top = -1;
int flagStack[15]; //��¼ÿ���ڵ���ʴ���ջ
tnode* p = T;
while (p != NULL || top != -1) {
if (p != NULL) { //��һ�η��ʣ�flag �� 1����ջ
stack[++top] = p;
flagStack[top] = 1;
p = p->left;
}
else {//��p == NULL��
if (flagStack[top] == 1) { //�ڶ��η��ʣ�flag �� 2��ȡջ��Ԫ�ص�����ջ
p = stack[top];
flagStack[top] = 2;
p = p->right;
}
else { //�����η��ʣ���ջ
p = stack[top--];
printf("%d ", getbalance(p)); //��ջʱ���������
p = NULL; //p �ÿգ��Ա������ջ
}
}
}
}
int main()
�������պ����ѧ�γ���Ʊ���
{
tnode* a = NULL;//��һ�ſ���
tnode* Search;//���ڴ洢������ָ��
int i,c;
char d;
for (i = 0; i < 20; i++) {
scanf("%d", &c);
insert(a, c);
scanf("%c", &d);
if (d == '\n') {
break;
}
}
printf("�ݹ��㷨:");
cout << '\n';
printf("ǰ�����:");
cout << '\n';
preodertraverse(a);
cout << '\n';
printf("���ڵ�ƽ������:");
cout << '\n';
prekey(a);
cout << '\n';
printf("�������:");
cout << '\n';
ineodertraverse(a);
cout << '\n';
printf("���ڵ�ƽ������:");
cout << '\n';
inkey(a);
cout << '\n';
printf("�������:");
cout << '\n';
postodertraverse(a);
cout << '\n';
printf("���ڵ�ƽ������:");
cout << '\n';
postkey(a);
cout << '\n';
printf("�ǵݹ��㷨:");
cout << '\n';
printf("ǰ�����:");
15
�������պ����ѧ�γ���Ʊ���
cout << '\n';
preOrder(a);
cout << '\n';
printf("���ڵ�ƽ������:");
cout << '\n';
prekkey(a);
cout << '\n';
printf("�������:");
cout << '\n';
inOrder(a);
cout << '\n';
printf("���ڵ�ƽ������:");
cout << '\n';
inkkey(a);
cout << '\n';
printf("�������:");
cout << '\n';
postOrder(a);
cout << '\n';
printf("���ڵ�ƽ������:");
cout << '\n';
postkkey(a);
system("pause");
return 0;
}
