#ifndef __DATASET
#define __DATASET

#include <stdbool.h>
enum status
{
  FAILURE,
  SUCCESS
};
typedef enum status Status;

typedef struct Category Category;
typedef struct FileNode FileNode;
typedef struct FileData FileData;

// Represents a category.
struct Category
{
  char *name;
  FileNode *list;
};

// Represents a node in the linked list.
struct FileNode
{
  FileData *file;
  FileNode *next;
};

// Represents a file and its category.
struct FileData
{
  char *file_name;
  char *category;
};

int category_add(Category dataset[], int number_of_categories, FileData files[],
                 int number_of_files, const char *file_name);
FileData *category_remove(Category dataset[], int number_of_categories,
                          const char *category, const char *file_name);
FileData *category_change(Category dataset[], int number_of_categories,
                          FileData files[], int number_of_files,
                          const char *file_name, const char *old_category,
                          const char *new_category);

bool list_contains(FileNode *list, const char *file_name);
Status add_file(FileNode **list, FileData *file);

#endif
