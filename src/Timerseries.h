/*
 * File:   Timerseries.h
 * Author: Nils Döring
 *
 * Created on July 30, 2015, 10:22 AM
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


#ifndef TIMERSERIES_H
#define	TIMERSERIES_H

#include <list>
#include "Timer.h"
#include "Timestamp.h"

/**
 * \brief This class stores series of Timer.
 *
 * This class facilitates the use of large numbers of timers. Especially those
 * created in loop and added automatically to a Timerseries.
 *
 * \attention This class is \b NOT reentrant and \b NOT thread-safe.
 */
class Timerseries {
public:

    /**
     * \brief Default constructor.
     *
     * Creates a new Timerseries with an empty container for Timer.
     */
    Timerseries();

    /**
     * \brief Copy constructor.
     *
     * Creates a new Timerseries object and copies all timers contained in the
     * original Timerseries. Both objects are independend, since all Timer are
     * copied.
     *
     * \attention This could take a while and a lot of space since all the
     * Timers are copied.
     * @param orig
     */
    Timerseries(const Timerseries& orig);

    /**
     * \brief Standard destructor.
     *
     * \attention This destroys all Timers contained in the Timerseries. This
     * can render pointer invalid.
     */
    virtual ~Timerseries();

    /**
     * \brief Assigns another Timerseries to this one.
     *
     * This is actually a deep copy. Both Timerseries are independend, since all
     * Timers are copied.
     * @param rhs
     */
    Timerseries& operator=(const Timerseries& rhs);

    /**
     * \brief Assigns all the timers from the rhs Timerseries to this one.
     *
     * This is also a deep copy. All Timers are copied. Therefore the
     * Timerseries stay independent
     * @param rhs
     */
    Timerseries& operator+=(const Timerseries& rhs);

    /**
     * \brief Adds the given Timer to this series.
     *
     * The Timer will not be copied. If the series is destroyed, it will destroy
     * this timer as well.
     *
     * @param timerToAdd
     */
    Timerseries& operator+=(Timer* timerToAdd);

    /**
     * \brief This removes all the Timer from this series that are also in the
     * other Timerseries.
     *
     * \attention At the moment, this is taking O(n^2) time. This could take
     * very long. As this is the basis for the most comparisons, they will also
     * take very long.
     * @param rhs
     */
    Timerseries& operator-=(const Timerseries& rhs);

    /**
     * \brief Remove the given Timer from this series.
     *
     * @param timerToRemove
     */
    Timerseries& operator-=(const Timer& timerToRemove);

    /**
     * \brief Adds both series together an returns the sum of both.
     *
     * @param rhs
     */
    const Timerseries operator+(const Timerseries& rhs);

    /**
     * \brief This adds a single timer to the a copy of this series and returns
     * the copy.
     *
     * The Timer will not be copied. If the series is destroyed, it will destroy
     * this timer as well.
     *
     * @param timerToAdd
     */
    const Timerseries operator+(Timer* timerToAdd);

    /**
     * \brief Subtracts the rhs series from this series and returns the
     * remaining Timer as a new series.
     *
     * \attention As described for Timerseries::operator-=(), this could take
     * very long( O(n^2) ).
     * @param rhs
     */
    const Timerseries operator-(const Timerseries& rhs);

    /**
     * \brief This subtracts the timer from the timeseries and returns the
     * remaining Timer a new series.
     * @param timerToRemove
     */
    const Timerseries operator-(const Timer& timerToRemove);

    /**
     * \brief Checks if both series consist of equal Timer.
     *
     * \attention As described for Timerseries::operator-=(), this could take
     * very long( O(n^2) ).
     * @param rhs
     */
    bool operator==(const Timerseries& rhs) const;

    /**
     * \brief Checks if both series have a different set of Timer.
     *
     * \attention As described for Timerseries::operator-=(), this could take
     * very long( O(n^2) ).
     * @param rhs
     */
    bool operator!=(const Timerseries& rhs) const;

    /**
     * \brief Checks if rhs is a subset of this series.
     *
     * \attention As described for Timerseries::operator-=(), this could take
     * very long( O(n^2) ).
     * @param rhs
     */
    bool operator>=(const Timerseries& rhs) const;

    /**
     * \brief Checks if this series is a subset of rhs.
     *
     * \attention As described for Timerseries::operator-=(), this could take
     * very long( O(n^2) ).
     * @param rhs
     */
    bool operator<=(const Timerseries& rhs) const;

    /**
     * \brief Checks whether rhs is a true subset of this series.
     *
     * This means (this >= rhs) && (this != rhs)
     *
     * \attention As described for Timerseries::operator-=(), this could take
     * very long( O(n^2) ).
     * @param rhs
     */
    bool operator>(const Timerseries& rhs) const;

    /**
     * \brief Checks whether this series is a true subset of rhs.
     *
     * This means (this <= rhs) && (this != rhs)
     *
     * \attention As described for Timerseries::operator-=(), this could take
     * very long( O(n^2) ).
     * @param rhs
     */
    bool operator<(const Timerseries& rhs) const;

    /**
     * \brief Append the Timer to the Timerseries.
     *
     * This adds the given Timer to the end of the Timerseries.
     *
     * \\attention This method is deprecated. Use operator+ and operator+=
     * instead.
     * @param newTimer
     */
#ifndef NO_CXX14
    [[deprecated("Replaced by operator+ and operator+=")]]
#endif
    void addTimer(Timer* newTimer);

    /**
     * \brief Create a new Timer in the Timerseries.
     *
     * This creates a new Timer object, appends it to the Timerseries and
     * returns a pointer to it.
     */
    Timer* newTimer();

    /**
     * \brief Creates a new Timer and starts it.
     *
     * This creates a new timer, appends it to the Timerseries and starts it.
     * The time measured with this timer does not include the time necessary to
     * append the timer to the container. A pointer to this object is returned,
     * after it has been started.
     */
    Timer* newStartedTimer();

    /**
     * \brief Stops all the timers in the Timerseries.
     *
     * This stops sequentially all the timers contained in the series. The
     * behaviour of stopping a Timer is described in Timer::stop(). This method
     * ensures that all timers are ended.
     */
    void stopAllTimer() const;

    /**
     * \brief Removes the given Timer from the Timeseries.
     *
     * This removes the given Timer from the Timerseries without deleting it.
     * @param toDelete
     */
    void removeTimer(Timer* const toDelete);

    /**
     * \brief Removes all Timers from the Timerseries.
     *
     * This method removes all the Timer objects from the Timerseries and
     * destroys them.
     *
     * \attention All contained elements are destructed. This can render
     * pointer invalid.
     */
    void clear();

    /**
     * \brief Returns the number of Timer in this Timerseries.
     */
    unsigned long getSize () const;

    /**
     * \brief Returns a copy of all Timers in this Timerseries.
     *
     * The Timerseries is independent from the returned list, since all elements
     * are copied.
     *
     * \attention This method duplicates the Timers contained.
     */
    std::list<Timer*>* getAllTimer() const;

    /**
     * \brief Get the Timestamps with the duration of all Timers.
     */
    std::list<Timestamp>* getTimes() const;

    /**
     * \brief Returns the times of all Timers in seconds.
     */
    std::list<double>* getTimesInSeconds() const;

    /**
     * \brief Returns the times of all Timers in milliseconds.
     */
    std::list<double>* getTimesInMilliSeconds() const;

    /**
     * \brief Returns the times of all Timers in microseconds.
     */
    std::list<double>* getTimesInMicroSeconds() const;

    /**
     * \brief Returns the times of all Timers in nanoseconds.
     */
    std::list<double>* getTimesInNanoSeconds() const;

    /**
     * \brief Returns the frequencies of all Timers.
     */
    std::list<double>* getFrequencies() const;

private:
    std::list<Timer*>* mTimer;

    const std::list<Timer*>& getTimer() const;
};

#endif	/* TIMERSERIES_H */
