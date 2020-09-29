#define SST_NUM_ROWS 12
#define SST_NUM_COLS 12
#define SST_DTYPE int
#include <stdlib.h>
#include <string.h>

struct row{
    SST_DTYPE cols[SST_NUM_COLS];
};

typedef struct row row_t;

struct sst{
    int my_row;
    struct row rows[SST_NUM_ROWS];
};

typedef struct sst sst_t;

void sync_sst(sst_t *_from, sst_t *_to){
    row_t* from = _from->rows + _from->my_row;
    row_t* to = _to->rows + _from->my_row;
    memcpy(to->cols,from->cols,sizeof(row_t));
}

typedef char bool;

typedef bool (*predicate_t)(sst_t*);
typedef void (*trigger_t)(sst_t*);

struct action{
    predicate_t prediate;
    trigger_t trigger;
};

typedef struct action action_t;

struct replica{
    sst_t sst;
    action_t actions[];
};

typedef struct replica replica_t;

replica_t* new_replica(replica_t* old, action_t *actions, size_t num_actions){
    static int next_replica_id = 0;
    replica_t* init = malloc(sizeof(replica_t) + (sizeof(action_t)*num_actions));
    //init actions
    for (size_t i = 0; i < num_actions; ++i) init->actions[i] = actions[i];
    //init sst
    if (old){
	memcpy(&init->sst, &old->sst, sizeof(sst_t));
    }
    else {
	bzero(&init->sst,sizeof(sst_t));
    }
    init->sst.my_row = next_replica_id++;
    return init;
}

int main(){}

