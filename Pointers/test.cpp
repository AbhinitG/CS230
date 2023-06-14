#include <gtest/gtest.h>

extern "C" {
#include <dataset.h>
}

#define MAX_LEN 1024

const char* names[5] = {"New", "Used", "Book", "Pen", "Laptop"};
Category dataset[2];
FileData files[4];


class basicDatabaseEnvironment : public testing::Environment {
 public:
  virtual void SetUp() {
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

  }
};

void reset_dataset() {
  dataset[0].list = NULL;
  dataset[1].list = NULL;
}

TEST(ProjectTests, Category_add_first) {
  reset_dataset();
  int result;
  result = category_add(dataset, 2, files, 4, "Book");
  EXPECT_EQ(result, 1) << "The return value of category_add should be 1";
  ASSERT_STREQ((dataset[0].list)->file->file_name, "Book")
      << "The first item in Category 'New' should be Book.";
}

TEST(ProjectTests, Category_add_none) {
  reset_dataset();
  int result;
  result = category_add(dataset, 2, files, 4, "Apple");
  EXPECT_EQ(result, 0) << "The return value of category_add should be 0";
}

TEST(ProjectTests, Category_add_multiple) {
  reset_dataset();
  int result;
  result = category_add(dataset, 2, files, 4, "Book");
  result = category_add(dataset, 2, files, 4, "Pen");
  EXPECT_EQ(result, 1) << "The return value of category_add should be 1";
  ASSERT_STREQ((dataset[0].list)->next->file->file_name, "Pen")
      << "The second item in Category 'New' should be Pen.";
  ASSERT_STREQ((dataset[1].list)->file->file_name, "Pen")
      << "The first item in Category 'Used' should be Pen.";
}

TEST(ProjectTests, Category_remove_second_item) {
  reset_dataset();
  category_add(dataset, 2, files, 4, "Book");
  category_add(dataset, 2, files, 4, "Pen");
  FileData* result_file = category_remove(dataset, 2, "New", "Pen");
  EXPECT_TRUE(result_file == &files[1])
      << "The returned file should be the second file in the file list.";
  ASSERT_STREQ((dataset[0].list)->file->file_name, "Book")
      << "The first item in Category 'New' should be Book.";
  ASSERT_STREQ((dataset[1].list)->file->file_name, "Pen")
      << "The first item in Category 'Used' should be Pen.";
  EXPECT_TRUE((dataset[0].list)->next == NULL)
      << "The Category 'New' should have only one item";
}

TEST(ProjectTests, Category_remove_none) {
  reset_dataset();
  category_add(dataset, 2, files, 4, "Book");
  category_add(dataset, 2, files, 4, "Pen");
  FileData* result_file = category_remove(dataset, 2, "New", "Pen");
  result_file = category_remove(dataset, 2, "New", "Pen");
  EXPECT_TRUE(result_file == NULL) << "The returned result should be NULL";
}

TEST(ProjectTests, Category_remove_first_item) {
  reset_dataset();
  category_add(dataset, 2, files, 4, "Book");
  category_add(dataset, 2, files, 4, "Pen");
  FileData* result_file = category_remove(dataset, 2, "Used", "Pen");
  EXPECT_TRUE(result_file == &files[2])
      << "The returned file should be the third file in the file list.";
  ASSERT_STREQ((dataset[0].list)->file->file_name, "Book")
      << "The first item in Category 'New' should be Book.";
  ASSERT_STREQ((dataset[0].list)->next->file->file_name, "Pen")
      << "The second item in Category 'New' should be Pen.";
  EXPECT_TRUE(dataset[1].list == NULL) << "The Category 'Used' should be empty";
}

TEST(ProjectTests, Change_file_not_included) {
  reset_dataset();
  FileData* result_file =
      category_change(dataset, 2, files, 4, "Laptop", "Used", "New");
  EXPECT_TRUE(result_file == &files[3])
      << "The returned file should be the forth file in the file list.";
  ASSERT_STREQ(files[3].category, "New")
      << "The category of Laptop should be changed to 'New'.";
}

TEST(ProjectTests, Change_file_with_incorrect_category) {
  reset_dataset();
  FileData* result_file =
      category_change(dataset, 2, files, 4, "Book", "Used", "New");
  EXPECT_TRUE(result_file == NULL)
      << "The returned result of changing Book from 'Used' to 'New' should be "
         "NULL since there is no Used Book.";

  result_file = category_change(dataset, 2, files, 4, "Laptop", "New", "Old");
  EXPECT_TRUE(result_file == NULL)
      << "The returned result of changing Book from 'Used' to 'Old' should be "
         "NULL because there is no category Old in the dataset.";
}

TEST(ProjectTests, Change_file_to_duplicate_category) {
  reset_dataset();
  FileData* result_file =
      category_change(dataset, 2, files, 4, "Pen", "Used", "New");
  EXPECT_TRUE(result_file == NULL)
      << "The returned result of changing Pen from 'Used' to 'New' should be "
         "NULL since there is a New Pen exist in the list.";
  ASSERT_STREQ(files[2].category, "Used")
      << "The category of Used Pen should not be changed.";
}

TEST(ProjectTests, Change_file_included) {
  reset_dataset();
  category_add(dataset, 2, files, 4, "Book");
  FileData* result_file =
      category_change(dataset, 2, files, 4, "Book", "New", "Used");
  EXPECT_TRUE(result_file == &files[0])
      << "The returned file should be the first file in the file list.";
  ASSERT_STREQ(files[0].category, "Used")
      << "The category of Book should be changed to Used";
  ASSERT_STREQ((dataset[1].list)->file->file_name, "Book")
      << "Book should be the first item of dataset[1].";
  EXPECT_TRUE(dataset[0].list == NULL)
      << "The dataset[0].list should be NULL because the category New has no "
         "item.";
}


int main(int argc, char** argv) {
testing:
  AddGlobalTestEnvironment(new basicDatabaseEnvironment);
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
