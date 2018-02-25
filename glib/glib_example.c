#include <stdio.h>
#include <glib.h>

static char * strArr[] = {"hello", "this", "is", "my", "first", "time", "to", "use", "glib"};


void
test_gqueue() {
  GQueue* queue = g_queue_new();
  for (int i=0; i<9; i++) {
    g_queue_push_head(queue, strArr[i]);
  }

  while (!g_queue_is_empty(queue)) {
    printf("%s\n", (char*)g_queue_pop_tail(queue));
  }
}

void
test_gstack() {
  GQueue* stack = g_queue_new();
  for (int i=0; i<9; i++) {
    g_queue_push_head(stack, strArr[i]);
  }
  while (!g_queue_is_empty(stack)) {
    printf("%s\n", (char*)g_queue_pop_head(stack));
  }
}

void
test_slist_queue() {
  GList* slist = NULL;
  GList* head = NULL;
  for (int i=0; i<9; i++) {
    slist = g_slist_append(slist, strArr[i]);
    if (head == NULL) head = slist;
  }
  for (;head;head = g_slist_next(head)) {
    puts((char*)head->data);
  }
}
``
void
test_slist_stack() {
  GList* slist = NULL;
  for (int i=0; i<9; i++) {
    slist = g_slist_prepend(slist, strArr[i]);
  }
  for (; slist; slist = g_slist_next(slist)) {
    puts((char*)slist->data);
  }
}

void print_list(int k, GList* list) {
  printf("[%d] ", k);
  list = g_list_first(list);
  for (; list; list = g_list_next(list)) {
    printf(" (%s) ", (char*)list->data);
  }
  printf("\n");
}
void
test_list() {
  GList* list = NULL;
  for (int i=0; i<9; i++) {
    if (i%2)
      list = g_list_append(list, strArr[i]);
    else
      list = g_list_prepend(list, strArr[i]);
      print_list(i, g_list_first(list));
  }
  list = g_list_first(list);
  for (; list; list = g_list_next(list)) {
    puts((char*)list->data);
  }
}

void print(gpointer data, gpointer userdata) {
  printf(" (%s) ", *(const char**)data);
}

gint compare(gconstpointer a, gconstpointer b) {
  return *(const char**)a > *(const char*)b;
}

void
test_garray() {
  GPtrArray* array = g_ptr_array_new();
  for (int i=0; i<9; i++) {
    g_ptr_array_add(array, strArr[i]);
  }
  printf("length(%d) : ", array->len);
  g_ptr_array_foreach(array, print, NULL); puts("");
  g_ptr_array_sort(array, compare);
  g_ptr_array_foreach(array, print, NULL); puts("");
}
int
main(int argc, char const *argv[]) {

  puts("### gqueue goes here");
  test_gqueue();

  puts("### gstack goes here");
  test_gstack();

  // singular linked list
  // glist.h
  // typedef struct _GList { gpointer data, GList* next, GList* prev; } GList;
  puts("### gslist queue goes here");
  test_slist_queue();

  puts("### gslist stack goes here");
  test_slist_stack();

  // doublely linked list
  // glist.h
  // typedef struct _GList { gpointer data, GList* next, GList* prev; } GList;
  puts("### gdlist goes here");
  test_list();

  // array
  // garray.h
  // typedef struct _GArray { gchar* data, guint len } GArray;
  // typedef struct _GByteArray { guint8* data, guint len } GArray;
  // typedef struct _GPtrArray { gpointer* data, guint len } GArray;
  puts("### garray goes here");
  test_garray();
  return 0;
}
