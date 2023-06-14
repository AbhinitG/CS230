#include <dataset.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char* names[5] = {"New", "Used", "Book", "Pen", "Laptop"};
  Category dataset[2];
  FileData files[4];
  dataset[0].name = (char*)malloc(4);
  strcpy(dataset[0].name, names[0]);
  dataset[0].list = NULL;
  dataset[1].name = (char*)malloc(5);
  strcpy(dataset[1].name, names[1]);
  dataset[1].list = NULL;

  files[0].category = (char*)malloc(4);
  files[0].file_name = (char*)malloc(5);
  strcpy(files[0].category, names[0]);
  strcpy(files[0].file_name, names[2]);
  files[1].category = (char*)malloc(4);
  files[1].file_name = (char*)malloc(4);
  strcpy(files[1].category, names[0]);
  strcpy(files[1].file_name, names[3]);
  files[2].category = (char*)malloc(5);
  files[2].file_name = (char*)malloc(4);
  strcpy(files[2].category, names[1]);
  strcpy(files[2].file_name, names[3]);
  files[3].category = (char*)malloc(5);
  files[3].file_name = (char*)malloc(7);
  strcpy(files[3].category, names[1]);
  strcpy(files[3].file_name, names[4]);

  int result;
  printf("\n=======  Test category_add  ========\n\n");
  result = category_add(dataset, 2, files, 4, "Book");
  printf("The result should be 1 and your result is %i\n", result);
  printf(
      "The first item in Category 'New' is Book. In your dataset, it is %s.\n",
      (dataset[0].list)->file->file_name);

  result = category_add(dataset, 2, files, 4, "Apple");
  printf("The result should be 0 and your result is %i\n", result);

  result = category_add(dataset, 2, files, 4, "Pen");
  printf("The result should be 1 and your result is %i\n", result);
  printf(
      "The Second item in Category 'New' is Pen. In your dataset, it is %s.\n",
      (dataset[0].list)->next->file->file_name);
  printf(
      "The first item in Category 'Used' is Pen. In your dataset, it is %s.\n",
      (dataset[1].list)->file->file_name);

  printf("\n=======  Test category_remove  ========\n\n");

  FileData* result_file = category_remove(dataset, 2, "New", "Pen");
  int comparison_result = (result_file == &files[1]);
  printf(
      "The comparison result should be 1 because the returned file should be "
      "the second file in the file list. Your result is %i.\n",
      comparison_result);

  result_file = category_remove(dataset, 2, "New", "Pen");
  printf(
      "The returned result of removing New Pen again should be NULL(nil). Your "
      "result is %p.\n",
      result_file);

  result_file = category_remove(dataset, 2, "Used", "Pen");
  comparison_result = (result_file == &files[2]);
  printf(
      "The comparison result should be 1 because the returned file should be "
      "the third file in the file list. Your result is %i.\n",
      comparison_result);
  printf(
      "The dataset[1].list should be NULL(nil) because the category Used has "
      "no item. Your result is %p.\n",
      dataset[1].list);

  printf("\n=======  Test category_change  ========\n\n");

  result_file = category_change(dataset, 2, files, 4, "Laptop", "Used", "New");
  comparison_result = (result_file == &files[3]);
  printf(
      "The comparison result should be 1 because the returned file should be "
      "the forth file in the file list. Your result is %i.\n",
      comparison_result);
  printf(
      "The category of Laptop should be changed to 'New', and your Laptop's "
      "category is '%s'.\n",
      files[3].category);

  result_file = category_change(dataset, 2, files, 4, "Book", "Used", "New");
  printf(
      "The returned result of changing Book from 'Used' to 'New' should be "
      "NULL(nil). Your result is %p.\n",
      result_file);

  result_file = category_change(dataset, 2, files, 4, "Laptop", "New", "Old");
  printf(
      "The returned result of changing Book from 'Used' to 'Old' should be "
      "NULL(nil) because there is no category Old in the dataset. Your result "
      "is %p.\n",
      result_file);

  result_file = category_change(dataset, 2, files, 4, "Pen", "Used", "New");
  printf(
      "The returned result of changing Pen from 'Used' to 'New' should be "
      "NULL(nil). Your result is %p.\n",
      result_file);
  printf(
      "The category of Pen should not be changed from 'Used' since the list "
      "aleady has Pen in category 'New'. Your result category is '%s'.\n",
      files[2].category);

  result_file = category_change(dataset, 2, files, 4, "Book", "New", "Used");
  comparison_result = (result_file == &files[0]);
  printf(
      "The comparison result should be 1 because the returned file should be "
      "the first file in the file list. Your result is %i.\n",
      comparison_result);
  printf(
      "The category of Book should be changed to 'Used', and your Book's "
      "category is '%s'.\n",
      files[0].category);
  printf("Book should be the first item of dataset[1]. Your result is %s.\n",
         (dataset[1].list)->file->file_name);
  printf(
      "The dataset[0].list should be NULL(nil) because the category New has "
      "no item. Your result is %p.\n",
      dataset[0].list);

  return 0;
}
