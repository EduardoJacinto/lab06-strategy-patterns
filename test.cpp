#include "spreadsheet.hpp"
#include "select.hpp"

#include "gtest/gtest.h"

#include <iostream>
#include <sstream>

using namespace std;

TEST(printTest, Empty) {
	Spreadsheet sheet1;
	Spreadsheet sheet2;
	stringstream out;
	stringstream out2;	

	sheet1.set_column_names(("First", "Last", "Age", "Major"));
	sheet1.add_row(("Amanda", "", "22", "business"));
	sheet1.add_row(("Brian", "cat", "21", "computer science"));
	sheet1.set_selection(new Select_Contains(&sheet, "Last", "")); 
	
	sheet1.print_selection(out);

	sheet2.set_column_names(("First", "Last", "Age", "Major"));
	sheet2.add_row(("Amanda", "", "22", "business"));
        sheet2.add_row(("Brian", "cat", "21", "computer science"));
        sheet2.print_selection(out2);


	EXPECT_EQ(out.str(), out2.str());
}

TEST(printTest, Cases) {
        Spreadsheet sheet1;
        Spreadsheet sheet2;
        stringstream out;
        stringstream out2;

        sheet1.set_column_names(("First", "Last", "Age", "Major"));
        sheet1.add_row(("Diane", "dole", "22", "business"));
        sheet1.add_row(("David", "Dole", "21", "computer science"));
        sheet1.set_selection(new Select_Contains(&sheet, "Last", "Dole"));

        sheet1.print_selection(out);

        sheet2.set_column_names(("First", "Last", "Age", "Major"));
        sheet2.add_row(("Diane", "dole", "22", "business"));
        sheet2.add_row(("David", "Dole", "21", "computer science"));
        sheet2.print_selection(out2);

	EXPECT_EQ(out.str(), out2.str());
}

TEST(printTest, Substring) {
        Spreadsheet sheet1;
        Spreadsheet sheet2;
        stringstream out;
        stringstream out2;

        sheet1.set_column_names(("First", "Last", "Age", "Major"));
        sheet1.add_row(("Diane", "apple", "22", "business"));
        sheet1.add_row(("David", "apples", "21", "computer science"));
	sheet1.add_row(("Sarah", "Snapple", "22", "computer science"));
	sheet1.add_row(("George", "APPLE", "21", "astrophysics"));
	sheet1.add_row(("Joe", "app", "21", "mathematics"));
        sheet1.set_selection(new Select_Contains(&sheet, "Last", "apple"));

        sheet1.print_selection(out);

        sheet2.set_column_names(("First", "Last", "Age", "Major"));
        sheet2.add_row(("Diane", "dole", "22", "business"));
        sheet2.add_row(("David", "Dole", "21", "computer science"));
	sheet2.add_row(("Sarah", "Snapple", "22", "computer science"));
        sheet2.add_row(("George", "APPLE", "21", "astrophysics"));
        sheet2.add_row(("Joe", "app", "21", "mathematics"));

        sheet2.set_selection(new Select_Contains(&sheet, "Last", "apple"));

        sheet2.print_selection(out2);

        EXPECT_EQ(out.str(), out2.str());
}












int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
