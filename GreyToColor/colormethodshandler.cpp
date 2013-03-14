/* === This file is part of GreyToColor ===
 *
 *	Copyright 2012, Antony Cherepanov <antony.cherepanov@gmail.com>
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
}

// Set type of colorization method to use
// @input:
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
			// start walsh simple
			break;

		case Methods::WALSH_NEIGHBOR:
			// start walsh neighbor
			break;

		case Methods::DEFAULT_LAST:
		default:
		{
			qDebug() << "SlotStartColorization(): Error - invalid colorization method type";
			return;
		}
	}
}
