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

void removeNode(TreeMap * tree, TreeNode* node) {
  TreeNode*padre=node->parent;
  TreeNode*hijoIzq=node->left;
  TreeNode*hijoDer=node->right;
  
  if(hijoIzq==NULL && hijoDer==NULL)
  {
    if(tree->lower_than(node->pair->key,parent->pair->key)==1)
    {
      parent->left=NULL;
    }
    else
    {
      parent->right=NULL;
    }
    node->left=NULL;
    node->right=NULL;
    node->parent=NULL;
    node->pair=NULL;
  }
  else
  {
    if(hijoIzq==NULL && hijoDer==NULL)
    {
      TreeNode*min=minimun(hijoDer);
      node->pair=min->pair;
      if(min->right!=NULL)
      {
        removeNode(tree,min);
      }
    }
  }
  else
  {
    TreeNode*hijo=NULL;
    if(hijoIzq!=NULL)
    {
      hijo=hijoIzq;
    }
    else
    {
      hijo=hijoDer;
    }
    node->pair=hijo->pair;
    node->right=hijo->right;
    node->left=hijo->left;
  }
  return;
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
