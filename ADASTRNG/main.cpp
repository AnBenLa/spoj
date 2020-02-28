//
// Created by Mortiferum on 12.01.2020.
//

#include<bits/stdc++.h>
#include <limits.h>
#include <stdlib.h>

using namespace std;
typedef unsigned int ui;

const ui max_dim = 300010;
char txt [max_dim];
ui suff_ind [max_dim], n, char_count[26];


#define C_SIZE (UCHAR_MAX+1)
#define C_CUM(c) C[c << 1]		//cumulative C array
#define C_CNT(c) C[(c << 1) + 1] 	//C array counting characters
#define GLINK PREV			//alias
#define GENDLINK ISA			//alias

//helper functions for GSIZE, an array for variable-length numbers:
//Let GSIZE[i]=k and GSIZE[j]=l (i < j) be any two numbers in GSIZE.
//Then, the algorithm always ensures that i+k <= j holds.
//All operations except calloc and free are supposed to be O(1).
void *       gsize_calloc( unsigned int n );
void         gsize_free( void *g );
void         gsize_set( void *g, unsigned int pos, unsigned int val );
unsigned int gsize_get( const void *g, unsigned int pos );
void         gsize_clear( void *g, unsigned int pos ); //sets gsize at pos to 0
unsigned int gsize_dec_get( void *g, unsigned int pos ); //first decrement, then read
void         gsize_inc( void *g, unsigned int pos ); //increment

int gsaca_unsigned() {
    unsigned int *ISA, *PREV;
    void *GSIZE;
    unsigned int i,j;
    unsigned int gstart, gend;
    unsigned int s, p, sr;
    unsigned int tmp, gstarttmp, gendtmp;
    unsigned int C[2*C_SIZE]; //counts and cumulative counts

    if (n == 0)		return 0;
    if (txt[n-1] != '\0')	return -1;

    //set up needed structures
    ISA = (unsigned int *)malloc( n * sizeof(unsigned int) );
    PREV = (unsigned int *)malloc( n * sizeof(unsigned int) );
    GSIZE = gsize_calloc( n );
    if (!ISA || !PREV || !GSIZE)	{
        free(ISA); free(PREV); gsize_free(GSIZE);
        return -2;
    }

    //// PHASE 1: pre-sort suffixes ////
    //build initial group structure
    for (i = 0; i < C_SIZE; ++i)	C_CNT(i) = 0;
    for (i = 0; i < n; ++i) ++C_CNT(txt[i]); //count characters

    if (C_CNT(0) != 1) { //more than 1 nullbyte
        free(ISA); free(PREV); gsize_free(GSIZE);
        return -1;
    }
    j = 0;
    for (i = 0; i < C_SIZE; ++i) { //build cumulative counts and set up GSIZE
        if (C_CNT(i) > 0) {
            C_CUM(i) = j;
            gsize_set(GSIZE, j, C_CNT(i));
            j += C_CNT(i);
        }
    }
    for (i = n-1; i < n; --i) { //set up ISA, GLINK and SA
        gstart = C_CUM(txt[i]);
        sr = gstart + --C_CNT(txt[i]);
        GLINK[i] = gstart;
        ISA[i] = sr;
        suff_ind[sr] = i;
    }

    //process groups from highest to lowest
    for (gend = n-1; gend > 0; gend = gstarttmp-1) {
        gstart = GLINK[suff_ind[gend]];
        gstarttmp = gstart;	gendtmp = gend;

        //clear GSIZE group size for marking
        gsize_clear(GSIZE, gstart);

        //compute prev - pointers and mark suffixes of own group that
        //have a prev-pointer of own group pointing to them
        for (i = gend; i >= gstart; --i) {
            s = suff_ind[i]; //use prev - pointers from already used groups
            for (p = s-1; p < n; p = PREV[p]) {
                if (ISA[p] <= gend) {
                    if (ISA[p] >= gstart) {
                        gsize_set(GSIZE, ISA[p], 1); //mark ISA[p]
                    }
                    break;
                }
            }
            PREV[s] = p;
        }

        //set GENDLINK of all suffixes for phase 2 and move unmarked
        // suffixes to the front of the actual group
        j = 0;
        for (i = gstart; i <= gend; ++i) {
            s = suff_ind[i];
            GENDLINK[s] = gend;
            if (gsize_get(GSIZE, i) == 0) { //i is not marked
                suff_ind[gstart+(j++)] = s;
            }
        }

        //order the suffixes according on how much suffixes of same
        //group are jumped by them
        gend = gstart + j; //exclusive bound by now
        j = 0;
        do {
            i = gend-1; sr = gend;
            while (i >= gstart) {
                s = suff_ind[i];
                p = PREV[s];
                if (p < n) {
                    if (ISA[p] < gstarttmp) { //p is in a lex. smaller group
                        suff_ind[i--] = suff_ind[--gend];
                        suff_ind[gend] = p; //push prev to back
                    } else { //p is in same group
                        PREV[s] = PREV[p];
                        PREV[p] = n; //clear prev pointer, is not used in phase 2
                        --i;
                    }
                } else { //prev points to nothing
                    suff_ind[i] = suff_ind[gstart++]; //remove entry
                }
            }
            //write number of suffixes written to end on stack using GSIZE
            if (gend < sr) {
                gsize_set(GSIZE, gend, sr-gend);
                ++j; //also, count number of splitted groups
            }
        } while (gstart < gend);

        //rearrange previous suffixes stored in other groups
        while (j--) {
            gend = gstart + gsize_get(GSIZE, gstart);
            //decrement group count of previous group suffixes, and move them to back
            for (i = gend-1; i >= gstart; --i) {
                p = suff_ind[i];
                sr = GLINK[p];
                sr += gsize_dec_get(GSIZE, sr);
                //move p to back by exchanging it with last suffix s of group
                s = suff_ind[sr];
                tmp = ISA[p];
                suff_ind[tmp] = s;	ISA[s] = tmp;
                suff_ind[sr] = p;	ISA[p] = sr;
            }
            //set new GLINK for moved suffixes
            for (i = gstart; i < gend; ++i) {
                p = suff_ind[i];
                sr = GLINK[p];
                sr += gsize_get(GSIZE, sr);
                GLINK[p] = sr;
            }
            //set up GSIZE for newly created groups
            for (i = gstart; i < gend; ++i) {
                p = suff_ind[i];
                sr = GLINK[p];
                gsize_inc(GSIZE, sr);
            }
            gstart = gend;
        }

        //prepare current group for phase 2
        suff_ind[gendtmp] = gstarttmp; //counter where to place next entry
    }

    //// PHASE 2: sort suffixes finally ////
    suff_ind[0] = n-1;
    for (i = 0; i < n; i++) {
        s = suff_ind[i]-1;
        while (s < n) {
            sr = GENDLINK[s];
            if (sr == n) //suffix already placed to SA, stop
                break;
            sr = suff_ind[sr]++; //get position where to write s
            suff_ind[sr] = s;
            //mark that suffix is placed in SA already
            GENDLINK[s] = n;
            /* NOTE: Using annother technique
               to indicate if a suffix is placed to SA already,
               ISA could be computed too. A possible way would be to
               set PREV[s] = s, and check that in the above if.
            */
            s = PREV[s]; //process next suffix
        }
    }

    free(ISA); free(PREV); gsize_free(GSIZE);
    return 0;
}

int gsaca(const unsigned char *S, int *SA, int n) {
    if (n < 0)	return -1;
    return gsaca_unsigned();
}

//// GSIZE OPERATIONS /////////////////////////////////////////////////////////
void *gsize_calloc( unsigned int n ) {
    return calloc(n, sizeof(unsigned int));
}

void gsize_free( void *g ) {
    free(g);
}

void gsize_set( void *g, unsigned int pos, unsigned int val ) {
    ((unsigned int *)g)[pos] = val;
}

unsigned int gsize_get( const void *g, unsigned int pos ) {
    return ((const unsigned int *)g)[pos];
}

void gsize_clear( void *g, unsigned int pos ) {
    ((unsigned int *)g)[pos] = 0;
}

unsigned int gsize_dec_get( void *g, unsigned int pos ) {
    return --((unsigned int *)g)[pos];
}

void gsize_inc( void *g, unsigned int pos ) {
    ++((unsigned int *)g)[pos];
}

int main() {
    scanf("%s", txt);
    n = strlen(txt);
    txt[n] = '\0';
    n++;
    gsaca_unsigned();

    for(ui i = 1; i < n; ++i){
        //find difference between adjacent words in the suffix array
        ui cur_i = suff_ind[i], cur_j = suff_ind[i+1], diff = 0;
        bool finished = false;
        while(!finished && cur_i < n && cur_j < n) {
            if (txt[cur_i] != txt[cur_j])
                finished = true;
            else {
                diff++; cur_i++; cur_j++;
            }
        }
        //increase the count for the character
        char_count[txt[suff_ind[i]] - 'a'] += n - 1 - suff_ind[i] - diff;
    }
    for (ui i = 0; i < 26; ++i){
        printf("%d ", char_count[i]);
    }
    return 0;
}
