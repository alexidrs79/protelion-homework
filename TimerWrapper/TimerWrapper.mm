#import "TimerWrapper.h"

#include "timer.h"

// Objective-C++ file that forwards calls to the C++ library.
// No timing logic here, all measurement happens in TimerLib.

@implementation TimerWrapper

+ (int)start {
    return ::start();
}

+ (int)stop {
    return ::stop();
}

@end
