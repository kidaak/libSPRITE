#ifndef __UNITS_GPS_TIME_H__
#define __UNITS_GPS_TIME_H__

#include "units/Seconds.h"

namespace units
{

    /**
     * Forward declataration of class.
     */
    class Days;
    class J2010_time;

    /**
     * This class embodies the concept of GPS time as a unit of measure.
     */
    class GPS_time
    {
        public:

            /**
             * Default constructor.
             */
            GPS_time() :
                m_week(1),
                m_seconds(0)
        {
        }


            /**
             * Constructor.
             * @param week Number weeks elapsed since the GPS epoch.
             * @param seconds Number seconds elapsed since the begining of the
             * current GPS week.
             */
            GPS_time(const unsigned int week, const Seconds& seconds) :
                m_week(week),
                m_seconds(seconds)
        {
        }


            /**
             * Constructor
             * @param t Time in J2010 format.
             */
            explicit GPS_time(const J2010_time& t);



            /**
             * Accessor method to retrieve the week number.
             * Returns the GPS week number.
             */
            int week() const
            {
                return m_week;
            }


            /**
             * Accessor method to retrieve the number of GPS seconds since the
             * beginning of the current week.
             * @return GPS seconds.
             */
            Seconds seconds() const
            {
                return m_seconds;
            }


            /**
             * Type conversion from GPS time to days.
             * @return GPS time converted to days.
             */
            Days toDays() const;


            /**
             * Type conversion from GPS epoch time to J2010 epoch days.
             * @return GPS time converted to the J2010 epoch and format.
             */
            J2010_time toJ2010_time() const;

            /**
             * Overload operator+=
             * @param rhs Right hand side of the operation.
             * @return This instance with the right hand side value added.
             */
            GPS_time& operator+=(const Seconds& rhs)
            {
                m_seconds += rhs;

                while(m_seconds > SECONDS_PER_WEEK)
                {
                    ++m_week;
                    m_seconds -= SECONDS_PER_WEEK;
                }

                return *this;
            }

            /**
             * Overload operator-
             * @param rhs Right hand side of the operation.
             * @return The subtracted value.
             */
            GPS_time operator-(const GPS_time& rhs) const
            {
                GPS_time t(m_week - rhs.m_week, m_seconds - rhs.m_seconds);
                if(t.m_seconds < 0)
                {
                    --t.m_week;
                    t.m_seconds += SECONDS_PER_WEEK;
                }

                return t;
            }

        private:

            /**
             * Number of weeks since the GPS epoch.
             */
            int m_week;

            /**
             * Number of seconds since the beginning of the current GPS week.
             */
            Seconds m_seconds;
    };

} // namespace

#endif // __UNITS_GPS_TIME_H__
