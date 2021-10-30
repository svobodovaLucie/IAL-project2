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
  (*tree) = NULL;
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
 /*
void bst_insert(bst_node_t **tree, char key, int value) {
  bst_node_t *tmp = *tree;
  bst_node_t *tmp_prev = NULL;
  
  while (tmp != NULL) {
    if (tmp->value > value) {
      tmp_prev = tmp;
      tmp = tmp->left;
    } else if (tmp->value < value) {
      tmp_prev = tmp;
      tmp = tmp->right;
    } else {
      return;
    }
  }
  bst_node_t *new = malloc(sizeof(bst_node_t));
  if (new == NULL)
    return;
  new->value = value;
  new->left = NULL;
  new->right = NULL;
  if (*tree == NULL) {
      (*tree) = new;
      return;
  }
  if (tmp_prev->value > value)
    tmp_prev->left = new;
  else
    tmp_prev->right = new;
}
*/
/*
void bst_insert(bst_node_t **tree, char key, int value) {
  bst_node_t *tmp = *tree;
  bst_node_t *tmp_prev = NULL;

  if (tmp == NULL) {
    bst_node_t *new = malloc(sizeof(bst_node_t));
    if (new == NULL)
      return;
    new->value = value;
    new->left = NULL;
    new->right = NULL;
    (*tree) = new;
  } else {
    while (tmp != NULL) {
      if (tmp->value > value) {
        tmp_prev = tmp;
        tmp = tmp->left;
      } else if (tmp->value < value) {
        tmp_prev = tmp;
        tmp = tmp->right;
      } else
        return;
    }
    bst_node_t *new = malloc(sizeof(bst_node_t));
    if (new == NULL)
      return;
    new->value = value;
    new->left = NULL;
    new->right = NULL;
    if (tmp_prev->value > value)
      tmp_prev->left = new;
    else
      tmp_prev->right = new;
  }
}
*/
/*
void bst_insert(bst_node_t **tree, char key, int value) {
  if ((*tree) == NULL) {
    bst_node_t *new = malloc(sizeof(bst_node_t));
    if (new == NULL)
      return;
    new->value = value;
    printf("Node: %d\n", value);
    new->left = NULL;
    new->right = NULL;
    (*tree) = new;
    return;
  }
  bst_node_t *tmp = (*tree);
  while (tmp != NULL) {
    if (tmp->value == value)
      break;
    if (tmp->value > value) {
      if (tmp->left != NULL) {
        tmp = tmp->left;
        continue;
      } else {
        bst_node_t *new = malloc(sizeof(bst_node_t));
        if (new == NULL)
          break;
        new->value = value;
        new->left = NULL;
        new->right = NULL;
        tmp->left = new;
      }
    }
    if (tmp->value < value) {
      if (tmp->right != NULL) {
        tmp = tmp->right;
        continue;
      } else {
        bst_node_t *new = malloc(sizeof(bst_node_t));
        if (new == NULL)
          break;
        new->value = value;
        new->left = NULL;
        new->right = NULL;
        tmp->right = new;
      }
    }
  }
}
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
  /*////////////////
  found ← false 
  if rootPtr = NULL then
    where ← NULL
  else
    repeat
      where ← rootPtr // uchování hodnoty where
      if k < rootPtr->key // posun doleva
        then rootPtr ← rootPtr->lPtr
      else
        if rootPtr->key < k // posun doprava
          then rootPtr ← rootPtr->rPtr
        else
          found ← true // našel
        end if
      end if
    until found or (rootPtr = NULL)
  end if
  return (found, where)

  found, where ← SearchIns(rootPtr,k)
  if found then
    where->data ← d // přepsání starých dat novými
  else
    newPtr ← CreateNode(k,d)
    if where = NULL // nový kořen do prázdného stromu
      then rootPtr ← newPtr
    else // nový se připojí jako list …
      if k < where->key
      then // … vlevo
        where->lPtr ← newPtr
      else // … vpravo
        where->rPtr ← newPtr
      end if
    end if // where = NULL
  end if // found
  return rootPtr
  */
  /*
  //////////////////// uprava
  bst_node_t *tmp = (*tree);
  bst_node_t *where = NULL;
  while (tmp != NULL) {
    if (tmp->key > key)
      tmp = tmp->left;
    else if (tmp->key < key)
      tmp = tmp->right;
    else {    // found
      tmp->value = value;
      return;
    }
  }
  
  // not found
  bst_node_t *new = malloc(sizeof(bst_node_t));
  if (new == NULL)
    return;
  new->key = key;
  new->value = value;
  new->right = NULL;
  new->left = NULL;
  printf("NEW: %d\n", new->value);
  if (tmp == NULL) {
    (*tree) = new;
    printf("Tmp byl null aka head\n");
    printf("Head ted je: %d\n", (*tree)->value);
    return;
  }
  
  if (tmp->key > key)
    tmp->left = new;
  else
    tmp->right = new;
  */

    //////////////////// uprava
    /*
  bst_node_t *where = NULL;
  if ((*tree) == NULL)
    where = NULL;
  else {
    while ((*tree) != NULL) {
      where = (*tree);
      if ((*tree)->key > key)
        (*tree) = (*tree)->left;
      else if ((*tree)->key < key)
        (*tree) = (*tree)->right;
      else {    // found
        (*tree)->value = value;
        return;
      }
    }
  }
  // not found
  bst_node_t *new = malloc(sizeof(bst_node_t));
  if (new == NULL)
    return;
  new->key = key;
  new->value = value;
  new->right = NULL;
  new->left = NULL;
  printf("NEW: %d\n", new->value);
  if (where == NULL) {
    (*tree) = new;
    printf("Tmp byl null aka head\n");
    printf("Head ted je: %d\n", (*tree)->value);
    return;
  }
  
  if (where->key > key)
    where->left = new;
  else
    where->right = new;
  */
  /*
  tmp = rootPtr;
    while (tmp != NULL)
      //where ← rootPtr // uchování hodnoty where
      if k < tmp->key // posun doleva
        then tmp ← tmp->lPtr
      else
        if tmp->key < k // posun doprava
          then tmp ← tmp->rPtr
        else  // nasel
          tmp->data ← d // přepsání starých dat novými
          return
        end if
      end if
    end while
  // nenasli jsme
  newPtr ← CreateNode(k,d)
  if tmp == NULL // nový kořen do prázdného stromu
    then (*tree) = newPtr
  else // nový se připojí jako list …
    if k < where->key
    then // … vlevo
      tmp->lPtr ← newPtr
    else // … vpravo
      tmp->rPtr ← newPtr
    end if
  end if // where = NULL
  */
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
  /*
  if (tree == NULL)
    return;

  stack_bst_t *stack = NULL;
  stack_bst_init(stack);

  bst_leftmost_preorder(tree, stack);

  while(!stack_bst_empty(stack)) {
    bst_node_t *tmp = stack_bst_pop(stack);
    if (tmp->right != NULL)
      bst_leftmost_preorder(tmp->right, stack);
  }
  */
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
  /*
  while (tree != NULL) {
    stack_bst_push(to_visit, tree);
    tree = tree->left;
  }
  */
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
  /*
  if (tree == NULL)
    return;

  stack_bst_t *stack = NULL;
  stack_bst_init(stack);

  bst_leftmost_inorder(tree, stack);

  while(!stack_bst_empty(stack)) {
    bst_node_t *tmp = stack_bst_pop(stack);
    bst_print_node(tmp);
    if (tmp->right != NULL)
      bst_leftmost_inorder(tmp->right, stack);
  }
  */
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
  /*
  if (tree == NULL)
    return;

  stack_bst_t *stack = NULL;
  stack_bst_init(stack);

  stack_bool_t *stack_bool = NULL;
  stack_bool_init(stack_bool);

  bst_leftmost_postorder(tree, stack, stack_bool);

  while(!stack_bst_empty(stack)) {
    bst_node_t *tmp = stack_bst_pop(stack);
    bool tmp_bool = stack_bool_pop(stack_bool);

    if (tmp->right != NULL) {
      if (tmp_bool) {
        stack_bst_push(stack, tmp);
        stack_bool_push(stack_bool, false);
      }
      bst_leftmost_postorder(tmp->right, stack, stack_bool);
    } else {
      bst_print_node(tmp);
    }
  }
  */
}
