// Fig. 7.22: GradeBook.h
// Definition of class GradeBook that uses a
// two-dimensional array to store test grades.(3 test scores for each student)
// Member functions are defined in GradeBook.cpp
#include <string> // program uses C++ Standard Library string class
using namespace std;

// GradeBook class definition
class GradeBook
{
	public:
	// constant -- number of students who took the test
	static const int students = 10 ;  // note public data
	static const int tests = 3; // number of tests
		
	// constructor initializes course name and array of grades
	GradeBook( string, const int [][ tests ] );
	
	void setCourseName( string ); // function to set the course name
	string getCourseName(); // function to retrieve the course name
	void displayMessage(); // display a welcome message
	void processGrades(); // perform various operations on the grade data
	int getMinimum(); // find the minimum grade for the test
	int getMaximum(); // find the maximum grade for the test
	double getAverage( const int [], const int ); // get student¡¯s average
	void outputBarChart(); // output bar chart of grade distribution
	void outputGrades(); // output the contents of the grades array
	private:
	string courseName; // course name for this grade book
	int grades[ students ][ tests ]; // two-dimensional array of grades
}; // end class GradeBook
