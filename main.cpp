/*
 * Full Name:     Isabella Ferrisi
 * Student ID:    002077163
 * Course:        EECE 2140 - Computing Fundamentals for Engineers
 * Section:       05
 * Semester:      Fall 2026
 * Assignment:    Homework 2 - Calendar Toolkit
 * Compilation:   g++ -std=c++11 main.cpp -o main
 * Description:   A menu-driven calendar toolkit that validates dates, finds
 *                the day of the week for any date from 1900 through 2100,
 *                counts the days between two dates, and runs a seeded
 *                weekday quiz.
 */

#include <iostream>
#include <cstdlib>   // rand, srand
#include <cassert>   // assert

// ---------------------------------------------------------------------
// Types and global named constants — do not modify
// ---------------------------------------------------------------------
enum class Weekday { Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday };

const int MIN_YEAR = 1900;   // earliest year the toolkit supports
const int MAX_YEAR = 2100;   // latest year the toolkit supports

// ---------------------------------------------------------------------
// Function declarations — do not modify these interfaces.
// The full contract of each function is in the TODO comment at its
// definition below main(). You may add your own helper functions.
// ---------------------------------------------------------------------
bool isLeapYear(int year);
int daysInMonth(int month, int year);
bool isValidDate(int day, int month, int year);
int daysSince1900(int day, int month, int year);
Weekday dayOfWeek(int day, int month, int year);
void printWeekdayName(Weekday weekday, bool abbreviated = false);
void printDate(int day, int month, int year);
int daysBetween(int day1, int month1, int year1, int day2, int month2, int year2);
int randomInRange(int low, int high);
void randomDate(int& day, int& month, int& year, int minYear, int maxYear);

// ---------------------------------------------------------------------
// main() — provided verbatim from the assignment. Do NOT modify it.
// ---------------------------------------------------------------------
int main()
{
    int choice = 0;

    std::cout << "=== EECE 2140 Calendar Toolkit ===" << std::endl;

    do
    {
        std::cout << std::endl
                  << "1) Day of the week for a date" << std::endl
                  << "2) Days between two dates" << std::endl
                  << "3) Weekday quiz" << std::endl
                  << "4) Exit" << std::endl
                  << "Enter your choice: ";

        if (!(std::cin >> choice))
        {
            choice = 4;   // end of input (or unreadable input) acts as Exit
        }

        switch (choice)
        {
            case 1:
            {
                int day = 0, month = 0, year = 0;
                std::cout << "Enter a date (day month year): ";
                std::cin >> day >> month >> year;
                if (!isValidDate(day, month, year))
                {
                    std::cout << "Invalid date." << std::endl;
                    break;
                }
                printDate(day, month, year);
                std::cout << " is a ";
                printWeekdayName(dayOfWeek(day, month, year));
                std::cout << "." << std::endl;
                break;
            }
            case 2:
            {
                int day1 = 0, month1 = 0, year1 = 0;
                int day2 = 0, month2 = 0, year2 = 0;
                std::cout << "Enter the first date (day month year): ";
                std::cin >> day1 >> month1 >> year1;
                std::cout << "Enter the second date (day month year): ";
                std::cin >> day2 >> month2 >> year2;
                if (!isValidDate(day1, month1, year1) || !isValidDate(day2, month2, year2))
                {
                    std::cout << "Invalid date." << std::endl;
                    break;
                }

                std::cout << "From ";
                printWeekdayName(dayOfWeek(day1, month1, year1), true);
                std::cout << " ";
                printDate(day1, month1, year1);
                std::cout << " to ";
                printWeekdayName(dayOfWeek(day2, month2, year2), true);
                std::cout << " ";
                printDate(day2, month2, year2);
                int difference = daysBetween(day1, month1, year1, day2, month2, year2);
                std::cout << ": " << difference
                          << ((difference == 1 || difference == -1) ? " day" : " days") << std::endl;
                break;
            }
            case 3:
            {
                unsigned int seed = 0;
                int numQuestions = 0, correct = 0;
                std::cout << "Random seed: ";
                std::cin >> seed;
                std::cout << "Number of questions: ";
                std::cin >> numQuestions;
                if (numQuestions < 1)
                {
                    std::cout << "Number of questions must be at least 1." << std::endl;
                    break;
                }

                std::srand(seed);   // seed ONCE, before any random numbers are drawn
                for (int question = 1; question <= numQuestions; ++question)
                {
                    int day = 0, month = 0, year = 0, guess = -1;
                    randomDate(day, month, year, MIN_YEAR, MAX_YEAR);

                    std::cout << "Question " << question << ": what day of the week was ";
                    printDate(day, month, year);
                    std::cout << "? (0=Sun 1=Mon 2=Tue 3=Wed 4=Thu 5=Fri 6=Sat): ";
                    std::cin >> guess;

                    Weekday answer = dayOfWeek(day, month, year);
                    if (guess == static_cast<int>(answer))
                    {
                        ++correct;
                        std::cout << "Correct!" << std::endl;
                    }
                    else
                    {
                        std::cout << "Not quite -- it was a ";
                        printWeekdayName(answer);
                        std::cout << "." << std::endl;
                    }
                }
                std::cout << "Quiz score: " << correct << " of " << numQuestions
                          << "." << std::endl;
                break;
            }
            case 4:
                std::cout << "Goodbye." << std::endl;
                break;
            default:
                std::cout << "Invalid choice." << std::endl;
        }
    } while (choice != 4);

    return 0;
}

// =====================================================================
// Function definitions — complete each TODO.
// Each body below is a placeholder that lets the template compile;
// replace it with your own implementation.
// =====================================================================

// TODO: isLeapYear
//   Parameter: year - a year in the Gregorian calendar.
//   Returns:   true if year is a leap year and false otherwise. A year is
//              a leap year when it is divisible by 4, except that a year
//              divisible by 100 is a leap year only if it is also
//              divisible by 400 (2000 and 2024 are leap years; 1900 and
//              2100 are not).
bool isLeapYear(int year)
{
    if (year % 4 == 0) // if statement if year is divisible by 4 is true
    {
        if (year % 100 == 0) // if state if year is divisible by 100 is true
        {
            if (year % 400 == 0) // if ststament is year is divisible by 400 is true
            {
                return true; // if year is divisible by 400 and 100 it is a leap year so its true
            }
            else
            {
                return false; // if divisible by 100 but not 400 then it is not a leap year so false
            }
        }
        else 
        {
            return true; // if year is divisible by 4 but not by 100 it is still a leap year
        }
    }
    else
    {
        return false; // if year is not divisible by 4 it is not a leap year so false
    }
}

// TODO: daysInMonth
//   Parameters:   month - a month number (1 = January ... 12 = December);
//                 year - the year the month belongs to.
//   Precondition: 1 <= month <= 12. Enforce this precondition with assert.
//   Returns:      the number of days in that month of that year (28 or 29
//                 for February, depending on whether year is a leap year).
int daysInMonth(int month, int year)
{
  assert(1 <= month && month <= 12); // asserting that month is valid if its between 1 and 12
  switch (month) // establishing month cases
  {
    case 2: // february case
        if (isLeapYear(year)) // if statement for if year is a leap year
        {
            return 29; // on a leap year the month of february will have 29 days
        }
        else
        {
            return 28; // on a non-leap year the month of february will have 28 days
        }
    case 4: // case for april
    case 6: // case for june
    case 9: // case for september
    case 11: // case for november
        return 30; // the above months will have 30 days in the month
    default: // default for case for all other months
        return 31;  // all other months will have 31 days in the month
  }
}

// TODO: isValidDate
//   Parameters: day, month, year - a candidate date (any int values).
//   Returns:    true if MIN_YEAR <= year <= MAX_YEAR, 1 <= month <= 12,
//               and 1 <= day <= the number of days in that month of that
//               year; false otherwise. Must not violate the precondition
//               of any function it calls, for ANY input values.
//   Constraint: use daysInMonth for the number of days in the month.
bool isValidDate(int day, int month, int year)
{
   if (year < MIN_YEAR || year > MAX_YEAR) // if statement for if the the year is not within the valid range
   {
        return false; // if year is not within the valid range it is not a valid date
   } 
   if (month < 1 || month > 12)
   {
        return false; // if month is not within the valid range it is not a valid date
   }
   if (day < 1 || day > daysInMonth(month, year))
   {
        return false; // if day is not within the valid range it is not a valid date
   }
   return true; // if year month and day are in the valid range it is a valid date
}

// TODO: daysSince1900
//   Parameters:   day, month, year - a date.
//   Precondition: isValidDate(day, month, year). Enforce this with assert.
//   Returns:      the number of days from 1 January 1900 to the given date
//                 (0 for 1 January 1900, 1 for 2 January 1900, 31 for
//                 1 February 1900, and so on).
int daysSince1900(int day, int month, int year)
{
    assert(isValidDate(day, month, year)); // asserting that the date is valid
    
    int daycount = 0; // declaring varibale "daycount" to store number of days
    
    for (int y = MIN_YEAR; y < year; ++y) // for loop to add days to the daycount starting from minimum year
    {
        if (isLeapYear(y)) // if statement for if the year is a leap year
        {
            daycount += 366; // adding 366 days for a leap year
        }
        else
        {
            daycount += 365; // adding 365 days for a non-leap year
        }
    }
    
    for (int m = 1; m < month; ++m) // for loop to add days to the daycount for each month before the given month
    {
        daycount += daysInMonth(m, year); // adding days for each month before the given month
    }

    daycount += day - 1; // adding days for given month - 1 to account for starting the count from day 1, not 0

    return daycount; // returning the total number of days since January 1st 1900
}
          
// TODO: dayOfWeek
//   Parameters:   day, month, year - a date.
//   Precondition: isValidDate(day, month, year). Enforce this with assert.
//   Returns:      the Weekday on which the date falls. (1 January 1900 was
//                 a Monday.)
//   Constraint:   use daysSince1900.
Weekday dayOfWeek(int day, int month, int year)
{
    assert(isValidDate(day, month, year)); // asserting that the date is valid
    int weekdaynumber = (1 + daysSince1900(day, month, year)) % 7; // calculating the day of the week based on days since 1900 and its divisibility by 7 
    //adding 1 to dayssince1900 to account for January 1st 1900 being a monday which = 1 in enum
    return static_cast<Weekday>(weekdaynumber); // returning what day of the week it is based on the calculated number
}

// TODO: printWeekdayName
//   Parameters: weekday - any Weekday value;
//               abbreviated - selects the form of the name (default false).
//   Behavior:   prints the weekday's name to std::cout: the full name
//               (Sunday, Monday, Tuesday, Wednesday, Thursday, Friday,
//               Saturday) when abbreviated is false, or the three-letter
//               form (Sun, Mon, Tue, Wed, Thu, Fri, Sat) when it is true.
//               No spaces and no newline before or after the name.
//   Returns:    nothing.
void printWeekdayName(Weekday weekday, bool abbreviated)
{
    switch (weekday) // switch statement for each day of the week
    {
        case Weekday::Sunday: // case for sunday
            std::cout << (abbreviated ? "Sun" : "Sunday"); // printing Sun or Sunday based on the abbreviated parameter
            break;
        case Weekday::Monday: // case for monday
            std::cout << (abbreviated ? "Mon" : "Monday"); // printing Mon or Monday based on the abbreviated parameter
            break;
        case Weekday::Tuesday: // case for tuesday
            std::cout << (abbreviated ? "Tue" : "Tuesday") ; // printing Tue or Tuesday based on the abbreviated parameter
            break;
        case Weekday::Wednesday: // case for wednesday
            std::cout << (abbreviated ? "Wed" : "Wednesday"); // printing Wed or Wednesday based on the abbreviated parameter
            break;
        case Weekday::Thursday: // case for thursday
            std::cout << (abbreviated ? "Thu" : "Thursday"); // printing Thu or Thursday based on the abbreviated parameter
            break;
        case Weekday::Friday: // case for friday
            std::cout << (abbreviated ? "Fri" : "Friday"); // printing Fri or Friday based on the abbreviated parameter
            break;
        case Weekday::Saturday: // case for saturday
            std::cout << (abbreviated ? "Sat" : "Saturday"); // printing Sat or Saturday based on the abbreviated parameter
            break;  
    }
}

// TODO: printDate
//   Parameters:   day, month, year - a date.
//   Precondition: isValidDate(day, month, year).
//   Behavior:     prints the date to std::cout in the form YYYY-MM-DD, with
//                 the month and the day always printed as two digits
//                 (for example, 2026-09-05). No spaces and no newline.
//   Returns:      nothing.
void printDate(int day, int month, int year)
{
    std::cout << year << "-"; // printing the year and a space

    if (month < 10) // if statement is month is less than 10
    {
        std::cout << 0; // print a zero if the month is less than 10
    }
    std::cout << month << "-"; // if not then print the month and a space
    
    if (day < 10) // if statement is day is less than 10
    {
        std::cout << 0; // print a zero if the day is less than 10
    }
    std::cout << day; // printing the day
}

// TODO: daysBetween
//   Parameters:   day1, month1, year1 - the first date;
//                 day2, month2, year2 - the second date.
//   Precondition: both dates are valid.
//   Returns:      the number of days from the first date to the second:
//                 positive when the second date is later, negative when it
//                 is earlier, and 0 when the dates are the same.
//   Constraint:   use daysSince1900.
int daysBetween(int day1, int month1, int year1, int day2, int month2, int year2)
{
    return daysSince1900(day2, month2, year2) - daysSince1900(day1, month1, year1); // returning the difference between two given dates
}

// TODO: randomInRange
//   Parameters:   low, high - the bounds of the range.
//   Precondition: low <= high and (high - low) <= RAND_MAX.
//   Returns:      a pseudorandom integer between low and high, inclusive,
//                 obtained from rand(). Every value in the range must be
//                 possible.
//   Constraint:   do not call srand in this function.
int randomInRange(int low, int high)
{
    long long range = static_cast<long long>(high) - low + 1; // calculating the range of possible values
    // long long used for range to handle large differences
    // static_cast used to convert the result of rand() % range to an int
    return low + static_cast<int>(rand() % range); // returning a random value within the range
}

// TODO: randomDate
//   Parameters:    day, month, year - output parameters (call-by-reference);
//                  minYear, maxYear - the range of years to draw from.
//   Precondition:  MIN_YEAR <= minYear <= maxYear <= MAX_YEAR; the random
//                  number generator has already been seeded by main().
//   Postcondition: day, month, and year hold a pseudorandom valid date
//                  with minYear <= year <= maxYear, drawn in exactly this
//                  order, each by its own call to randomInRange:
//                    1. year  from randomInRange(minYear, maxYear)
//                    2. month from randomInRange(1, 12)
//                    3. day   from randomInRange(1, number of days in that
//                             month of that year)
//                  No other random numbers are drawn.
//   Constraint:   do not call srand in this function.
void randomDate(int& day, int& month, int& year, int minYear, int maxYear)
{
    year = randomInRange(minYear, maxYear); // generating a random year within the range
    month = randomInRange(1, 12); // generating a random month within the range
    day = randomInRange(1, daysInMonth(month, year)); // generating a random day within the range
}
