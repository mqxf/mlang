#ifndef MLANG_FILE_H
#define MLANG_FILE_H
char* mlang_read(const char* filename);
void mlang_write(const char* filename, char* outbuffer);
char* sh(const char* cmd);
#endif
