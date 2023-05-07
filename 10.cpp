#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#define TRUE 1
#define ERROR 0
using namespace std;
typedef struct tnode
{
int dat;//数据域
int height;//节点自下向上高度
tnode* left;//左孩子
tnode* right;//右孩子
}tnode, * tree;//tnode 可用于反映节点所需的存储空间
tnode* buynode(int key)//生成一个节点，返回生成节点的地址
{
tnode* ntemp = (tnode*)malloc(sizeof(tnode));
if (ntemp == NULL)
exit(0);//分配存储粗空间失败
ntemp->dat = key;
ntemp->left = NULL;
ntemp->right = NULL;
ntemp->height = 1;
return ntemp;//返回生成节点的地址
}
int Max(int a, int b)//用于设置节点高度
{if (a > b)
return a;
else
return b;
}
int Height(tnode* a)//获取当前节点高度
{
if (a == NULL)//叶子结点
沈阳航空航天大学课程设计报告
9
{
return 0;
}
return a->height;
}
int getbalance(tnode* a)//获取平衡因子
{
if (a == NULL)//节点为空
{
return 0;
}
return Height(a->left) - Height(a->right);
}
tnode* rotateright(tnode* a)//右旋
{
tnode* y = a->left;//返回 RL 左旋的节点（RL 要先右旋再左旋） 或者 当前树的根节点
a->left = y->right;
y->right = a;
a->height = Max(Height(a->left), Height(a->left)) + 1;
y->height = Max(Height(y->left), Height(y->left)) + 1;
return y;
}
tnode* rotateleft(tnode* a)//左旋
{
tnode* y = a->right;
a->right = y->left;
y->left = a;
a->height = Max(Height(a->left), Height(a->left)) + 1;
y->height = Max(Height(y->left), Height(y->left)) + 1;
return y;
}
tnode* rebalance(tnode* a)//对二叉树进行平衡化
{
int balancefactor = getbalance(a);
if (balancefactor > 1 && getbalance(a->left) > 0)//LL 需经历一次平衡化
{
return rotateright(a);//右旋 返回左孩子
沈阳航空航天大学课程设计报告
}
if (balancefactor > 1 && getbalance(a->left) <= 0)//LR 需经历两次平衡化
{
tnode* t = rotateleft(a->left);//先对左子树的右子树左旋 再对左子树右旋
a->left = t;
return rotateright(a);
}
if (balancefactor < -1 && getbalance(a->right) <= 0)//RR 需经历一次平衡化
{
return rotateleft(a);//左旋 返回右孩子
}
if (balancefactor < -1 && getbalance(a->right)>0)//RL 需经历两次平衡化
{
tnode* t = rotateright(a->right);//先对右子树的左子树右旋 再对右子树左旋
a->right = t;
return rotateleft(a);
}
return a;
}
bool insert(tree& a, int key)//采用递归 此处也可使用二重指针
{
if (a == NULL)//如果孩子为空，则在此处插入
{
a = buynode(key);
}
//如果不为空树
else if (key > a->dat)
insert(a->right, key);
else if (key < a->dat)
insert(a->left, key);
else //查找到了
{
cout << "node " << key << " has existed";
return false;
}
a->height = Max(Height(a->left), Height(a->right)) + 1;//递归 改变节点高度
a = rebalance(a);//递归将树平衡化
return true;
}
void preodertraverse(tnode* a)//前序
{
if (a)
10
沈阳航空航天大学课程设计报告
{
cout << a->dat << ' ';
preodertraverse(a->left);
preodertraverse(a->right);
}
}
void prekey(tnode* a)//前序
{
if (a)
{
cout << getbalance(a) << ' ';
prekey(a->left);
prekey(a->right);
}
}
void ineodertraverse(tnode* a)//中序
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
void postodertraverse(tnode* a)//后序
{
if (a)
{
postodertraverse(a->left);
postodertraverse(a->right);
cout << a->dat << ' ';
11
沈阳航空航天大学课程设计报告
}
}
void postkey(tnode* a)//后序
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
printf("%d ", p->dat); //入栈时，访问输出
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
printf("%d ", getbalance(p)); //入栈时，访问输出
p = p->left;
}
else {
p = stack[top--];
p = p->right;
}
12
沈阳航空航天大学课程设计报告
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
printf("%d ", p->dat); //出栈时，访问输出
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
printf("%d ", getbalance(p)); //出栈时，访问输出
p = p->right;
}
}
}
void postOrder(tnode* T) {
tnode* stack[15];
int top = -1;
int flagStack[15]; //记录每个节点访问次数栈
tnode* p = T;
while (p != NULL || top != -1) {
if (p != NULL) { //第一次访问，flag 置 1，入栈
stack[++top] = p;
flagStack[top] = 1;
沈阳航空航天大学课程设计报告
14
p = p->left;
}
else {//（p == NULL）
if (flagStack[top] == 1) { //第二次访问，flag 置 2，取栈顶元素但不出栈
p = stack[top];
flagStack[top] = 2;
p = p->right;
}
else { //第三次访问，出栈
p = stack[top--];
printf("%d ", p->dat); //出栈时，访问输出
p = NULL; //p 置空，以便继续退栈
}
}
}
}
void postkkey(tnode* T) {
tnode* stack[15];
int top = -1;
int flagStack[15]; //记录每个节点访问次数栈
tnode* p = T;
while (p != NULL || top != -1) {
if (p != NULL) { //第一次访问，flag 置 1，入栈
stack[++top] = p;
flagStack[top] = 1;
p = p->left;
}
else {//（p == NULL）
if (flagStack[top] == 1) { //第二次访问，flag 置 2，取栈顶元素但不出栈
p = stack[top];
flagStack[top] = 2;
p = p->right;
}
else { //第三次访问，出栈
p = stack[top--];
printf("%d ", getbalance(p)); //出栈时，访问输出
p = NULL; //p 置空，以便继续退栈
}
}
}
}
int main()
沈阳航空航天大学课程设计报告
{
tnode* a = NULL;//给一颗空树
tnode* Search;//用于存储搜索的指针
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
printf("递归算法:");
cout << '\n';
printf("前序遍历:");
cout << '\n';
preodertraverse(a);
cout << '\n';
printf("各节点平衡因子:");
cout << '\n';
prekey(a);
cout << '\n';
printf("中序遍历:");
cout << '\n';
ineodertraverse(a);
cout << '\n';
printf("各节点平衡因子:");
cout << '\n';
inkey(a);
cout << '\n';
printf("后序遍历:");
cout << '\n';
postodertraverse(a);
cout << '\n';
printf("各节点平衡因子:");
cout << '\n';
postkey(a);
cout << '\n';
printf("非递归算法:");
cout << '\n';
printf("前序遍历:");
15
沈阳航空航天大学课程设计报告
cout << '\n';
preOrder(a);
cout << '\n';
printf("各节点平衡因子:");
cout << '\n';
prekkey(a);
cout << '\n';
printf("中序遍历:");
cout << '\n';
inOrder(a);
cout << '\n';
printf("各节点平衡因子:");
cout << '\n';
inkkey(a);
cout << '\n';
printf("后序遍历:");
cout << '\n';
postOrder(a);
cout << '\n';
printf("各节点平衡因子:");
cout << '\n';
postkkey(a);
system("pause");
return 0;
}
