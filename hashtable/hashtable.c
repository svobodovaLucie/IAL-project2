/*
 * Tabuľka s rozptýlenými položkami
 *
 * S využitím dátových typov zo súboru hashtable.h a pripravených kostier
 * funkcií implementujte tabuľku s rozptýlenými položkami s explicitne
 * zreťazenými synonymami.
 *
 * Pri implementácii uvažujte veľkosť tabuľky HT_SIZE.
 */

#include "hashtable.h"
#include <stdlib.h>
#include <string.h>

int HT_SIZE = MAX_HT_SIZE;

/*
 * Rozptyľovacia funkcia ktorá pridelí zadanému kľúču index z intervalu
 * <0,HT_SIZE-1>. Ideálna rozptyľovacia funkcia by mala rozprestrieť kľúče
 * rovnomerne po všetkých indexoch. Zamyslite sa nad kvalitou zvolenej funkcie.
 */
int get_hash(char *key) {
  int result = 1;
  int length = strlen(key);
  for (int i = 0; i < length; i++) {
    result += key[i];
  }
  return (result % HT_SIZE);
}

/*
 * Inicializácia tabuľky — zavolá sa pred prvým použitím tabuľky.
 */
void ht_init(ht_table_t *table) {
  for (unsigned i = 0; i < HT_SIZE; i++)
    (*table)[i] = NULL;
}

/*
 * Vyhľadanie prvku v tabuľke.
 *
 * V prípade úspechu vráti ukazovateľ na nájdený prvok; v opačnom prípade vráti
 * hodnotu NULL.
 */
ht_item_t *ht_search(ht_table_t *table, char *key) {
  if (table == NULL)
    return NULL;

  int i = get_hash(key);
  ht_item_t *tmp = (*table)[i];
  while (tmp != NULL) {
    if (key == tmp->key)
      return tmp;
    tmp = tmp->next;
  }
  return tmp;
}

/*
 * Vloženie nového prvku do tabuľky.
 *
 * Pokiaľ prvok s daným kľúčom už v tabuľke existuje, nahraďte jeho hodnotu.
 *
 * Pri implementácii využite funkciu ht_search. Pri vkladaní prvku do zoznamu
 * synonym zvoľte najefektívnejšiu možnosť a vložte prvok na začiatok zoznamu.
 */
void ht_insert(ht_table_t *table, char *key, float value) {
  ht_item_t *new = ht_search(table, key);
  if (new != NULL) {
    new->value = value;
    return;
  }
  new = malloc(sizeof(ht_item_t));
  if (new == NULL)
    return;
  new->key = key;
  new->value = value;
  int i = get_hash(key);
  new->next = (*table)[i];
  (*table)[i] = new;
}

/*
 * Získanie hodnoty z tabuľky.
 *
 * V prípade úspechu vráti funkcia ukazovateľ na hodnotu prvku, v opačnom
 * prípade hodnotu NULL.
 *
 * Pri implementácii využite funkciu ht_search.
 */
float *ht_get(ht_table_t *table, char *key) {
  ht_item_t *search = ht_search(table, key);
  if (search == NULL)
    return NULL;
  return &(search->value);
}

/*
 * Zmazanie prvku z tabuľky.
 *
 * Funkcia korektne uvoľní všetky alokované zdroje priradené k danému prvku.
 * Pokiaľ prvok neexistuje, nerobte nič.
 *
 * Pri implementácii NEVYUŽÍVAJTE funkciu ht_search.
 */
void ht_delete(ht_table_t *table, char *key) {
  if (table == NULL)
    return;

  int i = get_hash(key);
  ht_item_t *tmp = (*table)[i];
  ht_item_t *tmp_prev = (*table)[i];
  if (tmp == NULL || tmp_prev == NULL)
    return;
  
  // prvni polozka je hledana
  if (tmp->key == key) {
    (*table)[i] = tmp->next;
    free(tmp);
    return;
  }
  tmp = tmp->next;
  while (tmp != NULL) {
    if (tmp->key == key) {
      tmp_prev->next = tmp->next;
      free(tmp);
      return;
    }
    tmp_prev = tmp;
    tmp = tmp->next;
  }
}

/*
 * Zmazanie všetkých prvkov z tabuľky.
 *
 * Funkcia korektne uvoľní všetky alokované zdroje a uvedie tabuľku do stavu po
 * inicializácii.
 */
void ht_delete_all(ht_table_t *table) {
  if (table == NULL)
    return;
  for (unsigned i = 0; i < HT_SIZE; i++) {
    ht_item_t *tmp;
    while ((*table)[i] != NULL) {
      tmp = (*table)[i];
      (*table)[i] = (*table)[i]->next;
      free(tmp);
    }
  }
}
