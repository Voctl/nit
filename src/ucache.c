#include "../include/cache.h"

static int ccache_name(const char *name1, int len1, const char *name2, int len2){
    int len = len1 < len2 ? len1 : len2; // ternar operators ":" = if false "?" = if true
    int cmp;

    cmp = memcmp(name1, name2, len);
    if (cmp){
        return cmp;
    }
    if (len1 < len2){
        return -1;
    }
    if (len1 > len2){
        return 1;
    }
    return 0;
}


static int cache_namep(const char *name, int namelen){
    int first, last;

    first = 0;
    last = active_nr;

    while (last > first){
    int next = (last + first) >> 1;  // same with /2
    struct centry *ce = activec[next];
    int cmp = ccache_name(name, namelen, ce->name, ce->namelen);
    if (!cmp){
        return -next-1;
    }
    if (cmp < 0){
        last = next;
        continue;
    }
    first = next + 1;
    }
    return first;
}

static int rmffromc(char *path){
    int pos = cache_namep(path, strlen(path));
    if (pos < 0){
        pos = -pos-1;
        active_nr--;
        if (pos < active_nr)
            memmove(activec + pos, activec + pos + 1, (active_nr - pos -1) * sizeof(struct centry *));
    }
}

static int add_centry(struct centry *ce)
{
	int pos;

	pos = cache_namep(ce->name, ce->namelen);

	/* existing match? Just replace it */
	if (pos < 0) {
		activec[-pos-1] = ce;
		return 0;
	}

	/* Make sure the array is big enough .. */
	if (active_nr == active_alloc) {
		active_alloc = alloc_nr(active_alloc);
		activec = realloc(activec, active_alloc * sizeof(struct centry *));
	}

	/* Add it in.. */
	active_nr++;
	if (active_nr > pos)
		memmove(activec + pos + 1, activec + pos, (active_nr - pos - 1) * sizeof(ce));
	activec[pos] = ce;
	return 0;
}
