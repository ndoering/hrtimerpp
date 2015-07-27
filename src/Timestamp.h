/*
 * File:   Timestamp.h
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

#ifndef TIMESTAMP_H
#define	TIMESTAMP_H

#include <time.h>
#include <cmath>

class Timestamp {
public:
    /**
     * \brief Default constructor.
     *
     * Creates a new timestamp with the time from epoch until creation.
     */
    Timestamp();

    /**
     * \brief Creates new Timestamp from existing time.
     *
     * Needs the time given by clock_gettime(). See man 3 clock_gettime.
     * @param timestamp
     */
    Timestamp(const struct timespec timestamp);

    /**
     * \brief Creates a new Timestamp and adds an offset
     *
     * The Timestamp is created with the actual time. The offset is interpreted
     * as seconds and is added to this time.
     * @param offset
     */
    Timestamp(const double offset);

    /**
     * \brief Creates a new Timestamp an adds an offset
     *
     * The Timestamp is created with the actual time. The seconds and
     * nanoseconds are added to this time.
     * @param secondsOffset
     * @param nanosecondsOffset
     */
    Timestamp(const long secondsOffset, const long nanosecondsOffset);

    /**
     * \brief Creates a new Timestamp from another one.
     *
     * This is actually a deep copy, so there are no shared variables.
     * @param orig
     */
    Timestamp(const Timestamp& orig);

    /**
     * \brief Standard destructor.
     */
    virtual ~Timestamp();

    /**
     * \brief Assign a Timestamp object to another.
     *
     * This is actually a deep copy. All variables and therefore the objects
     * stay independent.
     * @param rhs
     * @return
     */
    Timestamp& operator=(const Timestamp& rhs);

    /**
     * \attention No overflow checking.
     * @param rhs
     * @return
     */
    Timestamp& operator+=(const Timestamp& rhs);

    /**
     * \attention No overflow checking.
     * @param rhs
     * @return
     */
    Timestamp& operator-=(const Timestamp& rhs);

    /**
     * \attention No overflow checking.
     * @param rhs
     * @return
     */
    const Timestamp operator+(const Timestamp& rhs) const;

    /**
     * \attention No overflow checking.
     * @param rhs
     * @return
     */
    const Timestamp operator-(const Timestamp& rhs) const;

    /**
     * Checks if the both objects are the same or of the same age, i.e. have the
     * same values for seconds and nanoseconds.
     * @param rhs
     * @return
     */
    bool operator==(const Timestamp& rhs) const;

    /**
     * Checks for inequality of both values.
     * @param rhs
     * @return
     */
    bool operator!=(const Timestamp& rhs) const;

    /**
     * Checks whether this object is newer as the other.
     * @param rhs
     * @return
     */
    bool operator>(const Timestamp& rhs) const;

    /**
     * Checks whether this object is newer or of the same age as the other.
     * @param rhs
     * @return
     */
    bool operator>=(const Timestamp& rhs) const;

    /**
     * Checks whether this object is older as the other.
     * @param rhs
     * @return
     */
    bool operator<(const Timestamp& rhs) const;

    /**
     * Checks whether this object is older or of the same age as the other.
     * @param rhs
     * @return
     */
    bool operator<=(const Timestamp& rhs) const;

    /**
     * Returns the structure holding the time. It is defined in the time.h
     * header file.
     * @return
     */
    struct timespec getTimestamp() const;

    /**
     * Returning only the seconds part of the time.
     * @return
     */
    long getSeconds() const;

    /**
     * Returns only the nanoseconds part of the time.
     * @return
     */
    long getNanoSeconds() const;

    /**
     * Returns the time in seconds as a double.
     *
     * \attention There is a possible loss of accuracy due to the precission of
     * double variables.
     * @return
     */
    double getTime() const;

    /**
     * Sets the time to the given values
     *
     * \attention No overflow checking for the seconds.
     * @param seconds
     * @param nanoseconds
     */
    void set(const long seconds, const long nanoseconds);

    /**
     * Sets the time to the given value. The parameter will be interpreted as
     * seconds
     *
     * \attention No overflow checking for the seconds.
     * @param seconds
     */
    void set(const double seconds);

    /**
     * Sets the seconds part of the time.
     *
     * \attention No overflow checking.
     * @param seconds
     */
    void setSeconds(const long seconds);

    /**
     * Sets the nanoseconds part of the time. Overflow will be returned as
     * seconds. To ensure the correct time, please update the seconds part
     * accordingly.
     *
     * @param nanoseconds
     * @return
     */
    long setNanoSeconds(const long nanoseconds);

    /**
     * Sets the time to the current time.
     */
    void setNow();

private:
    struct timespec mTimestamp;
};

#endif	/* TIMESTAMP_H */
