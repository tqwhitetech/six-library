/* =========================================================================
 * This file is part of six.sidd-c++
 * =========================================================================
 *
 * (C) Copyright 2004 - 2015, MDA Information Systems LLC
 *
 * six.sidd-c++ is free software; you can redistribute it and/or modify
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

#ifndef __SIX_SIDD_DERIVED_Elem_PARSER_100_H__
#define __SIX_SIDD_DERIVED_Elem_PARSER_100_H__

#include <six/sidd/DerivedXMLParser.h>

namespace six
{
namespace sidd
{
class DerivedXMLParser100 : public DerivedXMLParser
{
public:
    DerivedXMLParser100(logging::Logger* log = NULL,
                        bool ownLog = false);

    virtual xml::lite::Document* toXML(const DerivedData* data) const;

    virtual DerivedData* fromXML(const xml::lite::Document* doc) const;

protected:
    virtual void parseDerivedClassificationFromXML(
            const XMLElem classificationElem,
            DerivedClassification& classification) const;

    virtual XMLElem convertDerivedClassificationToXML(
            const DerivedClassification& classification,
            XMLElem parent = NULL) const;

    virtual XMLElem convertMeasurementToXML(
            const Measurement* measurement,
            XMLElem parent = NULL) const;

    virtual void parseMeasurementFromXML(
            const XMLElem measruementElem,
            Measurement* measurement) const;

    virtual XMLElem convertExploitationFeaturesToXML(
        const ExploitationFeatures* exploitationFeatures,
        XMLElem parent = NULL) const;

    virtual void parseProductFromXML(
        const XMLElem exploitationFeaturesElem,
        ExploitationFeatures* exploitationFeatures) const;

    virtual XMLElem convertDisplayToXML(const Display& display,
                                        XMLElem parent = NULL) const;

private:
    static const char VERSION[];
    static const char SI_COMMON_URI[];
    static const char ISM_URI[];

    XMLElem convertGeographicTargetToXML(const GeographicAndTarget& g,
                                         XMLElem parent = NULL) const;

    void parseGeographicTargetFromXML(
            const XMLElem elem,
            GeographicAndTarget* geographicAndTarget) const;

    void parseGeographicCoverageFromXML(
            const XMLElem elem,
            GeographicCoverage* geoCoverage) const;
};
}
}

#endif
