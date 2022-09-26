#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap* tree=(TreeMap*)malloc(sizeof(TreeMap));
    tree->lower_than = lower_than;
    return tree;
}

void insertTreeMap(TreeMap * tree, void* key, void * value) {
    TreeNode* aux;
    tree->current=tree->root;
    while(tree->current!=NULL)
    {
      if(is_equal(tree,key,tree->current->pair->key)==1)
      {
        return;
      }
      else
      {
        aux=createTreeNode(key,value);
        if(tree->lower_than(tree->current->pair->key,key)==1)
        {
          if(tree->current->right!=NULL)
          {
            tree->current=tree->current->right;
          }
          else
          {
            tree->current->right=aux;
            aux->parent=tree->current;
            tree->current=tree->current->right;
          }
        }
        else
        {
          if(tree->current->left!=NULL)
          {
            tree->current=tree->current->left;
          }
          else
          {
            tree->current->left=aux;
            aux->parent=tree->current;
            tree->current=tree->current->left;
          }
        }
      }
    }
}

TreeNode * minimum(TreeNode * x){
    TreeNode* aux=x;
    while(aux->left!=NULL)
    {
        aux=aux->left;
    }
    return aux;
}

void removeNode(TreeMap * tree, TreeNode* node){
  //0 Hijos
  if(node->left == NULL && node->right == NULL){
    if(node->parent==NULL){
      tree->root=NULL;
    }  
    if(node->parent->left==node){
      node->parent->left=NULL;
    }
    if(node->parent->right==node){
      node->parent->right=NULL;
    }  
  }
  //2 Hijos  
  else if(node->right != NULL && node->left != NULL){
    TreeNode *aux=minimum(node->right);
    node->pair=aux->pair;
    removeNode(tree, aux);  
  }
  // 1 Hijo  
  else{
    //izquierdo
    if(node->parent->left==node){
      if(node->right==NULL){
        node->parent->left=node->left;
        node->left->parent=node->parent;
      }
      if(node->left==NULL){
        node->parent->left=node->right;
        node->right->parent=node->parent;
      }
    }
    //derecho
    if(node->parent->right==node){
      if(node->right==NULL){
        node->parent->right=node->left;
        node->left->parent=node->parent;
      }
      if(node->left==NULL){
        node->parent->right=node->right;
        node->right->parent=node->parent;
      }
    }
    free(node);
  }
}


void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}

Pair * searchTreeMap(TreeMap * tree, void* key) {
    TreeNode*aux=tree->root;
    while(aux!=NULL)
    {
      if(is_equal(tree,aux->pair->key,key)==1)
      {
        tree->current=aux;
        return aux->pair;
      }
      else
      {
        if(tree->lower_than(aux->pair->key,key)==1)
        {
          aux=aux->right;
        }
        else
        {
          aux=aux->left;
        }
      }
    }
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
  Pair*aux=searchTreeMap(tree,key);
  if(aux!=NULL)
  {
    aux=aux;
  }
  else
  {
    if(tree->lower_than(tree->current->pair->key,key)!=1)
    {
      return tree->current->pair;
    }
    aux=nextTreeMap(tree);
  }
  return aux;
}

Pair * firstTreeMap(TreeMap * tree) {
  tree->current=minimum(tree->root);
  return tree->current->pair;
}

Pair * nextTreeMap(TreeMap * tree) {
  if(tree->current->right!=NULL)
  {
    tree->current=minimum(tree->current->right);
    return tree->current->pair;
  }
  else if(tree->current->parent == tree->root)
  {
    tree->current=NULL;
    return NULL;
  }
  if(tree->lower_than(tree->current->pair->key,tree->current->parent->pair->key)==1)
  {
    tree->current=tree->current->parent;
  }
  else if(tree->current->parent->parent==NULL)
  {
    tree->current=NULL;
    return NULL;
  }
  else tree->current=tree->current->parent->parent;
  return tree->current->pair;
  
  if(tree->current==NULL)
  {
    return NULL;
  }
}
