// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013-2014.
// Modifications copyright (c) 2013-2014, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_POINT_GEOMETRY_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_POINT_GEOMETRY_HPP

#include <boost/geometry/geometries/segment.hpp>

#include <boost/geometry/algorithms/covered_by.hpp>

#include <boost/geometry/algorithms/detail/disjoint/linear_linear.hpp>

#include <boost/geometry/algorithms/dispatch/disjoint.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace disjoint
{


template<typename Point, typename Geometry>
struct disjoint_point_linear
{
    static inline
    bool apply(Point const& pt, Geometry const& g)
    {
        return !geometry::covered_by(pt, g);
    }
};


template <typename Geometry1, typename Geometry2>
struct reverse_covered_by
{
    static inline
    bool apply(Geometry1 const& geometry1, Geometry2 const& geometry2)
    {
        return !geometry::covered_by(geometry1, geometry2);
    }
};


}} // namespace detail::disjoint
#endif // DOXYGEN_NO_DETAIL




#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template<typename Point, typename Linear, std::size_t DimensionCount>
struct disjoint<Point, Linear, DimensionCount, point_tag, linear_tag, false>
    : public detail::disjoint::disjoint_point_linear<Point, Linear>
{};


template <typename Point, typename Areal, std::size_t DimensionCount>
struct disjoint<Point, Areal, DimensionCount, point_tag, areal_tag, false>
    : detail::disjoint::reverse_covered_by<Point, Areal>
{};


template<typename Point, typename Segment, std::size_t DimensionCount>
struct disjoint<Point, Segment, DimensionCount, point_tag, segment_tag, false>
{
    static inline bool apply(Point const& point, Segment const& segment)
    {
        typedef geometry::model::referring_segment<Point const> other_segment;

        other_segment other(point, point);
        return detail::disjoint::disjoint_segment
            <
                Segment, other_segment
            >::apply(segment, other);
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry



#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_DISJOINT_POINT_GEOMETRY_HPP
