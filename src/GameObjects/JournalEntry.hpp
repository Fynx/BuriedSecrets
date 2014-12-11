/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#pragma once

#include "GameObjects/Object.hpp"

class JournalEntry : public Object {
public:
	JournalEntry(const Prototype *prototype);

	QString getText() const;
};