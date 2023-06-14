#include <dataset.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int category_add(Category dataset[], int number_of_categories, FileData files[],
                 int number_of_files, const char *file_name)
{
  // TODO
  int added = 0;

  for (int i = 0; i < number_of_files; i++)
  {
    if (strcmp(files[i].file_name, file_name) != 0)
      continue;
    else
    {
      for (int j = 0; j < number_of_categories; j++)
      {
        if (strcmp(dataset[j].name, files[i].category) == 0)
        {
          if (list_contains(dataset[j].list, files[i].file_name))
          {
            break;
          }
          else
          {
            Status status = add_file(&dataset[j].list, &files[i]);
            if (status == SUCCESS)
            {
              added = 1;
            }
          }
        }
      }
    }
  }
  return added;
}

FileData *category_remove(Category dataset[], int number_of_categories,
                          const char *category, const char *file_name)
{
  // TODO
  if (strlen(category) >= 1024)
  {
    return NULL;
  }

  for (int i = 0; i < number_of_categories; i++)
  {
    if (strcmp(dataset[i].name, category) == 0)
    {
      if (list_contains(dataset[i].list, file_name))
      {
        FileNode *prev = NULL;
        FileNode *curr = dataset[i].list;
        FileData *file = NULL;
        while (curr != NULL && strcmp(curr->file->file_name, file_name) != 0)
        {
          prev = curr;
          curr = curr->next;
        }
        if (prev == NULL && curr != NULL) {
          file = curr->file;
          dataset[i].list = curr->next;
          free(curr);
          return file;
        }
        else {
          prev->next = curr->next;
          file = curr->file;
          free(curr);
          return file;
        }
      }
    }
  }
  return NULL;
}

FileData *category_change(Category dataset[], int number_of_categories,
                          FileData files[], int number_of_files,
                          const char *file_name, const char *old_category,
                          const char *new_category)
{
  if (strcmp(old_category, new_category) == 0) {
    return NULL;
  }

  for (int i = 0; i < number_of_files; i++) {
    if (strcmp(files[i].file_name, file_name) == 0 && strcmp(files[i].category, new_category) == 0)
    {
      return NULL;
    }
  }

  int contains_file = -1;
  for (int i = 0; i < number_of_files; i++)
  {
    if (strcmp(files[i].file_name, file_name) == 0 && strcmp(files[i].category, old_category) == 0)
    {
      contains_file = 1;
    }
  }
  if (contains_file != 1)
  {
    return NULL;
  }

  int contains_old_category = -1;
  int contains_new_category = -1;
  for (int i = 0; i < number_of_categories; i++)
  {
    if (strcmp(dataset[i].name, old_category) == 0)
    {
      contains_old_category = 1;
    }
    if (strcmp(dataset[i].name, new_category) == 0)
    {
      contains_new_category = 1;
    }
  }

  if (contains_old_category != 1 || contains_new_category != 1)
  {
    return NULL;
  }

  for (int i = 0; i < number_of_categories; i++)
  {
    if (strcmp(dataset[i].name, new_category) == 0)
    {
      if (list_contains(dataset[i].list, file_name))
      {
        return NULL;
      }
      else
      {
        category_remove(dataset, number_of_categories, old_category, file_name);
        int index_of_file = 0;
        for (int j = 0; j < number_of_files; j++)
        {
          if (strcmp(files[j].file_name, file_name) == 0 && strcmp(files[j].category, new_category) == 0)
          {
            return NULL;
          }
          else if (strcmp(files[j].file_name, file_name) == 0)
          {
            free(files[j].category);
            files[j].category = (char *)malloc(sizeof(new_category));
            strcpy(files[j].category, new_category);
            index_of_file = j;
          }
          else
          {
            continue;
          }
        }
        Status status = add_file(&dataset[i].list, &files[index_of_file]);
        if (status == SUCCESS)
        {
          return &files[index_of_file];
        }
      }
    }
  }
  return NULL;
}

bool list_contains(FileNode *list, const char *file_name)
{
  FileNode *temp = list;
  while (temp)
  {
    if (strcmp(temp->file->file_name, file_name) == 0)
    {
      return true;
    }
    temp = temp->next;
  }
  return false;
}

Status add_file(FileNode **list, FileData *file)
{
  FileNode *curr = *list;
  FileNode *prev = NULL;
  FileNode *pNode = (FileNode *)malloc(sizeof(FileNode));

  if (pNode)
  {
    pNode->file = file;

    while (curr != NULL && strcmp(pNode->file->file_name, curr->file->file_name) > 0)
    {
      prev = curr;
      curr = curr->next;
    }
    // pNode->file = (FileData *)malloc(sizeof(FileData));
    // pNode->file->file_name = file->file_name;
    // pNode->file->category = file->category;
    if (prev == NULL)
    {
      pNode->next = curr;
      *list = pNode;
    }
    else
    {
      prev->next = pNode;
      pNode->next = curr;
    }
    return SUCCESS;
  }
  return FAILURE;
}