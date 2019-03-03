#pragma once

#ifndef NFS_H
#define NFS_H

struct NLTK_Media_Installed;

bool IsSDCardInserted(void);
bool IsGameCartInserted(void);
bool openSaveArchive(FS_Archive *out, u64 id, FS_MediaType mediaType);
bool tryOpenSaveArchive(FS_Archive *out, u64 id, FS_MediaType *mediaTypeOut);
NLTK_Media_Installed getInstalledTitles(FS_MediaType mediaType);
void checkInstalledTitles(void);
int get_file_size(FILE *file);
bool fileExists(const char *path);
bool file_write(void *sourcebuf, const char *path, int size);
bool file_read(void* destbuf, const char *path, int size);
void saveBackup(u64 tid);
bool checkGameCartTitleSame(u64 titleId);

#endif