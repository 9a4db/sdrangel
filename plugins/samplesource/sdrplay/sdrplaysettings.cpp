///////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2015 Edouard Griffiths, F4EXB                                   //
//                                                                               //
// This program is free software; you can redistribute it and/or modify          //
// it under the terms of the GNU General Public License as published by          //
// the Free Software Foundation as version 3 of the License, or                  //
//                                                                               //
// This program is distributed in the hope that it will be useful,               //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// GNU General Public License V3 for more details.                               //
//                                                                               //
// You should have received a copy of the GNU General Public License             //
// along with this program. If not, see <http://www.gnu.org/licenses/>.          //
///////////////////////////////////////////////////////////////////////////////////

#include "sdrplaysettings.h"

#include <QtGlobal>
#include "util/simpleserializer.h"

SDRPlaySettings::SDRPlaySettings()
{
	resetToDefaults();
}

void SDRPlaySettings::resetToDefaults()
{
	m_centerFrequency = 7040*1000;
    m_LOppmTenths = 0;
    m_frequencyBandIndex = 0;
    m_ifFrequencyIndex = 0;
    m_mirDcCorrIndex = 0;
    m_mirDcCorrTrackTimeIndex = 1;
    m_bandwidthIndex = 0;
	m_devSampleRateIndex = 0;
	m_gainRedctionIndex = 35;
    m_log2Decim = 0;
    m_fcPos = FC_POS_CENTER;
    m_dcBlock = false;
    m_iqCorrection = false;
}

QByteArray SDRPlaySettings::serialize() const
{
	SimpleSerializer s(1);

	s.writeS32(1, m_LOppmTenths);
    s.writeU32(2, m_frequencyBandIndex);
    s.writeU32(3, m_ifFrequencyIndex);
    s.writeU32(4, m_mirDcCorrIndex);
    s.writeU32(5, m_mirDcCorrTrackTimeIndex);
    s.writeU32(6, m_bandwidthIndex);
	s.writeU32(7, m_devSampleRateIndex);
    s.writeU32(8, m_gainRedctionIndex);
	s.writeU32(9, m_log2Decim);
	s.writeS32(10, (int) m_fcPos);
	s.writeBool(11, m_dcBlock);
	s.writeBool(12, m_iqCorrection);

	return s.final();
}

bool SDRPlaySettings::deserialize(const QByteArray& data)
{
	SimpleDeserializer d(data);

	if (!d.isValid())
	{
		resetToDefaults();
		return false;
	}

	if (d.getVersion() == 1)
	{
		int intval;

		d.readS32(1, &m_LOppmTenths, 0);
        d.readU32(2, &m_frequencyBandIndex, 0);
        d.readU32(3, &m_ifFrequencyIndex, 0);
        d.readU32(4, &m_mirDcCorrIndex, 0);
        d.readU32(5, &m_mirDcCorrTrackTimeIndex, 1);
        d.readU32(6, &m_bandwidthIndex, 0);
        d.readU32(7, &m_devSampleRateIndex, 0);
        d.readU32(8, &m_gainRedctionIndex, 35);
		d.readU32(9, &m_log2Decim, 0);
		d.readS32(10, &intval, 0);
		m_fcPos = (fcPos_t) intval;
		d.readBool(11, &m_dcBlock, false);
		d.readBool(12, &m_iqCorrection, false);

		return true;
	}
	else
	{
		resetToDefaults();
		return false;
	}
}