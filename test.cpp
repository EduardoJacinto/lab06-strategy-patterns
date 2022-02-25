#include "spreadsheet.hpp"
#include "select.hpp"

#include "gtest/gtest.h"

#include <iostream>
#include <sstream>

using namespace std;

TEST(printTest, printSelection) {
	Spreadsheet sheet;

	sheet.set_column_names({"First","Last","Age","Major"});
	sheet.add_row({"Amanda","Andrews","22","business"});
	sheet.add_row({"Brain","Becker","21","computer science"});
	
	sheet.print_selection(cout);
	cout << endl;
}

TEST(printTest, selectContains) {
	Spreadsheet sheet;

	sheet.set_column_names({"First", "Last", "Age", "Major"});
	sheet.add_row({"Amanda","Andrews","22","business"});
	sheet.add_row({"Brian","Becker","21","computer science"});
	sheet.set_selection(new Select_Contains(&sheet, "Last","Andrew"));

	sheet.print_selection(cout);
	cout << endl;
}


TEST(printTest, Empty) {
	Spreadsheet sheet1;
	Spreadsheet sheet2;
	stringstream out;
	stringstream out2;	

	sheet1.set_column_names({"First", "Last", "Age", "Major"});
	sheet1.add_row({"Amanda", "", "22", "business"});
	sheet1.add_row({"Brian", "cat", "21", "computer science"});
	sheet1.set_selection(new Select_Contains(&sheet1, "Last", "")); 
	
	sheet1.print_selection(out);

	sheet2.set_column_names({"First", "Last", "Age", "Major"});
	sheet2.add_row({"Amanda", "", "22", "business"});
        sheet2.add_row({"Brian", "cat", "21", "computer science"});
        sheet2.print_selection(out2);


	EXPECT_EQ(out.str(), out2.str());
}

TEST(printTest, Substring) {
        Spreadsheet sheet1;
        Spreadsheet sheet2;
        stringstream out;
        stringstream out2;

        sheet1.set_column_names({"First", "Last", "Age", "Major"});
        sheet1.add_row({"Diane", "apple", "22", "business"});
        sheet1.add_row({"David", "apples", "21", "computer science"});
	sheet1.add_row({"Sarah", "Snapple", "22", "computer science"});
	sheet1.add_row({"George", "APPLE", "21", "astrophysics"});
	sheet1.add_row({"Joe", "app", "21", "mathematics"});
        sheet1.set_selection(new Select_Contains(&sheet1, "Last", "apple"));

        sheet1.print_selection(out);

        sheet2.set_column_names({"First", "Last", "Age", "Major"});
        sheet2.add_row({"Diane", "apple", "22", "business"});
        sheet2.add_row({"David", "apples", "21", "computer science"});
	sheet2.add_row({"Sarah", "Snapple", "22", "computer science"});
        sheet2.print_selection(out2);

        EXPECT_EQ(out.str(), out2.str());
}


TEST(printTest, selectNot) {
	Spreadsheet sheet;
	Spreadsheet sheet2;
	stringstream out;
	stringstream out2;
	
	sheet.set_column_names({"First", "Last", "Age", "Major"});
	sheet.add_row({"Diane", "Dole", "22", "computer science"});
	sheet.add_row({"Sarah", "Summers", "20", "computer science"});
	sheet.add_row({"Joe", "Jackson", "21", "mathematics"});

	sheet.set_selection(
		new Select_Not(
			new Select_Contains(&sheet, "Major", "computer science")));
	
	sheet.print_selection(out);

	sheet2.set_column_names({"First", "Last", "Age", "Major"});
	sheet2.add_row({"Joe", "Jackson", "21", "mathematics"});
	sheet2.print_selection(out2);	
        
	EXPECT_EQ(out.str(), out2.str());	
	
}

TEST(printTest, selectAnd) {
        Spreadsheet sheet;
        Spreadsheet sheet2;
        stringstream out;
        stringstream out2;

        sheet.set_column_names({"First", "Last", "Age", "Major"});
        sheet.add_row({"Diane", "Dole", "22", "computer science"});
        sheet.add_row({"Sarah", "Summers", "20", "computer science"});
        sheet.add_row({"Joe", "Jackson", "21", "mathematics"});
	sheet.add_row({"Amanda", "Andrews", "22", "business"});
	sheet.add_row({"David", "Dole", "22", "electrical engineering"});
	sheet.add_row({"George", "Genius", "20", "computer science"});
	
        sheet.set_selection(
                new Select_And(
                        new Select_Contains(&sheet, "Major", "computer science"),
			new Select_Not(new Select_Contains(&sheet, "Age", "22"))));
        sheet.print_selection(out);

        sheet2.set_column_names({"First", "Last", "Age", "Major"});
        sheet2.add_row({"Sarah", "Summers", "20", "computer science"});
	sheet2.add_row({"George", "Genius", "20", "computer science"});
        sheet2.print_selection(out2);

        EXPECT_EQ(out.str(), out2.str());

}

TEST(printTest, selectOr) {
        Spreadsheet sheet;
        Spreadsheet sheet2;
        stringstream out;
        stringstream out2;

        sheet.set_column_names({"First", "Last", "Age", "Major"});
        sheet.add_row({"Diane", "Dole", "22", "computer science"});
        sheet.add_row({"Sarah", "Summers", "20", "computer science"});
        sheet.add_row({"Joe", "Jackson", "21", "mathematics"});
        sheet.add_row({"Amanda", "Andrews", "22", "business"});
        sheet.add_row({"David", "Dole", "22", "electrical engineering"});
        sheet.add_row({"George", "Genius", "20", "computer science"});

        sheet.set_selection(
                new Select_Or(
                        new Select_Contains(&sheet, "Major", "computer science"),
                        new Select_Contains(&sheet, "Age","22")));
        sheet.print_selection(out);

        sheet2.set_column_names({"First", "Last", "Age", "Major"});
	sheet2.add_row({"Diane","Dole","22","computer science"});
        sheet2.add_row({"Sarah", "Summers", "20", "computer science"});
	sheet2.add_row({"Amanda", "Andrews", "22", "business"});
	sheet2.add_row({"David", "Dole", "22", "electrical engineering"});
	sheet2.add_row({"George", "Genius", "20", "computer science"});


        sheet2.print_selection(out2);

        EXPECT_EQ(out.str(), out2.str());

}











int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
