/*
    Ross Bencina's Granular Synthesis Toolkit (RB-GST)
    Copyright (C) 2001 Ross Bencina.
    email: rossb@audiomulch.com
    web: http://www.audiomulch.com/~rossb/

    This file is part of RB-GST.

    RB-GST is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    RB-GST is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with RB-GST; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef INCLUDED_PERIODICSEQUENCESTRATEGY_H
#define INCLUDED_PERIODICSEQUENCESTRATEGY_H

#include <ctype.h>

/*
    PeriodicSequenceStrategy models SequenceStrategy (see Scheduler.h)

    PeriodicSequenceStrategy issues grains at a rate specified by the
    frequency parameter to frequencyOverlap(). the maximum number of overlapping
    grains at any instant is determined by the overlap parameter
*/

class PeriodicSequenceStrategy{
public:
    PeriodicSequenceStrategy()
        : interonset_( 441. )
        , duration_( 441. ) {} // initialise with sane initial values

    PeriodicSequenceStrategy& frequencyOverlap( double frequency, double overlap, double sr ) {
        interonset_ = sr / frequency;
        duration_ = interonset_ * overlap;
        return *this;
    }

    double nextInteronset() { return interonset_; }
    size_t nextDuration() { return duration_; }
    
private:
    double interonset_;
    size_t duration_;
};

#endif /* INCLUDED_PERIODICSEQUENCESTRATEGY_H */
