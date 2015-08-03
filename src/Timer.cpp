/*
 * File:   Timer.cpp
 * Author: Nils Döring
 *
 * Created on July 27, 2015, 3:20 PM
 */

/* Copyright (c) 2015, Nils Döring
  All rights reserved.
  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer.

  * Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

  * Neither the name of hrtimerpp nor the names of its
    contributors may be used to endorse or promote products derived from
    this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "Timer.h"

#define THOUSAND    1000.0
#define MILLION     1000000.0
#define BILLION     1000000000.0
/*
 * Create a new Timer object. The Timestamps are set to zero.
 */
Timer::Timer() :
    mStartTime(0.0),
    mStopTime(0.0),
    mIsRunning(false),
    mIsReset(true){
}

/*
 * Create a new object and copy the Timestamps and the current state to this
 * object.
 */
Timer::Timer(const Timer& orig) : Timer() {
    this->mStartTime = orig.mStartTime;
    this->mStopTime = orig.mStopTime;

    this->mIsRunning = orig.mIsRunning;
    this->mIsReset = orig.mIsReset;
}

/*
 * There is nothing to do here.
 */
Timer::~Timer() {
}

/*
 * Assign the values to this object. If the objects are the same, then there is
 * nothing to do.
 */
Timer& Timer::operator=(const Timer& rhs) {
    if(this == &rhs){  // the objects are the same
        return *this;
    }
    this->mStartTime = rhs.mStartTime;
    this->mStopTime = rhs.mStopTime;

    this->mIsRunning = rhs.mIsRunning;
    this->mIsReset = rhs.mIsReset;

    return *this;
}

/*
 * There is no sense in comparing the different start and stop times. Therefore
 * only the duration of both objects is considered. A new Timestamp object is
 * returned containing the sum of the durations.
 */
const Timestamp Timer::operator +(const Timer& rhs) const {
    Timestamp sum = this->getTime();
    sum += rhs.getTime();

    return sum;
}

/*
 * There is no sense in comparing the different start and stop times. Therefore
 * only the duration of both objects is considered. A new Timestamp object is
 * returned containing the difference of the durations.
 */
const Timestamp Timer::operator -(const Timer& rhs) const {
    Timestamp difference = this->getTime();
    difference -= rhs.getTime();

    return difference;
}

/*
 * Checks if the objects are the same. If not, it checks if the difference of
 * the durations is small enough to consider them as equal. This value is
 * arbitrarily chosen. You can set this value with the macro HRTPP_ERROR_MARGIN.
 * The bigger the margin is, the more duration difference are regarded as equal.
 */
bool Timer::operator ==(const Timer& rhs) const {
    if(this == &rhs) {  // the objects are the same
        return true;
    } else {
        double difference = fabs( this->getTimeInSeconds() -
            rhs.getTimeInSeconds() );

        return difference <= HRTPP_ERROR_MARGIN;
    }
}

/*
 * If the objects are not equal, this returns true. It invertes the answer given
 * by the check for equality.
 */
bool Timer::operator !=(const Timer& rhs) const {
    return !(*this == rhs);
}

/*
 * This checks if this object is significantly larger, hence the error margin,
 * as the other object.
 */
bool Timer::operator >(const Timer& rhs) const {
    //has to be bigger than zero
    double difference = this->getTimeInSeconds() - rhs.getTimeInSeconds();

    return (difference > HRTPP_ERROR_MARGIN and difference > 0.0);
}

/*
 * This checks if this object is significantly smaller, hence the error margin,
 * as the other object.
 */
bool Timer::operator <(const Timer& rhs) const {
    // has to be smaller than zero
    double difference = this->getTimeInSeconds() - rhs.getTimeInSeconds();

    return (fabs(difference) > HRTPP_ERROR_MARGIN and difference < 0.0);
}

/*
 * This check returns true, if the object is either significantly larger or of
 * the same size within the margin of error.
 */
bool Timer::operator >=(const Timer& rhs) const {
    return (*this > rhs) or (*this == rhs);
}

/*
 * This check returns true, if the object is either significantly smaller or of
 * the same size within the margin of error.
 */
bool Timer::operator <=(const Timer& rhs) const {
    return (*this < rhs) or (*this == rhs);
}

/*
 * This method checks not only if the objects are the same and if the durations
 * are the same, but also if the starting and the ending times are the same.
 * With this you can check for duplicate objects. Since the Timestamps work
 * with integral types, there is no margin of error necessary.
 */
bool Timer::isEqual(const Timer& rhs) const {
    if(this == &rhs) {  // the objects are the same
        return true;
    }

    if(*this == rhs and  // time range is equal
            this->mStartTime == rhs.mStartTime and  // start dates are equal
            this->mStopTime == rhs.mStopTime) {  // stop dates are equal
        return true;
    } else {
        return false;
    }
}

/*
 * Starts the Timer if has not been run previously and is not running at the
 * moment.
 */
void Timer::start() {
    if(this->mIsReset and !this->mIsRunning) {
        this->mStartTime.setNow();

        this->mIsReset = false;
        this->mIsRunning = true;
    }
}

/*
 * Stops the Timer if two conditions are met. The Timer will not be changed if
 * it hasn't been started or if it is not running currently.
 */
void Timer::stop() {
    if(!this->mIsReset and this->mIsRunning) {
        this->mStopTime.setNow();

        this->mIsRunning = false;
    }
}

/*
 * This resets the Timer. It does not regard the current state. The Timer will
 * be stopped afterwards and the Timestamps are zeroed.
 */
void Timer::reset() {
    this->mStartTime.set(0.0);
    this->mStopTime.set(0.0);

    this->mIsRunning = false;
    this->mIsReset = true;
}

/*
 * Getter for the state of running.
 */
bool Timer::isRunning() const {
    return this->mIsRunning;
}

/*
 * Getter for the reset status.
 */
bool Timer::isReset() const {
    return this->mIsReset;
}

/*
 * Calculates the duration between the start and the stop. If the Timer is
 * currently running, this calculates the duration between the start and the
 * moment you call this method. The Timer will not be stopped by this.
 */
const Timestamp Timer::getTime() const {
    if( this->isRunning() ) {  // the timer is currently running
        return Timestamp() - this->mStartTime;
    }

    Timestamp difference = this->mStopTime - this->mStartTime;

    return difference;
}

/*
 * This returns a double precission variable containing the duration this timer
 * was running. It returns the time as seconds.
 */
double Timer::getTimeInSeconds() const {
    Timestamp difference = this->getTime();

    return difference.getTime();  // this returns the time in seconds
}

/*
 * This returns a double precission variable containing the duration this timer
 * was running. It returns the time as milliseconds.
 */
double Timer::getTimeInMilliSeconds() const {
    Timestamp difference = this->getTime();

    double timeInMilliSeconds = difference.getSeconds() * THOUSAND
        + difference.getNanoSeconds() / MILLION;

    return timeInMilliSeconds;
}

/*
 * This returns a double precission variable containing the duration this timer
 * was running. It returns the time as microseconds.
 */
double Timer::getTimeInMicroSeconds() const {
    Timestamp difference = this->getTime();

    double timeInMicroSeconds = difference.getSeconds() * MILLION
        + difference.getNanoSeconds() / THOUSAND;

    return timeInMicroSeconds;
}

/*
 * This returns a double precission variable containing the duration this timer
 * was running. It returns the time as nanoseconds.
 */
double Timer::getTimeInNanoSeconds() const {
    Timestamp difference = this->getTime();

    double timeInNanoSeconds = difference.getSeconds() * BILLION
        + difference.getNanoSeconds();

    return timeInNanoSeconds;
}

/*
 * This returns a double precission variable containing the frequency, which
 * results from the time the Timer was running. The unit is Hertz(Hz). If the
 * Timer was not run, the frequency returned will be 0.
 */
double Timer::getFrequency() const {
    double time = this->getTimeInSeconds();
    double frequency;

    if(time != 0.0) {
        frequency = 1.0 / time;
    } else {
        frequency = 0.0;
    }

    return frequency;
}
