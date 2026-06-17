#include "../include/cache.h"

/*SOOO 
 its just initialize the whole system yk yk yk miningit 
 and making the .miningit/objects and it will make some stuff in future fr
 */

int main(int argc, char **argv){
  char *sha1fd = getenv(DB_ENVIRONMENT), *path;
  int len,i, fd;

  if (mkdir(".miningit", 0700) < 0 && errno != EEXIST) {
     perror(".miningit");
     exit(1);
  }
 if (mkdir(".miningit/objects", 0700) < 0 &&
    errno != EEXIST) {
    perror(".miningit/objects");
    exit(1);
  }

  sha1fd = getenv(DB_ENVIRONMENT);
  if (sha1fd){
    struct stat st;
    if(!stat(sha1fd, &st) && S_ISDIR(st.st_mode)){
        return 0;}
    fprintf(stderr, "DB_ENVIRONMENT set to bad directory mans hm %s: ", sha1fd);
  }


  sha1fd = DEFAULT_DB_ENVIRONMENT;
  fprintf(stderr, "defaulting to private storage are\n");
  len = strlen(sha1fd);


  path = malloc(len + 40);
  memcpy(path, sha1fd, len);
  for (i = 0; i < 256; i++){
        sprintf(path + len, "/%02x", i);
        if(mkdir(path, 0700) < 0){
            if (errno != EEXIST){
                perror(sha1fd);
                exit(1);
            }
        }
  }
  free(path);
  return 0;
}
