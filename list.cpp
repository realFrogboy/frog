#include "list.h"

list_t* list_ctor(){
    struct list_t *strc = (list_t*)calloc(1, sizeof(list_t));

    strc->arr = arr_ctor();
    strc->free_elem = stackCtor();

    for (int num = size_of_list; num >= 1; num--)
        stackPush(strc->free_elem, num);

    strc->num_of_free_elem = size_of_list;
    strc->head = 1;
    strc->tail = 0;
    strc->capacity = size_of_list;

    return strc;
}

void list_dtor(list_t*strc){
    assert(strc);

    free(strc->arr);
    stackDtor(strc->free_elem);
    free(strc);
}

arr_t *arr_ctor(){
    struct arr_t *arr = (arr_t *)calloc(size_of_list + 1, sizeof(arr_t));
    assert(arr);

    for (int idx = 0; idx <= size_of_list; idx++) {
        arr[idx].data = 0;
        arr[idx].next = -1;
        arr[idx].prev = -1;
    }

    arr[0].next = 0;
    arr[0].prev = 0;

    return arr;
}

size_t idx_of_head(const list_t *strc){
    assert(strc);
    return strc->head;
}

size_t idx_of_tail(const list_t *strc){
    assert(strc);
    return strc->tail;
}

size_t idx_of_next(const list_t *strc, size_t idx){
    assert(strc);
    assert(isfinite(idx));

    return strc->arr[idx].next;
}

size_t idx_of_prev(const list_t *strc, size_t idx){
    assert(strc);
    assert(isfinite(idx));

    return strc->arr[idx].prev;
}

void ins_at_the_beg(list_t *strc, double val){
    assert(strc);
    assert(isfinite(val));

    if (strc->num_of_free_elem == 0) 
        realloc_list(strc); 

    int idx = get_free_elem_idx(strc);

    strc->arr[idx].data = val;
    strc->arr[idx].next = strc->head;
    strc->arr[idx].prev = 0;

    strc->arr[strc->head].prev = idx;

    strc->arr[0].next = idx;

    strc->head = idx;
}

void ins_at_the_end(list_t *strc, double val){
    assert(strc);
    assert(isfinite(val));

    if (strc->num_of_free_elem == 0) 
        realloc_list(strc); 

    int idx = get_free_elem_idx(strc);

    strc->arr[idx].data = val;
    strc->arr[idx].next = 0;
    strc->arr[idx].prev = strc->tail;

    strc->arr[strc->tail].next = idx;

    strc->arr[0].prev = idx;

    strc->tail = idx;
}

void ins_before(list_t *strc, size_t elem, double val){
    assert(strc);
    assert(isfinite(val));
    assert(isfinite(elem));

    if (strc->num_of_free_elem == 0) 
        realloc_list(strc); 

    int idx = get_free_elem_idx(strc);

    size_t prev_of_elem = strc->arr[elem].prev;

    strc->arr[idx].data = val;
    strc->arr[idx].next = elem;
    strc->arr[idx].prev = prev_of_elem;

    strc->arr[elem].prev = idx;

    strc->arr[prev_of_elem].next = idx;
}

void ins_after(list_t *strc, size_t elem, double val){
    assert(strc);
    assert(isfinite(val));
    assert(isfinite(elem));

    if (strc->num_of_free_elem == 0) 
        realloc_list(strc); 

    int idx = get_free_elem_idx(strc);

    size_t next_of_elem = strc->arr[elem].next;

    strc->arr[idx].data = val;
    strc->arr[idx].next = next_of_elem;
    strc->arr[idx].prev = elem;

    strc->arr[elem].next = idx;

    strc->arr[next_of_elem].prev = idx;
}

void del_elem(list_t *strc, size_t elem){
    assert(strc);
    assert(isfinite(elem));

    if (elem == strc->head)
        strc->head = strc->arr[elem].next;

    if (elem == strc->tail)
        strc->tail = strc->arr[elem].prev;

    size_t next_of_elem = strc->arr[elem].next;
    size_t prev_of_elem = strc->arr[elem].prev;

    strc->arr[next_of_elem].prev = prev_of_elem;
    strc->arr[prev_of_elem].next = next_of_elem;

    strc->arr[elem].data = 0;
    strc->arr[elem].next = -1;
    strc->arr[elem].prev = -1;

    stackPush(strc->free_elem, elem);
    strc->num_of_free_elem++;
}

void del_ALL_elem(list_t *strc){
    assert(strc);

    for (unsigned idx = 0; idx <= strc->capacity; idx++) {
        strc->arr[idx].data = 0;
        strc->arr[idx].next = -1;
        strc->arr[idx].prev = -1;         
    }
}

void realloc_list(list_t *strc){
    assert(strc);

    size_t old_capacity = strc->capacity;
    strc->capacity *= resize_coeff;

    arr_t *tmp = (arr_t *)realloc(strc->arr, (strc->capacity + 1) * sizeof(arr_t));
    if (!tmp) 
        assert(0);

    strc->arr = tmp;

    for (unsigned idx = strc->capacity; idx >= old_capacity + 1; idx--) {
        stackPush(strc->free_elem, idx);
        strc->num_of_free_elem++;

        strc->arr[idx].data = 0;
        strc->arr[idx].next = -1;
        strc->arr[idx].prev = -1;  
    }
}


int get_free_elem_idx(list_t *strc) {
    assert(strc);

    int idx = strc->free_elem->data[strc->free_elem->Size - 1]; 
    stackPop(strc->free_elem);                               
    strc->num_of_free_elem--;

    return idx;
}




void make_graph_dump(const list_t *strc) {
    #ifdef GRAPH_DUMP
    
    assert(strc);

    FILE* output = fopen("GRAPH.dot", "wb");
    assert(output);

    fputs("digraph line{\n", output);
    fputs("\trankdir = LR;\n", output);
    
    for (unsigned num = 0;  num <= strc->capacity; num++) {
        if (strc->arr[num].next != -1) {
            fprintf(output, "\tstruct%d [shape = \"record\", style = \"filled\", fillcolor = \"beige\", label = \"<d>%d| %.2lf | <n>%d | %d\"];\n",
                            num, num, strc->arr[num].data, strc->arr[num].next, strc->arr[num].prev);
        }
    }

    fputs("subgraph cluster0 {\n", output);
    for (unsigned num = 0;  num <= strc->capacity; num++) {
        if (strc->arr[num].next == -1) 
            fprintf(output, "\tstruct%d [shape = \"octagon\", style = \"filled\", fillcolor = \"darkseagreen1\", label = \"%d\"];\n", num, num);
    }

    fputs("\tlabel = \"Free elements\";\n", output);
    fputs("\tcolor = green;\n", output);
    fprintf(output, "}\n");

    fprintf(output, "\tstructa [shape = \"house\", style = \"filled\", fillcolor = \"pink\", label = \"%ld\"];\n", strc->tail);
    fprintf(output, "\tstructb [shape = \"invhouse\", style = \"filled\", fillcolor = \"plum1\", label = \"%ld\"];\n", strc->head);

    for (unsigned num = 0; num <= strc->capacity; num++) {
        if (strc->arr[num].next !=-1) {
            fprintf(output, "\tstruct%d:<n> -> struct%d:<d>;\n", num, strc->arr[num].next);
        }
    }

    fprintf(output, "}");
    fclose(output);

    #endif
}