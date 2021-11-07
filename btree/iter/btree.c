/*
 * Binárny vyhľadávací strom — iteratívna varianta
 *
 * S využitím dátových typov zo súboru btree.h, zásobníkov zo súborov stack.h a
 * stack.c a pripravených kostier funkcií implementujte binárny vyhľadávací
 * strom bez použitia rekurzie.
 */

#include "../btree.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Inicializácia stromu.
 *
 * Užívateľ musí zaistiť, že incializácia sa nebude opakovane volať nad
 * inicializovaným stromom. V opačnom prípade môže dôjsť k úniku pamäte (memory
 * leak). Keďže neinicializovaný ukazovateľ má nedefinovanú hodnotu, nie je
 * možné toto detegovať vo funkcii.
 */
void bst_init(bst_node_t **tree) {
  *tree = NULL;
}

/*
 * Nájdenie uzlu v strome.
 *
 * V prípade úspechu vráti funkcia hodnotu true a do premennej value zapíše
 * hodnotu daného uzlu. V opačnom prípade funckia vráti hodnotu false a premenná
 * value ostáva nezmenená.
 *
 * Funkciu implementujte iteratívne bez použitia vlastných pomocných funkcií.
 */
bool bst_search(bst_node_t *tree, char key, int *value) {
  bool search = false;
  bool finish;
  bst_node_t *tmp = tree;
  if (tmp == NULL) {
    finish = true;
  } else {
    finish = false;
  }
  while (!finish) {
    if (tmp->key == key) {
      finish = true;
      search = true;
    } else {
      if (key < tmp->key) {
        tmp = tmp->left;
      } else {
        tmp = tmp->right;
      }
      if (tmp == NULL) {
        finish = true;
      }
    }
  }
  return search;
}

/*
 * Vloženie uzlu do stromu.
 *
 * Pokiaľ uzol so zadaným kľúčom v strome už existuje, nahraďte jeho hodnotu.
 * Inak vložte nový listový uzol.
 *
 * Výsledný strom musí spĺňať podmienku vyhľadávacieho stromu — ľavý podstrom
 * uzlu obsahuje iba menšie kľúče, pravý väčšie.
 *
 * Funkciu implementujte iteratívne bez použitia vlastných pomocných funkcií.
 */
void bst_insert(bst_node_t **tree, char key, int value) {
  bst_node_t *where = NULL;
  bst_node_t *tmp = (*tree);

  while (tmp != NULL) {
    where = tmp;
    if (tmp->key > key) {
      tmp = tmp->left;
      continue;
    } else if (tmp->key < key) {
      tmp = tmp->right;
      continue;
    } else {
      tmp->value = value ; // uzel jiz existuje, zmeni se hodnota
      return;
    }
  }
  bst_node_t *new = malloc(sizeof(bst_node_t));
  if (new == NULL)
    return;
  new->value = value;
  new->key = key;
  new->left = NULL;
  new->right = NULL;
  if (where == NULL) {
    (*tree) = new;
    return;
  }
  if (where->key > key) {
    where->left = new;
    return;
  }
  where->right = new;
}

/*
 * Pomocná funkcia ktorá nahradí uzol najpravejším potomkom.
 *
 * Kľúč a hodnota uzlu target budú nahradené kľúčom a hodnotou najpravejšieho
 * uzlu podstromu tree. Najpravejší potomok bude odstránený. Funkcia korektne
 * uvoľní všetky alokované zdroje odstráneného uzlu.
 *
 * Funkcia predpokladá že hodnota tree nie je NULL.
 *
 * Táto pomocná funkcia bude využitá pri implementácii funkcie bst_delete.
 *
 * Funkciu implementujte iteratívne bez použitia vlastných pomocných funkcií.
 */
void bst_replace_by_rightmost(bst_node_t *target, bst_node_t **tree) {
  bst_node_t *tmp = *tree;
  bst_node_t *tmp_prev = NULL;
  while (tmp->right != NULL) {
    tmp_prev = tmp;
    tmp = tmp->right;
  }
  target->key = tmp->key;
  target->value = tmp->value;
 
  if (tmp_prev != NULL) {
    if (tmp->left != NULL)
      tmp_prev->right = tmp->left;
    else
      tmp_prev->right = NULL;
  }
  free(tmp);
}

/*
 * Odstránenie uzlu v strome.
 *
 * Pokiaľ uzol so zadaným kľúčom neexistuje, funkcia nič nerobí.
 * Pokiaľ má odstránený uzol jeden podstrom, zdedí ho otec odstráneného uzla.
 * Pokiaľ má odstránený uzol oba podstromy, je nahradený najpravejším uzlom
 * ľavého podstromu. Najpravejší uzol nemusí byť listom!
 * Funkcia korektne uvoľní všetky alokované zdroje odstráneného uzlu.
 *
 * Funkciu implementujte iteratívne pomocou bst_replace_by_rightmost a bez
 * použitia vlastných pomocných funkcií.
 */
void bst_delete(bst_node_t **tree, char key) {
  if ((*tree) == NULL)
    return;
  bst_node_t *tmp = *tree;
  bst_node_t *prev = *tree ;
  bool in_left_subtree = false;

  while (tmp != NULL) {
    if (tmp->key == key)
      break;
    prev = tmp;
    if (tmp->key < key) {
      tmp = tmp->right;
      in_left_subtree = false;
    } else if (tmp->key > key) {
      tmp = tmp->left;
      in_left_subtree = true;
    }
  }
  if (tmp == NULL)  // not found
    return;

  if (tmp->left != NULL && tmp->right != NULL) {
    bst_replace_by_rightmost(tmp, &(tmp->left));
  } else {
    if (tmp->right != NULL) {
      if (in_left_subtree)
        prev->left = tmp->right;
      else
        prev->right = tmp->right;
    } else {
      if (in_left_subtree)
        prev->left = tmp->left;
      else
        prev->right = tmp->left;
    }
    free(tmp);
  }
}

/*
 * Zrušenie celého stromu.
 *
 * Po zrušení sa celý strom bude nachádzať v rovnakom stave ako po
 * inicializácii. Funkcia korektne uvoľní všetky alokované zdroje rušených
 * uzlov.
 *
 * Funkciu implementujte iteratívne pomocou zásobníku uzlov a bez použitia
 * vlastných pomocných funkcií.
 */
void bst_dispose(bst_node_t **tree) {
  if (*tree == NULL)
    return;
  bst_node_t *tmp = *tree;

  stack_bst_t *stack = malloc(sizeof(stack_bst_t));
  if (stack == NULL)
    return;
  stack_bst_init(stack);

  while (tmp != NULL || !stack_bst_empty(stack)) {
    if (tmp == NULL) {
      tmp = stack_bst_pop(stack);
    }
    if (tmp->right != NULL) {
      stack_bst_push(stack, tmp->right);
    }
    bst_node_t *del = tmp;
    tmp = tmp->left;
    free(del);
  }
  *tree = NULL;
  free(stack);
}

/*
 * Pomocná funkcia pre iteratívny preorder.
 *
 * Prechádza po ľavej vetve k najľavejšiemu uzlu podstromu.
 * Nad spracovanými uzlami zavola bst_print_node a uloží ich do zásobníku uzlov.
 *
 * Funkciu implementujte iteratívne pomocou zásobníku uzlov a bez použitia
 * vlastných pomocných funkcií.
 */
void bst_leftmost_preorder(bst_node_t *tree, stack_bst_t *to_visit) {
  while (tree != NULL) {
    bst_print_node(tree);
    stack_bst_push(to_visit, tree);
    tree = tree->left;
  }
}

/*
 * Preorder prechod stromom.
 *
 * Pre aktuálne spracovávaný uzol nad ním zavolajte funkciu bst_print_node.
 *
 * Funkciu implementujte iteratívne pomocou funkcie bst_leftmost_preorder a
 * zásobníku uzlov bez použitia vlastných pomocných funkcií.
 */
void bst_preorder(bst_node_t *tree) {
  if (tree == NULL)
    return;
  stack_bst_t stack;
  stack_bst_init(&stack);
  bst_leftmost_preorder(tree, &stack);
  while(!stack_bst_empty(&stack)) {
    bst_node_t *tmp = stack_bst_pop(&stack);
    if (tmp->right != NULL)
      bst_leftmost_preorder(tmp->right, &stack);
  }
}

/*
 * Pomocná funkcia pre iteratívny inorder.
 *
 * Prechádza po ľavej vetve k najľavejšiemu uzlu podstromu a ukladá uzly do
 * zásobníku uzlov.
 *
 * Funkciu implementujte iteratívne pomocou zásobníku uzlov a bez použitia
 * vlastných pomocných funkcií.
 */
void bst_leftmost_inorder(bst_node_t *tree, stack_bst_t *to_visit) {
  while (tree != NULL) {
    stack_bst_push(to_visit, tree);
    tree = tree->left;
  }
}

/*
 * Inorder prechod stromom.
 *
 * Pre aktuálne spracovávaný uzol nad ním zavolajte funkciu bst_print_node.
 *
 * Funkciu implementujte iteratívne pomocou funkcie bst_leftmost_inorder a
 * zásobníku uzlov bez použitia vlastných pomocných funkcií.
 */
void bst_inorder(bst_node_t *tree) {
  if (tree == NULL)
    return;
  stack_bst_t stack;
  stack_bst_init(&stack);
  bst_leftmost_inorder(tree, &stack);
  while(!stack_bst_empty(&stack)) {
    bst_node_t *tmp = stack_bst_pop(&stack);
    bst_print_node(tmp);
    if (tmp->right != NULL)
      bst_leftmost_inorder(tmp->right, &stack);
  }
}

/*
 * Pomocná funkcia pre iteratívny postorder.
 *
 * Prechádza po ľavej vetve k najľavejšiemu uzlu podstromu a ukladá uzly do
 * zásobníku uzlov. Do zásobníku bool hodnôt ukladá informáciu že uzol
 * bol navštívený prvý krát.
 *
 * Funkciu implementujte iteratívne pomocou zásobníkov uzlov a bool hodnôt a bez použitia
 * vlastných pomocných funkcií.
 */
void bst_leftmost_postorder(bst_node_t *tree, stack_bst_t *to_visit,
                            stack_bool_t *first_visit) {
  while (tree != NULL) {
    stack_bst_push(to_visit, tree);
    stack_bool_push(first_visit, true);
    tree = tree->left;
  }
}

/*
 * Postorder prechod stromom.
 *
 * Pre aktuálne spracovávaný uzol nad ním zavolajte funkciu bst_print_node.
 *
 * Funkciu implementujte iteratívne pomocou funkcie bst_leftmost_postorder a
 * zásobníkov uzlov a bool hodnôt bez použitia vlastných pomocných funkcií.
 */
void bst_postorder(bst_node_t *tree) {
  if (tree == NULL)
    return;

  stack_bst_t to_visit;
  stack_bst_init(&to_visit);
  stack_bool_t first_visit;
  stack_bool_init(&first_visit);

  bst_leftmost_postorder(tree, &to_visit, &first_visit);
  while (!stack_bst_empty(&to_visit)) {
    tree = stack_bst_pop(&to_visit);
    if (stack_bool_pop(&first_visit)) {
      stack_bst_push(&to_visit, tree);
      stack_bool_push(&first_visit, false);
      bst_leftmost_postorder(tree->right, &to_visit, &first_visit);
      continue;
    }
    bst_print_node(tree);
  }
}
