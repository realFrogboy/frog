#include "list.h"

int main() {
    struct list_t *lst = list_ctor();

    for (int i = 0; i < 100; i++) {
        ins_at_the_end(lst, i);
    }

    ins_before(lst, 2, 40);

    ins_before(lst, 2, 50);

    del_elem(lst, 1);

    ins_at_the_end(lst, 100);
    ins_at_the_end(lst, 200);
    ins_at_the_end(lst, 300);

    make_graph_dump(lst);

    list_dtor(lst);

    return 0;
}