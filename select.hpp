#ifndef __SELECT_HPP__
#define __SELECT_HPP__

#include <cstring>
class Select
{
public:
    virtual ~Select() = default;

    // Return true if the specified row should be selected.
    virtual bool select(const Spreadsheet* sheet, int row) const = 0;
};

// A common type of criterion for selection is to perform a comparison based on
// the contents of one column.  This class contains contains the logic needed
// for dealing with columns. Note that this class is also an abstract base
// class, derived from Select.  It introduces a new select function (taking just
// a string) and implements the original interface in terms of this.  Derived
// classes need only implement the new select function.  You may choose to
// derive from Select or Select_Column at your convenience.
class Select_Column: public Select
{
protected:
    int column;
public:
    Select_Column(const Spreadsheet* sheet, const std::string& name)
    {
        column = sheet->get_column_by_name(name);
    }

    virtual bool select(const Spreadsheet* sheet, int row) const
    {
        return select(sheet->cell_data(row, column));
    }

    // Derived classes can instead implement this simpler interface.
    virtual bool select(const std::string& s) const = 0;
};
				
 class Select_Contains: public Select_Column
{

protected:
       std::string name;
public:
        Select_Contains(Spreadsheet* sheet, const std::string cName, const std::string spreadName) : Select_Column(sheet,cName) {
        name = spreadName;
}

        virtual bool select(const std::string& word) const {
                if(word == "") {
                       return true;
                }
		
		int var1 = word.find(name);
		if(var1 == std::string::npos) {
			return false; 
		}
		else {
			return true;
		}
}
};

class Select_Not : public Select {
	
	protected:
		Select* temp1;

	public: 
		Select_Not(Select* select) {
			temp1 = select;
		}
		~Select_Not() {
			delete temp1;
		}
		virtual bool select(const Spreadsheet* sheet, int row) const {
			return ( !temp1->select(sheet,row));
		}
};	

class Select_And : public Select {
	protected:
		Select* temp1;
		Select* temp2;
	
	public:
		Select_And(Select* object, Select* object2) {
			temp1 = object;
			temp2 = object2;
		}
		~Select_And() {
		delete temp1;
		delete temp2;
		}
		
		virtual bool select(const Spreadsheet* sheet, int row) const {
			if (!((temp1->select(sheet,row) && (temp2->select(sheet,row))))) {
				return false;
			}
			else {	
				return true;
			}
		}
};

class Select_Or : public Select {
	protected: 
		Select* temp1;
		Select* temp2;		

	public:
		Select_Or(Select* object, Select* object2) {
			temp1 = object;
			temp2 = object2;
		}
		~Select_Or() {
			delete temp1;
			delete temp2;
		}
		
		virtual bool select( const Spreadsheet* sheet, int row) const {
			if(!((temp1->select(sheet,row) || temp2->select(sheet,row)))) {
				return false;
			}
			else {
				return true;
			}
		}
};


#endif //__SELECT_HPP__
