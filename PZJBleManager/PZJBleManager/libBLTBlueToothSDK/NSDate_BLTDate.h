//
//  NSDate_Omesoft.h
//  
//
//  Created by sincan on 11-8-2.
//  Copyright 2011年 Omesoft. All rights reserved.
//

#import <Foundation/Foundation.h>

struct BLTDateInformation {
	int day;
	int month;
	int year;
	int weekday;
	int minute;
	int hour;
	int second;
	 
};
typedef struct BLTDateInformation BLTDateInformation;

typedef enum : NSInteger {
    BLTWeekStateSunday = 1,
    BLTWeekStateMonday,
    BLTWeekStateTuesday,
    BLTWeekStateWednesday,
    BLTWeekStateThursday,
    BLTWeekStateFriday,
    BLTWeekStateSaturday
} BLTWeekState;

@interface NSDate (omesoft)
- (NSInteger)daysBetweenDate:(NSDate*)date;
- (NSInteger)minBetweenDate:(NSDate*)date;
- (NSInteger)monthBetweenDate:(NSDate *)date;
- (NSInteger)monthForTodayBetweenDate:(NSDate *)date;
- (NSInteger)yearBetweenDate:(NSDate *)date;
- (NSInteger)birthdayAge;
- (NSString *)ageDetailInfo;//N年N月N日
- (BLTDateInformation)dateInformation;
- (BLTDateInformation)dateInformationWithTimeZone:(NSTimeZone*)tz;
+ (NSDate*)dateFromBLTDateInformation:(BLTDateInformation)info timeZone:(NSTimeZone*)tz;

- (NSDate*)UTCDate;
- (NSDate*)SystemDate;
- (NSUInteger)year;
- (NSDate*)addHours:(NSInteger)hours;
- (NSDate *)reduceMinWithMin:(int)min;
- (NSDate *)startOfHour;
- (NSDate*)startOfHourWithTimeZone:(NSTimeZone *)tz;
- (NSDate*)startOfDay;
- (NSDate*)startOfDayWithTimeZone:(NSTimeZone *)tz;
- (NSDate*)startOfMonth;
- (NSDate*)startOfMonthWithTimeZone:(NSTimeZone *)tz;
- (NSDate*)startOfYear;
- (NSDate*)startOfYearWithTimeZone:(NSTimeZone *)tz;
- (NSDate*)tomorrow;
- (NSDate*)tomorrowWithTimeZone:(NSTimeZone *)tz;
- (NSDate*)nextMonth;
- (NSDate*)nextMonthWithNum:(int)num;
- (NSDate*)nextMonthWithTimeZone:(NSTimeZone *)tz;
- (NSDate*)nextYear;
- (NSDate*)nextYearWithNum:(int)num;
- (NSDate*)nextYearWithTimeZone:(NSTimeZone *)tz;
- (NSDate*)yesterday;
- (NSDate*)yesterdayWithTimeZone:(NSTimeZone *)tz;
- (NSDate*)previousDays:(NSUInteger)days;
- (NSDate*)laterDays:(NSUInteger)days;
- (NSDate*)weekBefore;
- (NSDate*)weekBeforeWithTimeZone:(NSTimeZone *)tz;
- (NSDate*)previousMonth;
- (NSDate*)previousMonthWithTimeZone:(NSTimeZone *)tz;
- (NSDate*)previousMonthWithNum:(int)num;
- (NSDate*)previousYear;
- (NSDate*)previousYearWithTimeZone:(NSTimeZone *)tz;
- (NSDate*)previousYearWithNum:(int)num;
- (BLTWeekState)weekday;
- (BLTWeekState)weekdayWithTimeZone:(NSTimeZone *)tz;
- (NSDate*)changeDayInDate:(int)day;
+ (NSDate*)stringToDateWithStr:(NSString*)str dateFormate:(NSString*)dateFormat;//timezone @"UTC"
- (int)dayInDateWithTimeZone:(NSTimeZone *)tz;
- (int)dayInDate;
- (int)hourInDate;
- (int)monthInDate;
- (int)yearInDate;
- (int)minInDate;
- (int)secondInDate;
- (BOOL)isToday;
- (NSString*)dateToStringWithDateFormate:(NSString*)dateForamt;
- (NSString *)dateToStringWithDateFormate:(NSString*)dateForamt timeZone:(NSTimeZone *)timezone locale:(NSLocale *)locale;
- (NSDate *)dateWithDateFromate:(NSString *)dateFormate;
- (NSString *)dateToLocalStringWithDateFormate:(NSString *)dateForamt;
- (NSDate *)dateWithDateFromate:(NSString *)dateFormate timeZone:(NSTimeZone *)timezone locale:(NSLocale *)locale;

- (NSString *)ageInDate:(NSDate*)endData;
- (NSString *)ageDetailInfoToDate:(NSDate *)endData;

+ (NSDate *)dateByAddingTimeIntervalSince2000Year:(NSInteger)interval;
@end
