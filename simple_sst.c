#define SST_NUM_ROWS 12
#define SST_NUM_COLS 12
#define SST_DTYPE int
#include <stdlib.h>
#include <string.h>

struct row{
    SST_DTYPE cols[SST_NUM_COLS];
};

typedef struct row row;

struct sst{
    int my_row;
    struct row rows[SST_NUM_ROWS];
};

typedef struct sst sst;

void sync_sst(sst *_from, sst *_to){
    row* from = _from->rows + _from->my_row;
    row* to = _to->rows + _from->my_row;
    memcpy(to->cols,from->cols,sizeof(row));
}

int main(){}

