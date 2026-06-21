#pragma once

#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <sys/mman.h>
#include <openssl/sha.h> /*its for SHA1 algorithm which is doing that shi for denis's project - In cryptography,
SHA-1 (Secure Hash Algorithm 1) is a hash function which takes an input and produces a 160-bit (20-byte)
hash value known as a message digest – typically rendered as 40 hexadecimal digits.*/
#include <zlib.h>
#include <string.h>
/*
 NOTE! Its basic data structures for directory cache yk
 its just for efficient
*/

#define CACHE_SIGNATURE 0x53484954	/* "SHIT" */

/*cache header structure*/

struct cache_header{
    unsigned int signature; //it will read my signature (shit)
    unsigned int version;  //project version
    unsigned int entries;  //the number of dirs which is in my that cache tuff
    unsigned char sha1[];
};

struct timeofc{
    unsigned int sec;
    unsigned int nsec;
}; // its just looking at the diff time of data with nanosec man

struct centry{
    struct timeofc ctime; //metadata diff time
    struct timeofc mtime; // last time of changing inside of file
    unsigned int stdev;  // passw of device
    unsigned int stino;  // the index number of dir in os
    unsigned int stmode;  // the permissions of file
    unsigned int stgid;  // user id
    unsigned int stuuid; //group id
    unsigned int stsize;  // byte of file
    unsigned char sha1[20];  //the inside of file in SHA1 (20 byte)
    unsigned short namelen;  // the length of filename
    unsigned char name[];  //Flexible Array Member hm (bro Linus know his job)
};


#define DB_ENVIRONMENT "SHA1_FILE_DIRECTORY"
#define DEFAULT_DB_ENVIRONMENT ".miningit/objects"


extern const char *sha1fd;
extern struct centry **activec;
extern unsigned int active_nr, active_alloc;


#define centry_size(len) ((offsetof(struct centry,name) + (len) + 8) & ~7)
#define ce_size(ce) cache_entry_size((ce)->namelen)
#define alloc_nr(x) (((x)+16)*3/2)
// some math shis to performance (i think its Linus's codes to performance)


//functions
static int ccache_name(const char *name1, int len1, const char *name2, int len2);
static int rmffromc(char *path);
static int cache_namep(const char *name, int namelen);
