/* === This file is part of GreyToColor ===
 *
 *	Copyright 2012-2013, Antony Cherepanov <antony.cherepanov@gmail.com>
 *
 *	GreyToColor is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	GreyToColor is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with GreyToColor. If not, see <http://www.gnu.org/licenses/>.
 */

#include "colormethodshandler.h"

ColorMethodsHandler::ColorMethodsHandler(QObject *parent) :
	QObject(parent)
{
	Clear();
}

ColorMethodsHandler::~ColorMethodsHandler()
{
	Clear();
}

// Clear all info
// @input:
// @output:
void ColorMethodsHandler::Clear()
{
	m_targetImg = NULL;
	m_sourceImg = NULL;
	m_methodToUse = Methods::WALSH_SIMPLE;
	m_lumEqualType = LumEqualization::SCALE_BY_MAX;
}

// Set type of colorization method to use
// @input:
// - Methods::Type - exist colorization method
// @output:
void ColorMethodsHandler::SlotSetMethodType(const Methods::Type &t_type)
{
	if ( Methods::DEFAULT_LAST == t_type )
	{
		qDebug() << "SlotSetMethodType(): Error - invalid arguments";
		return;
	}

	m_methodToUse = t_type;
}

// Set type of luminance equalisation to use
// @input:
// - LumEqualization::Type - exist luminance equalisation type
// @output:
void ColorMethodsHandler::SlotSetLumEqualType(const LumEqualization::Type &t_type)
{
	if ( LumEqualization::DEFAULT_LAST == t_type )
	{
		qDebug() << "SlotSetLumEqualType(): Error - invalid arguments";
		return;
	}

	m_lumEqualType = t_type;
}

// Start Colorization
// @input:
// @output:
void ColorMethodsHandler::SlotStartColorization()
{
	if ( (NULL == m_targetImg) ||
		 (NULL == m_sourceImg) ||
		 (false == m_targetImg->HasImage()) ||
		 (false == m_sourceImg->HasImage()) )
	{
		qDebug() << "SlotStartColorization(): Error - images not set yet";
		emit SignalProcError(tr("Can't start colorization. Please, set Target and Source images"));
		return;
	}

	switch( m_methodToUse )
	{
		case Methods::WALSH_SIMPLE:
			ColorizeByWalshSimple();
			break;

		case Methods::WALSH_NEIGHBOR:
			ColorizeByWalshNeighbor();
			break;

		case Methods::WALSH_NEIGHBOR_NORAND:
			ColorizeByWNNoRand();
			break;

		case Methods::WALSH_NEIGHBOR_ONERAND:
			ColorizeByWNOneRand();
			break;

		case Methods::DEFAULT_LAST:
		default:
		{
			qDebug() << "SlotStartColorization(): Error - invalid colorization method type";
			return;
		}
	}
}

// Get pointer to current target image
// @input:
// - TargetImage - unnull unempty pointer to loaded Target Image
// @output:
void ColorMethodsHandler::SlotGetTargetImg(TargetImage *t_targ)
{
	if ( (NULL == t_targ) || (false == t_targ->HasImage()) )
	{
		qDebug() << "SlotGetTargetImg(): Error - invalid arguments";
		return;
	}

	m_targetImg = t_targ;
}

// Get pointer to current source image
// @input:
// - SourceImage - unnull unempty pointer to loaded Source Image
// @output:
void ColorMethodsHandler::SlotGetSourceImg(SourceImage *t_source)
{
	if ( (NULL == t_source) || (false == t_source->HasImage()) )
	{
		qDebug() << "SlotGetSourceImg(): Error - invalid arguments";
		return;
	}

	m_sourceImg = t_source;
}

// Start colorization method Walsh Simple
// @input:
// @output:
void ColorMethodsHandler::ColorizeByWalshSimple()
{
	emit SignalCurrentProc(Program::COLORIZATION);

	WalshSimpleColorizator colorizator;
	bool targetColorized = colorizator.Colorize(m_targetImg,
												m_sourceImg,
												m_lumEqualType);

	if ( false == targetColorized )
	{
		qDebug() << "ColorizeByWalshSimple(): Error - can't colorize by Waslh Simple Method";
		emit SignalProcError(tr("Colorization failed"));
		return;
	}

	emit SignalColorizationDone();
	emit SignalProcDone();
}

// Start colorization method Walsh Neighbor
// @input:
// @output:
void ColorMethodsHandler::ColorizeByWalshNeighbor()
{
	emit SignalCurrentProc(Program::COLORIZATION);

	WalshNeighborColorizator colorizator;
	bool targetColorized = colorizator.Colorize(m_targetImg,
												m_sourceImg,
												m_lumEqualType);

	if ( false == targetColorized )
	{
		qDebug() << "ColorizeByWalshNeighbor(): Error - can't colorize by Waslh Neighbor Method";
		emit SignalProcError(tr("Colorization failed"));
		return;
	}

	emit SignalColorizationDone();
	emit SignalProcDone();
}

// Start colorization method Walsh Neighbor No Rand
// @input:
// @output:
void ColorMethodsHandler::ColorizeByWNNoRand()
{
	emit SignalCurrentProc(Program::COLORIZATION);

	WNNoRandColorizator colorizator;
	bool targetColorized = colorizator.Colorize(m_targetImg,
												m_sourceImg,
												m_lumEqualType);

	if ( false == targetColorized )
	{
		qDebug() << "ColorizeByWNNoRand(): Error - can't colorize by Waslh Neighbor Method";
		emit SignalProcError(tr("Colorization failed"));
		return;
	}

	emit SignalColorizationDone();
	emit SignalProcDone();
}

// Start colorization method Walsh Neighbor One Rand
// @input:
// @output:
void ColorMethodsHandler::ColorizeByWNOneRand()
{
	emit SignalCurrentProc(Program::COLORIZATION);

	WNOneRandColorizator colorizator;
	bool targetColorized = colorizator.Colorize(m_targetImg,
												m_sourceImg,
												m_lumEqualType);

	if ( false == targetColorized )
	{
		qDebug() << "ColorizeByWNOneRand(): Error - can't colorize by Waslh Neighbor Method";
		emit SignalProcError(tr("Colorization failed"));
		return;
	}

	emit SignalColorizationDone();
	emit SignalProcDone();
}
