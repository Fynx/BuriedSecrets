/* YoLoDevelopment, 2014
 * All rights reserved.
 */
#include "GameObjects/JournalEntry.hpp"

JournalEntry::JournalEntry(const Prototype *prototype)
	: Object(prototype)
{}

QString JournalEntry::getText() const
{
	return prototype->getProperty("text").toString();
}
