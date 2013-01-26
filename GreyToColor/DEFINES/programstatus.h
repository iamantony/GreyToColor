#ifndef PROGRAMSTATUS_H
#define PROGRAMSTATUS_H

namespace Program
{
	enum Status
	{
		OK = 0,
		COLORIZATION,
		SEARCHING_IMAGE_IN_DB,
		DB_FORMING,
		ERROR,
		DEFAULT_LAST
	};
}

#endif // PROGRAMSTATUS_H
