/*
 * File:   Timer.h
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

#ifndef TIMER_H
#define	TIMER_H

#include "Timestamp.h"

#ifndef HRTPP_ERROR_MARGIN
#define HRTPP_ERROR_MARGIN 10e-08
#endif

/**
 * \brief This class implements a simple start/stop timer.
 *
 * A Timer combines two Timestamps, one for the start time and one for the stop
 * time.
 *
 * \attention This class is \b NOT reentrant and \b NOT thread-safe.
 */
class Timer {
public:
    /**
     * \brief Default constructor.
     *
     * Creates two Timestamps which are set to zero.
     */
    Timer();

    /**
     * \brief Copy constructor.
     *
     * Creates an exact replica of the original Timer. Since all variables are
     * based on the stack, the both objects are fully independent.
     * @param orig
     */
    Timer(const Timer& orig);

    /**
     * \brief Standard destructor.
     *
     * Since all variables are on the stack, nothing is done here.
     */
    virtual ~Timer();

    /**
     * \brief Start the timer.
     *
     * The Timer can only be started if it is not already started and has not
     * been run allready.
     *
     * \attention This method fails silently. The user has to check if this
     * Timer is able to be started.
     */
    void start();

    /**
     * \brief Stop a running timer.
     *
     * The Timer will be stopped if it was running.
     *
     * \attention This method fails silently. The user has to check if the
     * timer is running and is able to be stopped.
     */
    void stop();

    /**
     * \brief Reset the timer.
     *
     * This method resets the timer. It will reset every timer, whether is
     * running or not.
     */
    void reset();

    /**
     * \brief Return if the timer is running.
     */
    bool isRunning() const;


    /**
     * \brief Return if the timer is reset.
     */
    bool isReset() const;

    /**
     * \brief Returns the duration.
     *
     * This method returns a Timestamp object holding the duration of the timer.
     * If the timer is running, this means the time elapsed from the start of
     * this Timer upto now. The Timer keeps on running.
     *
     * \attention This does not stop the Timer.
     */
    const Timestamp getTime() const;

    /**
     * \brief Returns the elapsed time in seconds
     *
     * \attention Due to the limited precission of a double variable, this can
     * be inaccurate.
     */
    double getTimeInSeconds() const;

    /**
     * \brief Returns the elapsed time in milliseconds
     *
     * \attention Due to the limited precission of a double variable, this can
     * be inaccurate.
     */
    double getTimeInMilliSeconds() const;

    /**
     * \brief Returns the elapsed time in microseconds
     *
     * \attention Due to the limited precission of a double variable, this can
     * be inaccurate.
     */
    double getTimeInMicroSeconds() const;

    /**
     * \brief Returns the elapsed time in nanoseconds
     *
     * \attention Due to the limited precission of a double variable, this can
     * be inaccurate.
     */
    double getTimeInNanoSeconds() const;

    /**
     * \brief Assign the values of the other Timer to this object
     *
     * This method assigns the values of the Timestamps to this Timer. Also the
     * state of running. Afterwards both Timer are completely independent, since
     * all the variables are hold on the stack.
     * @param rhs
     */
    Timer& operator=(const Timer& rhs);

    /**
     * \brief Returns the sum of durations.
     *
     * This method adds the durations of both Timer objects and returns it as an
     * Timestamp.
     * @param rhs
     */
    const Timestamp operator+(const Timer& rhs) const;

    /**
     * \brief Returns the difference of durations.
     *
     * This method subtracts the durations of both Timer objects and returns it
     * as an Timestamp.
     * @param rhs
     */
    const Timestamp operator-(const Timer& rhs) const;

    /**
     * This operator is deleted since it makes no sense.
     *
     * Since the both Timers might have different start and stop times, it is
     * not meaningful to add the second to the first one.
     * @param rhs
     */
    Timer operator+=(const Timer& rhs) = delete;

    /**
     * This operator is deleted since it makes no sense.
     *
     * Since the both Timers might have different start and stop times, it is
     * not meaningful to subtract the second to the first one.
     * @param rhs
     */
    Timer operator-=(const Timer& rhs) = delete;

    /**
     * \brief Checks for equality of duration
     *
     * This method first checks if the objects are the same. If not, the
     * duration of both Timers are checked whether they differ significantly or
     * not. Since double precission variables tend to be inaccurate in the last
     * digits of its fractional part. Therefore they are not checked for
     * equality but if they differ in the margin of error. I assume an error
     * margin of 10e-08 is suitable. You can adjust this with the macro
     * HRTPP_ERROR_MARGIN
     * @param rhs
     */
    bool operator==(const Timer& rhs) const;

    /**
     * \brief Checks for inequality of duration
     *
     * This is the opposite of the check for equality.
     * @param rhs
     */
    bool operator!=(const Timer& rhs) const;

    /**
     * \brief Checks whether this Timer has a bigger or equal duration as the
     * other.
     * @param rhs
     */
    bool operator>=(const Timer& rhs) const;

    /**
     * \brief Checks whether this Timer has a bigger duration as the other.
     * @param rhs
     */
    bool operator>(const Timer& rhs) const;

    /**
     * \brief Checks whether this Timer has a smaller or equal duration as the
     * other.
     * @param rhs
     */
    bool operator<=(const Timer& rhs) const;

    /**
     * \brief Checks whether this Timer has a bigger duration as the other.
     * @param rhs
     */
    bool operator<(const Timer& rhs) const;

    /**
     * \brief Checks for the equality of the duration and start ans stop times.
     *
     * While the ==-operator only checks the duration, this method also checks
     * if the start time and the stop time is the same.
     * @param rhs
     */
    bool isEqual(const Timer& rhs) const;

    /**
     * \brief Returns the frequency resulting from the time measured.
     *
     * This returns 1/s. Therefore its unit is Hertz(Hz). Returns 0, if there
     * is no time measured.
     */
    double getFrequency() const;

private:
    Timestamp mStartTime, mStopTime;

    bool mIsRunning;
    bool mIsReset;

};

#endif	/* TIMER_H */

