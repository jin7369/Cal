#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
bool isLeapYear(int year);
int is31Days(int month);
int is30Days(int month);
int main(void) {
	time_t unix_time = time(NULL);
	time_t minutes = unix_time / 60;
	time_t hours = minutes / 60;
	time_t days = hours / 24 + 1;
	time_t year = 1970;
	int calMatrix[6][7] = {{}, {}, {}, {}, {}, {}};
	int col = 0;
	int row = 0;
	int calMatrixStartPoint = 0;
	int week = (days + 3) % 7;
	int month = 1;
	int dayThisMonth = 31;
	int weekFirstDayOfThisMonth = 0;
	char weekName[12][3] = {"Su", "Mo", "Tu", "We", "Th", "Fr", "Sa"};
	char monthName[12][10] = {"January", 
		                "February", 
				"March", 
				"April", 
				"May", 
				"June", 
				"July", 
				"August", 
				"September", 
				"October", 
				"November", 
				"December"};
	while (days > 365) {
		days = isLeapYear(year) ? (days - 366) : (days - 365);
		year += 1;
	}
	while (days > 31) {
		if (is31Days(month)) {
			days -= 31;
		}
		else if (is30Days(month)) {
			days -= 30;
		}
		else if (month == 2) {
			days = isLeapYear(year) ? (days - 29) : (days - 28);
		}
		else {
			printf("Error\n");
			return -1;
		}
		month += 1;
	}
	if (is30Days(month)) {
		dayThisMonth = 30;
		days -= 30;
	}
	else if (month == 2) {
		if (isLeapYear(year)) {
			days -= 29;
			dayThisMonth = 29;
		}
		else {
			days -= 28;
			dayThisMonth = 31;
		}
	}
	weekFirstDayOfThisMonth = ((hours / 24) + 5 - days) % 7; 
	for (int i = 0; i < (20 - strlen(monthName[month]) - 4) / 2; i++) {
		printf(" ");
	}
	printf("%s %ld\n", monthName[month - 1], year);
	for (int i = 0; i < 7; i++) {
		printf("%-3s", weekName[i]);
	}
 
	printf("\n");
	col = weekFirstDayOfThisMonth;
	for (int i = 1; i <= dayThisMonth; i++) {
		calMatrix[row][col] = i;
		col++;
		if (col > 6) {
			row++;
			col = 0;
		}
	}
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			if (calMatrix[i][j] == 0) printf("   ");
			else printf("%-3d", calMatrix[i][j]); 
		}
		printf("\n");
	}
}

bool isLeapYear(int year) {
	bool dividedByFour = (year % 4 == 0);
	bool dividedByHundred = (year % 100 == 0);
	bool dividedByFourHundred = (year % 400 == 0);
	return (dividedByFour && !dividedByHundred) || (dividedByFourHundred);

}
int is31Days(int month) {
	return ((month == 1) ||
		(month == 3) ||
		(month == 5) ||
		(month == 7) ||
		(month == 8) ||
		(month == 10) ||
		(month == 12));
}
int is30Days(int month) {
	return ((month == 4) ||
		(month == 6) ||
		(month == 9) ||
		(month == 11));
}
