/* =========================================================================
 * This file is part of types-c++
 * =========================================================================
 *
 * (C) Copyright 2004 - 2014, MDA Information Systems LLC
 *
 * types-c++ is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this program; If not,
 * see <http://www.gnu.org/licenses/>.
 *
 */
 
#ifndef __TYPES_RG_AZ_H__
#define __TYPES_RG_AZ_H__

#include <limits>
#include <cmath>
#include <utility>

namespace types
{

/*!
 *  RgAz type is also roughly the same as RowCol,
 *  and can be used when the spacing is not
 *  in pixels, but in range azimuth coordinates.
 *
 *  Conversion between RowCol and RgAz is not provided
 *  here since, there is no guarantee that the Row direction
 *  of an image is oriented in Range.  However, for the
 *  sensor independent XML formats, this will pretty much
 *  always be the case.
 */
template<typename T> struct RgAz
{
    T rg;
    T az;

    RgAz() {}

    RgAz(T r, T c) :
        rg(r), az(c) {}

    template<typename Other_T> RgAz(const RgAz<Other_T>& p)
    {
        rg = (T)p.rg;
        az = (T)p.az;
    }

    RgAz(const std::pair<T, T>& p)
    {
        rg = p.first;
        az = p.second;
    }

    template<typename Other_T> RgAz& operator=(const RgAz<Other_T>& p)
    {
        if (this != (RgAz*)&p)
        {
            rg = (T)p.rg;
            az = (T)p.az;
        }
        return *this;
    }

    RgAz& operator=(const std::pair<T, T>& p)
    {
        rg = p.first;
        az = p.second;
        return *this;
    }

    
    template<typename Other_T> RgAz& operator+=(const RgAz<Other_T>& p)
    {
        rg += (T)p.rg;
        az += (T)p.az;
        return *this;
    }

    template<typename Other_T> RgAz operator+(const RgAz<Other_T>& p) const
    {
        RgAz copy(*this);
        return copy += p;
    }

    template<typename Other_T> RgAz& operator*=(const RgAz<Other_T>& p)
    {
        rg *= (T)p.rg;
        az *= (T)p.az;
        return *this;
    }

    template<typename Other_T> RgAz operator*(const RgAz<Other_T>& p) const
    {
        RgAz copy(*this);
        return copy *= p;
    }
    
    
    template<typename Other_T> RgAz& operator-=(const RgAz<Other_T>& p)
    {
        rg -= (T)p.rg;
        az -= (T)p.az;
        return *this;
    }
    
    template<typename Other_T> RgAz operator-(const RgAz<Other_T>& p) const
    {
        RgAz copy(*this);
        return copy -= p;
    }

    template<typename Other_T> RgAz& operator/=(const RgAz<Other_T>& p)
    {
        rg /= (T)p.rg;
        az /= (T)p.az;
        return *this;
    }
    
    template<typename Other_T> RgAz operator/(const RgAz<Other_T>& p) const
    {
        RgAz copy(*this);
        return copy /= p;
    }


    RgAz& operator+=(T scalar)
    {
        rg += scalar;
        az += scalar;
        return *this;
    }

    RgAz operator+(T scalar) const
    {
        RgAz copy(*this);
        return copy += scalar;
    }
    
    RgAz& operator-=(T scalar)
    {
        rg -= scalar;
        az -= scalar;
        return *this;
    }

    RgAz operator-(T scalar) const
    {
        RgAz copy(*this);
        return copy -= scalar;
    }

    RgAz& operator*=(T scalar)
    {
        rg *= scalar;
        az *= scalar;
        return *this;
    }

    RgAz operator*(T scalar) const
    {
        RgAz copy(*this);
        return copy *= scalar;
    }
    
    RgAz& operator/=(T scalar)
    {
        rg /= scalar;
        az /= scalar;
        return *this;
    }

    RgAz operator/(T scalar) const
    {
        RgAz copy(*this);
        return copy /= scalar;
    }

    /*!
     *  Compare the types considering that some
     *  specializations (e.g., double)
     *  are not exact
     */
    bool operator==(const RgAz<T>& p) const
    {
        return rg == p.rg && az == p.az;
    }


    bool operator!=(const RgAz<T>& p) const
    {
        return ! (RgAz::operator==(p));
    }
};

template <>
inline bool RgAz<float>::operator==(const RgAz<float>& p) const
{
    float eps = std::numeric_limits<float>::epsilon();
    return std::abs(rg - p.rg) < eps &&
           std::abs(az - p.az) < eps;
}
template <>
inline bool RgAz<double>::operator==(const RgAz<double>& p) const
{
    double eps = std::numeric_limits<double>::epsilon();
    return std::abs(rg - p.rg) < eps &&
           std::abs(az - p.az) < eps;
}

} 
#endif
