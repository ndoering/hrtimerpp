/*
 * File:   Timestamp.cpp
 * Author: Nils Döring
 *
 * Created on July 26, 2015, 11:50 AM
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

#include "Timestamp.h"

#define BILLION 1000000000.0

/*
 * Create a new Timestamp and seed it with the current time.
 */
Timestamp::Timestamp() {
    clock_gettime(CLOCK_REALTIME, &this->mTimestamp);
}

/*
 * Create a new Timestamp and seed it with the given time.
 */
Timestamp::Timestamp(const timespec timestamp) {
    this->set(timestamp.tv_sec, timestamp.tv_nsec);
}

/*
 * Create a new Timestamp and seed it with the given time.
 */
Timestamp::Timestamp(const double offset) : Timestamp() {
    this->set(offset);
}

/*
 * Create a new Timestamp and seed it with the given time.
 */
Timestamp::Timestamp(const long secondsOffset, const long nanosecondsOffset) :
    Timestamp() {
    this->set(secondsOffset, nanosecondsOffset);
}

/*
 * Copy the given Timestamp. This is a deep copy.
 */
Timestamp::Timestamp(const Timestamp& orig) {
    this->mTimestamp = orig.mTimestamp;
}

/*
 * Remove the object. Very empty since the time is saved in a stack object,
 * which will be deleted automatically.
 */
Timestamp::~Timestamp() {
}

/*
 * Get the structure saving the time. It is defined in the time.h header file.
 */
struct timespec Timestamp::getTimestamp() const{
    return this->mTimestamp;
}

/*
 * Get the number of seconds as an signed long integer.
 */
long Timestamp::getSeconds() const {
    return this->mTimestamp.tv_sec;
}

/*
 * Get the number of nanoseconds as an signed long integer.
 */
long Timestamp::getNanoSeconds() const {
    return this->mTimestamp.tv_nsec;
}

/*
 * Set the number of seconds.
 */
void Timestamp::setSeconds(const long seconds) {
    this->mTimestamp.tv_sec = seconds;
}

/*
 * Set the number of seconds. If there is an overflow, i.e. more than one
 * billion nanoseconds, the surplus will be saved in tv_nsec and the number of
 * seconds will be returned.
 */
long Timestamp::setNanoSeconds(const long nanoseconds) {
    long seconds = lround( floor(nanoseconds / BILLION) );

    this->mTimestamp.tv_nsec = nanoseconds - (seconds * BILLION);

    return seconds;
}

/*
 * Sets the time accordng to the parameter. The overflow of the nanoseconds will
 * be added to seconds. Please regard, an overflow of the seconds part will not
 * be handled.
 */
void Timestamp::set(const long seconds, const long nanoseconds) {
    long secondsOverflow = this->setNanoSeconds(nanoseconds);

    this->setSeconds(seconds + secondsOverflow);
}

/*
 * Converts the double to two integers and sets the time.
 */
void Timestamp::set(const double seconds) {
    double fractpart, intpart;
    long sec, nanosec;

    // deviding the double in the integer part and the fractional part
    fractpart = modf(seconds, &intpart);

    // convert both parts to long variables
    sec = lround(intpart);
    nanosec = lround(fractpart * BILLION);

    // set time
    this->set(sec, nanosec);
}

/*
 * Assign a Timestamp object to another. This is actually a deep copy, since the
 * time stored is copied to the left-hand-side object. Both objects stay
 * independent.
 */
Timestamp& Timestamp::operator =(const Timestamp& rhs) {
    if(this == &rhs) {  // objects are the same
        return *this;
    }

    // set time to values of the given Timestamp
    this->set(rhs.getSeconds(), rhs.getNanoSeconds());

    return *this;
}

/*
 * Adds the given Timestamp to this one.
 */
Timestamp& Timestamp::operator +=(const Timestamp& rhs) {
    this->set(this->getSeconds() + rhs.getSeconds(),
            this->getNanoSeconds() + rhs.getNanoSeconds());

    return *this;
}

/*
 * Subtracts the given Timestamp from this one.
 */
Timestamp& Timestamp::operator -=(const Timestamp& rhs) {
    this->set(this->getSeconds() - rhs.getSeconds(),
            this->getNanoSeconds() - rhs.getNanoSeconds());

    return *this;
}

/*
 * Creates a new Timestamp with the time value from this object and adds the
 * value from the other to it. The original objects are not changed.
 */
Timestamp Timestamp::operator +(const Timestamp& rhs) const {
    Timestamp newTimestamp = *this;

    newTimestamp += rhs;

    return newTimestamp;
}

/*
 * Creates a new Timestamp with the time value from this object and subtracts
 * the value from the other to it. The original objects are not changed.
 */
Timestamp Timestamp::operator -(const Timestamp& rhs) const {
    Timestamp newTimestamp = *this;

    newTimestamp -= rhs;

    return newTimestamp;
}

/*
 * Checks whether both objects are at the same memory location and if not, if
 * they hold the same values.
 */
bool Timestamp::operator ==(const Timestamp& rhs) const {
    if(this == &rhs){  // both objects have the same address
        return true;
    }

    // check for the time values
    if(this->getSeconds() == rhs.getSeconds() and
            this->getNanoSeconds() == rhs.getNanoSeconds()) {
        return true;
    } else {
        return false;
    }
}

/*
 * Checks whether they are the same and returns the opposite result.
 */
bool Timestamp::operator !=(const Timestamp& rhs) const {
    return !(*this == rhs);
}

/*
 * Checks whether this object is newer as the other or not. Newer means a higher
 * value for seconds and/or nanoseconds.
 */
bool Timestamp::operator >(const Timestamp& rhs) const {
    if(this->getSeconds() > rhs.getSeconds()) {
        return true;
    } else if (this->getSeconds() == rhs.getSeconds() &&
            this->getNanoSeconds() > rhs.getNanoSeconds()) {
        return true;
    } else {
        return false;
    }
}

/*
 * Checks if this object is older, i.e. smaller, than the other.
 */
bool Timestamp::operator <(const Timestamp& rhs) const {
    return rhs > *this;
}

/*
 * Checks if this object is newer or of the same age as the other.
 */
bool Timestamp::operator >=(const Timestamp& rhs) const {
    return (*this == rhs) or (*this > rhs);
}

/*
 * Checks if this object is older or of the same age as the other.
 */
bool Timestamp::operator <=(const Timestamp& rhs) const {
    return (*this == rhs) or (*this < rhs);
}

/*
 * Sets the time values to the current time.
 */
void Timestamp::setNow() {
    clock_gettime(CLOCK_REALTIME, &this->mTimestamp);
}
