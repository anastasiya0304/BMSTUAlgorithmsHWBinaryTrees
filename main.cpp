
#include <cmath>
#include <fstream>
#include <iostream>


struct node // структура для представления узлов дерева
{
    int key;
    unsigned char height;
    node* left;
    node* right;
    node(int k) { key = k; left = right = 0; height = 1; }
};

unsigned char height(node* p)
{
    return p?p->height:0;
}

int bfactor(node* p)
{
    return height(p->right)-height(p->left);
}

void fixheight(node* p)
{
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    p->height = (hl>hr?hl:hr)+1;
}

node* rotateright(node* p) // правый поворот вокруг p
{
    node* q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

node* rotateleft(node* q) // левый поворот вокруг q
{
    node* p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

node* balance(node* p) // балансировка узла p
{
    fixheight(p);
    if( bfactor(p)==2 )
    {
        if( bfactor(p->right) < 0 )
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if( bfactor(p)==-2 )
    {
        if( bfactor(p->left) > 0  )
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p; // балансировка не нужна
}


node* insertIn(node* p, int k) // вставка ключа k в дерево с корнем p
{

    if( !p ) return new node(k);
    if( k<p->key )
        p->left = insertIn(p->left,k);
    else
        p->right = insertIn(p->right,k);

    return balance(p);

}

void insert (int k) {
    node = insertIn(node,k);
}

node* searchmin(node* p) // поиск узла с минимальным ключом в дереве p
{
    return p->left?searchmin(p->left):p;
}

void searchIn(int x,node* p) {

    if (p==NULL) {
        std::cout<<"Такого элемента нет\n"<<std::endl;
    }
    else {
        if (x < p->key) {
            searchIn(x,p->left);
        }
        else {
            if (x>p->key) {
                searchIn(x,p->right);
            }
            else {
                std::cout<<"Такой элемент есть\n"<<std::endl;
            }
        }
    }


}

bool search(int k) {
    searchIn(k,node);
}

node* removemin(node* p) // удаление узла с минимальным ключом из дерева p
{
    if( p->left==0 )
        return p->right;
    p->left = removemin(p->left);
    return balance(p);


}

node* removeIn(node* p, int k) // удаление ключа k из дерева p
{
    if( !p ) return 0;
    if( k < p->key )
        p->left = removeIn(p->left,k);
    else if( k > p->key )
        p->right = removeIn(p->right,k);
    else //  k == p->key
    {
        node* q = p->left;
        node* r = p->right;
        delete p;
        if( !r ) return q;
        node* min = searchmin(r);
        min->right = removemin(r);
        min->left = q;
        return balance(min);
    }
    return balance(p);


}

void remove(int k) {
    node = removeIn(k,node);
}


void PrintIn (std::ostream &outputstream, node* p) {
    if (p == nullptr) {
        return;
    }
    PrintIn(outputstream, p->left);
    outputstream << p->key << " ";
    PrintIn(outputstream, p->right);
}

void print(std::ostream &outputstream) {
    PrintIn(outputstream, node);
}
