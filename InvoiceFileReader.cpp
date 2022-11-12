// Source(s) of logic assistance:  
// Gaddis, T. (2018). Starting out with C++: 
// From control structures through objects. Pearson. 

#include <iostream> // To use cin/cout
#include <iomanip>  // To access setw for output width
#include <fstream>  // To utilize ifstream, ofstream, fstream
using namespace std;

// Global Constant Initialization
const string PROG_TITLE = "Invoice File Reader Program";
const string REPORT_TITLE = "Forrest's Green Industries";
const string AUTHOR_LINE = "By Forrest Moulin";

// Function prototypes to notify compiler
// (similar format to Java interface methods)
double calculateCost(int quantity, double unitCost);
double accumulateCost(double totalCost, double itemCost);
void printLine(string itemNum, string name, int quantity,
	double unitCost, double totalCost);
void printInvoiceHeader(string date, int invNumber);
void printReportHeader();
void printTotal(double invoiceTotal);
void printDivider();

// Create output file stream object
// cout used for debugging/console
// fout used to print text to output file
ofstream fout;

int main()
{
	// Dynamic Variable Initialization
	// Create input file stream object
	ifstream fin;
	int items;
	string date;
	int numInvoices = 1;

	string itemNumber;
	string itemName;
	int quantity;
	double unitCost;
	double invoiceCost = 0;
	double totalCost = 0;

	// File paths for input/output.txt
	string txtFilePath = "C:\\Users\\UserName\\Path\\To\\input.txt"
	string outFilePath = "C:\\Users\\UserName\\Path\\To\\output.txt"

	// Program Logic
	// Use the txt/output file paths as arg s
	// to open the input/output stream file objects
	fin.open(txtFilePath);
	fout.open(outFilePath);

	// Console visibility
	cout << fixed << setprecision(2)
		<< PROG_TITLE << endl
		<< AUTHOR_LINE << endl << endl;

	// Print to output file
	fout << fixed << setprecision(2)
		<< PROG_TITLE << endl
		<< AUTHOR_LINE << endl << endl;
	printReportHeader();

	// End program in event of file loading failure
	if (fin.fail())
	{
		cout << "File open failure:" << endl
			<< txtFilePath << endl;
		fin.close();
		fout.close();
		return 0;
	}

	if (fout.fail())
	{
		cout << "File output failure:" << endl
			<< outFilePath << endl;
		fin.close();
		fout.close();
		return 0;
	}
	// While the input file stream contains items int and date string on a line
	while (fin >> items >> date)
	{
		// Reset invoice on each iteration
		invoiceCost = 0;
		printInvoiceHeader(date, numInvoices);
		// Loop based on number of items in each invoice
		for (int i = 0; i < items; i++)
		{
			// Read the item number, customer name, tuantity, and unit cost
			// from the input file stream
			fin >> itemNumber >> itemName >> quantity >> unitCost;
			// Add each calculated item cost to the invoice cost
			invoiceCost = accumulateCost(invoiceCost, calculateCost(quantity, unitCost));
			// Print the details for each item
			printLine(itemNumber, itemName, quantity, unitCost, calculateCost(quantity, unitCost));
		}
		// Visibility of system status/calculations
		printTotal(invoiceCost);
		// Track total cost of all invoices
		totalCost += invoiceCost;
		// Track number of invoices read
		numInvoices++;
		printDivider();
	}
	cout << "Total Cost: $ " << totalCost << endl;
	fout << "Total Cost: $ " << totalCost << endl;
	// Close file input/output streams upon completion
	fin.close();
	cout << endl << "Output file created successfully!" << endl;
	fout.close();
}
// Function definitions
double calculateCost(int quantity, double unitCost)
{
	return quantity * unitCost;
}

double accumulateCost(double invoiceCost, double itemCost)
{
	return itemCost + invoiceCost;
}

void printLine(string itemNum, string itemName, int quantity,
	double unitCost, double totalCost)
{
	cout << left << setw(9) << itemNum
		<< left << setw(12) << itemName
		<< left << setw(6) << quantity << "$ " << left << setw(8)
		<< unitCost << "$" << right << setw(10) << totalCost << endl;

	fout << left << setw(9) << itemNum
		<< left << setw(12) << itemName
		<< left << setw(6) << quantity << "$ " << left << setw(8)
		<< unitCost << "$" << right << setw(10) << totalCost << endl;
}

void printInvoiceHeader(string date, int invNumber)
{
	cout << "Invoice # " << invNumber << " Date:    " << date
		<< endl;

	fout << "Invoice # " << invNumber << " Date:    " << date
		<< endl;
}

void printReportHeader()
{
	cout << REPORT_TITLE << endl;
	fout << REPORT_TITLE << endl;
	printDivider();
}

void printTotal(double invoiceTotal)
{
	cout << endl << "Total Invoice Cost:" << setw(18) << " " << "$"
		<< right << setw(10) << invoiceTotal << endl;
}

void printDivider()
{
	// Creates divider of length 28 with '-' char
	// Then resets so that fill char is not fixed as '-'
	cout << setw(48) << setfill('-') << "" << setfill(' ') << "" << endl;
	fout << setw(48) << setfill('-') << "" << setfill(' ') << "" << endl;
}
/*
* INPUT.TXT FILE USED
* 3 2/12/2017
* 134276 Framis-R 8 7.35
* 125790 Framis-L 12 15.76
* 100086 Aglet  395 0.11
* 2 1/23/2017
* 135876 Wrench 12 22.50
* 543287 Henway 4 19.25
* 3 1/15/2017
* 161432 Widget 5 6.50
* 543289 Wodget 10 2.25
* 876234 Gadget  2 10.75
* 9 2/16/2017
* 198765 Corkle 2 12.18
* 107654 Swale 3  8.75
* 987987 Sinter 5 6.43
* 654821 Zangle 6 18.45
* 432165 Lunule 7 9.60
* 333221 Fangle 10 58.49
* 654098 Fwetstock 3 12.65
* 543210 Furnal 3  9.98
* 543287 Bobble 12 19.25
* 6 2/26/2017
* 654821 Muntin 2 18.45
* 766443 Finwiddie 9 2.22
* 120980 Ferkle 100 0.12
* 123222 Sneedooper 700 1.19
* 876543 Ferrule 2 345.77
* 877721 Uberfrock 14 88.93
*/

/*
* CONSOLE OUTPUT/OUTPUT FILE output.txt
* Invoice File Reader Program
* By Forrest Moulin
*
* Forrest's Green Industries
* ------------------------------------------------
* Invoice # 1 Date:    2/12/2017
* 134276   Framis-R    8     $ 7.35    $     58.80
* 125790   Framis-L    12    $ 15.76   $    189.12
* 100086   Aglet       395   $ 0.11    $     43.45
*
* Total Invoice Cost:                  $    291.37
* ------------------------------------------------
* Invoice # 2 Date:    1/23/2017
* 135876   Wrench      12    $ 22.50   $    270.00
* 543287   Henway      4     $ 19.25   $     77.00
*
* Total Invoice Cost:                  $    347.00
* ------------------------------------------------
* Invoice # 3 Date:    1/15/2017
* 161432   Widget      5     $ 6.50    $     32.50
* 543289   Wodget      10    $ 2.25    $     22.50
* 876234   Gadget      2     $ 10.75   $    110.70
*
* 333221   Fangle      10    $ 58.49   $    584.90
* 654098   Fwetstock   3     $ 12.65   $     37.95
* 543210   Furnal      3     $ 9
* 543287   Bobble      12    $ 19.25   $    231.00
*
* Total Invoice Cost:                  $   1144.45
* ------------------------------------------------
* Invoice # 5 Date:    2/26/2017
* 654821   Muntin      2     $ 18.45   $     36.90
* 766443   Finwiddie   9     $ 2.22    $     19.98
* 120980   Ferkle      100   $ 0.12    $     12.00
* 123222   Sneedooper  700   $ 1.19    $    833.00
* 876543   Ferrule     2     $ 345.77  $    691.54
* 877721   Uberfrock   14    $ 88.93   $   1245.02
*
* Total Invoice Cost:                  $   2838.44
* ------------------------------------------------
* Total Cost: $ 4697.76
* 
* Output file created successfully!
*/
