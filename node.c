#include "9cc.h"
#include "util.h"
#include "y.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Node *new_node(int ty, Node *lhs, Node *rhs) {
  Node *node = malloc(sizeof(Node));
  node->ty = ty;
  node->lhs = lhs;
  node->rhs = rhs;
  return node;
}

Node *new_node_num(int val) {
  Node *node = malloc(sizeof(Node));
  node->ty = NUMBER;
  node->val = val;
  return node;
}

Node *new_node_id(char name) {
  Node *node = malloc(sizeof(Node));
  node->ty = IDENT;
  node->name = name;
  return node;
}
