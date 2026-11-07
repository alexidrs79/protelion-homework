#import <Foundation/Foundation.h>

// Objective-C interface to TimerLib, imported by Swift.
// Kept free of C++ so Swift can read it.

@interface TimerWrapper  : NSObject

+ (int)start;

+ (int)stop;

@end 
